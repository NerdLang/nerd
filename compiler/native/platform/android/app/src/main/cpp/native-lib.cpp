#include <jni.h>
#include <string>
#include "android.hpp"

extern "C" JNIEXPORT void JNICALL
Java_com_nectarjs_nectarinterrop_MainActivity_callNectarJS(
        JNIEnv* env,
        jobject /* this */) {
    mainAndroid();
    return;
}
