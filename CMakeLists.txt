cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(EopParser LANGUAGES CXX)

include(CTest)

# PROJECT CONFIGURATION ============================================================================
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# enable for clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# define compiler and preprocessor options
set(EOPPARSER_COMPILE_DEFINITIONS_DEBUG "")
set(EOPPARSER_COMPILE_DEFINITIONS_RELEASE "NDEBUG")

set(EOPPARSER_COMPILE_OPTIONS "-Wall;-Wextra;-Wpedantic;-Wshadow;-Wconversion;-Wdouble-promotion;-Wfloat-equal;-Wundef;-Wformat=2")
set(EOPPARSER_COMPILE_OPTIONS_DEBUG "${EOPPARSER_COMPILE_OPTIONS};-Werror;-g3;-O0;-Wcast-align;-Wcast-qual")
set(EOPPARSER_COMPILE_OPTIONS_RELEASE "${EOPPARSER_COMPILE_OPTIONS};-O1")

# library name
set(EOPPARSER_LIB "eopparser")
set(EOPPARSER_LIB_OUTPUT_DIR ${PROJECT_BINARY_DIR}/lib/)

# project folders
set(SRC_DIR "src/")
set(INCL_DIR "include/")

# ADD THIRD PARTY ==================================================================================

set(THIRD_PARTY_DIR "third-party/")
add_subdirectory(${THIRD_PARTY_DIR}/csv-parser)  # AriaCsvParser

# BUILD LIBRARY ====================================================================================

file(GLOB EOPPARSER_SOURCES
    ${SRC_DIR}/*.cpp
    ${SRC_DIR}/utils/*.cpp
)

add_library(${EOPPARSER_LIB} SHARED
    ${EOPPARSER_SOURCES}
)

target_compile_definitions(${EOPPARSER_LIB} PUBLIC "$<$<CONFIG:DEBUG>:${EOPPARSER_COMPILE_DEFINITIONS_DEBUG}>")
target_compile_definitions(${EOPPARSER_LIB} PUBLIC "$<$<CONFIG:RELEASE>:${EOPPARSER_COMPILE_DEFINITIONS_RELEASE}>")

target_compile_options(${EOPPARSER_LIB} PRIVATE "$<$<CONFIG:DEBUG>:${EOPPARSER_COMPILE_OPTIONS_DEBUG}>")
target_compile_options(${EOPPARSER_LIB} PRIVATE "$<$<CONFIG:RELEASE>:${EOPPARSER_COMPILE_OPTIONS_RELEASE}>")

target_include_directories(${EOPPARSER_LIB} PUBLIC
    ${INCL_DIR}
)

set_target_properties(${EOPPARSER_LIB} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${EOPPARSER_LIB_OUTPUT_DIR}
)

target_link_libraries(${EOPPARSER_LIB} PUBLIC
    AriaCsvParser
)

# ADD TESTS ========================================================================================
enable_testing()
add_subdirectory("./test/")
