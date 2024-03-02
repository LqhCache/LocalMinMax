/*
* @Author: Qianhua Liu
* @Date: 2024-01-12
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#include "measurement/MeasureParam.h"

namespace localminmax::measurement {
void MeasureParam::setNeighborCheckDistance(double neighbor_check_distance)
{
    m_neighbor_check_distance = neighbor_check_distance;
}

void MeasureParam::setNeighborCheckTolerance(double neighbor_check_tolerance)
{
    m_neighbor_check_tolerance = neighbor_check_tolerance;
}

void MeasureParam::setLongFlatThreshold(double long_flat_threshold)
{
    m_long_flat_threshold = long_flat_threshold;
}

void MeasureParam::setAngleCheckTolerance(int64_t angle_check_tolerance)
{
    m_angle_check_tolerance = angle_check_tolerance;
}

void MeasureParam::setSameDirection(bool is_same_direction)
{
    m_is_same_direction = is_same_direction;
}

double MeasureParam::getNeighborCheckDistance() const
{
    return m_neighbor_check_distance;
}

double MeasureParam::getNeighborCheckTolerance() const
{
    return m_neighbor_check_tolerance;
}

double MeasureParam::getLongFlatThreshold() const
{
    return m_long_flat_threshold;
}

int64_t MeasureParam::getAngleCheckTolerance() const
{
    return m_angle_check_tolerance;
}

bool MeasureParam::isSameDirection() const
{
    return m_is_same_direction;
}

} // localminmax::measurement