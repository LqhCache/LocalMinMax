/*
* @Author: Qianhua Liu
* @Date: 2024-01-06
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_MEASUREMENT_MEASUREPATH_H
#define LOCALMINMAX_MEASUREMENT_MEASUREPATH_H

#include <memory>

#include "measurement/MeasureUnit.h"

namespace localminmax::measurement {
class MeasurePath {
public:
    MeasurePath() = default;
    MeasurePath(const std::shared_ptr<std::list<MeasurePoint>>& measure_path);
    ~MeasurePath() = default;
    bool isMeasurePathEnd(const MeasurePointIter& iter) const;
private:
    std::shared_ptr<std::list<MeasurePoint>> m_measure_path = nullptr;
};

} // localminmax::measurement

#endif // LOCALMINMAX_MEASUREMENT_MEASUREPATH_H
