add_rules("mode.debug", "mode.release")

add_requires("vulkansdk", {system=true })
add_requires("libsdl2")

target("imgui_sdl_vk")
    set_kind("binary")
    set_targetdir('bin')
    -- 应用依赖包
    add_packages("vulkansdk", "libsdl2")
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
    -- imgui配置
    add_includedirs("imgui")
    add_files("imgui/*.cpp")
    -- 项目源码
    add_includedirs("src")
    add_includedirs("src/public")
    add_files("src/**.cpp")
    -- 如果imgui需要sdl和vulkan的backend实现文件
target_end()