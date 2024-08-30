cmake_minimum_required(VERSION 3.18.5)

project(AVToys)

add_subdirectory(3rdparty/zcf/)

#minimal require c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 编译输出详细信息
set(CMAKE_VERBOSE_MAKEFILE ON)
# 设置编译输出路径

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 设置msvc字符集
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

option(HCSDK_SUPPORT "Hikvison SDK Support" ON)
option(DHSDK_SUPPORT "DaHua SDK Support" ON)

if(HCSDK_SUPPORT)
    add_library(HCSDK STATIC IMPORTED)
    set_target_properties(HCSDK PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/HCSDK/include"
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/HCSDK/lib/HCNetSDK.lib"
    )
endif()

if(DHSDK_SUPPORT)
    add_library(DHSDK STATIC IMPORTED)
    set_target_properties(DHSDK PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/DHSDK/Include/Common"
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/DHSDK/Lib/Win64/dhnetsdk.lib"
    )
endif()

#Qt5 set
set(Qt5_DIR "D:\\Qt5.15.2\\5.15.2\\msvc2019_64\\lib\\cmake\\Qt5")
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(src)


