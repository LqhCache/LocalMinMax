/*
* @Author: Qianhua Liu
* @Date: 2024-01-06
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#include "defectresolver/DefectResolver.h"

#include "common/BasePoint.h"

namespace localminmax::defectresolver {
DefectResolver::DefectResolver(const std::shared_ptr<MeasureResult> measure_result) :
    m_measure_result(measure_result) {}

bool DefectResolver::resolve(std::list<std::shared_ptr<Defect>>& defect_lists)
{
    
    return true;
}

} // localminmax::defectresolver