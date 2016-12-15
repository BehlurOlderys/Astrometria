/*
 * featuresextractorfactory.cpp
 *
 *  Created on: 3 Dec 2016
 *      Author: Bartek
 */

#include "featuresextractorfactory.h"
#include "testfeaturesextractor.h"
#include "Options/options.h"
#include "Logger/ilogger.h"

//*****************************************************************************
FeaturesExtractorFactory::FeaturesExtractorFactory(ILogger& logger) :
	m_Logger(logger)
//*****************************************************************************
{}

//*****************************************************************************
IFeaturesExtractorPtr FeaturesExtractorFactory::GetFeaturesExtractor(BrightnessLinearizer linearizer)
//*****************************************************************************
{
	m_Logger.Log("FeaturesExtractorFactory");
	if (Options::g_GlobalOptions.sFeaturesExtractor == "test")
	{
		return IFeaturesExtractorPtr(new TestFeaturesExtractor(linearizer, m_Logger));
	}
	return IFeaturesExtractorPtr(new NullFeaturesExtractor());
}
