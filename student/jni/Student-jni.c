#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <jni.h>
#include <assert.h>
#include <android/log.h>

# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))

#define JNIMAIN_CLASS "com/example/student/MainActivity"
#define JNISTUDENT_CLASS "com/example/student/Student"
#define JNIEXCEPTION_CLASS "com/example/student/exception/ExceptionNDK"


#define  TAG    "Student-jni"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)


struct StudentOffsets
{
    jfieldID    name;
    jfieldID    age;
    jfieldID    height;
} gStudentOffsets;


typedef struct tagStudent
{
    char    mName[10];
    int     mAge;
    float   mHeight;
}Student;



static Student gStudent[] = {
    {"skywang", 25, 175},
    {"eman"   , 30, 166},
    {"Dan"    , 51, 172},
};

#define GSTUDENT_NUM NELEM(gStudent)

JNIEXPORT jint JNICALL Native_getStudentInfoByIndex(JNIEnv *env, jobject thiz, jobject student, jint index)
{


    if ((int)index<0 || (int)index>=GSTUDENT_NUM)
        return -1;


    Student *pStudent = &gStudent[index];

    jstring name = (*env)->NewStringUTF(env, pStudent->mName);
    (*env)->SetObjectField(env, student, gStudentOffsets.name, name);
    (*env)->SetIntField(env, student, gStudentOffsets.age, pStudent->mAge);
    (*env)->SetFloatField(env, student, gStudentOffsets.height, pStudent->mHeight);

    LOGD("%s index:%d  mName:%s, mAge:%d, mHeight:%f\n",
            __func__, index, pStudent->mName, pStudent->mAge, pStudent->mHeight);

    return 0;
}

static void nativeClassInit (JNIEnv *env)
{
    jclass studentClass = (*env)->FindClass(env, JNISTUDENT_CLASS);
    gStudentOffsets.name     = (*env)->GetFieldID(env, studentClass, "mName"  , "Ljava/lang/String;");
    gStudentOffsets.age      = (*env)->GetFieldID(env, studentClass, "mAge"   , "I");
    gStudentOffsets.height   = (*env)->GetFieldID(env, studentClass, "mHeight", "F");
}



JNIEXPORT jstring JNICALL Native_stringFromJni(JNIEnv *env, jobject thiz)
{
    jstring str = (*env)->NewStringUTF(env, "Hello From Jni");
    return str;
}

JNIEXPORT void JNICALL Native_stringToJni(JNIEnv *env, jobject thiz, jstring val)
{
    char *str = (char *)(*env)->GetStringUTFChars(env, val, JNI_FALSE);
    LOGD("%s str=%s\n", __func__, str);
}

JNIEXPORT jfloat JNICALL Native_floatFromJni(JNIEnv *env, jobject clazz)
{
    return (jfloat)1.34;
}

JNIEXPORT void JNICALL Native_floatToJni(JNIEnv *env, jobject thiz, jfloat val)
{
    float f = (float)val;
    LOGD("%s f=%f\n", __func__, f);
}

JNIEXPORT jint JNICALL Native_intFromJni(JNIEnv *env, jobject thiz)
{
    return (jint)25;
}


JNIEXPORT void JNICALL Native_intToJni(JNIEnv *env, jobject thiz, jint val)
{
    int i = (int)val;
    LOGD("%s i=%d\n", __func__, i);
}

JNIEXPORT jstring JNICALL native_hello(JNIEnv *env, jclass thiz)
{
	 LOGI("%s info\n", __func__);
    return (*env)->NewStringUTF(env, "hello All");
}




static JNINativeMethod method_table_main[] = {
    { "stringFromJNIDynamic", "()Ljava/lang/String;", (void*)native_hello },
    { "intFromJni", "()I", (void*)Native_intFromJni},
    { "intToJni", "(I)V", (void*)Native_intToJni},
    { "floatFromJni", "()F", (void*)Native_floatFromJni},
    { "floatToJni", "(F)V", (void*)Native_floatToJni},
    { "stringFromJni", "()Ljava/lang/String;", (void*)Native_stringFromJni},
    { "stringToJni", "(Ljava/lang/String;)V", (void*)Native_stringToJni},
    { "getStudentInfoByIndex", "(Lcom/example/student/Student;I)I", (void*)Native_getStudentInfoByIndex},
};



JNIEXPORT void JNICALL Native_sayHello(JNIEnv *env, jobject thiz){
    jclass student_clazz = (*env)->GetObjectClass(env,thiz);
    LOGI("%s info\n", __func__);
    jfieldID fieldID_name = (*env)->GetFieldID(env,student_clazz,"mName","Ljava/lang/String;");
    jfieldID fieldID_age = (*env)->GetFieldID(env,student_clazz,"mAge","I");
    jfieldID fieldID_height = (*env)->GetFieldID(env,student_clazz,"mHeight","F");
    jfieldID fieldID_count = (*env)->GetStaticFieldID(env,student_clazz,"count","I");


    jmethodID getInfoPublic_func=(*env)->GetMethodID(env,student_clazz,"getInfoPublic","()Ljava/lang/String;");
    jmethodID getInfoPrivate_func=(*env)->GetMethodID(env,student_clazz,"getInfoPrivate","()Ljava/lang/String;");
    jmethodID getInfoStatic_func=(*env)->GetStaticMethodID(env,student_clazz,"getInfoStatic","(I)Ljava/lang/String;");



    jobject result1 = (*env)->CallObjectMethod(env,thiz,getInfoPublic_func);
    char *str1 = (char *)(*env)->GetStringUTFChars(env, (jstring)result1, JNI_FALSE);
    LOGD("Call java public Method result:%s\n",str1);

    jobject result2 = (*env)->CallObjectMethod(env,thiz,getInfoPrivate_func);
    char *str2 = (char *)(*env)->GetStringUTFChars(env, (jstring)result2, JNI_FALSE);
    LOGD("Call java private Method result:%s\n",str2  );


    jint count = (*env)->GetStaticIntField(env,student_clazz,fieldID_count);
    count++;
    LOGD("The count is:%d\n",(int)count);

    jobject result3 = (*env)->CallStaticObjectMethod(env,student_clazz,getInfoStatic_func,count);
    char *str3 = (char *)(*env)->GetStringUTFChars(env, (jstring)result3, JNI_FALSE);
    LOGD("Call java static method  result:%s\n",str3);

    jobject name = (*env)->GetObjectField(env,thiz,fieldID_name);

    char *str = (char *)(*env)->GetStringUTFChars(env, (jstring)name, JNI_FALSE);
    LOGD("name:%s\n",str);

    jint age= (*env)->GetIntField(env,thiz,fieldID_age);

    jfloat height= (*env)->GetFloatField(env,thiz,fieldID_height);
    LOGD("Before modify:age=%d\n", (int)age);

   (*env)->SetIntField(env,thiz,fieldID_age,50);
    age= (*env)->GetIntField(env,thiz,fieldID_age);
    LOGD("After modify , The age changed:age=%d\n", (int)age);
 }


static JNINativeMethod method_table_student[] = {
   {"sayHello", "()V", (void*)Native_sayHello},
};








JNIEXPORT jstring JNICALL Native_showException  (JNIEnv *env, jobject thiz, jint index){
	jclass exceptionNDK_clazz = (*env)->GetObjectClass(env,thiz);
	jmethodID jni_call_back_id=(*env)->GetMethodID(env,exceptionNDK_clazz,"jni_call_back","(I)V");

	 LOGD("In  Native_showException, the index is %d\n", (int)index);

	(*env)->CallVoidMethod(env,thiz,jni_call_back_id,index);

	if((*env)->ExceptionCheck(env))  {
		//jclass exception_clazz;
		(*env)->ExceptionDescribe(env);
		(*env)->ExceptionClear(env);
	/*	exception_clazz = (*env)->FindClass(env,"java/IllegalArgumentException");
		if(exception_clazz==NULL){
			 LOGE("In %s IllegalArgumentException not found !\n", __func__);
			 return   (*env)->NewStringUTF(env, "catch exception");
		}
		(*env)->ThrowNew(env,exception_clazz,"thrown for C code!");*/

		return (*env)->NewStringUTF(env, "catch exception !\n");
	}else{
		return (*env)->NewStringUTF(env, "not catch exception!\n");
	}
}


JNIEXPORT void JNICALL Native_doit(JNIEnv *env, jobject thiz){
	jthrowable exc;
	jclass clazz=(*env)->GetObjectClass(env,thiz);
	jmethodID callback_id= (*env)->GetMethodID(env,clazz,"callback","()V");
	if(callback_id==NULL){
		 LOGD("In %s,  callback_id is null!\n", __func__);
		 return;
	}
	if(exc){
		jclass exception_clazz;
		(*env)->ExceptionDescribe(env);
		(*env)->ExceptionClear(env);
		exception_clazz = (*env)->FindClass(env,"java/lang/IllegalArgumentException");
		if(exception_clazz==NULL){
			 LOGD("In %s,  IllegalArgumentException is not found!\n", __func__);
				 return;
		}else{
			(*env)->ThrowNew(env,exception_clazz,"throw the IllegalArgumentException in C-Code ");
		}
	}else{
		 LOGD("In %s,  callback throw is not happenedl!\n", __func__);
	     return;
	}

}


JNIEXPORT jstring JNICALL Native_test(JNIEnv *env, jobject thiz){
	//return (*env)->NewStringUTF(env, "not catch exception!\n");
	return (*env)->NewStringUTF(env, "wifi resut test !\n");
}

JNIEXPORT jobjectArray JNICALL Native_testArray (JNIEnv *env, jobject thiz){
		jobjectArray ret;
	    int i;

	    char *message[5]= {"first",
		"second",
		"third",
		"fourth",
		"fifth"};

	    ret= (jobjectArray)(*env)->NewObjectArray(env,5,
	         (*env)->FindClass(env,"java/lang/String"),
	         (*env)->NewStringUTF(env,""));

	    for(i=0;i<5;i++) {
	        (*env)->SetObjectArrayElement(env,
			ret,i,(*env)->NewStringUTF(env,message[i]));
	    }
	    return(ret);
}

JNIEXPORT jobject JNICALL Native_testObject (JNIEnv *env, jobject thiz)
{
	jclass m_cls  = (*env)->FindClass(env,"com/example/student/exception/ScanResult");
	jmethodID mid = (*env)->GetMethodID(env,m_cls,"<init>","()V");
	jobject obj   = (*env)->NewObject(env,m_cls,mid);

	jfieldID fid_ssid  = (*env)->GetFieldID(env,m_cls,"ssid","Ljava/lang/String;");
	jfieldID fid_mac   = (*env)->GetFieldID(env,m_cls,"mac","Ljava/lang/String;");
	jfieldID fid_level = (*env)->GetFieldID(env,m_cls,"level","I");

	(*env)->SetObjectField(env,obj,fid_ssid,(*env)->NewStringUTF(env,"AP1"));
	(*env)->SetObjectField(env,obj,fid_mac,(*env)->NewStringUTF(env,"00-11-22-33-44-55"));
	(*env)->SetIntField(env,obj,fid_level,-66);
	return obj;
}

JNIEXPORT jobjectArray JNICALL Native_getScanResultsA (JNIEnv *env, jobject thiz)
{
    int i;
	jclass cls_array=(*env)->FindClass(env,"java/lang/Object");
	jobjectArray obj_array=(*env)->NewObjectArray(env,2,cls_array,0);

	jclass cls_obj = (*env)->FindClass(env,"com/example/student/exception/ScanResult");
	jmethodID m    = (*env)->GetMethodID(env,cls_obj,"<init>","()V");

	jfieldID fid_ssid  = (*env)->GetFieldID(env,cls_obj,"ssid","Ljava/lang/String;");
	jfieldID fid_mac   = (*env)->GetFieldID(env,cls_obj,"mac","Ljava/lang/String;");
	jfieldID fid_level = (*env)->GetFieldID(env,cls_obj,"level","I");

	for(i=0;i<2;i++)
	{
		jobject obj=(*env)->NewObject(env,cls_obj,m);

		jobject o1=(*env)->NewStringUTF(env,"AP2");
		(*env)->SetObjectField(env,obj,fid_ssid,o1);

		jobject o2=(*env)->NewStringUTF(env,"22-22-22-22-22-22");
		(*env)->SetObjectField(env,obj,fid_mac,o2);

		(*env)->SetIntField(env,obj,fid_level,-66);

		(*env)->SetObjectArrayElement(env,obj_array,i,obj);
	}
	return obj_array;
}


JNIEXPORT jobject JNICALL Native_getScanResults (JNIEnv *env,  jobject thiz){

	jclass m_cls_list    = (*env)->FindClass(env,"java/util/ArrayList");
	jmethodID m_mid_list = (*env)->GetMethodID(env,m_cls_list,"<init>","()V");
	jobject m_obj_list   = (*env)->NewObject(env,m_cls_list,m_mid_list);

	jmethodID m_mid_add  = (*env)->GetMethodID(env,m_cls_list,"add","(Ljava/lang/Object;)Z");

	jclass m_cls_result    = (*env)->FindClass(env,"com/example/student/exception/ScanResult");
	jmethodID m_mid_result = (*env)->GetMethodID(env,m_cls_result,"<init>","()V");
	jobject m_obj_result   = (*env)->NewObject(env,m_cls_result,m_mid_result);

	jfieldID m_fid_1 = (*env)->GetFieldID(env,m_cls_result,"ssid","Ljava/lang/String;");
	jfieldID m_fid_2 = (*env)->GetFieldID(env,m_cls_result,"mac","Ljava/lang/String;");
	jfieldID m_fid_3 = (*env)->GetFieldID(env,m_cls_result,"level","I");

	(*env)->SetObjectField(env,m_obj_result,m_fid_1,(*env)->NewStringUTF(env,"AP6"));
	(*env)->SetObjectField(env,m_obj_result,m_fid_2,(*env)->NewStringUTF(env,"66-66-66-66-66-66"));
	(*env)->SetIntField(env,m_obj_result,m_fid_3,-66);

	(*env)->CallBooleanMethod(env,m_obj_list,m_mid_add,m_obj_result);

	return m_obj_list;
}


static JNINativeMethod method_table_exception[] = {
   {"showException", "(I)Ljava/lang/String;", (void*)Native_showException},
   {"doit", "()V", (void*)Native_doit},
   {"test", "()Ljava/lang/String;", (void*)Native_test},
   {"testArray", "()[Ljava/lang/String;", (void*)Native_testArray},
   {"testObject", "()Lcom/example/student/exception/ScanResult;", (void*)Native_testObject},
   {"getScanResultsA", "()[Lcom/example/student/exception/ScanResult;", (void*)Native_getScanResultsA},
   {"getScanResults", "()Ljava/util/List;", (void*)Native_getScanResults},
};



static int registerNativeMethods(JNIEnv* env, const char* className,
        JNINativeMethod* gMethods, int numMethods)
{
    jclass clazz;
    clazz = (*env)->FindClass(env, className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if ((*env)->RegisterNatives(env, clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

int register_ndk_load(JNIEnv *env)
{
    nativeClassInit(env);

    registerNativeMethods(env, JNISTUDENT_CLASS,
    		method_table_student, NELEM(method_table_student));

    registerNativeMethods(env, JNIEXCEPTION_CLASS,
    		method_table_exception, NELEM(method_table_exception));

    return registerNativeMethods(env, JNIMAIN_CLASS,
            method_table_main, NELEM(method_table_main));
}



JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;

    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return result;
    }

    register_ndk_load(env);


    return JNI_VERSION_1_4;
}



 /*
#include <jni.h>

JNIEXPORT void JNICALL Java_ExceptionAccess_doThrowException(JNIEnv *env, jclass cls , jint age ){
	jclass stucls ;                                                        //Student类的类
	jmethodID cmid ,setmid ,getmid ;                                   //Student类的构造器方法、set/get方法
	jobject stuobj ;                                                        //Student类的一个对象
	jthrowable exc;                                                  //JNI中的异常――本篇的重点哦！

	jint result ;                                                               //简单的返回结果

	stucls = (*env)->FindClass(env, "Student");               //得到Student类的类
	if (stucls == NULL) {             return ;        }
	cmid = (*env)->GetMethodID(env, stucls,"<init>", "()V");       //构造Student类
								//在JNI中，构造器其实就是一个名称为"<init>"的方法，返回值为void
	if (cmid == NULL) {             return ;        }
	stuobj = (*env)->NewObject(env, stucls, cmid, NULL);              //创建该Student类的实例

	setmid=(*env)->GetMethodID(env, stucls, "setAge", "(I)V");       //得到Student类的set方法
	if (setmid == NULL) {       return; }
	(*env)->CallVoidMethod(env, stuobj, setmid,age);
		   //调用Student类的set方法，输入为本地方法中的参数age哦！仔细看清楚了！
	exc = (*env)->ExceptionOccurred(env);                            //从env中得到是否发生异常
	if (exc) {                                                                     //异常发生，则……
		   jclass newExcCls;                                                 //在JNI中创建一个异常对象
		   (*env)->ExceptionDescribe(env);                                   //得到异常的描述
		   (*env)->ExceptionClear(env);                               //清除异常
		   newExcCls = (*env)->FindClass(env,"AgeOutofBoundsException");  //建立一个对于的异常
		   if (newExcCls == NULL) {return;}
		   (*env)->ThrowNew(env, newExcCls, "Thrown from C code!\n Age is out of Bound !\n");
																   //在JNI中抛出异常！异常到此结束！
	}

	getmid=(*env)->GetMethodID(env, stucls, "getAge", "()I");              //得getAge方法
	if (getmid == NULL) {       return; }
	result = (*env)->CallIntMethod(env, stuobj, getmid);                 //调用getAge方法
	printf("We are going to set the age ! age =  %d\n",result);              //在本地方法中输出结果

}
*/
