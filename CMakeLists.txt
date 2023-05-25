cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(SpaceDataParser LANGUAGES CXX
    DESCRIPTION "Space data parser"
)

# ADD MODULES AND THIRD PARTY ======================================================================

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

include(FetchContent)

FetchContent_Declare(
    AriaCsvParser
    GIT_REPOSITORY https://github.com/AriaFallah/csv-parser.git
    GIT_TAG 4965c9f320d157c15bc1f5a6243de116a4caf101
)

FetchContent_MakeAvailable(AriaCsvParser)

# PROJECT CONFIGURATION ============================================================================
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# enable for clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# define compiler and preprocessor options
set(SDP_COMPILE_DEFINITIONS_DEBUG "")
set(SDP_COMPILE_DEFINITIONS_RELEASE "NDEBUG")

set(SDP_COMPILE_OPTIONS "-Wall;-Wextra;-Wpedantic;-Wshadow;-Wconversion;-Wdouble-promotion;-Wfloat-equal;-Wundef;-Wformat=2")
set(SDP_COMPILE_OPTIONS_DEBUG "${SDP_COMPILE_OPTIONS};-Werror;-g3;-O0;-Wcast-align;-Wcast-qual")
set(SDP_COMPILE_OPTIONS_RELEASE "${SDP_COMPILE_OPTIONS};-O1")

# library name
set(SDP_LIB "sdp")

# outputs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

# options
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# project folders
set(SRC_DIR ./src/)
set(INCL_DIR ./include/)

# BUILD LIBRARY ====================================================================================
# decide which lib type to build
if(BUILD_SHARED_LIBS)
    add_library(${SDP_LIB} SHARED)
else()
    add_library(${SDP_LIB} STATIC)
endif()

# get lib sources
file(GLOB SDP_SOURCES
    ${SRC_DIR}/*.cpp
    ${SRC_DIR}/utils/*.cpp
)

target_sources(${SDP_LIB} PRIVATE
    ${SDP_SOURCES}
)


# define compile stuff
target_compile_definitions(${SDP_LIB} PUBLIC $<$<CONFIG:DEBUG>:${SDP_COMPILE_DEFINITIONS_DEBUG}>)
target_compile_definitions(${SDP_LIB} PUBLIC $<$<CONFIG:RELEASE>:${SDP_COMPILE_DEFINITIONS_RELEASE}>)

target_compile_options(${SDP_LIB} PRIVATE $<$<CONFIG:DEBUG>:${SDP_COMPILE_OPTIONS_DEBUG}>)
target_compile_options(${SDP_LIB} PRIVATE $<$<CONFIG:RELEASE>:${SDP_COMPILE_OPTIONS_RELEASE}>)

target_include_directories(${SDP_LIB} PRIVATE
    ${INCL_DIR}
)

target_link_libraries(${SDP_LIB} PRIVATE
    AriaCsvParser
)

# INSTALL CONFIGURATION ============================================================================

# ADD TESTS ========================================================================================
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory("./test/")
endif()

# RESOURCES
#   https://decovar.dev/blog/2021/03/08/cmake-cpp-library/
#   https://cmake.org/cmake/help/latest/guide/tutorial/Selecting%20Static%20or%20Shared%20Libraries.html
