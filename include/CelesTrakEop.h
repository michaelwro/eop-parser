/**
 * @file CelesTrakEop.h
 * @author Michael Wrona
 * @date 2023-05-27
 */

#ifndef SDP_CELESTRAK_EOP_H_
#define SDP_CELESTRAK_EOP_H_

#include <utils/TableInterpolator.h>

#include <string>

namespace sdp {

class CelesTrakEop {
public:
    CelesTrakEop() = default;
    ~CelesTrakEop() = default;
    CelesTrakEop(const CelesTrakEop& other) = default;
    CelesTrakEop(CelesTrakEop&& other) = default;
    CelesTrakEop& operator=(const CelesTrakEop& other) = default;
    CelesTrakEop& operator=(CelesTrakEop&& other) = default;


    explicit CelesTrakEop(const std::string& csv_file);

    void load();
    bool is_loaded() const {
        return m_loaded;
    }

    double get_x(const double mjd) const;

protected:
private:
    utils::TableInterpolator<double> m_x_interpolator;
    bool m_loaded {false};
    std::string m_filename {""};  ///< CSV file name and path.
    unsigned int m_table_start_mjd {0};  ///< EOP dataset beginning MJD.
    unsigned int m_table_end_mjd {0};  ///< EOP dataset end MJD.
};



}


#endif  // SDP_CELESTRAK_EOP_H_
