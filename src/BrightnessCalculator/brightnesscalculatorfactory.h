// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef BRIGHTNESSCALCULATOR_BRIGHTNESSCALCULATORFACTORY_H_
#define BRIGHTNESSCALCULATOR_BRIGHTNESSCALCULATORFACTORY_H_

#include "ibrightnesscalculator.h"

class ILogger;

//*****************************************************************************
class BrightnessCalculatorFactory
{
public:
	BrightnessCalculatorFactory(ILogger& logger);
	BrightnessCalculatorPtr GetCalculator();
private:
	ILogger& m_Logger;
};

#endif // BRIGHTNESSCALCULATOR_BRIGHTNESSCALCULATORFACTORY_H_ 
