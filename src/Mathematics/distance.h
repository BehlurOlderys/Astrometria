/*
 * distance.h
 *
 *  Created on: 4 Dec 2016
 *      Author: Bartek
 */

#ifndef MATHEMATICS_DISTANCE_H_
#define MATHEMATICS_DISTANCE_H_

#include "common.h"

class IFeaturesCarrier;
class Feature;

namespace distance
{
double CalculateSquare2D	(const double x1, const double y1,
				   	     	 const double x2, const double y2);
double CalculateSquare2D_FC	(const IFeaturesCarrier& a, const IFeaturesCarrier& b);
double CalculateSquareND	(const double vec1[], const double vec2[], const u32 N);
double CalculateSquare_Feat	(const Feature& f1, const Feature& f2);

double NormalizedAngleBetweenThreePoints(const IFeaturesCarrier& a, const IFeaturesCarrier& b, const IFeaturesCarrier& c);
}

//*****************************************************************************
struct DistanceAndIndex
{
	DistanceAndIndex() : m_fDist(0.), m_uIndex1(0), m_uIndex2(0) {}
	DistanceAndIndex(double d, u64 index1, u64 index2) : m_fDist(d), m_uIndex1(index1), m_uIndex2(index2) {}
	double GetDistance() const { return m_fDist; }
	u64 GetFirstIndex() const { return m_uIndex1; }
	u64 GetSecondIndex() const { return m_uIndex2; }
	void SetDistance(const double d){ m_fDist = d; }

	std::string ToString() const { return (boost::format("%d <-> %d = %f") % m_uIndex1 % m_uIndex2 % m_fDist).str(); }

	double m_fDist;
	u64 m_uIndex1;
	u64 m_uIndex2;
};

//*****************************************************************************
struct DistanceAndIndexByDistance
{
    inline bool operator() (const DistanceAndIndex& struct1, const DistanceAndIndex& struct2)
    {
        return (struct1.m_fDist < struct2.m_fDist);
    }
};

#endif /* MATHEMATICS_DISTANCE_H_ */
