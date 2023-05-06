/**
 * @file ymd_to_mjd.cpp
 * @author Michael Wrona
 * @date 2023-04-23
 * @copyright Copyright (c) 2023 Michael Wrona
 */

#include "utils/ymd_to_mjd.h"

#include <stdexcept>

namespace EopParser {
namespace EopUtils {

unsigned int ymd_to_mjd(unsigned int year, unsigned int month, unsigned int day) {
    if (month == 0 || month > 12)
    {
        throw std::domain_error("Invalid month number");
    }

    if (day == 0 || day > 31)
    {
        throw std::domain_error("Invalid day number");
    }

    // correct date components depending on month number
    if (month == 1 || month == 2)
    {
        year -= 1;
        month += 12;
    }

    const auto A = static_cast<unsigned int>(year / 100);
    const unsigned int B = 2 - A + static_cast<unsigned int>(A / 4);

    return static_cast<unsigned int>(365.25 * (year + 4716))
        + static_cast<unsigned int>(30.6001 * (month + 1))
        + day + B - 2401525U;  // -1524.5 - 2400000.5
}

}  // namespace EopUtils
}  // namespace EopParser
