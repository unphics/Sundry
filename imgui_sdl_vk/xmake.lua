-- xmake.lua

-- 1. 全局配置 (必须放在 target 外)
if is_plat("android") then
    set_config("ndk_sdkver", "24")
end

add_rules("mode.debug", "mode.release")

-- 2. 依赖声明
add_requires("libsdl2")
-- Android 不需要 vulkansdk 包，直接用系统库
if not is_plat("android") then
    add_requires("vulkansdk")
end

target("imgui_sdl_vk")
    if is_plat("android") then
        set_kind("shared")
        set_basename("main") -- 必须叫 libmain.so
    else
        set_kind("binary")
    end

    add_packages("libsdl2")
    if not is_plat("android") then
        add_packages("vulkansdk")
    end

    add_includedirs("imgui", "src", "src/public")
    
    add_files("imgui/*.cpp")
    add_files("src/private/sdl2/*.cpp")
    add_files("src/private/vulkan/*.cpp")
    add_files("src/main.cpp") 

    if is_plat("android") then
        -- 链接系统库 (xmake 识别到 API 24 后会自动处理路径)
        add_syslinks("android", "log", "vulkan", "EGL", "GLESv2")
        
        -- 允许未定义符号 (关键)
        add_ldflags("-Wl,--allow-shlib-undefined")
    end
target_end()