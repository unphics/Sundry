#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <algorithm>

#include <android/log.h>
#include <android_native_app_glue.h>

// 安卓原生 App 的真正入口
void android_main(struct android_app* state) {
    // 这里的 state 包含了窗口句柄、输入事件等
    
    // 安卓原生的“printf”是 Logcat
    __android_log_print(ANDROID_LOG_INFO, "RiverTag", "Hello Android Native!");

    int running = 1;
    while (running) {
        // 处理事件（比如点击屏幕、按返回键）
        int events;
        struct android_poll_source* source;
        while (ALooper_pollAll(0, nullptr, &events, (void**)&source) >= 0) {
            if (source != nullptr) source->process(state, source);
            if (state->destroyRequested != 0) running = 0;
        }
        
        // 这里写你的渲染逻辑 (OpenGL/Vulkan)
    }
}