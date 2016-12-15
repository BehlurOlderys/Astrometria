// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef BRIGHTNESSCALCULATOR_CIRCLEBRIGHTNESSCALCULATOR_H_
#define BRIGHTNESSCALCULATOR_CIRCLEBRIGHTNESSCALCULATOR_H_

#include "ibrightnesscalculator.h"

//*****************************************************************************
class CircleBrightnessCalculator : public IBrightnessCalculator
{
public:
	CircleBrightnessCalculator(const uint32 radius);
	uint32 CalculateBrightnessForPixel(const RasterImagePtr pImage, const Point& center);
private:
	const int m_Radius;
	const int m_R2;
};

#endif // BRIGHTNESSCALCULATOR_CIRCLEBRIGHTNESSCALCULATOR_H_ 
