// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef THRESHOLDFILTER_ITHRESHOLDFILTER_H_
#define THRESHOLDFILTER_ITHRESHOLDFILTER_H_

#include "RasterImage/rasterimage.h"

#define TRUE_PIXEL 1

//*****************************************************************************
class IThresholdFilter
{
public:
	virtual ~IThresholdFilter(){}
	virtual RasterImagePtr GetBinaryImage() const = 0;
};

//*****************************************************************************
class NullThresholdFilter : public IThresholdFilter
{
public:
	NullThresholdFilter(){}
	RasterImagePtr GetBinaryImage() const { return RasterImagePtr(); }
};

typedef boost::shared_ptr<IThresholdFilter> IThresholdFilterPtr;

#endif // THRESHOLDFILTER_ITHRESHOLDFILTER_H_ 
