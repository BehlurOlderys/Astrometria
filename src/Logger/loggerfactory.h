// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef LOGGER_LOGGERFACTORY_H_
#define LOGGER_LOGGERFACTORY_H_

#include "ilogger.h"

class LoggerFactory
{
public:
			   LoggerFactory();
	ILoggerPtr GetLogger(const std::string& type);
};

#endif // LOGGER_LOGGERFACTORY_H_ 
