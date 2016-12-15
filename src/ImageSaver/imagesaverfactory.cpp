/*
 * imagesaverfactory.cpp
 *
 *  Created on: 15 Dec 2016
 *      Author: Bartek
 */

#include "imagesaverfactory.h"
#include "pgmimagesaver.h"

//*****************************************************************************
IImageSaverPtr ImageSaverFactory::GetImageSaver(const std::string& type)
//*****************************************************************************
{
	if (type == "intermediate")
	{
		return IImageSaverPtr(new PGMImageSaver());
	}
	return IImageSaverPtr(new NullImageSaver());
}


