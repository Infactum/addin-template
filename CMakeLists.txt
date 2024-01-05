cmake_minimum_required(VERSION 3.10)
project(SampleAddIn)

set(CMAKE_CXX_STANDARD 17)
set(TARGET SampleAddIn)
set(ATTACH_TYPE "ANY" CACHE STRING "Attach type: ISOLATED | NOT_ISOLATED | ANY (default)")

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

set(ATTACH_TYPE_ANY 0)
set(ATTACH_TYPE_ISOLATED 1)
set(ATTACH_TYPE_NOT_ISOLATED 2)

target_compile_definitions(${TARGET} PRIVATE ATTACH_TYPE_ANY=${ATTACH_TYPE_ANY})
target_compile_definitions(${TARGET} PRIVATE ATTACH_TYPE_ISOLATED=${ATTACH_TYPE_ISOLATED})
target_compile_definitions(${TARGET} PRIVATE ATTACH_TYPE_NOT_ISOLATED=${ATTACH_TYPE_NOT_ISOLATED})

if (${ATTACH_TYPE} STREQUAL "ANY")
    set(ATTACH_TYPE ${ATTACH_TYPE_ANY})
elseif (${ATTACH_TYPE} STREQUAL "ISOLATED")
    set(ATTACH_TYPE ${ATTACH_TYPE_ISOLATED})
elseif (${ATTACH_TYPE} STREQUAL "NOT_ISOLATED")
    set(ATTACH_TYPE ${ATTACH_TYPE_NOT_ISOLATED})
else()
    message(FATAL_ERROR "Unrecognized ATTACH_TYPE ${ATTACH_TYPE}")
endif ()

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
    # https://stackoverflow.com/questions/11040133/what-does-defining-win32-lean-and-mean-exclude-exactly
    target_compile_definitions(${TARGET} PRIVATE
            _WINDOWS
            _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING WIN32_LEAN_AND_MEAN)
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