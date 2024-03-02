/*
* @Author: Qianhua Liu
* @Date: 2024-01-06
* @Description:
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#include "measurement/MeasurePoint.h"

namespace localminmax::measurement {
void MeasurePoint::setIsPrimary(bool is_primary)
{
    m_is_primary = is_primary;
}

bool MeasurePoint::isPrimary() const
{
    return m_is_primary;
}

} // localminmax::measurement