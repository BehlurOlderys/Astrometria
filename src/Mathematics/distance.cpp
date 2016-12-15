/*
 * distance.cpp
 *
 *  Created on: 4 Dec 2016
 *      Author: Bartek
 */

#include "distance.h"
#include <cmath>

#include "StarInfo/star.h"
#include "FeaturesExtractor/ifeaturesextractor.h"

//*****************************************************************************
double distance::CalculateSquare2D(const double x1, const double y1,
								   const double x2, const double y2)
//*****************************************************************************
{
	return std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2);
}

//*****************************************************************************
double distance::CalculateSquare2D_FC(const IFeaturesCarrier& a, const IFeaturesCarrier& b)
//*****************************************************************************
{
	return CalculateSquare2D(a.GetXPosition(), a.GetYPosition(), b.GetXPosition(), b.GetYPosition());
}

//*****************************************************************************
double distance::CalculateSquareND(const double vec1[], const double vec2[], const u32 N)
//*****************************************************************************
{
	double d = 0.;
	for (u32 i=0; i < N; ++i)
	{
		d += std::pow(vec1[i] - vec2[i], 2);
	}
	return d;
}

//*****************************************************************************
double distance::CalculateSquare_Feat(const Feature& f1, const Feature& f2)
//*****************************************************************************
{
	return CalculateSquareND(f1.m_vValues, f2.m_vValues, NUMBER_OF_FEATURES);
}
