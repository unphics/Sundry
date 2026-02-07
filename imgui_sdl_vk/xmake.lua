add_rules("mode.debug", "mode.release")

-- 1. 依赖包管理
if is_plat("android") then
    add_requires("libsdl2")
else
    -- windows
    add_requires("vulkansdk", {system=true })
    add_requires("libsdl2")
end


target("imgui_sdl_vk")
    -- 2. 根据平台设置生成的类型
    if is_plat("android") then
        set_kind("shared")
    else
        set_kind("binary")
        set_targetdir('bin')
    end

    -- 3. 应用依赖包
    add_packages("vulkansdk", "libsdl2")

    -- 4. 自动处理sdl2路径
    -- 因为 ImGui 代码里通常写的是 #include <SDL.h> 
    -- 而包管理器下载的路径可能是 include/SDL2/SDL.h
    after_load(function (target)
        local sdl2 = target:pkg("libsdl2")
        if sdl2 then
            local incdirs = sdl2:get("includedirs")
            for _, dir in ipairs(incdirs) do
                -- 自动把 .../include/SDL2 也加入搜索路径
                target:add("includedirs", path.join(dir, "SDL2"))
            end
        end
    end)

    -- 5.头文件路径
    add_includedirs("imgui")
    add_includedirs("src")
    add_includedirs("src/public")

    -- 6.源文件路径
    add_files("imgui/*.cpp")
    add_files("src/**.cpp")
    add_files("src/**.cc")
    -- 如果imgui需要sdl和vulkan的backend实现文件

    -- 7. 安卓平台特有的系统库链接和配置
    if is_plat("android") then
        -- log: 打印日志到Logcat; android: 安卓核心库; vulkan: 核心渲染库
        add_links("android", "log", "vulkan")

        -- 解决NDK入口函数问题
        add_defines("SDL_MAIN_HANDLED")
    end
target_end()

-- xmake f -p android --ndk="C:\Users\zys\AppData\Local\Android\Sdk\ndk\25.1.8937393" -a arm64-v8a --ndk_sdkver=24 -c
-- xmake