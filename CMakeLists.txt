# cmake_minimum_required(VERSION 3.10)
# project(cv_project)

# find_package(OpenCV REQUIRED)
# include_directories(${OpenCV_INCLUDE_DIRS})

# add_executable(my_project main.cpp)
# target_link_libraries(my_project ${OpenCV_LIBS})
cmake_minimum_required(VERSION 3.10)
project(TcpImageServer)

set(CMAKE_CXX_STANDARD 17)

# 包含 server 目录
add_subdirectory(server)