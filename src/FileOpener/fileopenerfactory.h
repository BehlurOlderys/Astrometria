// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef FILEOPENER_FILEOPENERFACTORY_H_
#define FILEOPENER_FILEOPENERFACTORY_H_

#include "boost/shared_ptr.hpp"
#include "ifileopener.h"

class ILogger;

typedef boost::shared_ptr<IFileOpener> IFileOpenerPtr;

//*****************************************************************************
class FileOpenerFactory
{
public:
	FileOpenerFactory(ILogger& logger);
	IFileOpenerPtr GetFileOpener();
private:
	ILogger& m_Logger;
};

#endif // FILEOPENER_FILEOPENERFACTORY_H_ 
