/*
* @Author: Qianhua Liu
* @Date: 2024-01-12
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_MEASUREMENT_MEASURPARAM_H
#define LOCALMINMAX_MEASUREMENT_MEASURPARAM_H

#include "common/Math.h"

namespace localminmax::measurement {
class MeasureParam {
public:
    MeasureParam() = default;
    ~MeasureParam() = default;
    void setNeighborCheckDistance(double neighbor_check_distance);
    void setNeighborCheckTolerance(double neighbor_check_tolerance);
    void setLongFlatThreshold(double long_flat_threshold);
    void setAngleCheckTolerance(int64_t angle_check_tolerance);
    void setSameDirection(bool is_same_direction);
    double getNeighborCheckDistance() const;
    double getNeighborCheckTolerance() const;
    double getLongFlatThreshold() const;
    int64_t getAngleCheckTolerance() const;
    bool isSameDirection() const;
private:
    double m_neighbor_check_distance = 12;
    double m_neighbor_check_tolerance = 4;
    double m_long_flat_threshold = 100;
    int64_t m_angle_check_tolerance = 10;
    bool m_is_same_direction = true;
};

} // localminmax::measurement

#endif // LOCALMINMAX_MEASUREMENT_MEASURPARAM_H