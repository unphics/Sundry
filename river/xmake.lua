set_project("river")
set_version("1.0.0")
add_rules("mode.debug", "mode.release")
add_requires("libsdl2")

if is_plat("android") then
    add_requires("ndk", {configs = {sdkver = "24"}})
    set_toolchains("@ndk", {sdkver = "24"})
end

target("river")
    set_languages("c++20")
    add_packages("libsdl2")
    add_files("src/**.cc")

    if is_plat("windows") then
        add_ldflags("/SUBSYSTEM:CONSOLE")
        set_kind("binary") -- build .exe in windows
    elseif is_plat("android") then
        set_kind("shared") -- build .so in android
        set_rules("android.application")

        -- 安卓包信息配置
        add_files("android/java/**.java") -- 编译 Java 源码
        set_configvar("android.manifest", "android/AndroidManifest.xml")
        set_configvar("android.packageName", "org.libsdl.app")

       -- 链接安卓系统库
        add_syslinks("android", "log", "GLESv2", "EGL")

        -- 解决符号问题
        add_ldflags("-Wl,--allow-shlib-undefined")
    end
target_end()