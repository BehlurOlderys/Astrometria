/*
 * iimagesaver.h
 *
 *  Created on: 14 Dec 2016
 *      Author: Bartek
 */

#ifndef IMAGESAVER_IIMAGESAVER_H_
#define IMAGESAVER_IIMAGESAVER_H_

#include "RasterImage/rasterimage.h"

class IImageSaver
{
public:
	virtual ~IImageSaver(){}
	virtual void SaveImage(const RasterImagePtr pImage, const std::string& path) = 0;
};

class NullImageSaver : public IImageSaver
{
public:
	NullImageSaver(){}
	void SaveImage(const RasterImagePtr, const std::string&){}
};

typedef boost::shared_ptr<IImageSaver> IImageSaverPtr;

#endif /* IMAGESAVER_IIMAGESAVER_H_ */
