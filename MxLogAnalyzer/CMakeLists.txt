cmake_minimum_required(VERSION 3.20)
project(MxLogAnalyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include 目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 收集源文件
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(MxLogAnalyzer ${SOURCES} "src/parsing/ImportLog.cpp" "include/mxlog/parsing/ImportLog.h" "src/parsing/transAtomic.cpp" "include/mxlog/parsing/transAtomic.h" "src/common/MonthlyActive.cpp" "include/mxlog/common/MonthlyActive.h" "include/mxlog/common/UsageRate.h" "src/common/UsageRate.cpp" "include/mxlog/common/EffectiveUsage.h" "src/common/EffectiveUsage.cpp")