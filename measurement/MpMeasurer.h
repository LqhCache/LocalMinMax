/*
* @Author: Qianhua Liu
* @Date: 2024-03-02
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_MEASUREMENT_MPMEASURER_H
#define LOCALMINMAX_MEASUREMENT_MPMEASURER_H

#include <vector>
#include <memory>

#include "measurement/MeasurePath.h"
#include "measurement/MeasureResult.h"
#include "measurement/MeasureParam.h"

namespace localminmax::measurement {

class MpMeasurer {
public:
    MpMeasurer() = default;
    MpMeasurer(const MeasureParam& measure_param);
    ~MpMeasurer() = default;
    bool measure(const std::shared_ptr<MeasurePath>& mp1, const std::shared_ptr<MeasurePath>& mp2, 
                 const std::shared_ptr<MeasureResult>& result);
private:
    bool measureAllAngle(const std::shared_ptr<MeasurePath>& mp1, const std::shared_ptr<MeasurePath>& mp2, 
                         const std::shared_ptr<MeasureResult>& result);
    bool measureFixedAngle(const std::shared_ptr<MeasurePath>& mp1, const std::shared_ptr<MeasurePath>& mp2, 
                           const std::shared_ptr<MeasureResult>& result);
    bool measurePerpendicular(const std::shared_ptr<MeasurePath>& mp1, const std::shared_ptr<MeasurePath>& mp2, 
                              const std::shared_ptr<MeasureResult>& result);
    MeasureParam m_measure_param;
};

} // localminmax::measurement

#endif // LOCALMINMAX_MEASUREMENT_MPMEASURER_H
