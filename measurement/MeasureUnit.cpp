/*
* @Author: Qianhua Liu
* @Date: 2024-01-12
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#include "common/GeometryAlgo.h"
#include "measurement/MeasureUnit.h"

namespace localminmax::measurement {
using localminmax::common::point2PointDistance;
using localminmax::common::doubleEqual;
using localminmax::common::DistanceType;
using localminmax::common::dot;

MeasureUnit::MeasureUnit(const MeasurePoint& point1, const MeasurePoint& point2, double size)
    : m_point1(point1), m_point2(point2), m_size(size) {}

MeasureUnit::MeasureUnit(const MeasurePoint& point1, const MeasurePoint& point2, double size,
                         bool is_point1_on_vertex, bool is_point2_on_vertex,
                         const MeasurePointIter& iter1, const MeasurePointIter& iter2,
                         const MeasurePointIter& mp_iter1_end, const MeasurePointIter& mp_iter2_end)
    : m_point1(point1), m_point2(point2), m_size(size)
{
    m_p1_property = std::make_shared<MeasurePointProperty>();
    m_p2_property = std::make_shared<MeasurePointProperty>();
    m_p1_property->m_iter = iter1;
    m_p1_property->m_is_on_vertex = is_point1_on_vertex;
    m_p1_property->m_mp_iter_end = mp_iter1_end;
    m_p1_property->dx = point2.x() - point1.x();
    m_p1_property->dy = point2.y() - point1.y();
    m_p2_property->m_iter = iter2;
    m_p2_property->m_is_on_vertex = is_point2_on_vertex;
    m_p2_property->m_mp_iter_end = mp_iter2_end;
    m_p2_property->dx = point1.x() - point2.x();
    m_p2_property->dy = point1.y() - point2.y();
    if (!m_point1.isPrimary()) {
        std::swap(m_point1, m_point2);
        std::swap(m_p1_property, m_p2_property);
    }
    markMeasureUnitFlags();
}

const MeasurePoint& MeasureUnit::getPoint1() const 
{
    return m_point1;
}

const MeasurePoint& MeasureUnit::getPoint2() const 
{
    return m_point2;
}

const double MeasureUnit::getSize() const 
{
    return m_size;
}

void MeasureUnit::markMeasureUnitFlags()
{
    if (doubleEqual(m_size, 0.0)) {
        // handle zero sized measurement unit
        
    }else {
        // handle non zero sized measurement unit
        markMeasurePointFlags(m_point1, m_p1_property);
        markMeasurePointFlags(m_point2, m_p2_property);
    }
}

void MeasureUnit::markMeasurePointFlags(const MeasurePoint& point, const std::shared_ptr<MeasurePointProperty>& point_property)
{
    
}

MeasurePointIter MeasureUnit::findQualifiedNeighbor(const MeasurePoint& point, 
                                                    const std::shared_ptr<MeasurePointProperty>& point_property, bool is_forward)
{
    const double eps = m_measure_param.getNeighborCheckTolerance();
    const auto& start_iter = point_property->m_iter;
    const auto& end_iter = point_property->m_mp_iter_end;
    for (MeasurePointIter iter = start_iter; iter != end_iter; is_forward ? ++iter : --iter) {
        if (point2PointDistance(*iter, point) > eps) {
            return iter;
        }
    }
    return end_iter;
}

MeasurePointIter MeasureUnit::findFlatNeighbor(const MeasurePoint& point, 
                                               const std::shared_ptr<MeasurePointProperty>& point_property, 
                                               bool is_forward, bool is_break)
{
    const double eps = m_measure_param.getNeighborCheckTolerance();
    const double long_flat_thre = m_measure_param.getLongFlatThreshold();
    const int64_t angle_tol = m_measure_param.getAngleCheckTolerance();
    const bool is_on_vertex = point_property->m_is_on_vertex;
    const auto& start_iter = (is_on_vertex | is_forward) ? point_property->m_iter : -- point_property->m_iter;
    const auto& end_iter = point_property->m_mp_iter_end;
    MeasurePointIter result = end_iter;
    MeasurePointIter iter = start_iter;
    for (; iter != end_iter; is_forward ? ++iter : --iter) {
        if (point2PointDistance(*iter, point) > eps) {
            break;
        }
    }
    for (; iter != end_iter; is_forward ? ++iter : --iter) {
        checkRightAngle(point, point_property, iter, is_forward, angle_tol);
        const auto& flags_bitset = is_forward ? point_property->m_next_flags : point_property->m_prev_flags;
        bool min = flags_bitset[static_cast<int8_t>(MeasurePointFlags::MIN)];
        bool max = flags_bitset[static_cast<int8_t>(MeasurePointFlags::MAX)];
        if (min || max) {
            return result;
        }
        result = iter;
        if (is_break && point2PointDistance(point, *iter, DistanceType::EUCLIDEAN_SQUARE) > long_flat_thre * long_flat_thre) {
            return result; // long enough
        }
    }
    return result;
}

void MeasureUnit::checkRightAngle(const MeasurePoint& point, const std::shared_ptr<MeasurePointProperty>& point_property, 
                                  const MeasurePointIter& iter, bool is_forward, int64_t angle_tol)
{
    double dx = point.x() - iter->x();
    double dy = point.y() - iter->y();
    double dot_value = dot(point_property->dx, point_property->dy, dx, dy);
    double dist_square = dot(dx, dy, dx, dy);
    if (dot_value * dot_value * (static_cast<int64_t>(1) << angle_tol) < dist_square) {
        // is right angle
        return ;
    }
    auto measure_point_flag = dot_value > 0 ? MeasurePointFlags::MAX : MeasurePointFlags::MIN;
    auto& flags_bitset = is_forward ? point_property->m_next_flags : point_property->m_prev_flags;
    flags_bitset.set(static_cast<int8_t>(measure_point_flag));
}

} // localminmax::measurement