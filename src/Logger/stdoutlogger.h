// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef LOGGER_STDOUTLOGGER_H_
#define LOGGER_STDOUTLOGGER_H_

#include "ilogger.h"

//*****************************************************************************
class StdOutLogger : public ILogger
{
public:
		 StdOutLogger(){}
	void Log		 (const std::string& text);
};

#endif // LOGGER_STDOUTLOGGER_H_ 
