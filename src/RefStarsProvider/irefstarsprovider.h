// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef REFSTARSPROVIDER_IREFSTARSPROVIDER_H_
#define REFSTARSPROVIDER_IREFSTARSPROVIDER_H_

#include <vector>
#include "StarInfo/star.h"

class IRefStarsProvider
{
public:
	virtual ~IRefStarsProvider(){}
	virtual void ProvideRefStars(RefStarVector& vStars) = 0;
};

class NullRefStarsProvider : public IRefStarsProvider
{
public:
	NullRefStarsProvider(){}
	void ProvideRefStars(RefStarVector& vStars){}
};

typedef boost::shared_ptr<IRefStarsProvider> IRefStarsProviderPtr;

#endif // REFSTARSPROVIDER_IREFSTARSPROVIDER_H_ 
