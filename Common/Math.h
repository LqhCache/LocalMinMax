/*
* @Author: Qianhua Liu
* @Date: 2024-01-06
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_COMMON_MATH_H
#define LOCALMINMAX_COMMON_MATH_H

namespace LocalMinMax::Common {
using int16_t = short int;
using uint16_t = unsigned short int;
using int32_t = int;
using uint32_t = unsigned int;
using int64_t = long long;
using uint64_t = unsigned long long;

constexpr double default_eps = 1e-9;

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

template<typename T>
T cross(T x1, T y1, T x2, T y2) 
{
    return x1 * y2 - x2 * y1;
}

template<typename T>
T dot(T x1, T y1, T x2, T y2) 
{
    return x1 * y1 + x2 * y2;
}

template<typename Point>
double cross(Point p1, Point p2) 
{
    return static_cast<double>(p1.x()) * static_cast<double>(p2.y()) - 
           static_cast<double>(p2.x()) * static_cast<double>(p1.y());
}

template<typename Point>
double dot(Point p1, Point p2)
{
    return static_cast<double>(p1.x()) * static_cast<double>(p2.x()) + 
           static_cast<double>(p1.y()) * static_cast<double>(p2.y());
}

} // LocalMinMax::Common

#endif