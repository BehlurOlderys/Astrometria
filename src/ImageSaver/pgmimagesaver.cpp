/*
 * pgmimagesaver.cpp
 *
 *  Created on: 15 Dec 2016
 *      Author: Bartek
 */

#include "pgmimagesaver.h"
#include <fstream>

PGMImageSaver::PGMImageSaver(){}

//*****************************************************************************
void PGMImageSaver::SaveImage(RasterImagePtr pImage, const std::string& path)
//*****************************************************************************
{
	const std::string ending = ".pgm";
	std::ofstream outFile((path + ending).c_str(), std::ios_base::binary);

	const u32 uMin = 1;
	const u32 uMax = 255;
	const u32 uMaxDepth = std::min(uMax, std::max(uMin, pImage->GetMaxValue()));

	outFile << "P5\n";
	outFile << pImage->Width << "\n";
	outFile << pImage->Height << "\n";
	outFile << uMaxDepth << "\n";

	for (u32 uH = 0; uH < pImage->Height; ++uH)
	{
		const u32 uOffset = uH * pImage->Width;
		for (u32 uW = 0; uW < pImage->Width; ++uW)
		{
			outFile.write(reinterpret_cast<const char*>(&pImage->Raster[uOffset + uW]), 1);
		}
	}

	outFile.close();
}
