/**
 * @file datestr_to_ymd.cpp
 * @author Michael Wrona
 * @date 2023-05-25
 * @copyright Copyright (c) 2023 Michael Wrona
 */

#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>

#include <utils/datestr_to_ymd.h>

namespace sdp {
namespace utils {


static inline std::string invalid_str_error_msg(const std::string& input) {
    return std::string("Could not convert " + input + " to YY-mm-dd format.");
}

datestr_to_ymd_t datestr_to_ymd(const std::string& datestr) {
    static const std::string DATE_FORMAT {"%Y-%m-%d"};  // date string format

    std::istringstream ss {datestr};
    std::tm tm_components {};
    ss >> std::get_time(&tm_components, DATE_FORMAT.c_str());

    if (!ss) {
        throw std::invalid_argument(invalid_str_error_msg(datestr));
    }

    const unsigned int year = tm_components.tm_year + 1900;
    const unsigned int month = tm_components.tm_mon + 1;
    const unsigned int day = tm_components.tm_mday;

    return std::make_tuple(year, month, day);
}

}  // namespace utils
}  // namespace sdp
