#include <CelesTrakEop.h>

#include <gtest/gtest.h>

#include <stdexcept>

namespace {

// TEST(CelesTrakEopTest, NoFilename) {

//     sdp::CelesTrakEop parser;

//     EXPECT_THROW({
//         parser.load();
//     }, std::invalid_argument);

// }

// TEST(CelesTrakEopTest, InvalidFilename) {

//     sdp::CelesTrakEop parser("sdsdsgdffgdfg");

//     EXPECT_THROW({
//         parser.load();
//     }, std::runtime_error);
// }

TEST(CelesTrakEopTest, ForReal) {

    const std::string test_file_directory = std::string(TEST_FILE_DIR);
    const std::string celestrak_csv {test_file_directory + "/" + "celestrak_short.csv"};

    sdp::CelesTrakEop parser(celestrak_csv);

    parser.load();

}


// =================================================================================================
int main(int argc, char** argv) {
    ::testing::GTEST_FLAG(death_test_style) = "threadsafe";

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace
