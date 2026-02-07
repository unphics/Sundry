# 目录结构
```
imgui_sdl_vk/
├── bin/                    # 可执行文件及其配置存放目录
├── doc/                    # 文档
├── imgui/                  # dear_imgui源码
├── lib/                    # 存放sdl2/vulkan等库
├── src/                    # 工程源代码
|   ├── private/            # 工程的源文件
|   └── public/             # 工程的头文件
|       ├── sdl2/           # imgui中对sdl的封装文件
|       └── vulkan/         # imgui中对vulkan的封装文件
└── xmake.lua               # xmake构建脚本
````