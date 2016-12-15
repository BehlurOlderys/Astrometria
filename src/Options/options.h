// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef OPTIONS_H_
#define OPTIONS_H_

#include "common.h"
#include <string>

struct Options
{
	Options() :
		uRadiusForCircleBrightnessCalculator(10),
		fThresholdForSimpleThresholdFilter(0.5),
		uMedianSizeForBetterThresholdFilter(20),
		sLoggerType("stdout"),
		sFileLoggerOutput("wynik.log"),
		sFileOpenerType("tiff"),
		sCatalogueFilePath("dane.cat"),
		fMaximalMagnitude(15.0),
		sStarsExtractor("test"),
		sThresholdFilter("simple"),
		sRefStarsProvider("test"),
		sFileOpener("tiff"),
		sBrightnessCalculator("circle"),
		uMaxStarsLoaded(10000000),
		sFeaturesExtractor("test")
	{}
	u32 uRadiusForCircleBrightnessCalculator;
	double fThresholdForSimpleThresholdFilter;
	u32 uMedianSizeForBetterThresholdFilter;
	std::string sLoggerType;
	std::string sFileLoggerOutput;
	std::string sFileOpenerType;
	std::string sStarExtractorType;
	std::string sCatalogueFilePath;
	double fMaximalMagnitude;
	std::string sStarsExtractor;
	std::string sThresholdFilter;
	std::string sRefStarsProvider;
	std::string sFileOpener;
	std::string sBrightnessCalculator;
	u64 		uMaxStarsLoaded;
	std::string sFeaturesExtractor;
	static Options g_GlobalOptions;
};

#endif // OPTIONS_H_ 
