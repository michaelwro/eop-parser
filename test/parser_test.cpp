#include <gtest/gtest.h>

#include "parser.hpp"

#include <string>


namespace {

class CsvParsingTest : public ::testing::Test {
protected:
    CsvParsingTest() = default;
    ~CsvParsingTest() = default;

    void SetUp() override {

    }

    void TearDown() override {
        csv_stream.close();
    }

    const std::string test_file_directory = std::string(TEST_FILE_DIR);
    const std::string simple_csv_file {test_file_directory + "/" + "simple.csv"};

    std::ifstream csv_stream {simple_csv_file};
};



TEST_F(CsvParsingTest, Test1) {

    aria::csv::CsvParser parser(csv_stream);

    for (auto row_itr = ++parser.begin(); row_itr != parser.end(); ++row_itr) {
        for (auto& field : *row_itr) {
            std::cout << std::stod(field) << "|";
        }
        std::cout << "\n";
    }

}

// =================================================================================================
int main(int argc, char** argv) {
    ::testing::GTEST_FLAG(death_test_style) = "threadsafe";

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace
