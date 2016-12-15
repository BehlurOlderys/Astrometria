// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef MATHEMATICS_AREA_H_
#define MATHEMATICS_AREA_H_

#include "point.h"
#include <cmath>

//*****************************************************************************
double TriangleArea(const Point& A, const Point& B, const Point& C)
//*****************************************************************************
{
    const double ax = A.x;
    const double bx = B.x;
    const double cx = C.x;
    const double ay = A.y;
    const double by = B.y;
    const double cy = C.y;

    const double abc = ax * (by - cy);
    const double bca = bx * (cy - ay);
    const double cab = cx * (ay - by);

	return std::abs((abc + bca + cab) / 2.0 );
}

//*****************************************************************************
double PlaneSign(const Point& p1, const Point& p2, const Point& p3)
//*****************************************************************************
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

//*****************************************************************************
double PointInTriangle(const Point& pt, const Point& v1, const Point& v2, const Point& v3)
//*****************************************************************************
{
    bool b1, b2, b3;

    b1 = PlaneSign(pt, v1, v2) < 0.0f;
    b2 = PlaneSign(pt, v2, v3) < 0.0f;
    b3 = PlaneSign(pt, v3, v1) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}

#endif // MATHEMATICS_AREA_H_ 
