/**
 * @file CelesTrakEop.cpp
 * @author Michael Wrona
 * @date 2023-05-27
 */

#include <CelesTrakEop.h>

#include <parser.hpp>

#include <fstream>
#include <stdexcept>
#include <cstddef>
#include <iostream>

namespace sdp {

/** @brief Number of CSV columns in CelesTrak EOP CSV files. */
static constexpr std::size_t CELESTRAK_CSV_COLS = 12;

CelesTrakEop::CelesTrakEop(const std::string& csv_file)
    :filename(csv_file)
{}

void CelesTrakEop::load() {
    if (filename.empty()) {
        throw std::invalid_argument("No file name specified.");
    }
    // #region File stuff
    // open file
    std::ifstream file(filename, std::ifstream::in);

    if (!file.good()) {
        throw std::runtime_error("Error opening file.");
    }
    // #endregion

}

}
