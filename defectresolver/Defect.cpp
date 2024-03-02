/*
* @Author: Qianhua Liu
* @Date: 2024-03-02
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#include "defectresolver/Defect.h"

namespace localminmax::defectresolver {
Defect::Defect(int64_t id) : m_index(id) {}

void Defect::appendPoint(const std::shared_ptr<DoublePoint>& point) 
{
    m_defect_points.emplace_back(point);
}

void Defect::appendPoint(const DoublePoint& point)
{
    m_defect_points.emplace_back(std::make_shared<DoublePoint>(point.x(), point.y()));
}

} // localminmax::defectresolver
