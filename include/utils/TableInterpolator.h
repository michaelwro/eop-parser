/**
 * @file TableInterpolator.h
 * @author Michael Wrona
 * @date 2023-05-29
 * @copyright Copyright (c) 2023 Michael Wrona
 */

#ifndef SDP_TABLE_INTERPOLATOR_H_
#define SDP_TABLE_INTERPOLATOR_H_

#include <utils/print.h>

#include <vector>
#include <algorithm>
#include <type_traits>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <array>

namespace sdp {
namespace utils {

template<typename T>
struct CubicSpline {
public:
    static_assert(std::is_floating_point<T>::value, "Floating-point types only.");

    CubicSpline() = default;

    T evaluate(const T x) const {
        // ENSURE THAT X IS LESS THAN X_UPPER
        const T h = x - x_lower;//get_h();
        return a + (b * h) + (c * h * h) + (d * h * h * h);
    }

    T get_h() {
        return x_upper - x_lower;
    }

    template<typename Ts>
    friend std::ostream& operator<<(std::ostream& os, const CubicSpline<Ts>& spline);

    T a {0};
    T b {0};
    T c {0};
    T d {0};
    T x_lower {0};
    T x_upper {0};
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const CubicSpline<T>& spline) {
    os << std::fixed << "x_lower: " << (spline.x_lower) << "\n"
        << "x_upper: " << (spline.x_upper) << "\n"
        << "a: " << (spline.a) << "\n"
        << "b: " << (spline.b) << "\n"
        << "c: " << (spline.c) << "\n"
        << "d: " << (spline.d) << "\n";

    return os;
}



template<typename T>
class TableInterpolator {
public:
    static_assert(std::is_floating_point<T>::value, "Floating-point types only.");

    TableInterpolator() = default;

    void generate(const std::vector<T>& x, const std::vector<T>& y) {
        // CHECK IF X AND Y AREN'T EMPTY
        // CHECK IF X AND Y ARE THE SAME SIZE
        // CHECK IF X/Y LENGTH IS GREATER THAN 4

        const std::size_t n = x.size() - 1;
        const std::size_t n_plus1 = n + 1;

        m_splines.clear();
        m_splines.reserve(n);

        std::vector<T> a(y);

        for (std::size_t ix = 0; ix < n; ix++) {
            CubicSpline<T> spline {};  // zero elements
            spline.a = y.at(ix);
            spline.x_lower = x.at(ix);
            spline.x_upper = x.at(ix + 1);
            m_splines.emplace_back(spline);
        }

        std::vector<T> alpha(n, 0);

        for (std::size_t ix = 1; ix < n; ix++) {
            alpha.at(ix) = 3.0 / m_splines.at(ix).get_h() * (a.at(ix+1) - a.at(ix))
                - 3.0 / m_splines.at(ix-1).get_h() * (a.at(ix) - a.at(ix-1));

            // std::cout << "IX: " << ix << "H: " << m_splines.at(ix).get_h() << "\n";
        }


        std::vector<T> c(n_plus1, 0);
        std::vector<T> L(n_plus1, 0);
        std::vector<T> u(n_plus1, 0);
        std::vector<T> z(n_plus1, 0);

        L.at(0) = 1.0;

        for (std::size_t ix = 1; ix < n; ix++) {
            L.at(ix) = 2.0 * (x.at(ix+1) - x.at(ix-1)) - m_splines.at(ix-1).get_h() * u.at(ix-1);
            u.at(ix) = m_splines.at(ix).get_h() / L.at(ix);
            z.at(ix) = (alpha.at(ix) - m_splines.at(ix-1).get_h() * z.at(ix-1)) / L.at(ix);
        }


        L.at(n) = 1;
        z.at(n) = 0;
        c.at(n) = 0;

        std::vector<T> b(n, 0);
        std::vector<T> d(n, 0);

        // NOTE: had to shift the indices w.r.t. the original to use unsinged std::size_t
        for (std::size_t ix = n; ix != 0; ix--) {
            c.at(ix-1) = z.at(ix-1) - u.at(ix-1) * c.at(ix);
            b.at(ix-1) = (a.at(ix) - a.at(ix-1)) / m_splines.at(ix-1).get_h()
                - (m_splines.at(ix-1).get_h() * (c.at(ix) + 2.0 * c.at(ix-1))) / 3.0;
            d.at(ix-1) = (c.at(ix) - c.at(ix-1)) / (3.0 * m_splines.at(ix-1).get_h());
        }

        assert(m_splines.size() == n);

        for (std::size_t ix = 0; ix < n; ix++) {
            m_splines.at(ix).a = a.at(ix);
            m_splines.at(ix).b = b.at(ix);
            m_splines.at(ix).c = c.at(ix);
            m_splines.at(ix).d = d.at(ix);
        }
    }

    T evaluate(const T x_val) const {
        auto spline_itr = std::find_if(
            m_splines.begin(), m_splines.end(),
            [x_val](const CubicSpline<T>& spline) {
                return (x_val > spline.x_lower) && (x_val < spline.x_upper);
            }
        );

        assert(spline_itr != m_splines.end());

        // std::cout << (*spline_itr);

        return spline_itr->evaluate(x_val);
    }

private:
    std::vector<CubicSpline<T>> m_splines {};
};

}  // namespace utils
}  // namespace sdp

#endif  // SDP_TABLE_INTERPOLATOR_H_
