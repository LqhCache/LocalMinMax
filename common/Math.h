/*
* @Author: Qianhua Liu
* @Date: 2024-01-06
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#include <math.h>

#ifndef LOCALMINMAX_COMMON_MATH_H
#define LOCALMINMAX_COMMON_MATH_H

namespace localminmax::common {
using int16_t = short int;
using uint16_t = unsigned short int;
using int32_t = int;
using uint32_t = unsigned int;
using int64_t = long long;
using uint64_t = unsigned long long;

constexpr double default_eps = 1e-9;
constexpr int64_t c_bit1 = static_cast<int64_t>(1) << 0;
constexpr int64_t c_bit2 = static_cast<int64_t>(1) << 1;
constexpr int64_t c_bit3 = static_cast<int64_t>(1) << 2;
constexpr int64_t c_bit4 = static_cast<int64_t>(1) << 3;
constexpr int64_t c_bit5 = static_cast<int64_t>(1) << 4;
constexpr int64_t c_bit6 = static_cast<int64_t>(1) << 5;
constexpr int64_t c_bit7 = static_cast<int64_t>(1) << 6;
constexpr int64_t c_bit8 = static_cast<int64_t>(1) << 7;

bool doubleLess(double a, double b, double eps = default_eps) 
{
    return a - b < -eps;
}

bool doubleLessEqual(double a, double b, double eps = default_eps)
{
    return a - b <= eps;
}

bool doubleEqual(double a, double b, double eps = default_eps) 
{
    return std::fabs(a - b) <= eps;
}

bool doubleGreater(double a, double b, double eps = default_eps)
{
    return a - b > eps;
}

bool doubleGreaterEqual(double a, double b, double eps = default_eps) 
{
    return a - b >= -eps;
}

bool oppositeSign(double a, double b, double eps = default_eps) 
{
    return (doubleLess(a, 0.0) && doubleGreater(b, 0.0)) || 
           (doubleGreater(a, 0.0) && doubleLess(b, 0.0));
}

bool sameSign(double a, double b, double eps = default_eps) 
{
    return (doubleLess(a, 0.0) && doubleLess(b, 0.0)) || 
           (doubleGreater(a, 0.0) && doubleGreater(b, 0.0));
}

template<typename T>
T cross(T x1, T y1, T x2, T y2) 
{
    return x1 * y2 - x2 * y1;
}

template<typename T>
T dot(T x1, T y1, T x2, T y2) 
{
    return x1 * x2 + y1 * y2;
}

template<typename Point>
double cross(Point p1, Point p2) 
{
    return cross<double>(p1.x(), p1.y(), p2.x(), p2.y());
}

template<typename Point>
double dot(Point p1, Point p2)
{
    return dot<double>(p1.x(), p1.y(), p2.x(), p2.y());
}

} // localminmax::common

#endif