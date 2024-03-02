/*
* @Author: Qianhua Liu
* @Date: 2024-03-02
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#include "common/Math.h"

namespace localminmax::common {
bool doubleLess(double a, double b, double eps) 
{
    return a - b < -eps;
}

bool doubleLessEqual(double a, double b, double eps)
{
    return a - b <= eps;
}

bool doubleEqual(double a, double b, double eps) 
{
    return std::fabs(a - b) <= eps;
}

bool doubleGreater(double a, double b, double eps)
{
    return a - b > eps;
}

bool doubleGreaterEqual(double a, double b, double eps) 
{
    return a - b >= -eps;
}

bool oppositeSign(double a, double b, double eps) 
{
    return (doubleLess(a, 0.0) && doubleGreater(b, 0.0)) || 
           (doubleGreater(a, 0.0) && doubleLess(b, 0.0));
}

bool sameSign(double a, double b, double eps) 
{
    return (doubleLess(a, 0.0) && doubleLess(b, 0.0)) || 
           (doubleGreater(a, 0.0) && doubleGreater(b, 0.0));
}

} // localminmax::common