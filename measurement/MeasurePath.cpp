/*
* @Author: Qianhua Liu
* @Date: 2024-01-06
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#include "measurement/MeasurePath.h"

namespace localminmax::measurement {
MeasurePath::MeasurePath(const std::shared_ptr<std::list<MeasurePoint>>& measure_points)
    : m_measure_points(measure_points) {}

void MeasurePath::setIsPrimary(bool is_primary)
{
    m_is_primary = is_primary;
}

void MeasurePath::setIsDt(bool is_dt) 
{
    m_is_dt = is_dt;
}

bool MeasurePath::isPrimary() const
{
    return m_is_primary;
}

bool MeasurePath::isDt() const
{
    return m_is_dt;
}

bool MeasurePath::isMeasurePathEnd(const MeasurePointIter& iter) const
{
    return iter == m_measure_points->end();
}

} // localminmax::measurement