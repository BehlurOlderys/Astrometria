/*
 * starsextractorfactory.cpp
 *
 *  Created on: 23 Nov 2016
 *      Author: Bartek
 */

#include "starsextractorfactory.h"
#include "teststarsextractor.h"
#include "Logger/ilogger.h"
#include "Options/options.h"
#include "ImageSaver/iimagesaver.h"

//*****************************************************************************
StarsExtractorFactory::StarsExtractorFactory(ILogger& logger) :
	m_Logger(logger)
//*****************************************************************************
{}

//*****************************************************************************
IStarsExtractorPtr StarsExtractorFactory::GetStarExtractor(IImageSaver& imageSaver)
//*****************************************************************************
{
	m_Logger.Log("GetStarExtractor:");
	if (Options::g_GlobalOptions.sStarsExtractor == "test")
	{
		m_Logger.Log("TestStarsExtractor");
		return IStarsExtractorPtr(new TestStarsExtractor(m_Logger, imageSaver));
	}
	m_Logger.Log("NullStarsExtractor");
	return IStarsExtractorPtr(new NullStarsExtractor());
}
