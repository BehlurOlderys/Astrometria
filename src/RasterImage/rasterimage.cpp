/*
 * rasterimage.cpp
 *
 *  Created on: 15 Dec 2016
 *      Author: Bartek
 */

#include "rasterimage.h"

u32 GetRedFromPixel		(const u32 pixel){ return pixel & 0xff; }
u32 GetGreenFromPixel	(const u32 pixel){ return ( pixel >> 8 ) & 0xff; }
u32 GetBlueFromPixel	(const u32 pixel){ return ( pixel >> 16 ) & 0xff; }
u32 GetLumFromPixel		(const u32 pixel){ return uint32((GetRedFromPixel(pixel) + GetGreenFromPixel(pixel) + GetBlueFromPixel(pixel)) / 3); }
//*****************************************************************************
u32 CombineRGBToPixel	(const u32 red, const u32 green, const u32 blue)
//*****************************************************************************
{
	return red + (green << 8) + (blue << 16);
}


//*****************************************************************************
RasterImagePtr ConvertToGreyscale(const RasterImagePtr pImage)
//*****************************************************************************
{
	RasterImagePtr greyscaleImage(new RasterImage());
	greyscaleImage->CopySizeOnlyFrom(pImage);
	const u32 uPixels = greyscaleImage->GetPixelNumber();
	for (u32 uIndex = 0; uIndex < uPixels; ++uIndex)
	{
		greyscaleImage->Raster[uIndex] = pImage->GetLum(uIndex);
	}
	return greyscaleImage;
}

//*****************************************************************************
u32 RasterImage::GetMaxValue()
//*****************************************************************************
{
	const u32 uN = GetPixelNumber();
	u32 uMax = 0;
	for (u32 uIndex = 0; uIndex < uN; ++uIndex)
	{
		const u32 uLum = GetLum(uIndex);
		if (uLum > uMax)
		{
			uMax = uLum;
		}
	}
	return uMax;
}

