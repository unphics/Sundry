-- 设置项目名
set_project("LuaJitStudy")
-- 设置版本
set_version("1.0.0")
-- 允许调试和发布模式
add_rules("mode.debug", "mode.release")

-- 定义目标
target("luajit")
    set_kind("binary") -- 编译为可执行程序

    -- 添加头文件包含
    add_includedirs("libs/LuaJIT-2.1.0-beta3/src")

    -- 添加源文件
    add_files("src/*.cc")

    -- 宏定义
    add_defines("USING_LUAJIT=1")
    add_defines("_CRT_SECURE_NO_WARNINGS")

    -- LuaJIT在Win64下必须开启GC64宏
    if is_plat("windows") and is_arch("x64") then
        add_defines("LUAJIT_ENABLE_GC64=1")
        add_defines("LUA_BUILD_AS_DLL") -- 链接DLL
    end

    -- 链接库文件
    add_linkdirs("libs/LuaJIT-2.1.0-beta3/lib-c/Win64/Release")
    add_links("Lua") -- lua51.lib

    -- 自动把DLL拷贝到运行目录
    after_build(function(target)
        import("core.project.task")
        local dllpath = "libs/LuaJIT-2.1.0-beta3/lib-c/Win64/Release/Lua.dll"
        if os.exists(dllpath) then
            os.cp(dllpath, target:targetdir())
        end
    end)
--[[
    -- 自动化构建
    before_build(function (target)
        if is_plat("windows") then
            -- 如果 lib 不存在，则自动调用脚本
            if not os.exists("3rd/luajit/src/lua51.lib") then
                print("Building LuaJIT via script...")
                os.cd("3rd/luajit/script")
                os.run("build_win64_jit.bat Release")
                os.cd("-")
            end
        end
    end)
--]]