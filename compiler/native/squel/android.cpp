 #define _USE_MATH_DEFINES
 #include <cmath>
 #include <string>
 #include <iostream>
 #include <string>
 #include <cstring>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sstream>
 #include <vector>
 #include <memory>
 #include <jni.h>

 #include "nectar.cpp"
 using namespace NectarCore::Global;
 using namespace NectarCore::Functions;
 //#include "httplib.h"
 
 var __NJS_ENV = "android";
 var __NJS_PLATFORM = "{{__PLATFORM__}}";
 #define __NJS_Create_Object() new NectarCore::Class::Object()
 #define __NJS_Create_Array(_arr) new NectarCore::Class::Array(_arr)
 #define __NJS_InitVar() NectarCore::VAR()
 
JNIEnv* globalEnv;
jobject mainObject;

void drawJNI(const char* _str)
{
    jclass mainClass = globalEnv->GetObjectClass(mainObject);
    jmethodID _draw        = globalEnv->GetMethodID(mainClass, "drawNectar",
                                                    "(Ljava/lang/String;)V");
    jstring _html = globalEnv->NewStringUTF(_str);
    globalEnv->CallVoidMethod(mainObject, _draw, _html);
}

void navigateJNI(const char* _str)
{
    jclass mainClass = globalEnv->GetObjectClass(mainObject);
    jmethodID _draw        = globalEnv->GetMethodID(mainClass, "navigateNectar",
                                                    "(Ljava/lang/String;)V");
    jstring _html = globalEnv->NewStringUTF(_str);
    globalEnv->CallVoidMethod(mainObject, _draw, _html);
}

 {INCLUDE}
 
 {DECL}

extern "C" JNIEXPORT void JNICALL
Java_com_nectarjs_nectar_1android_1app_MainActivity_callbackFromJNI(
        JNIEnv* env,
        jobject thiz,
        jstring _str) {

    globalEnv = env;
    mainObject = thiz;

    const char *nString = env->GetStringUTFChars(_str, NULL);
	Nectar["onEvent"](nString);
    env->ReleaseStringUTFChars(_str, nString);
    
}

extern "C" JNIEXPORT void JNICALL
Java_com_nectarjs_nectar_1android_1app_MainActivity_serveFromJNI(
        JNIEnv* env,
        jobject thiz) {

    globalEnv = env;
    mainObject = thiz;

    //using namespace httplib;

    //Server svr;
    //svr.set_mount_point("/", "/data/user/0/com.nectarjs.nectar_android_app/files/raw/");
    //svr.listen("localhost", 12001);

}

extern "C" JNIEXPORT void JNICALL
Java_com_nectarjs_nectar_1android_1app_MainActivity_callFromJNI(
        JNIEnv* env,
        jobject thiz)
{
    globalEnv = env;
    mainObject = thiz;

    
	{INIT}

	{
		{CODE}
	}
	
    return;
}