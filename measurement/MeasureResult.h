/*
* @Author: Qianhua Liu
* @Date: 2024-01-12
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_MEASUREMENT_MEASURERESULT_H
#define LOCALMINMAX_MEASUREMENT_MEASURERESULT_H

#include <vector>
#include <memory>

#include "measurement/MeasureUnit.h"

namespace localminmax::measurement {
class MeasureResult {
public:
    MeasureResult() = default;
    MeasureResult(const std::vector<std::shared_ptr<MeasureUnit>>& measure_units);
    ~MeasureResult() = default;
    void appendMeasureUnit(const std::shared_ptr<MeasureUnit>& measure_unit);
    const std::vector<std::shared_ptr<MeasureUnit>>& getMeasureResult() const;
private:
    std::vector<std::shared_ptr<MeasureUnit>> m_measure_units = {};
};

} // localminmax::measurement

#endif // LOCALMINMAX_MEASUREMENT_MEASURERESULT_H
