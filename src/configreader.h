// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef CONFIGREADER_H_
#define CONFIGREADER_H_

#include "Options/options.h"
#include "Logger/ilogger.h"

//*****************************************************************************
void ReadConfigFile(const ILoggerPtr& pLogger)
{
	std::ifstream configFile;
	std::ios_base::iostate exceptionMask = configFile.exceptions()
			| std::ios::failbit;
	configFile.exceptions(exceptionMask);
	const char delim = '=';
	try {
		configFile.open("config.txt");
	} catch (...) {
		pLogger->Log("Nie udalo sie otworzyc pliku konfiguracyjnego!");
	}
	try {
		std::string bin;
		std::getline(configFile, bin, delim);
		configFile >> Options::g_GlobalOptions.uRadiusForCircleBrightnessCalculator;
		std::getline(configFile, bin, delim);
		configFile >> Options::g_GlobalOptions.fThresholdForSimpleThresholdFilter;
		std::getline(configFile, bin, delim);
		configFile >> Options::g_GlobalOptions.uMedianSizeForBetterThresholdFilter;
		std::getline(configFile, bin, delim);
		configFile >> Options::g_GlobalOptions.sLoggerType;
		std::getline(configFile, bin, delim);
		configFile >> Options::g_GlobalOptions.sFileLoggerOutput;
		std::getline(configFile, bin, delim);
		configFile >> Options::g_GlobalOptions.sFileOpenerType;
		std::getline(configFile, bin, delim);
		configFile >> Options::g_GlobalOptions.sCatalogueFilePath;
		std::getline(configFile, bin, delim);
		configFile >> Options::g_GlobalOptions.fMaximalMagnitude;
		std::getline(configFile, bin, delim);
		configFile >> Options::g_GlobalOptions.sStarsExtractor;
		std::getline(configFile, bin, delim);
		configFile >> Options::g_GlobalOptions.sThresholdFilter;
		std::getline(configFile, bin, delim);
		configFile >> Options::g_GlobalOptions.sRefStarsProvider;
		std::getline(configFile, bin, delim);
		configFile >> Options::g_GlobalOptions.sFileOpener;
		std::getline(configFile, bin, delim);
		configFile >> Options::g_GlobalOptions.sBrightnessCalculator;
		std::getline(configFile, bin, delim);
		configFile >> Options::g_GlobalOptions.uMaxStarsLoaded;
		std::getline(configFile, bin, delim);
		configFile >> Options::g_GlobalOptions.sFeaturesExtractor;
	} catch (...) {
		pLogger->Log("Nie udalo sie przeczytac calej konfiguracji, czesc bedzie ustawiona domyslnie!");
	}
}


#endif // CONFIGREADER_H_ 
