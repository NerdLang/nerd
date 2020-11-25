/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
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