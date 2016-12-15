/*
 * simplethresholdfilter.cpp
 *
 *  Created on: 23 Nov 2016
 *      Author: Bartek
 */

#include "simplethresholdfilter.h"
#include <iostream>
#include "common.h"

//*****************************************************************************
SimpleThresholdFilter::SimpleThresholdFilter(RasterImagePtr rasterImage, const double fThreshold) :
	m_pImage(rasterImage),
	m_fThreshold(fThreshold)
//*****************************************************************************
{}

//*****************************************************************************
RasterImagePtr SimpleThresholdFilter::GetBinaryImage() const
//*****************************************************************************
{
	std::cout<< "float threshold = " << m_fThreshold << std::endl;
	RasterImagePtr binaryImage(new RasterImage());
	binaryImage->CopySizeOnlyFrom(m_pImage);
	uint32 N = m_pImage->GetPixelNumber();

	uint32 uMaxValue = m_pImage->GetMaxValue();

	std::cout<< "max value = " << uMaxValue << std::endl;
	const uint32 uAbsThreshold = uint32(m_fThreshold * uMaxValue);
	std::cout<< "abs threshold = " << uAbsThreshold << std::endl;

	for (uint32 i = 0; i < N; ++i)
	{
		if (m_pImage->GetLum(i) > uAbsThreshold)
		{
			binaryImage->Raster[i] = TRUE_PIXEL;
		}
	}
	return binaryImage;
}
