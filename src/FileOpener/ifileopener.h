// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef FILEOPENER_IFILEOPENER_H_
#define FILEOPENER_IFILEOPENER_H_

#include "RasterImage/rasterimage.h"

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
class IFileOpener
{
public:
	virtual ~IFileOpener(){}
	virtual RasterImagePtr OpenFile(const std::string& sFileName) = 0;
};

//*****************************************************************************
class NullFileOpener : public IFileOpener
{
public:
	NullFileOpener(){}
	RasterImagePtr OpenFile(const std::string&) { return RasterImagePtr(); }
};

#endif // FILEOPENER_IFILEOPENER_H_ 
