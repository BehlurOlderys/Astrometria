// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef BRIGHTNESSCALCULATOR_IBRIGHTNESSCALCULATOR_H_
#define BRIGHTNESSCALCULATOR_IBRIGHTNESSCALCULATOR_H_

#include "RasterImage/rasterimage.h"
#include "Mathematics/point.h"

//*****************************************************************************
class IBrightnessCalculator
{
public:
	virtual ~IBrightnessCalculator(){}
	virtual uint32 CalculateBrightnessForPixel(const RasterImagePtr pImage, const Point& center) = 0;
};

typedef boost::shared_ptr<IBrightnessCalculator> BrightnessCalculatorPtr;

//*****************************************************************************
class NullBrightnessCalculator : public IBrightnessCalculator
{
public:
	NullBrightnessCalculator(){}
	uint32 CalculateBrightnessForPixel(const RasterImagePtr, const Point&){ return 0; }
};

#endif // BRIGHTNESSCALCULATOR_IBRIGHTNESSCALCULATOR_H_ 
