/**
 * @file CelesTrakEop.cpp
 * @author Michael Wrona
 * @date 2023-05-27
 */

#include <CelesTrakEop.h>
#include <sdp_defs.h>

#include <parser.hpp>

#include <fstream>
#include <stdexcept>
#include <cstddef>
#include <iostream>

#include <cstdlib>

namespace sdp {

/** @brief Number of CSV columns in CelesTrak EOP CSV files. */
static constexpr std::size_t CELESTRAK_CSV_COLS = 12;

enum EopColumn : std::size_t {
    DATE = 0,
    MJD,
    X,
    Y,
    DUT1,
    LOD,
    DPSI,
    DEPS,
    DX,
    DY,
    DAT,
    DATA_TYPE
};





CelesTrakEop::CelesTrakEop(const std::string& csv_file)
    :filename(csv_file)
{}

void CelesTrakEop::load() {
    if (filename.empty()) {
        throw std::invalid_argument("No file name specified.");
    }

    // open file
    std::ifstream file(filename, std::ifstream::in);

    if (!file.good()) {
        throw std::runtime_error("Error opening file.");
    }

    aria::csv::CsvParser parser(file);

    std::size_t row_num = 1;

    for (auto row_itr = ++parser.begin(); row_itr != parser.end(); ++row_itr) {
        row_num++;


        if (row_itr->size() != CELESTRAK_CSV_COLS) {
            // std::cerr << "Invalid number of rows in CSV file, row " << row_num << "\n";
            throw std::runtime_error("Invalid number of rows in CSV file, row " + std::to_string(row_num));
        }

        const std::string date = row_itr->at(EopColumn::DATE);

        double mjd = 2;
        try {
            // mjd = std::stod(row_itr->at(EopColumn::MJD));

            auto valid_double = [](const std::string& str) {
                char* end {};
                (void)std::strtod(str.c_str(), &end);

                if (end == str.c_str() || *end != '\0')
                    return false;

                return true;
            };
            // char* end {};
            // mjd = std::strtod(row_itr->at(EopColumn::MJD).c_str(), &end);
            if (!valid_double(row_itr->at(EopColumn::MJD)))
                throw std::runtime_error("fddfgdfg");
        }
        catch (const std::exception& e) {
            std::cerr << "Error parsing data in row " << row_num << ".\n";
        }

        std::cout << "MJD: " << mjd << "\n";
        mjd += 123;



    }

}

}
