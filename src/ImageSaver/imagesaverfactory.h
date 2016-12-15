/*
 * imagesaverfactory.h
 *
 *  Created on: 15 Dec 2016
 *      Author: Bartek
 */

#ifndef IMAGESAVER_IMAGESAVERFACTORY_H_
#define IMAGESAVER_IMAGESAVERFACTORY_H_

#include "iimagesaver.h"

class ImageSaverFactory
{
public:
	ImageSaverFactory(){}
	IImageSaverPtr GetImageSaver(const std::string& type);
};

#endif /* IMAGESAVER_IMAGESAVERFACTORY_H_ */
