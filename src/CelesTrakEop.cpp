/**
 * @file CelesTrakEop.cpp
 * @author Michael Wrona
 * @date 2023-05-27
 */

#include <CelesTrakEop.h>

#include <utils/print.h>
#include <sdp_defs.h>

#include <parser.hpp>

#include <fstream>
#include <stdexcept>
#include <cstddef>
#include <iostream>
#include <tuple>
#include <cstdlib>
#include <iomanip>

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
using eop_row_t = std::tuple<double, double>;
static eop_row_t parse_row(const aria::csv::CsvParser::iterator& csv_row);




CelesTrakEop::CelesTrakEop(const std::string& csv_file)
    :m_filename(csv_file)
{}

void CelesTrakEop::load() {
    if (m_filename.empty()) {
        throw std::invalid_argument("No file name specified.");
    }

    // open file
    std::ifstream file(m_filename, std::ifstream::in);

    if (!file.good()) {
        file.close();
        throw std::runtime_error("Error opening file.");
    }

    aria::csv::CsvParser parser(file);

    std::size_t row_num = 1;

    std::vector<double> mjd {};
    std::vector<double> x {};

    for (auto row_itr = ++parser.begin(); row_itr != parser.end(); ++row_itr) {
        row_num++;


        if (row_itr->size() != CELESTRAK_CSV_COLS) {
            // std::cerr << "Invalid number of rows in CSV file, row " << row_num << "\n";
            file.close();
            throw std::runtime_error("Invalid number of rows in CSV file, row " + std::to_string(row_num));
        }

        double mjd_parsed {};
        double x_parsed {};
        std::tie(mjd_parsed, x_parsed) = parse_row(row_itr);

        mjd.emplace_back(mjd_parsed);
        x.emplace_back(x_parsed);
    }

    // std::cout << "X:\n";
    // utils::print(x);

    m_loaded = true;
    m_x_interpolator.generate(mjd, x);
    // utils::TableInterpolator<double> interp;
    // interp.generate(mjd, x);

    // double res = interp.evaluate(58119.5);
    // std::cout << std::fixed << "\n\nRESULT: " << res << "\n";

}


double CelesTrakEop::get_x(const double mjd) const {
    if (!m_loaded) {
        throw std::runtime_error("Table not yet loaded.");
    }

    return m_x_interpolator.evaluate(mjd);
}






eop_row_t parse_row(const aria::csv::CsvParser::iterator& csv_row) {

    auto validate_double_field = [](const std::string& val_str) {
        char* end {};
        const double val = std::strtod(val_str.c_str(), &end);

        if ((end == val_str.c_str()) || (*end != '\0')) {
            throw std::runtime_error("Cound not convert CSV element to double.");
        }

        return val;
    };

    // MJD
    double mjd = validate_double_field(csv_row->at(EopColumn::MJD));
    double x = validate_double_field(csv_row->at(EopColumn::X));

    return eop_row_t(mjd, x);
}

}
