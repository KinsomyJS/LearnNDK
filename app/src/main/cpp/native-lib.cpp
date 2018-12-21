#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_kinsomy_learnndk_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kinsomy_learnndk_MainActivity_test(JNIEnv *env, jobject instance) {

    jclass clazz = env->GetObjectClass(instance);
    jmethodID mid =env->GetMethodID(clazz, "callNullPointerException", "()V");
    env->CallVoidMethod(instance, mid); // will throw a NullPointerException
    jthrowable exc = env->ExceptionOccurred(); // 检测是否发生异常
    if (exc) {
        printf("============");
        env->ExceptionDescribe(); // 打印异常信息
        printf("============");
        env->ExceptionClear(); // 清除掉发生的异常
        jclass newExcCls = env->FindClass("java/lang/IllegalArgumentException");
        env->ThrowNew(newExcCls, "throw from JNI"); // 返回一个新的异常到 Java
    }else {
        jclass npe = env->FindClass("java/lang/NullPointerException");
        env->ThrowNew(npe,"throw from JNI");
    }

}