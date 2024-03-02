/*
* @Author: Qianhua Liu
* @Date: 2024-01-06
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_COMMON_BASEPOINT_H
#define LOCALMINMAX_COMMON_BASEPOINT_H

#include "common/Math.h"

namespace localminmax::common {

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
    bool operator<(const BasePoint& rhs) const 
    {
        if (doubleEqual(m_x, rhs.m_x)) {
            return doubleLess(m_y, rhs.m_y);
        }
        return doubleLess(m_x, rhs.m_x);
    }
    bool operator==(const BasePoint& rhs) const 
    {
        return doubleEqual(m_x, rhs.m_x) && doubleEqual(m_y, rhs.m_y);
    }
    bool operator>(const BasePoint& rhs) const 
    {
        if (doubleEqual(m_x, rhs.m_x)) {
            return doubleGreater(m_y, rhs.m_y);
        }
        return doubleGreater(m_x, rhs.m_x);
    }
    bool operator<=(const BasePoint& rhs) const 
    {
        return !(*this > rhs);
    }
    bool operator>=(const BasePoint& rhs) const 
    {
        return !(*this < rhs);
    }
    BasePoint operator-(const BasePoint& rhs) const 
    {
        return BasePoint(m_x - rhs.m_x, m_y - rhs.m_y);
    }
    BasePoint operator+(const BasePoint& rhs) const 
    {
        return BasePoint(m_x + rhs.m_x, m_y + rhs.m_y);
    }

private:
    coordinate_type m_x;
    coordinate_type m_y;
};

} // localminmax::common

#endif // LOCALMINMAX_COMMON_BASEPOINT_H