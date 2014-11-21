 LOCAL_PATH := $(call my-dir)

   include $(CLEAR_VARS)
   
   LOCAL_LDLIBS    := -llog 
   
   LOCAL_MODULE    := ascii2bin
   LOCAL_SRC_FILES := Ascii2Bin_src/math/Ascii2Bin.cpp Ascii2Bin_src/math/Ascii2Bin_JNI.cpp

   include $(BUILD_SHARED_LIBRARY)