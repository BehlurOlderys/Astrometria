// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef RASTERIMAGE_RASTERIMAGE_H_
#define RASTERIMAGE_RASTERIMAGE_H_

#include <cstring>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "common.h"

typedef unsigned int uint32;


u32 GetRedFromPixel(const u32 pixel);
u32 GetGreenFromPixel(const u32 pixel);
u32 GetBlueFromPixel(const u32 pixel);
u32 GetLumFromPixel(const u32 pixel);
u32 CombineRGBToPixel(const u32 red, const u32 green, const u32 blue);

//*****************************************************************************
struct RasterImage
{
	RasterImage() :
		Raster(),
		Width(0),
		Height(0) {}

	//*****************************************************************************
	virtual ~RasterImage()
	//*****************************************************************************
	{
		delete[] Raster;
	}
	//*****************************************************************************
	uint32 GetPixelNumber()
	//*****************************************************************************
	{
		return uint32(Width*Height);
	}
	uint32 GetRPixel(const u32 index){ return GetRedFromPixel  (Raster[index]); }
	uint32 GetGPixel(const u32 index){ return GetGreenFromPixel(Raster[index]); }
	uint32 GetBPixel(const u32 index){ return GetBlueFromPixel (Raster[index]); }
	uint32 GetLum	(const u32 index){ return GetLumFromPixel  (Raster[index]); }

	u32 GetMaxValue();

	//*****************************************************************************
	void CopySizeOnlyFrom(const boost::shared_ptr<RasterImage> pImage)
	//*****************************************************************************
	{
		Raster = new uint32[pImage->GetPixelNumber()];
		Width = pImage->Width;
		Height = pImage->Height;
		std::memset(Raster, 0, pImage->GetPixelNumber()* sizeof(uint32));
	}
	uint32* Raster;
	uint32  Width;
	uint32  Height;
};

typedef boost::shared_ptr<RasterImage> RasterImagePtr;

RasterImagePtr ConvertToGreyscale(const RasterImagePtr pImage);

#endif // RASTERIMAGE_RASTERIMAGE_H_ 
