/**
 * @file datestr_to_ymd.cpp
 * @author Michael Wrona
 * @date 2023-05-25
 * @copyright Copyright (c) 2023 Michael Wrona
 */

#include <utils/datestr_to_ymd.h>

#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace sdp {
namespace utils {


static inline std::string invalid_str_error_msg(const std::string& input) {
    return std::string("Could not convert " + input + " to YY-mm-dd format.");
}

std::tuple<unsigned int, unsigned int, unsigned int> datestr_to_ymd(const std::string& datestr) {
    static const std::string DATE_FORMAT {"%Y-%m-%d"};  // date string format

    std::istringstream ss {datestr};
    std::tm tm_components {};
    ss >> std::get_time(&tm_components, DATE_FORMAT.c_str());

    if (!ss) {
        throw std::invalid_argument(invalid_str_error_msg(datestr));
    }

    const auto year = static_cast<unsigned int>(tm_components.tm_year + 1900);
    const auto month = static_cast<unsigned int>(tm_components.tm_mon + 1);
    const auto day = static_cast<unsigned int>(tm_components.tm_mday);

    return std::make_tuple(year, month, day);
}

}  // namespace utils
}  // namespace sdp
