cmake_minimum_required(VERSION 3.21)
project(DrogonDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 从vcpkg找drogon
find_package(Drogon CONFIG REQUIRED)

# 自动收集src下所有cpp
file(GLOB_RECURSE SRC_FILES
    src/*.cpp
)

add_executable(DrogonDemo ${SRC_FILES})

target_link_libraries(DrogonDemo PRIVATE Drogon::Drogon)

# VS分组显示
source_group(TREE ${CMAKE_SOURCE_DIR}/src PREFIX "Source Files" FILES ${SRC_FILES})
