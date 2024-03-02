/*
* @Author: Qianhua Liu
* @Date: 2024-01-06
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#include "measurement/MeasurePath.h"

namespace localminmax::measurement {
MeasurePath::MeasurePath(const std::shared_ptr<std::list<MeasurePoint>>& measure_path)
    : m_measure_path(measure_path) {}

bool MeasurePath::isMeasurePathEnd(const MeasurePointIter& iter) const
{
    return iter == m_measure_path->end();
}

} // localminmax::measurement