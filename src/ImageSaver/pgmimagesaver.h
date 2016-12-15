/*
 * pgmimagesaver.h
 *
 *  Created on: 15 Dec 2016
 *      Author: Bartek
 */

#ifndef IMAGESAVER_PGMIMAGESAVER_H_
#define IMAGESAVER_PGMIMAGESAVER_H_

#include "iimagesaver.h"

class PGMImageSaver : public IImageSaver
{
public:
	PGMImageSaver();
	void SaveImage(const RasterImagePtr pImage, const std::string& path);
};



#endif /* IMAGESAVER_PGMIMAGESAVER_H_ */
