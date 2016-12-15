// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef STARSEXTRACTOR_ISTARSEXTRACTOR_H_
#define STARSEXTRACTOR_ISTARSEXTRACTOR_H_

#include <boost/shared_ptr.hpp>

#include "StarInfo/starscontainer.h"
#include "RasterImage/rasterimage.h"

//*****************************************************************************
class IStarsExtractor
{
public:
	virtual ~IStarsExtractor(){}
	virtual void ExtractStars(RasterImagePtr pImage, std::vector<IFeaturesCarrierPtr>& vStars) const = 0;
};

//*****************************************************************************
class NullStarsExtractor: public IStarsExtractor
{
public:
	NullStarsExtractor(){}
	void ExtractStars(RasterImagePtr, std::vector<IFeaturesCarrierPtr>&) const {}
};

typedef boost::shared_ptr<IStarsExtractor> IStarsExtractorPtr;

#endif // STARSEXTRACTOR_ISTARSEXTRACTOR_H_ 
