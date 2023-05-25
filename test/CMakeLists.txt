# GET GTEST ========================================================================================
include(CTest)
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest/
    GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(googletest)


# MAKE TESTS =======================================================================================
link_directories(
    ${SDP_LIB_OUTPUT_DIR}
)

# test tools dir
set(SDP_TEST_DIR ${CMAKE_SOURCE_DIR}/test/)

# Make tests in this folder
set(TEST_SDP_EXEC sdp_test)
file(GLOB SDP_TEST_SRC
    ./*.cpp
    ./utils/*.cpp
)

add_executable(${TEST_SDP_EXEC}
    ${SDP_TEST_SRC}
)

target_include_directories(${TEST_SDP_EXEC} PUBLIC
    ${CMAKE_SOURCE_DIR}/${INCL_DIR}
    ${SDP_TEST_DIR}
)

target_link_libraries(${TEST_SDP_EXEC} PUBLIC
    ${SDP_LIB}
    GTest::gtest_main
    AriaCsvParser
)

# define directory where test data files are located
target_compile_definitions(${TEST_SDP_EXEC} PRIVATE
    "TEST_FILE_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/data/\""
)

# ADD TESTS ========================================================================================
add_test(NAME ${TEST_SDP_EXEC}
    COMMAND ${TEST_SDP_EXEC}
)
