#include <CelesTrakEop.h>

#include <gtest/gtest.h>

#include <stdexcept>
#include <fstream>

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
    const std::string celestrak_csv {test_file_directory + "/" + "celestrak_1yr_1mo.csv"};

    sdp::CelesTrakEop parser(celestrak_csv);

    parser.load();

    constexpr double mjd_start = 58119.1;
    constexpr double mjd_end = 58453.0-0.1;
    constexpr std::size_t n = 365;
    constexpr double dt = (mjd_end - mjd_start) / n;

    std::vector<double> mjd {};
    for (std::size_t ix = 0; ix < n; ix++) {
        mjd.emplace_back(mjd_start + (static_cast<double>(ix) * dt));
    }

    std::vector<double> x {};
    for (std::size_t ix = 0; ix < n; ix++) {
        x.emplace_back(parser.get_x(mjd.at(ix)));

    }

    std::fstream os("interp_data.csv", std::ios::out);
    os << "MJD,X\n";
    for (std::size_t ix = 0; ix < n; ix++) {
        os << std::fixed << mjd.at(ix) << "," << x.at(ix) << "\n";
    }

    os.close();




}


// =================================================================================================
int main(int argc, char** argv) {
    ::testing::GTEST_FLAG(death_test_style) = "threadsafe";

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace
