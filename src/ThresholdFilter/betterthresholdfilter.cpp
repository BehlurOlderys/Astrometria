/*
 * betterthresholdfilter.cpp
 *
 *  Created on: 15 Dec 2016
 *      Author: Bartek
 */

#include "betterthresholdfilter.h"
#include "common.h"

namespace
{

#define MAX_SIZE 1000

//*****************************************************************************
u32 MedianValueForPixel(RasterImagePtr rasterImage, const int x, const int y, const int iRadius)
//*****************************************************************************
{
	const int iW = rasterImage->Width;
	const int iH = rasterImage->Height;
	const u32 uTopBorder = u32(std::max(0, y - iRadius));
	const u32 uBottomBorder = u32(std::min(iH, y + iRadius));
	const u32 uLeftBorder = u32(std::max(0, x - iRadius));
	const u32 uRightBorder = u32(std::min(iW, x + iRadius));

	int iSize = (uBottomBorder - uTopBorder)*(uRightBorder - uLeftBorder);

	if (iSize > MAX_SIZE)
	{
		throw;
	}

//	static u32 g_vRedValues[MAX_SIZE];
//	static u32 g_vGreenValues[MAX_SIZE];
//	static u32 g_vBlueValues[MAX_SIZE];
//
//	memset(g_vRedValues, 0, sizeof(g_vRedValues));
//	memset(g_vGreenValues, 0, sizeof(g_vGreenValues));
//	memset(g_vBlueValues, 0, sizeof(g_vBlueValues));
	u32 uRed = 0;
	u32 uGreen = 0;
	u32 uBlue = 0;

	u32 uCounter = 0;

	for (u32 Yindex = uTopBorder; Yindex < uBottomBorder; ++Yindex)
	{
		for (u32 Xindex = uLeftBorder; Xindex < uRightBorder; ++Xindex)
		{
			const u32 index = u32( Yindex * iW + Xindex);
			uRed += rasterImage->GetRPixel(index);
			uGreen += rasterImage->GetGPixel(index);
			uBlue += rasterImage->GetBPixel(index);

			uCounter++;
		}
	}

	return CombineRGBToPixel(uRed / uCounter,
							 uGreen / uCounter,
							 uBlue / uCounter);
}

//*****************************************************************************
u32 MeanValueForPixel(RasterImagePtr rasterImage, const int index, const int iRadius)
//*****************************************************************************
{
	const int iW = rasterImage->Width;
	return MedianValueForPixel(rasterImage, index % iW, index / iW, iRadius);
}

} // namespace

//*****************************************************************************
BetterThresholdFilter::BetterThresholdFilter(RasterImagePtr rasterImage, const u32 uMedianSize) :
	m_pImage(rasterImage),
	m_MedianSize(uMedianSize)
//*****************************************************************************
{}

//*****************************************************************************
RasterImagePtr BetterThresholdFilter::GetBinaryImage() const
//*****************************************************************************
{
	RasterImagePtr binaryImage(new RasterImage());
	binaryImage->CopySizeOnlyFrom(m_pImage);
	uint32 N = m_pImage->GetPixelNumber();

	// TODO: treat whole image with median filter 3x3 for noise
	for (uint32 i = 0; i < N; ++i)
	{
		binaryImage->Raster[i] = MeanValueForPixel(m_pImage, i, 1);
	}

	RasterImagePtr medianImage(new RasterImage());
	medianImage->CopySizeOnlyFrom(m_pImage);
	for (uint32 i = 0; i < N; ++i)
	{
		medianImage->Raster[i] = MeanValueForPixel(m_pImage, i, m_MedianSize);
	}
//	// TODO: subtract this from image
//
//	for (uint32 i = 0; i < N; ++i)
//	{
//		if (m_pImage->GetLum(i) > uAbsThreshold)
//		{
//			binaryImage->Raster[i] = TRUE_PIXEL;
//		}
//	}
	return medianImage;
}
