// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef FILEOPENER_TIFFFILEOPENER_H_
#define FILEOPENER_TIFFFILEOPENER_H_

#include "ifileopener.h"

class ILogger;

//*****************************************************************************
class TiffFileOpener : public IFileOpener
{
public:
	TiffFileOpener(ILogger& logger);
	RasterImagePtr OpenFile(const std::string& sFileName);
private:
	ILogger& m_Logger;
};

#endif // FILEOPENER_TIFFFILEOPENER_H_ 
