#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <jni.h>
#include <assert.h>
#include <android/log.h>

# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))

#define JNIMAIN_CLASS "com/example/student/MainActivity"
#define JNISTUDENT_CLASS "com/example/student/Student"


#define  TAG    "Student-jni"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

// jfieldID结构体，用于保存类“Student.java”的filedID
struct StudentOffsets
{
    jfieldID    name;
    jfieldID    age;
    jfieldID    height;
} gStudentOffsets;

// 与“Student.java”对应的结构体，用于保存数据，并将数据赋值给Student.java的成员
typedef struct tagStudent
{
    char    mName[10];
    int     mAge;
    float   mHeight;
}Student;


// 定义了3个Student
static Student gStudent[] = {
    {"skywang", 25, 175},
    {"eman"   , 30, 166},
    {"Dan"    , 51, 172},
};

#define GSTUDENT_NUM NELEM(gStudent)

JNIEXPORT jint JNICALL Native_getStudentInfoByIndex(JNIEnv *env, jobject clazz, jobject student, jint index)
{

    // 若index无效，则直接返回-1。
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



JNIEXPORT jstring JNICALL Native_stringFromJni(JNIEnv *env, jobject clazz)
{
    jstring str = (*env)->NewStringUTF(env, "Hello From Jni");
    return str;
}

JNIEXPORT void JNICALL Native_stringToJni(JNIEnv *env, jobject clazz, jstring val)
{
    char *str = (char *)(*env)->GetStringUTFChars(env, val, JNI_FALSE);
    LOGD("%s str=%s\n", __func__, str);
}

JNIEXPORT jfloat JNICALL Native_floatFromJni(JNIEnv *env, jobject clazz)
{
    return (jfloat)1.34;
}

JNIEXPORT void JNICALL Native_floatToJni(JNIEnv *env, jobject clazz, jfloat val)
{
    float f = (float)val;
    LOGD("%s f=%f\n", __func__, f);
}

JNIEXPORT jint JNICALL Native_intFromJni(JNIEnv *env, jobject clazz)
{
    return (jint)25;
}


JNIEXPORT void JNICALL Native_intToJni(JNIEnv *env, jobject clazz, jint val)
{
    int i = (int)val;
    LOGD("%s i=%d\n", __func__, i);
}

JNIEXPORT jstring JNICALL native_hello(JNIEnv *env, jclass clazz)
{
	 LOGI("%s info\n", __func__);
    return (*env)->NewStringUTF(env, "hello All");
}



JNIEXPORT void JNICALL Native_sayHello(JNIEnv *env, jobject clazz){
    jclass student_clazz = (*env)->GetObjectClass(env,clazz);
    LOGI("%s info\n", __func__);
    jfieldID fieldID_name = (*env)->GetFieldID(env,student_clazz,"mName","Ljava/lang/String;");
    jfieldID fieldID_age = (*env)->GetFieldID(env,student_clazz,"mAge","I");
    jfieldID fieldID_height = (*env)->GetFieldID(env,student_clazz,"mHeight","F");
    jfieldID fieldID_count = (*env)->GetStaticFieldID(env,student_clazz,"count","I");

    //得到jmethodID
    jmethodID getInfoPublic_func=(*env)->GetMethodID(env,student_clazz,"getInfoPublic","()Ljava/lang/String;");
    jmethodID getInfoPrivate_func=(*env)->GetMethodID(env,student_clazz,"getInfoPrivate","()Ljava/lang/String;");
    jmethodID getInfoStatic_func=(*env)->GetStaticMethodID(env,student_clazz,"getInfoStatic","(I)Ljava/lang/String;");


    //调用方法
    jobject result1 = (*env)->CallObjectMethod(env,clazz,getInfoPublic_func);
    char *str1 = (char *)(*env)->GetStringUTFChars(env, (jstring)result1, JNI_FALSE);
    LOGD("Call java public Method result:%s\n",str1);

    jobject result2 = (*env)->CallObjectMethod(env,clazz,getInfoPrivate_func);
    char *str2 = (char *)(*env)->GetStringUTFChars(env, (jstring)result2, JNI_FALSE);
    LOGD("Call java private Method result:%s\n",str2  );

    //得到count属性
    jint count = (*env)->GetStaticIntField(env,student_clazz,fieldID_count);
    count++;
    LOGD("The count is:%d\n",(int)count);

    jobject result3 = (*env)->CallStaticObjectMethod(env,student_clazz,getInfoStatic_func,count);
    char *str3 = (char *)(*env)->GetStringUTFChars(env, (jstring)result3, JNI_FALSE);
    LOGD("Call java static method  result:%s\n",str3);
    //得到name属性
    jobject name = (*env)->GetObjectField(env,clazz,fieldID_name);

    char *str = (char *)(*env)->GetStringUTFChars(env, (jstring)name, JNI_FALSE);
    LOGD("name:%s\n",str);
    //得到age属性
    jint age= (*env)->GetIntField(env,clazz,fieldID_age);
    //得到height属性
    jfloat height= (*env)->GetFloatField(env,clazz,fieldID_height);
    LOGD("Before modify:age=%d\n", (int)age);
    //修改number属性的值
    (*env)->SetIntField(env,clazz,fieldID_age,50);
    age= (*env)->GetIntField(env,clazz,fieldID_age);
    LOGD("After modify , The age changed:age=%d\n", (int)age);
 }

/*JNIEXPORT jstring JNICALL  Native_stringFromJNIStatic(JNIEnv* env,jobject thiz) {
	 LOGI("%s info\n", __func__);
     LOGD("%s debug\n", __func__);
     LOGE("%s error\n", __func__);
	return (*env)->NewStringUTF(env, "Hello yanjun, Good Afternoon !");
}*/


static JNINativeMethod method_table_main[] = {
    { "stringFromJNIDynamic", "()Ljava/lang/String;", (void*)native_hello },//绑定
    { "intFromJni", "()I", (void*)Native_intFromJni},
    { "intToJni", "(I)V", (void*)Native_intToJni},
    { "floatFromJni", "()F", (void*)Native_floatFromJni},
    { "floatToJni", "(F)V", (void*)Native_floatToJni},
    { "stringFromJni", "()Ljava/lang/String;", (void*)Native_stringFromJni},
    { "stringToJni", "(Ljava/lang/String;)V", (void*)Native_stringToJni},
    { "getStudentInfoByIndex", "(Lcom/example/student/Student;I)I", (void*)Native_getStudentInfoByIndex},
};

static JNINativeMethod method_table_student[] = {
   {"sayHello", "()V", (void*)Native_sayHello},
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
    // 调用注册方法
    registerNativeMethods(env, JNISTUDENT_CLASS,
    		method_table_student, NELEM(method_table_student));
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

    // 返回jni的版本
    return JNI_VERSION_1_4;
}
