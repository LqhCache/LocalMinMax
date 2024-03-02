/*
* @Author: Qianhua Liu
* @Date: 2024-01-06
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_MEASUREMENT_MEASUREPOINT_H
#define LOCALMINMAX_MEASUREMENT_MEASUREPOINT_H

#include <list>
#include <memory>

#include "common/BasePoint.h"
#include "common/Math.h"

namespace localminmax::measurement {

enum class MeasurePointFlags {
    MIN,
    MAX,
    FLAT
};

class MeasurePoint : public localminmax::common::BasePoint<int64_t> {
public:
    MeasurePoint() = default;
    ~MeasurePoint() = default;
    void setIsPrimary(bool is_primary);
    bool isPrimary() const;
private:
    bool m_is_dt;
    bool m_is_primary;
    bool m_is_external;
};

using MeasurePointIter = std::list<MeasurePoint>::iterator;

} // localminmax::measurement

#endif // LOCALMINMAX_MEASUREMENT_MEASUREPOINT_H