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

#include "C:\Users\adrien\Desktop\nectarjs\.nectar\y5dcg\lib\lib.h"

var android;var Math;var __MODULE_dvdjrhlazo;var __MODULE_2zgn2a33lq;var __2hv0pr;var __a9bke;var __vkogwj;var __obi22u;var __io35ki; var _tpl; var __uu2l3;

extern "C" JNIEXPORT void JNICALL
Java_com_nectarjs_nectar_1android_1app_MainActivity_callbackFromJNI(
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
Java_com_nectarjs_nectar_1android_1app_MainActivity_callFromJNI(
        JNIEnv* env,
        jobject thiz)
{
    globalEnv = env;
    mainObject = thiz;


    __NJS_DECL_FUNCTION<__NJS_VAR ()>* __NJS_FN___kj1kb = new __NJS_DECL_FUNCTION<__NJS_VAR ()>([&](  ) -> __NJS_VAR {
        var module = __NJS_Create_Object();

        ;
        var _android = __NJS_Create_Object();

        __NJS_Object_Set("draw", __NJS_ANDROID_DRAW, _android);

        ;

        var __sk8dc3 =
                __NJS_VAR();

        ;

        __sk8dc3 = _android;

        __NJS_Object_Set("exports", __sk8dc3, module);

        ;
        return __NJS_Object_Get("exports", module);
        ;return __NJS_Create_Undefined();} );__MODULE_dvdjrhlazo=__NJS_VAR(__NJS_FUNCTION, __NJS_FN___kj1kb);

    ;

    __NJS_DECL_FUNCTION<__NJS_VAR ()>* __NJS_FN___n0hp8r = new __NJS_DECL_FUNCTION<__NJS_VAR ()>([&](  ) -> __NJS_VAR {
        var module = __NJS_Create_Object();

        var _Math = __NJS_Create_Object();

        __NJS_Object_Set("E", 2.718, _Math);

        __NJS_Object_Set("LN2", 2.302, _Math);

        __NJS_Object_Set("LOG2E", 1.442, _Math);

        __NJS_Object_Set("LOG10E", 0.434, _Math);

        __NJS_Object_Set("PI", 3.141592653589793, _Math);

        __NJS_Object_Set("SQRT1_2", 0.707, _Math);

        __NJS_Object_Set("SQRT2", 1.414, _Math);

        __2hv0pr = __NJS_VAR(__NJS_FUNCTION, new function<__NJS_VAR (vector<var>)> ([&](vector<var> __NJS_VARARGS) -> __NJS_VAR{var i; if(__NJS_VARARGS.size() > 0) i = __NJS_VARARGS[0];
            if (i < 0) return -i;
            return i;

            return __NJS_Create_Undefined();}));;

        __NJS_Object_Set("abs", __2hv0pr, _Math);

        __a9bke = __NJS_VAR(__NJS_FUNCTION, new function<__NJS_VAR (vector<var>)> ([&](vector<var> __NJS_VARARGS) -> __NJS_VAR{var x; if(__NJS_VARARGS.size() > 0) x = __NJS_VARARGS[0];var  y; if(__NJS_VARARGS.size() > 1)  y = __NJS_VARARGS[1];
            var _res = 0;
            _res = x * y;
            return _res;

            return __NJS_Create_Undefined();}));;

        __NJS_Object_Set("imul", __a9bke, _Math);

        __vkogwj = __NJS_VAR(__NJS_FUNCTION, new function<__NJS_VAR (vector<var>)> ([&](vector<var> __NJS_VARARGS) -> __NJS_VAR{var _array; if(__NJS_VARARGS.size() > 0) _array = __NJS_VARARGS[0];
            var _res =
                    __NJS_VAR();

            ;

            for (var i = 0; i < __NJS_Object_Get("length", _array); i++) {
                if (__NJS_Typeof(__NJS_Object_Get(i, _array)) == "number") {
                    if (__NJS_Typeof(_res) == "undefined") _res = __NJS_Object_Get(i, _array);
                    if (__NJS_Object_Get(i, _array) > _res) _res = __NJS_Object_Get(i, _array);
                }
            }

            if (__NJS_Typeof(_res) == "undefined") _res = 0;
            return _res;

            return __NJS_Create_Undefined();}));;

        __NJS_Object_Set("max", __vkogwj, _Math);

        __obi22u = __NJS_VAR(__NJS_FUNCTION, new function<__NJS_VAR (vector<var>)> ([&](vector<var> __NJS_VARARGS) -> __NJS_VAR{var _array; if(__NJS_VARARGS.size() > 0) _array = __NJS_VARARGS[0];
            var _res =
                    __NJS_VAR();

            ;

            for (var i = 0; i < __NJS_Object_Get("length", _array); i++) {
                if (__NJS_Typeof(__NJS_Object_Get(i, _array)) == "number") {
                    if (__NJS_Typeof(_res) == "undefined") _res = __NJS_Object_Get(i, _array);
                    if (__NJS_Object_Get(i, _array) < _res) _res = __NJS_Object_Get(i, _array);
                }
            }

            if (__NJS_Typeof(_res) == "undefined") _res = 0;
            return _res;

            return __NJS_Create_Undefined();}));;

        __NJS_Object_Set("min", __obi22u, _Math);

        __io35ki = __NJS_VAR(__NJS_FUNCTION, new function<__NJS_VAR (vector<var>)> ([&](vector<var> __NJS_VARARGS) -> __NJS_VAR{var i; if(__NJS_VARARGS.size() > 0) i = __NJS_VARARGS[0];var  j; if(__NJS_VARARGS.size() > 1)  j = __NJS_VARARGS[1];
            if (j == 0) return 1;else if (j > 0) {
                j--;

                while (j) {
                    i *= i;
                    j--;
                }
            } else if (j < 0) {
                i = 1 / __NJS_Call_Function(__io35ki, i, __NJS_Call_Function(__2hv0pr, j));
            }
            return i;

            return __NJS_Create_Undefined();}));;

        __NJS_Object_Set("pow", __io35ki, _Math);

        ;

        var __z9kcc =
                __NJS_VAR();

        ;

        __z9kcc = _Math;

        __NJS_Object_Set("exports", __z9kcc, module);

        return __NJS_Object_Get("exports", module);
        ;return __NJS_Create_Undefined();} );__MODULE_2zgn2a33lq=__NJS_VAR(__NJS_FUNCTION, __NJS_FN___n0hp8r);

    ;

    android = __NJS_Call_Function(__MODULE_dvdjrhlazo);
    Math = __NJS_Call_Function(__MODULE_2zgn2a33lq);
    _tpl = "Text: <input id='test' type='text' /><br>";
    _tpl += "<button onClick='Nectar.fireEvent(document.getElementById(\"test\").value);'>{{CONTENT}}</button>";

    __NJS_Call_Function(__NJS_Object_Get("draw", android), __NJS_Call_Function(__NJS_Object_Get("replace", _tpl), "{{CONTENT}}", "Hello NectarJS !"));

    __uu2l3 =
            __NJS_VAR();

    ;

    __uu2l3 = __NJS_VAR(__NJS_FUNCTION, new function<__NJS_VAR (vector<var>)> ([&](vector<var> __NJS_VARARGS) -> __NJS_VAR{var _event; if(__NJS_VARARGS.size() > 0) _event = __NJS_VARARGS[0];
        __NJS_Call_Function(__NJS_Object_Get("draw", android), __NJS_Call_Function(__NJS_Object_Get("replace", _tpl), "{{CONTENT}}", _event));

        return __NJS_Create_Undefined();}));;

    __NJS_Object_Set("onEvent", __uu2l3, android);
    return;
}