# GET GTEST ========================================================================================
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest/
    GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(googletest)


# MAKE TESTS =======================================================================================
link_directories(
    ${EOPPARSER_LIB_OUTPUT_DIR}
)

# test tools dir
set(EOPPARSER_TEST_DIR ${CMAKE_SOURCE_DIR}/test/)

# Make tests in this folder
set(TEST_EOPPARSER_EXEC eop_parser_test)
file(GLOB EOPPARSER_TEST_SRC
    ./*.cpp
    ./utils/*.cpp
)

add_executable(${TEST_EOPPARSER_EXEC}
    ${EOPPARSER_TEST_SRC}
)

target_include_directories(${TEST_EOPPARSER_EXEC} PUBLIC
    ${CMAKE_SOURCE_DIR}/${INCL_DIR}
    ${EOPPARSER_TEST_DIR}
)

target_link_libraries(${TEST_EOPPARSER_EXEC} PUBLIC
    ${EOPPARSER_LIB}
    GTest::gtest_main
)


# ADD TESTS ========================================================================================
add_test(NAME ${TEST_EOPPARSER_EXEC}
    COMMAND ${TEST_EOPPARSER_EXEC}
)
