/**
 * @file eop_defs.h
 * @author Michael Wrona
 * @date 2023-04-23
 * @copyright Copyright (c) 2023 Michael Wrona
 */

#ifndef EOPPARSER_EOP_DEFS_H_
#define EOPPARSER_EOP_DEFS_H_

namespace EopParser {

/**
 * @brief EOP set fron CelesTrak data.
 */
struct celestrak_data_t
{
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

}  // namespace EopParser

#endif  // EOPPARSER_EOP_DEFS_H_
