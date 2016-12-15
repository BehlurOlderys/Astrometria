// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef STARSEXTRACTOR_TESTSTARSEXTRACTOR_H_
#define STARSEXTRACTOR_TESTSTARSEXTRACTOR_H_

#include "istarsextractor.h"
#include "StarInfo/starscontainer.h"

class ILogger;
class IImageSaver;

//*****************************************************************************
class TestStarsExtractor : public IStarsExtractor
{
public:
	TestStarsExtractor(ILogger& logger, IImageSaver& imageSaver);
	void ExtractStars(RasterImagePtr pImage, std::vector<IFeaturesCarrierPtr>& vStars) const;
private:
	ILogger& m_Logger;
	IImageSaver& m_ImageSaver;
};

#endif // STARSEXTRACTOR_TESTSTARSEXTRACTOR_H_ 
