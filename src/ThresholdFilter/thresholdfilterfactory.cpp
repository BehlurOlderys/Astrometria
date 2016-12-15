/*
 * thresholdfilterfactory.cpp
 *
 *  Created on: 23 Nov 2016
 *      Author: Bartek
 */

#include "thresholdfilterfactory.h"
#include <boost/format.hpp>
#include "Options/options.h"
#include "simplethresholdfilter.h"
#include "betterthresholdfilter.h"
#include "Logger/ilogger.h"


//*****************************************************************************
ThresholdFilterFactory::ThresholdFilterFactory(ILogger& logger) :
	m_Logger(logger)
//*****************************************************************************
{}

//*****************************************************************************
IThresholdFilterPtr ThresholdFilterFactory::GetThresholdFilter(const RasterImagePtr pImage)
//*****************************************************************************
{
	m_Logger.Log((boost::format("Size of uint32 = %d and size of long unsigned int = %d") % sizeof(uint32) % sizeof(u64)).str());
	if (Options::g_GlobalOptions.sThresholdFilter == "simple")
	{
		m_Logger.Log("SimpleThresholdFilter");
		return IThresholdFilterPtr(new SimpleThresholdFilter(pImage, Options::g_GlobalOptions.fThresholdForSimpleThresholdFilter));
	}
	if (Options::g_GlobalOptions.sThresholdFilter == "better")
	{
		m_Logger.Log("BetterThresholdFilter");
		m_Logger.Log((boost::format("uMedianSizeForBetterThresholdFilter = %d") % Options::g_GlobalOptions.uMedianSizeForBetterThresholdFilter).str());
		return IThresholdFilterPtr(new BetterThresholdFilter(pImage, Options::g_GlobalOptions.uMedianSizeForBetterThresholdFilter));
	}
	m_Logger.Log("NullThresholdFilter");
	return IThresholdFilterPtr(new NullThresholdFilter());
}
