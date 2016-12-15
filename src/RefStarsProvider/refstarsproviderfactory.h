// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef REFSTARSPROVIDER_REFSTARSPROVIDERFACTORY_H_
#define REFSTARSPROVIDER_REFSTARSPROVIDERFACTORY_H_

#include "irefstarsprovider.h"

class ILogger;

class RefStarsProviderFactory
{
public:
	RefStarsProviderFactory(ILogger& logger);
	IRefStarsProviderPtr GetRefStarsProvider();
private:
	ILogger& m_Logger;
};

#endif // REFSTARSPROVIDER_REFSTARSPROVIDERFACTORY_H_ 
