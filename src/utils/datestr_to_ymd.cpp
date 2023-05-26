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

std::tuple<unsigned int, unsigned int, unsigned int> datestr_to_ymd(const std::string& datestr) {
    static const std::string date_format {"%Y-%m-%d"};  // date string format

    std::istringstream ss {datestr};
    std::tm tm_components {};
    ss >> std::get_time(&tm_components, date_format.c_str());

    if (!ss) {
        throw std::invalid_argument(
            "Could not convert " + datestr + " to " + date_format
        );
    }

    return std::make_tuple(
        static_cast<unsigned int>(tm_components.tm_year + 1900),  // yr
        static_cast<unsigned int>(tm_components.tm_mon + 1),  // mo
        static_cast<unsigned int>(tm_components.tm_mday)  // dy
    );
}

}  // namespace utils
}  // namespace sdp
