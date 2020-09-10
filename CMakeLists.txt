cmake_minimum_required(VERSION 3.10)
project(SampleAddIn)

set(CMAKE_CXX_STANDARD 17)
set(TARGET SampleAddIn)

option(CASE_INSENSITIVE "Case insensitive method names" OFF)
option(STATIC_CRT "Static CRT linkage" OFF)
option(OUT_PARAMS "Support output parameters" OFF)

list(APPEND SOURCES
        src/addin.def
        src/stdafx.h
        src/dllmain.cpp
        src/exports.cpp
        src/Component.cpp
        src/Component.h
        src/SampleAddIn.cpp
        src/SampleAddIn.h)

if (ANDROID)
    list(APPEND SOURCES
            src/jnienv.cpp
            src/jnienv.h)
endif ()

add_library(${TARGET} SHARED
        ${SOURCES})

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

if (WIN32 AND NOT MSVC)
    message(FATAL_ERROR "Must be compiled with MSVC on Windows")
endif ()

if (WIN32)
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

if (ANDROID)
    if (CMAKE_BUILD_TYPE STREQUAL Release)
        add_custom_command(TARGET ${TARGET} POST_BUILD
                COMMAND ${CMAKE_STRIP} ${CMAKE_SHARED_LIBRARY_PREFIX}${TARGET}${CMAKE_SHARED_LIBRARY_SUFFIX})
    endif ()
endif ()