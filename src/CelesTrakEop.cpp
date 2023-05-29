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
#include <tuple>

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
    DAT
};


// using eop_row_t = std::tuple<double, double, double, double, double, double, double, double, double, double>;
using eop_row_t = std::tuple<double>;
static eop_row_t parse_row(const aria::csv::CsvParser::iterator& csv_row);




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

        double mjd {};

        std::tie(mjd) = parse_row(row_itr);

        // const std::string date = row_itr->at(EopColumn::DATE);



    }

}







eop_row_t parse_row(const aria::csv::CsvParser::iterator& csv_row) {

    auto validate_double_field = [](const std::string& val_str) {
        char* end {};
        const double val = std::strtod(val_str.c_str(), &end);

        if ((end == val_str.c_str()) || (*end != '\0')) {
            throw std::invalid_argument("Cound not convert CSV element to double.");
        }

        return val;
    };

    // MJD
    double mjd = validate_double_field(csv_row->at(EopColumn::MJD));

    return eop_row_t(mjd);
}

}
