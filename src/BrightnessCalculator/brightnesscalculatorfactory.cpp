/*
 * brightnesscalculatorfactory.cpp
 *
 *  Created on: 29 Nov 2016
 *      Author: Bartek
 */

#include "brightnesscalculatorfactory.h"
#include "circlebrightnesscalculator.h"
#include "Options/options.h"
#include "Logger/ilogger.h"

//*****************************************************************************
BrightnessCalculatorFactory::BrightnessCalculatorFactory(ILogger& logger) :
	m_Logger(logger)
//*****************************************************************************
{}

//*****************************************************************************
BrightnessCalculatorPtr BrightnessCalculatorFactory::GetCalculator()
//*****************************************************************************
{
	m_Logger.Log("BrightnessCalculatorFactory::GetCalculator");
	if (Options::g_GlobalOptions.sBrightnessCalculator == "circle")
	{
		m_Logger.Log((boost::format("CircleBrightnessCalculator with radius %d") % Options::g_GlobalOptions.uRadiusForCircleBrightnessCalculator).str());
		return BrightnessCalculatorPtr(new CircleBrightnessCalculator(Options::g_GlobalOptions.uRadiusForCircleBrightnessCalculator));
	}
	m_Logger.Log("NullBrightnessCalculator");
	return BrightnessCalculatorPtr(new NullBrightnessCalculator());
}
