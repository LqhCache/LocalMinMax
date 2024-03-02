/*
* @Author: Qianhua Liu
* @Date: 2024-01-12
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#include "measurement/MeasureResult.h"

namespace localminmax::measurement {
MeasureResult::MeasureResult(const std::vector<std::shared_ptr<MeasureUnit>>& measure_units)
    : m_measure_units(measure_units) {}

void MeasureResult::appendMeasureUnit(const std::shared_ptr<MeasureUnit>& measure_unit) 
{
    m_measure_units.emplace_back(measure_unit);
}

const std::vector<std::shared_ptr<MeasureUnit>>& MeasureResult::getMeasureResult() const
{
    return m_measure_units;
}

} // localminmax::measurement