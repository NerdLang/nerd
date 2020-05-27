/*
 * This file is part of NectarJS
 * Copyright (c) 2017-2020 Adrien THIERRY
 * http://nectarjs.com - https://www.linkedin.com/in/adrien-thierry-fr/
 *
 * sources : https://github.com/nectarjs/nectarjs/
 *
 * this program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * You can be released from the requirements of the license by purchasing
 * a commercial license. Buying such a license is mandatory as soon as you
 * develop commercial activities involving the NectarJS software without
 * disclosing the source code of your own applications. Visit http://seraum.com/
 * and feel free to contact us.
 *
 */
 
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

 using namespace std;

 #include "njs.h"
 
JNIEnv* globalEnv;
jobject mainObject;

void drawJNI(char* _str)
{
    jclass mainClass = globalEnv->GetObjectClass(mainObject);
    jmethodID _draw        = globalEnv->GetMethodID(mainClass, "drawNectar",
                                                    "(Ljava/lang/String;)V");
    jstring _html = globalEnv->NewStringUTF(_str);
    globalEnv->CallVoidMethod(mainObject, _draw, _html);
}

 {INCLUDE}
 
 {DECL}

extern "C" JNIEXPORT void JNICALL
Java_com_nectarjs_myapplication_MainActivity_callbackFromJNI(
        JNIEnv* env,
        jobject thiz,
        jstring _str) {

    globalEnv = env;
    mainObject = thiz;

    const char *nString = env->GetStringUTFChars(_str, NULL);
    __NJS_Call_Function(__NJS_Object_Get("onEvent", android), nString);
    env->ReleaseStringUTFChars(_str, nString);
    
}

extern "C" JNIEXPORT void JNICALL
Java_com_nectarjs_myapplication_MainActivity_callFromJNI(
        JNIEnv* env,
        jobject thiz)
{
    globalEnv = env;
    mainObject = thiz;

    
	{INIT}

	{CODE}
    return;
}