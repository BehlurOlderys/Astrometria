/*
 * teststarsextractor.cpp
 *
 *  Created on: 23 Nov 2016
 *      Author: Bartek
 */

#include "teststarsextractor.h"

#include <string>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <vector>

#include "ThresholdFilter/thresholdfilterfactory.h"
#include "BrightnessCalculator/brightnesscalculatorfactory.h"
#include "Options/options.h"
#include "ImageSaver/iimagesaver.h"

struct PixelMarker
{
	//*****************************************************************************
	PixelMarker(const uint32 uLabel, RasterImagePtr binaryImage) :
		label(uLabel),
		image(binaryImage),
		maxNumber(binaryImage->GetPixelNumber()),
		width(binaryImage->Width),
		coords()
	//*****************************************************************************
	{}

	//*****************************************************************************
	void MarkAllPixels(const uint32 index)
	//*****************************************************************************
	{
		if (index > maxNumber)
		{
			return;
		}
		uint32& pixel = image->Raster[index];
		if (pixel == TRUE_PIXEL)
		{
			pixel = label;
			coords.push_back(Blob(index % width, index / width, 0));
			MarkAllPixels(index - 1  - width);
			MarkAllPixels(index 	 - width);
			MarkAllPixels(index + 1  - width);
			MarkAllPixels(index - 1);
			MarkAllPixels(index + 1);
			MarkAllPixels(index - 1  + width);
			MarkAllPixels(index		 + width);
			MarkAllPixels(index + 1  + width);
		}
	}

	//*****************************************************************************
	Blob GetCenter()
	//*****************************************************************************
	{
		Blob center(0, 0, coords.size());
		BOOST_FOREACH(Blob& c, coords)
		{
			center.x += c.x;
			center.y += c.y;
		}
		center.x /= coords.size();
		center.y /= coords.size();
		return center;
	}

	const uint32 		label;
	RasterImagePtr 		image;
	const uint32 		maxNumber;
	const uint32 		width;
	std::vector<Blob>   coords;
};

struct BlobByBrightness
{
    inline bool operator() (const Blob& struct1, const Blob& struct2)
    {
        return (struct1.brightnessOnImage > struct2.brightnessOnImage);
    }
};

//*****************************************************************************
TestStarsExtractor::TestStarsExtractor(ILogger& logger, IImageSaver& imageSaver) :
	m_Logger(logger),
	m_ImageSaver(imageSaver)
//*****************************************************************************
{}

//*****************************************************************************
void TestStarsExtractor::ExtractStars(RasterImagePtr pImage, std::vector<IFeaturesCarrierPtr>& vStars) const
{
	if (!pImage)
	{
		return;
	}

	// progowanie:
	ThresholdFilterFactory thresholdFilterFactory(m_Logger);
	IThresholdFilterPtr thresholdFilter = thresholdFilterFactory.GetThresholdFilter(pImage);
	RasterImagePtr binaryImage = thresholdFilter->GetBinaryImage();

	m_ImageSaver.SaveImage(binaryImage, "thresholdImage");

	uint32 N = binaryImage->GetPixelNumber();
	uint32 uCounter = 0;
	for (uint32 i = 0; i < N; ++i)
	{
		if (binaryImage->Raster[i] > 0)
		{
			uCounter++;
		}
	}
	m_Logger.Log((boost::format("uCounter = %d!)") % uCounter).str());

	std::vector<Blob> vBlobs;
	// Count stars:
	const uint32 uLabelStart = 3;
	uint32 uLabel = uLabelStart;
	for (uint32 i = 0; i < N; ++i)
	{
		if (binaryImage->Raster[i] == TRUE_PIXEL)
		{
			uLabel++;
			PixelMarker marker(uLabel, binaryImage);
			marker.MarkAllPixels(i);
			vBlobs.push_back(marker.GetCenter());
		}
	}

	BrightnessCalculatorFactory brightnessCalculatorFactory(m_Logger);
	BrightnessCalculatorPtr brightnessCalculator = brightnessCalculatorFactory.GetCalculator();

	std::vector<Blob> vBlobsWithBrightness;
	BOOST_FOREACH(Blob& star, vBlobs)
	{
		Blob printed(star.x, pImage->Height - star.y, star.sizeOfBlob);
		printed.brightnessOnImage = brightnessCalculator->CalculateBrightnessForPixel(pImage, star);
		vBlobsWithBrightness.push_back(printed);
	}
	std::sort(vBlobsWithBrightness.begin(), vBlobsWithBrightness.end(), BlobByBrightness()); // should be descending

	BOOST_FOREACH(Blob& star, vBlobsWithBrightness)
	{
		vStars.push_back(IFeaturesCarrierPtr(new Blob(star)));
	}
}
