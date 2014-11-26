#include <jni.h>
#include <assert.h>
#include <pthread.h>
#include <android/log.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


#include "Ascii2Bin_JNI.h"



//Here comes the java mess...
//Java wrapped functions for export to JNI

# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#define JNISTRINGCONVERTER_CLASS "com/yanjun/ascilltobin/math/StringConverter"


JNIEXPORT jstring JNICALL Native_calculateBinFromAsciiStringJNI( JNIEnv* env,jobject jobj,jstring jstr){
	Ascii2Bin* ascii2bin_ptr = new Ascii2Bin();
	const char *cstr_ptr = env->GetStringUTFChars(jstr, 0);
	//char cap[1024];
	std::string cppString(cstr_ptr);
	//strcpy(cap, cstr_ptr);
	env->ReleaseStringUTFChars(jstr, cstr_ptr);
	cppString = ascii2bin_ptr->calculateBinFromAsciiString(cppString);
	delete ascii2bin_ptr;
	return env->NewStringUTF(cppString.c_str());

}
JNIEXPORT jstring JNICALL Native_calculateAsciiFromBinStringJNI( JNIEnv* env,jobject jobj, jstring jstr ){
		Ascii2Bin* ascii2bin_ptr = new Ascii2Bin(); //should be automatically destroyed when it goes out of scope from this function... not quite sure though
		const char *cstr_ptr = env->GetStringUTFChars(jstr, 0);
		//char cap[1024];
		std::string cppString(cstr_ptr);
		//strcpy(cap, cstr_ptr);
		env->ReleaseStringUTFChars(jstr, cstr_ptr);
		cppString = ascii2bin_ptr->calculateAsciiFromBinString(cppString);
		delete ascii2bin_ptr;
		return env->NewStringUTF(cppString.c_str());
}


	static JNINativeMethod method_table_StringConverter[] = {
	   {"calculateBinFromAsciiStringJNI", "(Ljava/lang/String;)Ljava/lang/String;", (void*) Native_calculateBinFromAsciiStringJNI},
	   {"calculateAsciiFromBinStringJNI", "(Ljava/lang/String;)Ljava/lang/String;", (void*) Native_calculateAsciiFromBinStringJNI},
	};



	static int registerNativeMethods(JNIEnv* env, const char* className,
			JNINativeMethod* gMethods, int numMethods)
	{
		jclass clazz;
		clazz = env->FindClass( className);
		if (clazz == NULL) {
			return JNI_FALSE;
		}
		if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
			return JNI_FALSE;
		}

		return JNI_TRUE;
	}



	int register_ndk_load(JNIEnv *env)
	{

		return registerNativeMethods(env, JNISTRINGCONVERTER_CLASS,
				method_table_StringConverter, NELEM(method_table_StringConverter));
	}



	JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
	{
		JNIEnv* env = NULL;

		if (vm->GetEnv( (void**) &env, JNI_VERSION_1_6) != JNI_OK) {
			  LOGE("In %s Failed to get the environment using GetEnv()",__func__);
					return -1;
		}

		register_ndk_load(env);

		return JNI_VERSION_1_6;
	}

