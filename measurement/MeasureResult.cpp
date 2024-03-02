/*
* @Author: Qianhua Liu
* @Date: 2024-01-12
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#include "measurement/MeasureResult.h"

namespace localminmax::measurement {
MeasureResult::MeasureResult(const std::vector<std::shared_ptr<MeasureUnit>>& measure_result)
    : m_measure_result(measure_result) {}

const std::vector<std::shared_ptr<MeasureUnit>>& MeasureResult::getMeasureResult() const
{
    return m_measure_result;
}

} // localminmax::measurement