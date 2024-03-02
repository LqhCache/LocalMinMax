/*
* @Author: Qianhua Liu
* @Date: 2024-03-02
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
 (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#include "measurement/MpMeasurer.h"

namespace localminmax::measurement {
MpMeasurer::MpMeasurer(const MeasureParam& measure_param) :
    m_measure_param(measure_param) {}

bool MpMeasurer::measure(const std::shared_ptr<MeasurePath>& mp1, const std::shared_ptr<MeasurePath>& mp2, 
                         const std::shared_ptr<MeasureResult>& result) 
{
    const MeasureType& measure_type = m_measure_param.getMeasureType();
    switch (measure_type) {
    case MeasureType::ALL_ANGLE:
        return measureAllAngle(mp1, mp2, result);
    case MeasureType::FIXED_ANGLE:
        return measureFixedAngle(mp1, mp2, result);
    case MeasureType::PERPENDICULAR:
        return measurePerpendicular(mp1, mp2, result);
    default:
        return false;
    }
}

bool MpMeasurer::measureAllAngle(const std::shared_ptr<MeasurePath>& mp1, const std::shared_ptr<MeasurePath>& mp2, 
                                 const std::shared_ptr<MeasureResult>& result) 
{
    
}

bool MpMeasurer::measureFixedAngle(const std::shared_ptr<MeasurePath>& mp1, const std::shared_ptr<MeasurePath>& mp2, 
                                   const std::shared_ptr<MeasureResult>& result) 
{
    
}

bool MpMeasurer::measurePerpendicular(const std::shared_ptr<MeasurePath>& mp1, const std::shared_ptr<MeasurePath>& mp2, 
                                      const std::shared_ptr<MeasureResult>& result) 
{

}

} // localminmax::measurement