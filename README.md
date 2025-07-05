📸 Qt-OpenCV 图像远程处理系统
基于 Qt 客户端和 Linux OpenCV 服务器的远程图像处理系统，支持多线程 TCP 通信、图像上传与处理命令发送、结果回传与展示。

🧩 项目结构
bash
复制
编辑
opencv_remote_processor/
├── client/            # Windows 客户端（基于 Qt 开发）
│   ├── mainwindow.ui
│   ├── mainwindow.cpp/h
│   └── ...
│
├── server/            # Linux 服务器（基于 C++/OpenCV）
│   ├── tcp_server.cpp/h
│   ├── imageProcessor.cpp/h
│   └── ...
│
├── image_processing/  # 图像处理模块（支持扩展）
│   └── imageProcessor.cpp/h
│
├── cmake/             # CMake 构建配置
│   └── CMakeLists.txt
│
├── docs/              # 项目文档
│   ├── 通信协议说明.md
│   ├── 使用指南.md
│   └── 项目展示截图/
│
└── README.md
🚀 功能简介
✅ Qt 客户端支持图像选择、上传、指令发送

✅ 支持多种图像处理命令（如：灰度化、模糊、边缘提取等）

✅ 客户端接收并显示处理后的图像

✅ Linux 服务器支持多线程 TCP 并发连接

✅ 图像以压缩格式（JPEG）传输，命令参数可扩展

🧠 核心技术
Qt5 / Qt6 —— 客户端 GUI 与 TCP Socket

OpenCV —— 图像处理核心库（在 Linux 服务器端）

C++ 多线程（std::thread） + 自定义协议

CMake 跨平台构建系统

💻 编译与运行
🔹 客户端（Windows）
bash
复制
编辑
# 使用 Qt Creator 打开 client 项目
# 编译并运行即可
🔸 服务器端（Linux）
bash
复制
编辑
cd server
mkdir build && cd build
cmake ..
make

# 启动服务端程序（默认监听 6666 端口）
./server
📡 通信协议
字段	长度	说明
type	1 byte	0xA0 表示图片, 0xB0 表示命令
length	4 bytes	后续 payload 的长度（大端序）
payload	可变	图片（压缩图像）或 UTF-8 命令

示例：

命令包：0xB0 + 00 00 00 0A + grayscale

图片包：0xA0 + 00 01 3A B4 + JPEG图像二进制

🧪 支持的图像处理命令（持续扩展）
grayscale

blur|ksize

canny|threshold1|threshold2

invert

...（可通过滑动条传参）

📷 效果展示
操作界面	图像处理前	图像处理后

🧰 项目亮点
简洁高效的图像远程处理系统

自定义通信协议，支持扩展命令与参数

Qt GUI 用户友好，操作直观

C++ 多线程服务器，处理多个客户端请求

实用性强，适用于远程医疗图像处理、教学实验、AI前后处理模块开发等场景

✨ TODO（可选扩展）
 添加图像处理结果对比功能

 支持视频逐帧上传处理

 用户权限管理与历史记录查看

 压缩优化图像传输带宽

🔗 项目部署建议
若需他人使用该系统，可按如下方式部署：

服务器端：

在公网 Linux 服务器编译运行（需开放指定端口）

使用 systemd 配置为后台服务

客户端：

使用 Qt Installer Framework 或 windeployqt 打包为可执行程序

