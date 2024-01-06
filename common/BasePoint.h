/*
* @Author: Qianhua Liu
* @Date: 2024-01-06
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_COMMON_BASEPOINT_H
#define LOCALMINMAX_COMMON_BASEPOINT_H

namespace LocalMinMax::Common {

template<typename coordinate_type>
class BasePoint {
public:
    BasePoint() = default;
    BasePoint(coordinate_type x, coordinate_type y) : m_x(x), m_y(y) {}
    void setX(coordinate_type x)
    {
        m_x = x;
    }
    void setY(coordinate_type y)
    {
        m_y = y;
    }
    const coordinate_type x() const
    {
        return m_x;
    }
    const coordinate_type y() const
    {
        return m_y;
    }

private:
    coordinate_type m_x, m_y;
};

} // LocalMinMax::Common

#endif