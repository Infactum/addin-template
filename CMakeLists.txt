cmake_minimum_required(VERSION 3.12)
project(SampleAddIn)

set(CMAKE_CXX_STANDARD 17)
set(TARGET SampleAddIn)

option(CASE_INSENSITIVE "Case insensitive method names" OFF)
option(STATIC_CRT "Static CRT linkage" OFF)
option(OUT_PARAMS "Support output parameters" OFF)

add_library(${TARGET} SHARED
        src/addin.def
        src/stdafx.h
        src/Component.cpp
        src/Component.h
        src/Library.cpp
        src/SampleAddIn.cpp
        src/SampleAddIn.h)

target_compile_definitions(${TARGET} PRIVATE
        UNICODE
        _UNICODE)

if (CASE_INSENSITIVE)
    target_compile_definitions(${TARGET} PRIVATE CASE_INSENSITIVE)
endif ()

if (OUT_PARAMS)
    target_compile_definitions(${TARGET} PRIVATE OUT_PARAMS)
endif ()

target_include_directories(${TARGET} PRIVATE
        include)

if (MSVC)
    if (STATIC_CRT)
        string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
        string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    endif ()
    target_compile_definitions(${TARGET} PRIVATE
            _WINDOWS
            _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)
    target_compile_options(${TARGET} PRIVATE /utf-8)
endif ()

if (UNIX)
    if (TARGET_ARCH STREQUAL "x86")
        set(CMAKE_C_FLAGS "-m32 ${CMAKE_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "-m32 ${CMAKE_CXX_FLAGS}")
    endif ()
endif ()