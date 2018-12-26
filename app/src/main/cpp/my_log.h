/**
 * Created by kinsomy on 2018/12/25.
 * NDK基本日志框架
 */

#ifndef LEARNNDK_MY_LOG_H
#define LEARNNDK_MY_LOG_H

#include <android/log.h>

#define MY_LOG_LEVEL_VERBOSE 1
#define MY_LOG_LEVEL_DEBUG 2
#define MY_LOG_LEVEL_INFO 3
#define MY_LOG_LEVEL_WARNING 4
#define MY_LOG_LEVEL_ERROR 5
#define MY_LOG_LEVEL_FATAL 6
#define MY_LOG_LEVEL_SILENT 7

#define MY_LOG_TAG "MY_JNI_LOG"
#ifndef MY_LOG_TAG
#   define MY_LOG_TAG __FILE__
#endif

#ifndef MY_LOG_LEVEL
#   define MY_LOG_LEVEL MY_LOG_LEVEL_VERBOSE
#endif

#define MY_LOG_NOOP (void) 0

#define MY_LOG_PRINT(level, fmt, ...) \
        __android_log_print(level,MY_LOG_TAG,"(%s:%u) %s: " fmt, \
                __FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__)

#if MY_LOG_LEVEL_VERBOSE >= MY_LOG_LEVEL
#define LOGV(fmt, ...) \
        MY_LOG_PRINT(ANDROID_LOG_VERBOSE,fmt,##__VA_ARGS__)
#else
#define LOGV(...) MY_LOG_NOOP
#endif

#if MY_LOG_LEVEL_DEBUG >= MY_LOG_LEVEL
#define LOGD(fmt, ...) \
        MY_LOG_PRINT(ANDROID_LOG_DEBUG,fmt,##__VA_ARGS__)
#else
#define LOGD(...) MY_LOG_NOOP
#endif

#if MY_LOG_LEVEL_INFO >= MY_LOG_LEVEL
#define LOGI(fmt, ...) \
        MY_LOG_PRINT(ANDROID_LOG_INFO,fmt,##__VA_ARGS__)
#else
#define LOGI(...) MY_LOG_NOOP
#endif

#if MY_LOG_LEVEL_WARNING >= MY_LOG_LEVEL
#define LOGW(fmt, ...) \
        MY_LOG_PRINT(ANDROID_LOG_WARN,fmt,##__VA_ARGS__)
#else
#define LOGW(...) MY_LOG_NOOP
#endif

#if MY_LOG_LEVEL_ERROR >= MY_LOG_LEVEL
#define LOGE(fmt, ...) \
        MY_LOG_PRINT(ANDROID_LOG_ERROR,fmt,##__VA_ARGS__)
#else
#define LOGE(...) MY_LOG_NOOP
#endif

#if MY_LOG_LEVEL_FATAL >= MY_LOG_LEVEL
#define LOGF(fmt, ...) \
        MY_LOG_PRINT(ANDROID_LOG_FATAL,fmt,##__VA_ARGS__)
#else
#define LOGF(...) MY_LOG_NOOP
#endif

#if MY_LOG_LEVEL_FATAL >= MY_LOG_LEVEL
#define LOGASSERT(expression, fmt, ...) \
        if(!(expression)) \
        { \
          __android_log_assert(#expression,MY_LOG_TAG, \
                fmt, ##__VA_ARGS__); \
        }
#else
#define LOGASSERT(...) MY_LOG_NOOP
#endif


#endif //LEARNNDK_MY_LOG_H
