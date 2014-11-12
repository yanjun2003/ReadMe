
#include <jni.h>
#include <assert.h>
#include <pthread.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


#include <assert.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>



# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))

#define JNIMAIN_CLASS "com/example/student/MainActivity"
#define JNISTUDENT_CLASS "com/example/student/Student"
#define JNIEXCEPTION_CLASS "com/example/student/exception/ExceptionNDK"
#define JNITHREAD_CLASS "com/example/student/thread/ThreadNDK"
#define JNIGL_CLASS "com/example/student/gl_test/OpenGL"
#define JNISL_CLASS "com/example/student/gl_test/SLAudio"


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

static JavaVM *gJavaVM;
static jclass gClass;
static jobject gObject;
static int threadFlag = 1;


typedef enum {
  RETURN_VOID = 0,
  RETURN_VOID_INPUT_PARA,
  RETURN_INT,
  RETURN_INT_INPUT_PARA,
  RETURN_FLOAT,
  RETURN_FLOAT_INPUT_PARA
} func_para;

typedef enum {
	INT = 0,
	FLOAT,
	STRING,
} input_type;

typedef struct {
	int i;
	float f;
	char* s;
	input_type type;
} nvalue;

typedef struct {
    const char* funcName;
    const char* funcSignature;
    func_para funcPara;
    jmethodID funcMethod;
} func_info;

func_info functions[] = {
  // cb[0]
  {
    "callback1", "()V", RETURN_VOID,
  },
  // cb[1]
  {
    "callback2", "(IFLjava/lang/String;)I", RETURN_INT_INPUT_PARA,
  },
  // cb[2]
  {
	"callback3", "(Ljava/lang/String;)V", RETURN_VOID_INPUT_PARA,
  },
  // cb[3]
  {
  	"callback4", "(F)F", RETURN_FLOAT_INPUT_PARA,
  },
};

int callMethodWrapper(JNIEnv* env, int mid, nvalue npar[], int paraSize) {
	LOGI("callStaticMethodWrapper called for cb[%d] method %s,signature %s,"
			"switch case %d", mid, functions[mid].funcName, functions[mid].funcSignature,
			functions[mid].funcPara);


	jvalue jpara[paraSize];
	if (paraSize > 0) {
		//Handle mapping nvalue -> jvalue
		int i;
		for (i=0; i<paraSize; i++) {
			switch (npar[i].type) {
			case INT:
				jpara[i].i = npar[i].i;
			break;
			case FLOAT:
				jpara[i].f = npar[i].f;
			break;
			case STRING:
				jpara[i].l = (*env)->NewStringUTF(env, npar[i].s);
			break;
			}
		}
	}
	switch (functions[mid].funcPara) {
	  case RETURN_VOID:
		  (*env)->CallVoidMethod(env, gObject, functions[mid].funcMethod);
	  break;
	  case RETURN_INT:
		  (*env)->CallIntMethod(env, gObject, functions[mid].funcMethod);
	  break;
	  case RETURN_FLOAT:
		  (*env)->CallFloatMethod(env, gObject, functions[mid].funcMethod);
	  break;
	  case RETURN_VOID_INPUT_PARA:
		  (*env)->CallVoidMethodA(env, gObject, functions[mid].funcMethod, jpara);
	  break;
	  case RETURN_INT_INPUT_PARA:
		  (*env)->CallIntMethodA(env, gObject, functions[mid].funcMethod, jpara);
	  break;
	  case RETURN_FLOAT_INPUT_PARA:
		  (*env)->CallFloatMethodA(env, gObject, functions[mid].funcMethod, jpara);
	  break;
	}
	return 0;
}
void* randomThread(void* arg) {
	threadFlag = 1;
	JNIEnv *env;
	int isAttached = 0;
	int status = (*gJavaVM)->GetEnv(gJavaVM, (void **) &env, JNI_VERSION_1_4);
	if(status < 0) {
		LOGE("callback_handler: failed to get JNI environment, assuming native thread");
		status = (*gJavaVM)->AttachCurrentThread(gJavaVM, &env, NULL);
		if(status < 0) {
			LOGE("callback_handler: failed to attach current thread");
		}
		isAttached = 1;
	}
	int i=0;
	nvalue v1, v2, v3, npar[3];
	while (threadFlag == 1) {
		switch(i){
			case 0:
				i=1;
				callMethodWrapper(env, 0, NULL, 0);
			break;
			case 1:
				i=2;
				v1.type = INT;
				v1.i = 12;
				v2.type = FLOAT;
				v2.f = 2.3;
				v3.type = STRING;
				v3.s = "string";
				npar[0] = v1;
				npar[1] = v2;
				npar[2] = v3;
				callMethodWrapper(env, 1, npar, 3);
			break;
			case 2:
				i=3;
				v1.type = STRING;
				v1.s = "test string :)";
				npar[0] = v1;
				callMethodWrapper(env, 2, npar, 1);
			break;
			case 3:
				i=0;
				v1.type = FLOAT;
				v1.f = 2.3;
				npar[0] = v1;
				callMethodWrapper(env, 3, npar, 1);
			break;
		}
		sleep(2);
	}

	if(isAttached)
		(*gJavaVM)->DetachCurrentThread(gJavaVM);

    return ((void*)0);
}


void threadStart() {
	LOGI("In %s threadStart called!", __func__);
	pthread_t thread;
	char *message = "Thread 1 started!";

	//iret =
	pthread_create( &thread, NULL, randomThread, NULL);
}

void threadStop() {
	LOGI("In %s daemonStop called!", __func__);
	threadFlag = 0;
}


JNIEXPORT void JNICALL Native_startThread(JNIEnv *env, jobject thiz){
		threadStart();
}

JNIEXPORT void JNICALL Native_stopThread(JNIEnv *env, jobject thiz){
	threadStop();
}

JNIEXPORT void JNICALL  Native_initThread(JNIEnv *env, jobject thiz){

	LOGI("In %s init native function called",__func__);
	int status;
	int isAttached = 0;
	gObject = (jobject)(*env)->NewGlobalRef(env, thiz);
	jclass clazz = (*env)->GetObjectClass(env, thiz);
	gClass = (jclass)(*env)->NewGlobalRef(env, clazz);
	if (!clazz) {
		LOGE("In %s callback_handler: failed to get object Class",__func__);
	}
	int num = NELEM(functions);    //sizeof functions/ sizeof functions[0];
	LOGI("getting methodIDs of %d configured callback methods", num);
	while(num--) {
		LOGI("Method %d is %s with signature %s", num, functions[num].funcName, functions[num].funcSignature);
		functions[num].funcMethod = (*env)->GetMethodID(env, clazz, functions[num].funcName, functions[num].funcSignature);
		if(!functions[num].funcMethod) {
			LOGE("callback_handler: failed to get method ID");
		}
	}

}


static JNINativeMethod method_table_thread[] = {
   {"startThread", "()V", (void*)Native_startThread},
   {"stopThread", "()V", (void*)Native_stopThread},
   {"initThread", "()V", (void*)Native_initThread},
};


static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("In %s ,GL %s = %s\n",__func__, name, v);
}

static void checkGlError(const char* op) {


}

static const char gVertexShader[] =
    "attribute vec4 vPosition;\n"
    "void main() {\n"
    "  gl_Position = vPosition;\n"
    "}\n";

static const char gFragmentShader[] =
    "precision mediump float;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
    "}\n";

GLuint loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    LOGI("In %s , The pSource is %s \n", __func__, pSource);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                            shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
    LOGI("In %s, the pVertexSource is %s", __func__, pVertexSource);
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }
    LOGI("In %s, the pFragmentSource is %s", __func__, pFragmentSource);
    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint gProgram;
GLuint gvPositionHandle;

int  setupGraphics(int w, int h) {
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d)", w, h);
    gProgram = createProgram(gVertexShader, gFragmentShader);
    if (!gProgram) {
        LOGE("Could not create program.");
        return 0;
    }
    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
            gvPositionHandle);

    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    return 1;
}

const GLfloat gTriangleVertices[] = { 0.0f, 0.6f, -0.6f, -0.6f,
        0.6f, -0.6f };

void renderFrame() {
    static float grey;
/*    grey += 0.01f;
    if (grey > 1.0f) {
        grey = 0.0f;
    }*/
    grey =0.0f;
   // LOGI("In %s", __func__);
    glClearColor(grey, grey, grey, 1.0f);
    checkGlError("glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");

    glUseProgram(gProgram);
    checkGlError("glUseProgram");

    glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(gvPositionHandle);
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLES, 0, 3);
    checkGlError("glDrawArrays");
}

JNIEXPORT void JNICALL Native_Renderer_init(JNIEnv *env, jobject thiz,jint width,jint height){
	    LOGI("In %s, and the parameter of width is %d, the height is %d!\n",__func__,width,height);
	    setupGraphics(width, height);
}


JNIEXPORT void JNICALL Native_Renderer_step(JNIEnv *env, jobject thiz){
	  renderFrame();
}

static JNINativeMethod method_table_GL[] = {
   {"Renderer_init", "(II)V", (void*)Native_Renderer_init},
   {"Renderer_step", "()V", (void*)Native_Renderer_step},
};





static SLObjectItf engineObject = NULL;
static SLEngineItf engineEngine;

// output mix interfaces
static SLObjectItf outputMixObject = NULL;
static SLEnvironmentalReverbItf outputMixEnvironmentalReverb = NULL;

// buffer queue player interfaces
static SLObjectItf bqPlayerObject = NULL;
static SLPlayItf bqPlayerPlay;
static SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue;
static SLEffectSendItf bqPlayerEffectSend;
static SLMuteSoloItf bqPlayerMuteSolo;
static SLVolumeItf bqPlayerVolume;

// aux effect on the output mix, used by the buffer queue player
static const SLEnvironmentalReverbSettings reverbSettings =
    SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;

// URI player interfaces
static SLObjectItf uriPlayerObject = NULL;
static SLPlayItf uriPlayerPlay;
static SLSeekItf uriPlayerSeek;
static SLMuteSoloItf uriPlayerMuteSolo;
static SLVolumeItf uriPlayerVolume;

// file descriptor player interfaces
static SLObjectItf fdPlayerObject = NULL;
static SLPlayItf fdPlayerPlay;
static SLSeekItf fdPlayerSeek;
static SLMuteSoloItf fdPlayerMuteSolo;
static SLVolumeItf fdPlayerVolume;

// recorder interfaces
static SLObjectItf recorderObject = NULL;
static SLRecordItf recorderRecord;
static SLAndroidSimpleBufferQueueItf recorderBufferQueue;

// synthesized sawtooth clip
#define SAWTOOTH_FRAMES 8000
static short sawtoothBuffer[SAWTOOTH_FRAMES];

// 5 seconds of recorded audio at 16 kHz mono, 16-bit signed little endian
#define RECORDER_FRAMES (16000 * 5)
static short recorderBuffer[RECORDER_FRAMES];
static unsigned recorderSize = 0;
static SLmilliHertz recorderSR;

// pointer and size of the next player buffer to enqueue, and number of remaining buffers
static short *nextBuffer;
static unsigned nextSize;
static int nextCount;




#include "hello_clip.h"
#include "android_clip.h"

/*
__attribute__((constructor)) static void onDlOpen(void)
{
    unsigned i;
    LOGI("In %s", __func__);
    for (i = 0; i < SAWTOOTH_FRAMES; ++i) {
        sawtoothBuffer[i] = 32768 - ((i % 100) * 660);
    }
}
*/



void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context)
{
    assert(bq == bqPlayerBufferQueue);
    assert(NULL == context);
    LOGI("In %s", __func__);
    if (--nextCount > 0 && NULL != nextBuffer && 0 != nextSize) {
        SLresult result;
        result = (*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue, nextBuffer, nextSize);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}


void bqRecorderCallback(SLAndroidSimpleBufferQueueItf bq, void *context)
{
    assert(bq == bqRecorderBufferQueue);
    assert(NULL == context);
    LOGI("In %s", __func__);
    SLresult result;
    result = (*recorderRecord)->SetRecordState(recorderRecord, SL_RECORDSTATE_STOPPED);
    if (SL_RESULT_SUCCESS == result) {
        recorderSize = RECORDER_FRAMES * sizeof(short);
        recorderSR = SL_SAMPLINGRATE_16;
    }
}

JNIEXPORT void JNICALL NativeAudio_createEngine(JNIEnv* env, jobject thiz)
{
    SLresult result;
    LOGI("In %s", __func__);
    result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
    const SLboolean req[1] = {SL_BOOLEAN_FALSE};
    result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 1, ids, req);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    result = (*outputMixObject)->GetInterface(outputMixObject, SL_IID_ENVIRONMENTALREVERB,
            &outputMixEnvironmentalReverb);
    if (SL_RESULT_SUCCESS == result) {
        result = (*outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(
                outputMixEnvironmentalReverb, &reverbSettings);
        (void)result;
    }

}


// create buffer queue audio player
JNIEXPORT void JNICALL  NativeAudio_createBufferQueueAudioPlayer(JNIEnv* env,
        jobject thiz)
{
    SLresult result;
    LOGI("In %s", __func__);
    // configure audio source
    SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
    SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM, 1, SL_SAMPLINGRATE_8,
        SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
        SL_SPEAKER_FRONT_CENTER, SL_BYTEORDER_LITTLEENDIAN};
    SLDataSource audioSrc = {&loc_bufq, &format_pcm};

    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    // create audio player
    const SLInterfaceID ids[3] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND,
            /*SL_IID_MUTESOLO,*/ SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,
            /*SL_BOOLEAN_TRUE,*/ SL_BOOLEAN_TRUE};
    result = (*engineEngine)->CreateAudioPlayer(engineEngine, &bqPlayerObject, &audioSrc, &audioSnk,
            3, ids, req);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // realize the player
    result = (*bqPlayerObject)->Realize(bqPlayerObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the play interface
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAY, &bqPlayerPlay);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the buffer queue interface
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_BUFFERQUEUE,
            &bqPlayerBufferQueue);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // register callback on the buffer queue
    result = (*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue, bqPlayerCallback, NULL);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the effect send interface
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_EFFECTSEND,
            &bqPlayerEffectSend);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

#if 0   // mute/solo is not supported for sources that are known to be mono, as this is
    // get the mute/solo interface
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_MUTESOLO, &bqPlayerMuteSolo);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;
#endif

    // get the volume interface
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_VOLUME, &bqPlayerVolume);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // set the player's state to playing
    result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;
}


// create URI audio player
JNIEXPORT jboolean JNICALL NativeAudio_createUriAudioPlayer(JNIEnv* env, jobject thiz,
        jstring uri)
{
    SLresult result;
    LOGI("In %s", __func__);
    // convert Java string to UTF-8
    const char *utf8 = (*env)->GetStringUTFChars(env, uri, NULL);
    assert(NULL != utf8);

    // configure audio source
    // (requires the INTERNET permission depending on the uri parameter)
    SLDataLocator_URI loc_uri = {SL_DATALOCATOR_URI, (SLchar *) utf8};
    SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
    SLDataSource audioSrc = {&loc_uri, &format_mime};

    // configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    // create audio player
    const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
    result = (*engineEngine)->CreateAudioPlayer(engineEngine, &uriPlayerObject, &audioSrc,
            &audioSnk, 3, ids, req);
    // note that an invalid URI is not detected here, but during prepare/prefetch on Android,
    // or possibly during Realize on other platforms
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // release the Java string and UTF-8
    (*env)->ReleaseStringUTFChars(env, uri, utf8);

    // realize the player
    result = (*uriPlayerObject)->Realize(uriPlayerObject, SL_BOOLEAN_FALSE);
    // this will always succeed on Android, but we check result for portability to other platforms
    if (SL_RESULT_SUCCESS != result) {
        (*uriPlayerObject)->Destroy(uriPlayerObject);
        uriPlayerObject = NULL;
        return JNI_FALSE;
    }

    // get the play interface
    result = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_PLAY, &uriPlayerPlay);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the seek interface
    result = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_SEEK, &uriPlayerSeek);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the mute/solo interface
    result = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_MUTESOLO, &uriPlayerMuteSolo);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // get the volume interface
    result = (*uriPlayerObject)->GetInterface(uriPlayerObject, SL_IID_VOLUME, &uriPlayerVolume);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    return JNI_TRUE;
}


// set the playing state for the URI audio player
// to PLAYING (true) or PAUSED (false)
JNIEXPORT void JNICALL  NativeAudio_setPlayingUriAudioPlayer(JNIEnv* env,
        jobject thiz, jboolean isPlaying)
{
    SLresult result;
    LOGI("In %s", __func__);
    // make sure the URI audio player was created
    if (NULL != uriPlayerPlay) {

        // set the player's state
        result = (*uriPlayerPlay)->SetPlayState(uriPlayerPlay, isPlaying ?
            SL_PLAYSTATE_PLAYING : SL_PLAYSTATE_PAUSED);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }

}


// set the whole file looping state for the URI audio player
JNIEXPORT void JNICALL  NativeAudio_setLoopingUriAudioPlayer(JNIEnv* env,
        jobject thiz, jboolean isLooping)
{
    SLresult result;
    LOGI("In %s", __func__);
    // make sure the URI audio player was created
    if (NULL != uriPlayerSeek) {

        // set the looping state
        result = (*uriPlayerSeek)->SetLoop(uriPlayerSeek, (SLboolean) isLooping, 0,
                SL_TIME_UNKNOWN);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }

}


// expose the mute/solo APIs to Java for one of the 3 players

static SLMuteSoloItf getMuteSolo()
{
	 LOGI("In %s", __func__);
    if (uriPlayerMuteSolo != NULL)
        return uriPlayerMuteSolo;
    else if (fdPlayerMuteSolo != NULL)
        return fdPlayerMuteSolo;
    else
        return bqPlayerMuteSolo;
}

JNIEXPORT void JNICALL  NativeAudio_setChannelMuteUriAudioPlayer(JNIEnv* env,
        jobject thiz, jint chan, jboolean mute)
{
    SLresult result;
    LOGI("In %s", __func__);
    SLMuteSoloItf muteSoloItf = getMuteSolo();
    if (NULL != muteSoloItf) {
        result = (*muteSoloItf)->SetChannelMute(muteSoloItf, chan, mute);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}

JNIEXPORT void JNICALL  NativeAudio_setChannelSoloUriAudioPlayer(JNIEnv* env,
        jobject clazz, jint chan, jboolean solo)
{
    SLresult result;
    LOGI("In %s", __func__);
    SLMuteSoloItf muteSoloItf = getMuteSolo();
    if (NULL != muteSoloItf) {
        result = (*muteSoloItf)->SetChannelSolo(muteSoloItf, chan, solo);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}
JNIEXPORT jint JNICALL  NativeAudio_getNumChannelsUriAudioPlayer(JNIEnv* env, jobject thiz)
{
    SLuint8 numChannels;
    SLresult result;
    SLMuteSoloItf muteSoloItf = getMuteSolo();
    LOGI("In %s", __func__);
    if (NULL != muteSoloItf) {
        result = (*muteSoloItf)->GetNumChannels(muteSoloItf, &numChannels);
        if (SL_RESULT_PRECONDITIONS_VIOLATED == result) {
            // channel count is not yet known
            numChannels = 0;
        } else {
            assert(SL_RESULT_SUCCESS == result);
        }
    } else {
        numChannels = 0;
    }
    return numChannels;
}

// expose the volume APIs to Java for one of the 3 players

static SLVolumeItf getVolume()
{
	 LOGI("In %s", __func__);
    if (uriPlayerVolume != NULL)
        return uriPlayerVolume;
    else if (fdPlayerVolume != NULL)
        return fdPlayerVolume;
    else
        return bqPlayerVolume;
}

JNIEXPORT void JNICALL  NativeAudio_setVolumeUriAudioPlayer(JNIEnv* env, jobject thiz,
        jint millibel)
{
    SLresult result;
    LOGI("In %s", __func__);
    SLVolumeItf volumeItf = getVolume();
    if (NULL != volumeItf) {
        result = (*volumeItf)->SetVolumeLevel(volumeItf, millibel);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}

JNIEXPORT void JNICALL  NativeAudio_setMuteUriAudioPlayer(JNIEnv* env, jobject thiz,
        jboolean mute)
{
    SLresult result;
    LOGI("In %s", __func__);
    SLVolumeItf volumeItf = getVolume();
    if (NULL != volumeItf) {
        result = (*volumeItf)->SetMute(volumeItf, mute);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}

JNIEXPORT void JNICALL  NativeAudio_enableStereoPositionUriAudioPlayer(JNIEnv* env,
        jobject thiz, jboolean enable)
{
    SLresult result;
    LOGI("In %s", __func__);
    SLVolumeItf volumeItf = getVolume();
    if (NULL != volumeItf) {
        result = (*volumeItf)->EnableStereoPosition(volumeItf, enable);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}

JNIEXPORT void JNICALL  NativeAudio_setStereoPositionUriAudioPlayer(JNIEnv* env,
        jobject thiz, jint permille)
{
    SLresult result;
    LOGI("In %s", __func__);
    SLVolumeItf volumeItf = getVolume();
    if (NULL != volumeItf) {
        result = (*volumeItf)->SetStereoPosition(volumeItf, permille);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }
}


JNIEXPORT jboolean JNICALL  NativeAudio_enableReverb(JNIEnv* env, jobject thiz,
        jboolean enabled)
{
    SLresult result;
    LOGI("In %s", __func__);
    if (NULL == outputMixEnvironmentalReverb) {
        return JNI_FALSE;
    }

    result = (*bqPlayerEffectSend)->EnableEffectSend(bqPlayerEffectSend,
            outputMixEnvironmentalReverb, (SLboolean) enabled, (SLmillibel) 0);
    if (SL_RESULT_SUCCESS != result) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}


JNIEXPORT jboolean JNICALL  NativeAudio_selectClip(JNIEnv* env, jobject thiz, jint which,
        jint count)
{
	 LOGI("In %s", __func__);
    switch (which) {
    case 0:     // CLIP_NONE
        nextBuffer = (short *) NULL;
        nextSize = 0;
        break;
    case 1:     // CLIP_HELLO
        nextBuffer = (short *) hello_clip;
        nextSize = sizeof(hello_clip);
        break;
    case 2:     // CLIP_ANDROID
        nextBuffer = (short *) android_clip;
        nextSize = sizeof(android_clip);
        break;
    case 3:
        nextBuffer = sawtoothBuffer;
        nextSize = sizeof(sawtoothBuffer);
        break;
    case 4:
        if (recorderSR == SL_SAMPLINGRATE_16) {
            unsigned i;
            for (i = 0; i < recorderSize; i += 2 * sizeof(short)) {
                recorderBuffer[i >> 2] = recorderBuffer[i >> 1];
            }
            recorderSR = SL_SAMPLINGRATE_8;
            recorderSize >>= 1;
        }
        nextBuffer = recorderBuffer;
        nextSize = recorderSize;
        break;
    default:
        nextBuffer = NULL;
        nextSize = 0;
        break;
    }
    nextCount = count;
    if (nextSize > 0) {
        SLresult result;
        result = (*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue, nextBuffer, nextSize);
        if (SL_RESULT_SUCCESS != result) {
            return JNI_FALSE;
        }
    }

    return JNI_TRUE;
}


JNIEXPORT jboolean JNICALL  NativeAudio_createAssetAudioPlayer(JNIEnv* env, jobject thiz,
        jobject assetManager, jstring filename)
{
    SLresult result;
	 LOGI("In %s", __func__);
    // convert Java string to UTF-8
    const char *utf8 = (*env)->GetStringUTFChars(env, filename, NULL);
    assert(NULL != utf8);

    // use asset manager to open asset by filename
    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
    assert(NULL != mgr);
    AAsset* asset = AAssetManager_open(mgr, utf8, AASSET_MODE_UNKNOWN);


    (*env)->ReleaseStringUTFChars(env, filename, utf8);


    if (NULL == asset) {
        return JNI_FALSE;
    }

    off_t start, length;
    int fd = AAsset_openFileDescriptor(asset, &start, &length);
    assert(0 <= fd);
    AAsset_close(asset);

    SLDataLocator_AndroidFD loc_fd = {SL_DATALOCATOR_ANDROIDFD, fd, start, length};
    SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
    SLDataSource audioSrc = {&loc_fd, &format_mime};

    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
    result = (*engineEngine)->CreateAudioPlayer(engineEngine, &fdPlayerObject, &audioSrc, &audioSnk,
            3, ids, req);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;


    result = (*fdPlayerObject)->Realize(fdPlayerObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;


    result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_PLAY, &fdPlayerPlay);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;


    result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_SEEK, &fdPlayerSeek);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_MUTESOLO, &fdPlayerMuteSolo);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;


    result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_VOLUME, &fdPlayerVolume);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;


    result = (*fdPlayerSeek)->SetLoop(fdPlayerSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    return JNI_TRUE;
}


JNIEXPORT void JNICALL   NativeAudio_setPlayingAssetAudioPlayer(JNIEnv* env,
        jobject thiz, jboolean isPlaying)
{
    SLresult result;
	 LOGI("In %s", __func__);
    if (NULL != fdPlayerPlay) {

        result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay, isPlaying ?
            SL_PLAYSTATE_PLAYING : SL_PLAYSTATE_PAUSED);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }

}


JNIEXPORT jboolean JNICALL  NativeAudio_createAudioRecorder(JNIEnv* env, jobject thiz)
{
    SLresult result;
	LOGI("In %s", __func__);
    SLDataLocator_IODevice loc_dev = {SL_DATALOCATOR_IODEVICE, SL_IODEVICE_AUDIOINPUT,
            SL_DEFAULTDEVICEID_AUDIOINPUT, NULL};
    SLDataSource audioSrc = {&loc_dev, NULL};


    SLDataLocator_AndroidSimpleBufferQueue loc_bq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
    SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM, 1, SL_SAMPLINGRATE_16,
        SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
        SL_SPEAKER_FRONT_CENTER, SL_BYTEORDER_LITTLEENDIAN};
    SLDataSink audioSnk = {&loc_bq, &format_pcm};


    const SLInterfaceID id[1] = {SL_IID_ANDROIDSIMPLEBUFFERQUEUE};
    const SLboolean req[1] = {SL_BOOLEAN_TRUE};
    result = (*engineEngine)->CreateAudioRecorder(engineEngine, &recorderObject, &audioSrc,
            &audioSnk, 1, id, req);
    if (SL_RESULT_SUCCESS != result) {
        return JNI_FALSE;
    }

    result = (*recorderObject)->Realize(recorderObject, SL_BOOLEAN_FALSE);
    if (SL_RESULT_SUCCESS != result) {
        return JNI_FALSE;
    }

    result = (*recorderObject)->GetInterface(recorderObject, SL_IID_RECORD, &recorderRecord);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;


    result = (*recorderObject)->GetInterface(recorderObject, SL_IID_ANDROIDSIMPLEBUFFERQUEUE,
            &recorderBufferQueue);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;


    result = (*recorderBufferQueue)->RegisterCallback(recorderBufferQueue, bqRecorderCallback,
            NULL);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    return JNI_TRUE;
}


JNIEXPORT void JNICALL  NativeAudio_startRecording(JNIEnv* env, jobject thiz)
{
    SLresult result;
	LOGI("In %s", __func__);
    result = (*recorderRecord)->SetRecordState(recorderRecord, SL_RECORDSTATE_STOPPED);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;
    result = (*recorderBufferQueue)->Clear(recorderBufferQueue);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    recorderSize = 0;


    result = (*recorderBufferQueue)->Enqueue(recorderBufferQueue, recorderBuffer,
            RECORDER_FRAMES * sizeof(short));

    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    result = (*recorderRecord)->SetRecordState(recorderRecord, SL_RECORDSTATE_RECORDING);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;
}


JNIEXPORT void JNICALL  NativeAudio_shutdown(JNIEnv* env, jobject thiz)
{
	LOGI("In %s", __func__);
    if (bqPlayerObject != NULL) {
        (*bqPlayerObject)->Destroy(bqPlayerObject);
        bqPlayerObject = NULL;
        bqPlayerPlay = NULL;
        bqPlayerBufferQueue = NULL;
        bqPlayerEffectSend = NULL;
        bqPlayerMuteSolo = NULL;
        bqPlayerVolume = NULL;
    }

    if (fdPlayerObject != NULL) {
        (*fdPlayerObject)->Destroy(fdPlayerObject);
        fdPlayerObject = NULL;
        fdPlayerPlay = NULL;
        fdPlayerSeek = NULL;
        fdPlayerMuteSolo = NULL;
        fdPlayerVolume = NULL;
    }

    if (uriPlayerObject != NULL) {
        (*uriPlayerObject)->Destroy(uriPlayerObject);
        uriPlayerObject = NULL;
        uriPlayerPlay = NULL;
        uriPlayerSeek = NULL;
        uriPlayerMuteSolo = NULL;
        uriPlayerVolume = NULL;
    }

    if (recorderObject != NULL) {
        (*recorderObject)->Destroy(recorderObject);
        recorderObject = NULL;
        recorderRecord = NULL;
        recorderBufferQueue = NULL;
    }

    if (outputMixObject != NULL) {
        (*outputMixObject)->Destroy(outputMixObject);
        outputMixObject = NULL;
        outputMixEnvironmentalReverb = NULL;
    }

    if (engineObject != NULL) {
        (*engineObject)->Destroy(engineObject);
        engineObject = NULL;
        engineEngine = NULL;
    }

}

static JNINativeMethod method_table_SL[] = {
   {"SL_shutdown", "()V", (void*) NativeAudio_shutdown},
   {"SL_startRecording", "()V", (void*) NativeAudio_startRecording},
   {"SL_createAudioRecorder", "()Z", (void*) NativeAudio_createAudioRecorder},
   {"SL_enableReverb", "(Z)Z", (void*) NativeAudio_enableReverb},
   {"SL_selectClip", "(II)Z", (void*) NativeAudio_selectClip},
   {"SL_setStereoPositionUriAudioPlayer", "(I)V", (void*) NativeAudio_setStereoPositionUriAudioPlayer},
   {"SL_enableStereoPositionUriAudioPlayer", "(Z)V", (void*) NativeAudio_enableStereoPositionUriAudioPlayer},
   {"SL_setMuteUriAudioPlayer", "(Z)V", (void*) NativeAudio_setMuteUriAudioPlayer},
   {"SL_setVolumeUriAudioPlayer", "(I)V", (void*) NativeAudio_setVolumeUriAudioPlayer},
   {"SL_getNumChannelsUriAudioPlayer", "()I", (void*) NativeAudio_getNumChannelsUriAudioPlayer},
   {"SL_setChannelSoloUriAudioPlayer", "(IZ)V", (void*) NativeAudio_setChannelSoloUriAudioPlayer},
   {"SL_setChannelMuteUriAudioPlayer", "(IZ)V", (void*) NativeAudio_setChannelMuteUriAudioPlayer},
   {"SL_setLoopingUriAudioPlayer", "(Z)V", (void*) NativeAudio_setLoopingUriAudioPlayer},
   {"SL_setPlayingUriAudioPlayer", "(Z)V", (void*) NativeAudio_setPlayingUriAudioPlayer},
   {"SL_createUriAudioPlayer", "(Ljava/lang/String;)Z", (void*) NativeAudio_createUriAudioPlayer},
   {"SL_setPlayingAssetAudioPlayer", "(Z)V", (void*) NativeAudio_setPlayingAssetAudioPlayer},
   {"SL_createAssetAudioPlayer", "(Landroid/content/res/AssetManager;Ljava/lang/String;)Z", (void*) NativeAudio_createAssetAudioPlayer},
   {"SL_createBufferQueueAudioPlayer", "()V", (void*) NativeAudio_createBufferQueueAudioPlayer},
   {"SL_createEngine", "()V", (void*) NativeAudio_createEngine},
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

    registerNativeMethods(env, JNITHREAD_CLASS,
    		method_table_thread, NELEM(method_table_thread));

    registerNativeMethods(env, JNIGL_CLASS,
    		method_table_GL, NELEM(method_table_GL));

    registerNativeMethods(env, JNISL_CLASS,
       		method_table_SL, NELEM(method_table_SL));


    return registerNativeMethods(env, JNIMAIN_CLASS,
            method_table_main, NELEM(method_table_main));
}



JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    gJavaVM = vm;

    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
    	  LOGE("In %s Failed to get the environment using GetEnv()",__func__);
    	        return -1;
    }

    register_ndk_load(env);

    return JNI_VERSION_1_4;
}




