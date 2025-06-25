# 添加源文件
add_executable(server
    serverMain.cpp
    tcp_server.cpp
)

# 链接 socket 库（Linux 下必需）
target_link_libraries(server pthread)