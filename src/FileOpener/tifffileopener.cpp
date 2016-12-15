/*
 * tifffileopener.cpp
 *
 *  Created on: 22 Nov 2016
 *      Author: Bartek
 */

#include "tifffileopener.h"

#include <boost/format.hpp>
#include <cstring>
#include "tiffio.h"
#include "Logger/ilogger.h"

//*****************************************************************************
TiffFileOpener::TiffFileOpener(ILogger& logger) :
	m_Logger(logger)
//*****************************************************************************
{}
//*****************************************************************************
RasterImagePtr TiffFileOpener::OpenFile(const std::string& sFileName)
//*****************************************************************************
{
	TIFF* tif = TIFFOpen(sFileName.c_str(), "r");
	if (!tif)
	{
		m_Logger.Log((boost::format("Nie udalo sie otworzyc pliku o nazwie %s!") % sFileName).str());
		return RasterImagePtr();
	}

	RasterImagePtr image(new RasterImage());

	TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &image->Width);
	TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &image->Height);

	size_t npixels = image->GetPixelNumber();
	const uint32 uSizeOfRasterInBytes = uint32(npixels * sizeof (uint32));
	uint32* raster = (uint32*) _TIFFmalloc(uSizeOfRasterInBytes);
	if (raster == NULL)
	{
		m_Logger.Log("Raster okazal sie nullem!");
		return RasterImagePtr();
	}
	if (TIFFReadRGBAImage(tif,
						  image->Width,
						  image->Height,
						  raster,
						  0))
	{
		m_Logger.Log((boost::format("Plik ma szerokosc = %d, wysokosc = %d") % image->Width % image->Height).str());
		image->Raster = new uint32[npixels];
		std::memcpy(image->Raster, raster, uSizeOfRasterInBytes);
	}
	_TIFFfree(raster);
	TIFFClose(tif);
	return image;
}
