#include <jni.h>
#include <string>
#include <iostream>
#include <dirent.h>
//#include "LogUtils.h"
#include "my_log.h"
#include <android/bitmap.h>

extern "C" {

using namespace std;

void showAllFiles(string dir_name) {

    if (dir_name.empty()) {
        LOGE("dir_name is null !");
        return;
    }

    //打开文件夹
    DIR *dir = opendir(dir_name.c_str());

    //检查是否是dir
    if (NULL == dir) {
        LOGE("Can't open the dir. Check path if the path is correct ! ");
        return;
    }

    struct dirent *file;

    //遍历读取dir下的文件
    while ((file = readdir(dir)) != NULL) {
        //跳过 "." 和 ".."
        if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
            LOGV("ignore . and ..");
            continue;
        }

        if (file->d_type == DT_DIR) {
            //如果是dir类型就递归
            string filePath = dir_name + "/" + file->d_name;
            showAllFiles(filePath);
        } else {
            //如果是file类型就输出
            LOGI("filePath: %s/%s", dir_name.c_str(), file->d_name);
        }
    }
    closedir(dir);
}


JNIEXPORT void JNICALL
Java_com_kinsomy_learnndk_MainActivity_showDir(JNIEnv *env, jobject instance, jstring dirPath_) {
    const char *dirPath = env->GetStringUTFChars(dirPath_, 0);
    showAllFiles(string(dirPath));
    env->ReleaseStringUTFChars(dirPath_, dirPath);

}
}

extern "C" {
JNIEXPORT void JNICALL
Java_com_kinsomy_learnndk_MainActivity_passBitmap(JNIEnv *env, jobject instance, jobject bitmap) {
    if (NULL == bitmap) {
        LOGE("bitmap is null !");
        return;
    }

    AndroidBitmapInfo info;
    int result;

    result = AndroidBitmap_getInfo(env, bitmap, &info);
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        LOGE("AndroidBitmao_getInfo failed, result: %d", result);
        return;
    }

    LOGD("bitmap width: %d, height: %d, format: %d, stride: %d",
         info.width, info.height, info.format, info.stride);

    //获取像素信息
    unsigned char *addrPtr;
    result = AndroidBitmap_lockPixels(env, bitmap, reinterpret_cast<void **> (&addrPtr));
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        LOGE("AndroidBitmap_lockPixels failed, result: %d", result);
        return;
    }

    int length = info.stride * info.height;
    for (int i = 0; i < length; ++i) {
        LOGD("value: %x", addrPtr[i]);
    }

    result = AndroidBitmap_unlockPixels(env, bitmap);
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        LOGE("AndroidBitmap_unlockPixels failed, result: %d", result);
    }
}
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_kinsomy_learnndk_MainActivity_stringFromJNI(JNIEnv *env, jobject instance) {
    std::string hello = "Hello from C++";
    LOGV("method stringFromJNI is called.");
    LOGD("env address: %p, jobject address: %p", env, instance);
    LOGASSERT(0 != env, "JNIEnv can not be null!")
    LOGI("Returning a new string.");
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kinsomy_learnndk_MainActivity_test(JNIEnv *env, jobject instance) {

    jclass clazz = env->GetObjectClass(instance);
    jmethodID mid = env->GetMethodID(clazz, "callNullPointerException", "()V");
    env->CallVoidMethod(instance, mid); // will throw a NullPointerException
    jthrowable exc = env->ExceptionOccurred(); // 检测是否发生异常
    if (exc) {
        printf("============");
        env->ExceptionDescribe(); // 打印异常信息
        printf("============");
        env->ExceptionClear(); // 清除掉发生的异常
        jclass newExcCls = env->FindClass("java/lang/IllegalArgumentException");
        env->ThrowNew(newExcCls, "throw from JNI"); // 返回一个新的异常到 Java
    } else {
        jclass npe = env->FindClass("java/lang/NullPointerException");
        env->ThrowNew(npe, "throw from JNI");
    }

}

