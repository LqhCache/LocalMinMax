/*
* @Author: Qianhua Liu
* @Date: 2024-01-06
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_DEFECTRESOLVER_DefectResolver_H
#define LOCALMINMAX_DEFECTRESOLVER_DefectResolver_H

#include <vector>
#include <memory>

#include "defectresolver/Defect.h"
#include "measurement/MeasureResult.h"

namespace localminmax::defectresolver {
using MeasureResult = measurement::MeasureResult;

class DefectResolver {
public:
    DefectResolver() = default;
    DefectResolver(const std::shared_ptr<MeasureResult> measure_result);
    ~DefectResolver() = default;

    bool resolve(std::list<std::shared_ptr<Defect>>& defect_lists);
private:
    std::shared_ptr<MeasureResult> m_measure_result = nullptr;
};

} // localminmax::defectresolver

#endif // LOCALMINMAX_DEFECTRESOLVER_DefectResolver_H