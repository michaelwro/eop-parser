/**
 * @file sdp_defs.h
 * @author Michael Wrona
 * @date 2023-05-25
 * @copyright Copyright (c) 2023 Michael Wrona
 */

#ifndef SDP_SDPDEFS_H_
#define SDP_SDPDEFS_H_

namespace sdp {

/**
 * @brief EOP set fron CelesTrak data.
 */
struct celestrak_eop_t {
    double MJD;  ///< [days] Modified Julian date.
    double dUT1;  ///< [sec] UT1-UTC.
    double X;  ///< [arcsec] X (xp) pole coordinate (CIP -> IRP deflection).
    double Y;  ///< [arcsec] Y (yp) pole coordinate (CIP -> IRP deflection).
    double LOD;  ///< [sec] Length of day offset (excess length of day).
    double dX;  ///< [arcsec] X (xp) pole correction (celestial pole offset).
    double dY;  ///< [arcsec] Y (yp) pole correction (celestial pole offset).
    double dPsi;  ///< [arcsec] Nutation correction.
    double dEps;  ///< [arcsec] Obliquity of the ecliptic correction.
};

}  // namespace sdp

#endif  // SDP_SDPDEFS_H_
