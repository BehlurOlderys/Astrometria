// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef THRESHOLDFILTER_THRESHOLDFILTERFACTORY_H_
#define THRESHOLDFILTER_THRESHOLDFILTERFACTORY_H_

#include "ithresholdfilter.h"

class ILogger;

class ThresholdFilterFactory
{
public:
	ThresholdFilterFactory(ILogger& logger);
	IThresholdFilterPtr GetThresholdFilter(const RasterImagePtr pImage);
private:
	ILogger& m_Logger;
};

#endif // THRESHOLDFILTER_THRESHOLDFILTERFACTORY_H_ 
