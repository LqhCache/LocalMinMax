/*
* @Author: Qianhua Liu
* @Date: 2024-01-06
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_COMMON_GEOMETRYALGO_H
#define LOCALMINMAX_COMMON_GEOMETRYALGO_H

#include <iostream>

#include "common/BasePoint.h"
#include "common/Math.h"

namespace localminmax::common {
enum class IntersectionType {
    NO_INTERSECTION,
    NORMAL_INTERSECTION,
    INTERSECTION_AT_ENDPOINTS
};
enum class PointLineRelationship {
    ON_LEFT = c_bit1,
    ON_RIGHT = c_bit2,
    ON_LINE = c_bit3,
    ON_SEGMENT = c_bit4 | ON_LINE,
    ON_ENDPOINT = c_bit5 | ON_SEGMENT
};
enum class DistanceType {
    MANHATTAN,
    EUCLIDEAN,
    EUCLIDEAN_SQUARE
};

template<typename Point>
PointLineRelationship getPointLineRelationship(const Point& p, const Point& q_start, const Point& q_end) 
{
    if (p == q_start || p == q_end) {
        return PointLineRelationship::ON_ENDPOINT;
    }
    double qstart_p_turn_to_qstart_qend = cross(p - q_start, q_end - q_start);
    if (doubleEqual(0.0, qstart_p_turn_to_qstart_qend)) {
        // collinear
        double p_qstart_proj_to_p_qend = dot(q_start - p, q_end - p);
        if (doubleLessEqual(p_qstart_proj_to_p_qend, 0.0)) {
            return PointLineRelationship::ON_SEGMENT;
        }
        return PointLineRelationship::ON_LINE;
    }else if (doubleLess(qstart_p_turn_to_qstart_qend, 0.0)) {
        return PointLineRelationship::ON_LEFT;
    }else {
        return PointLineRelationship::ON_RIGHT;
    }
}

template<typename Point>
IntersectionType getIntersectionType(const Point& p1, const Point& p2, const Point& q1, const Point& q2)
{
    auto on_segment = [](const Point& p, const Point& _q1, const Point& _q2) {
        return static_cast<int32_t>(PointLineRelationship::ON_SEGMENT) &
               static_cast<int32_t>(getPointLineRelationship(p, _q1, _q2));
    };
    if (on_segment(p1, q1, q2) || on_segment(p2, q1, q2) || 
        on_segment(q1, p1, p2) || on_segment(q2, p1, p2)) {
        return IntersectionType::INTERSECTION_AT_ENDPOINTS;
    }
    double p1_p2_turn_to_p1_q1 = cross(p2 - p1, q1 - p1);
    double p1_p2_turn_to_p1_q2 = cross(p2 - p1, q2 - p1);
    double q1_q2_turn_to_q1_p1 = cross(q2 - q1, p1 - q1);
    double q1_q2_turn_to_q1_p2 = cross(q2 - q1, p2 - q1);
    if (oppositeSign(p1_p2_turn_to_p1_q1, p1_p2_turn_to_p1_q2) && 
        oppositeSign(q1_q2_turn_to_q1_p1, q1_q2_turn_to_q1_p2)) {
        return IntersectionType::NORMAL_INTERSECTION;
    }
    return IntersectionType::NO_INTERSECTION;
}

template<typename Point1, typename Point2>
double point2PointDistance(const Point1& p1, const Point2& p2, DistanceType distance_type = DistanceType::EUCLIDEAN)
{
    switch(distance_type) {
    case DistanceType::EUCLIDEAN: {
        return std::sqrt(dot(p1 - p2, p1 - p2));
    }
    case DistanceType::EUCLIDEAN_SQUARE: {
        return dot(p1 - p2, p1 - p2);
    }
    case DistanceType::MANHATTAN: {
        return std::fabs(p1.x() - p2.x()) + std::fabs(p1.y() - p2.y());
    }
    default: 
        return 0;
    }
}

} // localminmax::common

#endif // LOCALMINMAX_COMMON_GEOMETRYALGO_H