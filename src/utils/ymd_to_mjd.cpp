/**
 * @file ymd_to_mjd.cpp
 * @author Michael Wrona
 * @date 2023-04-22
 */

#include <utils/ymd_to_mjd.h>

#include <cmath>
#include <stdexcept>

namespace EopUtils {

using int_type = unsigned int;

int_type ymd_to_mjd(int_type year, int_type month, int_type day) {
    if (month == 0 || month > 12) {
        throw std::domain_error("Invalid month number");
    }

    if (day == 0 || day > 31) {
        throw std::domain_error("Invalid day number");
    }

    // correct date components depending on month number
    if (month == 1) {
        year -= 1;
        month += 12;
    }
    else if (month == 2) {
        year -= 1;
        month += 12;
    }

    const auto A = static_cast<int_type>(year / 100);
    const int_type B = 2 - A + static_cast<int_type>(A / 4);

    return static_cast<int_type>(365.25 * (year + 4716))
        + static_cast<int_type>(30.6001 * (month + 1))
        + day + B - 2401525u;  // -1524.5 - 2'400'000.5
}

}  // namespace EopUtils
