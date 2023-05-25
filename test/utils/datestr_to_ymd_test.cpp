/**
 * @file datestr_to_ymd_test.cpp
 * @author Michael Wrona
 * @date 2023-05-25
 * @copyright Copyright (c) 2023 Michael Wrona
 */

#include <utils/datestr_to_ymd.h>

#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

using sdp::utils::datestr_to_ymd;
using sdp::utils::datestr_to_ymd_t;

namespace {

TEST(DatestrToYmdTest, Test1) {
    const unsigned int exp_yr = 2023;
    const unsigned int exp_mo = 11;
    const unsigned int exp_dy = 17;
    const std::string ymd_str = "2023-11-17";

    unsigned int yr{};
    unsigned int mo{};
    unsigned int dy{};

    std::tie(yr, mo, dy) = datestr_to_ymd(ymd_str);

    EXPECT_EQ(exp_yr, yr);
    EXPECT_EQ(exp_mo, mo);
    EXPECT_EQ(exp_dy, dy);
}

TEST(DatestrToYmdTest, Test2) {
    const unsigned int exp_yr = 2019;
    const unsigned int exp_mo = 1;
    const unsigned int exp_dy = 30;
    const std::string ymd_str = "2019-1-30";

    unsigned int yr{};
    unsigned int mo{};
    unsigned int dy{};

    std::tie(yr, mo, dy) = datestr_to_ymd(ymd_str);

    EXPECT_EQ(exp_yr, yr);
    EXPECT_EQ(exp_mo, mo);
    EXPECT_EQ(exp_dy, dy);
}

TEST(DatestrToYmdTest, InvalidMonth) {
    unsigned int yr{};
    unsigned int mo{};
    unsigned int dy{};

    EXPECT_THROW({
        std::tie(yr, mo, dy) = datestr_to_ymd("2022-13-12");
    }, std::invalid_argument);
}

TEST(DatestrToYmdTest, InvalidDay) {
    unsigned int yr{};
    unsigned int mo{};
    unsigned int dy{};

    EXPECT_THROW({
        std::tie(yr, mo, dy) = datestr_to_ymd("2022-09-32");
    }, std::invalid_argument);
}

TEST(DatestrToYmdTest, InvalidDelim) {
    unsigned int yr{};
    unsigned int mo{};
    unsigned int dy{};

    EXPECT_THROW({
        std::tie(yr, mo, dy) = datestr_to_ymd("2022/05/21");
    }, std::invalid_argument);
}

// =================================================================================================
int main(int argc, char** argv) {
    ::testing::GTEST_FLAG(death_test_style) = "threadsafe";

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}
