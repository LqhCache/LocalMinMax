/*
* @Author: Qianhua Liu
* @Date: 2024-01-07
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#include <gtest/gtest.h>

#include "common/GeometryAlgo.h"

namespace localminmax::common::unittest {
using Int64Point = localminmax::common::BasePoint<int64_t>;

TEST(getPointLineRelationship, testPointLineRelationship)
{
    {
        Int64Point p(0, 0);
        Int64Point q_start(-1, 1);
        Int64Point q_end(0, 0);
        EXPECT_EQ(getPointLineRelationship(p, q_start, q_end), PointLineRelationship::ON_ENDPOINT);
    }
    {
        Int64Point p(0, 0);
        Int64Point q_start(-1, 1);
        Int64Point q_end(1, -1);
        EXPECT_EQ(getPointLineRelationship(p, q_start, q_end), PointLineRelationship::ON_SEGMENT);
    }
    {
        Int64Point p(0, 0);
        Int64Point q_start(-1, 1);
        Int64Point q_end(-3, 3);
        EXPECT_EQ(getPointLineRelationship(p, q_start, q_end), PointLineRelationship::ON_LINE);
    }
    {
        Int64Point p(0, 0);
        Int64Point q_start(1, 0);
        Int64Point q_end(1, 1);
        EXPECT_EQ(getPointLineRelationship(p, q_start, q_end), PointLineRelationship::ON_LEFT);
    }
    {
        Int64Point p(0, 0);
        Int64Point q_start(-1, 0);
        Int64Point q_end(-1, 1);
        EXPECT_EQ(getPointLineRelationship(p, q_start, q_end), PointLineRelationship::ON_RIGHT);
    }
}

TEST(getIntersectionType, testIntersectionType) 
{
    {
        Int64Point p1(0, 0);
        Int64Point p2(1, 0);
        Int64Point q1(0, 0);
        Int64Point q2(0, 1);
        EXPECT_EQ(getIntersectionType(p1, p2, q1, q2), IntersectionType::INTERSECTION_AT_ENDPOINTS);
    }
    {
        Int64Point p1(-1, 1);
        Int64Point p2(1, -1);
        Int64Point q1(1, 1);
        Int64Point q2(-1, -1);
        EXPECT_EQ(getIntersectionType(p1, p2, q1, q2), IntersectionType::NORMAL_INTERSECTION);
    }
    {
        Int64Point p1(0, 0);
        Int64Point p2(0, 1);
        Int64Point q1(1, 0);
        Int64Point q2(1, 1);
        EXPECT_EQ(getIntersectionType(p1, p2, q1, q2), IntersectionType::NO_INTERSECTION);
    }
}

} // localminmax::common::unittest