# 添加源文件
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(server
    serverMain.cpp
    tcp_server.cpp
)

target_link_libraries(server ${OpenCV_LIBS})

# 链接 socket 库（Linux 下必需）
target_link_libraries(server pthread)