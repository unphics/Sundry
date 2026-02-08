-- xmake.lua
add_defines("VK_NO_PROTOTYPES")
add_defines("IMGUI_IMPL_VULKAN_USE_VOLK")
-- 1. 强制 NDK 版本
if is_plat("android") then
    set_config("ndk_sdkver", "24")
end

add_rules("mode.debug", "mode.release")

add_requires("libsdl2")

target("imgui_sdl_vk")
    if is_plat("android") then
        set_kind("shared")
        set_basename("main")
        -- 【核心修改 1】开启 Volk 宏
        add_defines("IMGUI_IMPL_VULKAN_USE_VOLK")
    else
        set_kind("binary")
        add_packages("vulkansdk")
    end

    add_packages("libsdl2")
    add_includedirs("imgui", "src", "src/public", "src/private")
    
    add_files("imgui/*.cpp")
    add_files("src/private/sdl2/*.cpp")
    add_files("src/private/vulkan/*.cpp")
    add_files("src/private/vulkan/*.c")
    add_files("src/**.c")
    -- 【核心修改 2】添加 volk.c 源文件
    add_files("src/private/vulkan/volk.c") 
    add_files("src/main.cpp") 

    if is_plat("android") then
        add_defines("IMGUI_IMPL_VULKAN_USE_VOLK")
        add_defines("VK_NO_PROTOTYPES") 
        -- 【核心修改 3】
        -- 当使用 Volk 时，我们不再直接链接 vulkan 库（或只链接 dl 用于加载）
        -- 这样就不会在加载 libmain.so 时去检查 vkMapMemory 等符号了
        add_syslinks("android", "log", "dl") -- dl 是必须的，用于动态加载 .so
        
        -- 如果编译时提示找不到 vulkan.h，可以保留这个 links
        -- 但有了 Volk，它不会在运行时产生符号引用冲突
        -- add_links("vulkan") 

        add_ldflags("-Wl,--allow-shlib-undefined")
    end
target_end()