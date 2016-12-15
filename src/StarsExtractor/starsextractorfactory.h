// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef STARSEXTRACTOR_STARSEXTRACTORFACTORY_H_
#define STARSEXTRACTOR_STARSEXTRACTORFACTORY_H_

#include "istarsextractor.h"

class ILogger;
class IImageSaver;

class StarsExtractorFactory
{
public:
	StarsExtractorFactory(ILogger& logger);
	IStarsExtractorPtr GetStarExtractor(IImageSaver& imageSaver);
private:
	ILogger& m_Logger;
};

#endif // STARSEXTRACTOR_STARSEXTRACTORFACTORY_H_ 
