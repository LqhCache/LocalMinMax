/*
* @Author: Qianhua Liu
* @Date: 2024-03-02
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_DEFECTRESOLVER_DEFECT_H
#define LOCALMINMAX_DEFECTRESOLVER_DEFECT_H

#include <vector>
#include <memory>

#include "common/BasePoint.h"

enum class DefectType {
    LINE,
    RECTANGLE
};

namespace localminmax::defectresolver {
class Defect {
public:
    using DoublePoint = common::BasePoint<double>;

    Defect() = default;
    Defect(int64_t id);
    ~Defect() = default;

    void appendPoint(const std::shared_ptr<DoublePoint>& point);
    void appendPoint(const DoublePoint& point);

private:
    std::vector<std::shared_ptr<DoublePoint>> m_defect_points = {};
    int64_t m_index = -1;
    DefectType m_defect_type = {};
};

} // localminmax::defectresolver

#endif //LOCALMINMAX_DEFECTRESOLVER_DEFECT_H