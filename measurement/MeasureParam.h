/*
* @Author: Qianhua Liu
* @Date: 2024-01-12
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_MEASUREMENT_MEASURPARAM_H
#define LOCALMINMAX_MEASUREMENT_MEASURPARAM_H

#include "common/Math.h"
#include "common/BasePoint.h"

namespace localminmax::measurement {
using DoublePoint = common::BasePoint<double>;

enum class MeasureType {
    FIXED_ANGLE,
    ALL_ANGLE,
    PERPENDICULAR
};

class MeasureParam {
public:
    MeasureParam() = default;
    ~MeasureParam() = default;

    void setNeighborCheckDistance(double neighbor_check_distance);
    void setNeighborCheckTolerance(double neighbor_check_tolerance);
    void setLongFlatThreshold(double long_flat_threshold);
    void setAngleCheckTolerance(int64_t angle_check_tolerance);
    void setSameDirection(bool is_same_direction);
    void setMeasureType(const MeasureType& measure_type);
    void setMeasureVector(const DoublePoint& measure_vector);

    double getNeighborCheckDistance() const;
    double getNeighborCheckTolerance() const;
    double getLongFlatThreshold() const;
    int64_t getAngleCheckTolerance() const;
    bool isSameDirection() const;
    MeasureType getMeasureType() const;
    const DoublePoint& getMeasureVector() const;

private:
    double m_neighbor_check_distance = 12;
    double m_neighbor_check_tolerance = 4;
    double m_long_flat_threshold = 100;
    int64_t m_angle_check_tolerance = 10;
    bool m_is_same_direction = true;
    DoublePoint m_measure_vector = {};
    MeasureType m_measure_type = {};
};

} // localminmax::measurement

#endif // LOCALMINMAX_MEASUREMENT_MEASURPARAM_H