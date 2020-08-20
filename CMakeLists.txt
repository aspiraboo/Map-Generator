cmake_minimum_required(VERSION 3.10)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(map)

add_subdirectory(src)
add_executable(map ${map_SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set_target_properties(map PROPERTIES CXX_STANDARD 11)
set_target_properties(map PROPERTIES CXX_STANDARD_REQUIRED ON)

if (${CMAKE_VERSION} VERSION_GREATER "3.16.0")
    target_precompile_headers(map PUBLIC src/otpch.h)
else ()
    include(cotire)
    set_target_properties(map PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "src/otpch.h")
    set_target_properties(map PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
    cotire(map)
endif ()

if (NOT WIN32)
    add_compile_options(-Wall -Werror -pipe -fvisibility=hidden)
endif ()

set(CMAKE_CXX_FLAGS_PERFORMANCE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")

if (CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-fno-strict-aliasing)
endif ()

### INTERPROCEDURAL_OPTIMIZATION ###
cmake_policy(SET CMP0069 NEW)
include(CheckIPOSupported)
check_ipo_supported(RESULT result OUTPUT error)
if (result)
    message(STATUS "IPO / LTO enabled")
    set_target_properties(map PROPERTIES INTERPROCEDURAL_OPTIMIZATION True)
else ()
    message(STATUS "IPO / LTO not supported: <${error}>")
endif ()
### END INTERPROCEDURAL_OPTIMIZATION ###