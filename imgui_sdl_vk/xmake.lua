-- xmake.lua

-- 1. 基础配置
add_rules("mode.debug", "mode.release")

-- 2. 依赖管理
add_requires("libsdl2")

-- 【关键】Android 平台不需要 vulkansdk 包，直接用系统库
if not is_plat("android") then
    add_requires("vulkansdk")
end

target("imgui_sdl_vk")
    -- 设定目标类型
    if is_plat("android") then
        set_kind("shared")
        set_basename("main") -- 必须叫 libmain.so
    else
        set_kind("binary")
    end

    -- 应用依赖
    add_packages("libsdl2")
    if not is_plat("android") then
        add_packages("vulkansdk")
    end

    -- 头文件路径
    add_includedirs("imgui", "src", "src/public")
    
    -- 源文件
    add_files("imgui/*.cpp")
    add_files("src/private/sdl2/*.cpp")
    add_files("src/private/vulkan/*.cpp")
    add_files("src/main.cpp") 

    -- 【核心修复】Android 链接配置
    if is_plat("android") then
        -- 1. 强制设置 API 版本 (作为双重保险)
        set_config("ndk_sdkver", "24")

        -- 2. 链接 Android 系统库
        -- 注意：不要在这里写 linkdirs，让 xmake 根据 ndk_sdkver 自动推导
        add_syslinks("android", "log", "vulkan", "EGL", "GLESv2")
        
        -- 3. 允许未定义符号 (解决 SDL2 的 JNI 入口问题)
        add_ldflags("-Wl,--allow-shlib-undefined")
    end
target_end()