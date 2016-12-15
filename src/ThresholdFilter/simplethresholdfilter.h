// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef THRESHOLDFILTER_SIMPLETHRESHOLDFILTER_H_
#define THRESHOLDFILTER_SIMPLETHRESHOLDFILTER_H_

#include "ithresholdfilter.h"

class SimpleThresholdFilter : public IThresholdFilter
{
public:
	SimpleThresholdFilter(RasterImagePtr rasterImage, const double fThreshold);
	RasterImagePtr GetBinaryImage() const;
private:
	RasterImagePtr m_pImage;
	const double   m_fThreshold;
};

#endif // THRESHOLDFILTER_SIMPLETHRESHOLDFILTER_H_ 
