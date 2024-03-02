/*
* @Author: Qianhua Liu
* @Date: 2024-01-12
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_MEASUREMENT_MEASUREUNIT_H
#define LOCALMINMAX_MEASUREMENT_MEASUREUNIT_H

#include <bitset>
#include <memory>

#include "measurement/MeasurePoint.h"
#include "measurement/MeasureParam.h"
#include "measurement/MeasurePath.h"

namespace localminmax::measurement {
using MeasurePoint = localminmax::measurement::MeasurePoint;
using MeasureParam = localminmax::measurement::MeasureParam;

enum class MeasureUnitFlags {
    FLAT,
    LONG_FLAT,
    LOCAL_MIN,
    LOCAL_MAX,
    FORWARD_MIN,
    FORWARD_MAX,
    BACKWARD_MIN,
    BACKWARD_MAX
};

struct MeasurePointProperty {
    MeasurePointIter m_iter;
    MeasurePointIter m_mp_iter_end;
    std::bitset<4> m_prev_flags;
    std::bitset<4> m_next_flags;
    bool m_is_on_vertex;
    double dx;
    double dy;
};

class MeasureUnit {
public:
    MeasureUnit() = default;
    MeasureUnit(const MeasurePoint& point1, const MeasurePoint& point2, double size = 0);
    MeasureUnit(const MeasurePoint& point1, const MeasurePoint& point2, double size,
                bool is_point1_on_vertex, bool is_point2_on_vertex, 
                const MeasurePointIter& iter1, const MeasurePointIter& iter2,
                const MeasurePointIter& mp_iter1_end, const MeasurePointIter& mp_iter2_end);
    ~MeasureUnit() = default;
    const MeasurePoint& getPoint1() const;
    const MeasurePoint& getPoint2() const;
    const double getSize() const;

    void markMeasureUnitFlags();
    void markMeasurePointFlags(const MeasurePoint& point, const std::shared_ptr<MeasurePointProperty>& point_property);

    static void setMeasureParam(const MeasureParam& measure_param) 
    {
        m_measure_param = measure_param;
    }
    static const MeasureParam& getMeasureParam()
    {
        return m_measure_param;
    }
private:
    MeasurePointIter findQualifiedNeighbor(const MeasurePoint& point, 
                                           const std::shared_ptr<MeasurePointProperty>& point_property, bool is_forward);
    MeasurePointIter findFlatNeighbor(const MeasurePoint& point, const std::shared_ptr<MeasurePointProperty>& point_property,
                                      bool is_forward, bool is_break = true);
    void checkRightAngle(const MeasurePoint& point, const std::shared_ptr<MeasurePointProperty>& point_property, 
                         const MeasurePointIter& iter, bool is_forward, int64_t angle_tol);

    MeasurePoint m_point1; // from measure path1
    MeasurePoint m_point2; // from measure path2
    double m_size;
    std::shared_ptr<MeasurePointProperty> m_p1_property;
    std::shared_ptr<MeasurePointProperty> m_p2_property;
    std::bitset<8> m_flags;

    static MeasureParam m_measure_param;
};

MeasureParam MeasureUnit::m_measure_param = {};

} // localminmax::measurement

#endif // LOCALMINMAX_MEASUREMENT_MEASUREUNIT_H