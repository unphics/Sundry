add_rules("mode.debug", "mode.release")

target("imgui_sdl_vk")
    set_kind("binary")
    set_targetdir('./out')
    add_includedirs("d:/Lib/VulkanSDK/1.3.290.0/Include/")
    add_links("d:/Lib/VulkanSDK/1.3.290.0/Lib/vulkan-1.lib")
    add_includedirs("./lib/sdl2/include/")
    add_links("./lib/sdl2/build/Release/SDL2")
    add_includedirs("imgui")
    add_files("imgui/*.cpp")
    add_includedirs("src")
    add_files("src/*.cpp")
target_end()