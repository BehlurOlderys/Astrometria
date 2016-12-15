/*
 * betterthresholdfilter.h
 *
 *  Created on: 15 Dec 2016
 *      Author: Bartek
 */

#ifndef THRESHOLDFILTER_BETTERTHRESHOLDFILTER_H_
#define THRESHOLDFILTER_BETTERTHRESHOLDFILTER_H_

#include "ithresholdfilter.h"

class BetterThresholdFilter : public IThresholdFilter
{
public:
	BetterThresholdFilter(RasterImagePtr rasterImage, const u32 uMedianSize);
	RasterImagePtr GetBinaryImage() const;
private:
	RasterImagePtr m_pImage;
	const u32      m_MedianSize;
};

#endif /* THRESHOLDFILTER_BETTERTHRESHOLDFILTER_H_ */
