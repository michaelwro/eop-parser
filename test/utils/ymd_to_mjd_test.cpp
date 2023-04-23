/**
 * @file ymd_to_mjd_test.cpp
 * @author Michael Wrona
 * @date 2023-04-23
 */

#include <gtest/gtest.h>

#include <utils/ymd_to_mjd.h>

#include <stdexcept>
#include <string>

using EopParser::EopUtils::ymd_to_mjd;

namespace {

const std::string test_reports_file = std::string("ymd_to_mjd.xml");

/**
 * NOTE: Generated test cases from this utility: http://www.csgnetwork.com/julianmodifdateconv.html
 */

// =================================================================================================
TEST(YmdToMjdTest, Test1)
{
    EXPECT_EQ(ymd_to_mjd(2023, 4, 23), 60057);
}

TEST(YmdToMjdTest, Test2)
{
    EXPECT_EQ(ymd_to_mjd(2020, 1, 4), 58852);
}

TEST(YmdToMjdTest, Test3)
{
    EXPECT_EQ(ymd_to_mjd(1981, 2, 12), 44647);
}

TEST(YmdToMjdTest, Test4)
{
    EXPECT_EQ(ymd_to_mjd(2020, 10, 3), 59125);
}

TEST(YmdToMjdTest, CatchesBadDateInputs)
{
    EXPECT_THROW({
        ymd_to_mjd(2021, 14, 1);  // bad month
    }, std::domain_error);

    EXPECT_THROW({
        ymd_to_mjd(2021, 7, 33);  // bad day
    }, std::domain_error);
}


// =================================================================================================
int main(int argc, char** argv)
{
    ::testing::GTEST_FLAG(output) = std::string("xml:") + test_reports_file;
    ::testing::GTEST_FLAG(death_test_style) = "threadsafe";

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace

