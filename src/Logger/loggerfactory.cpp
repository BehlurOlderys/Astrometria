/*
 * loggerfactory.cpp
 *
 *  Created on: 22 Nov 2016
 *      Author: Bartek
 */

#include "loggerfactory.h"

#include <iostream>

#include "stdoutlogger.h"
#include "filelogger.h"
#include "Options/options.h"

//*****************************************************************************
LoggerFactory::LoggerFactory()
//*****************************************************************************
{}

//*****************************************************************************
ILoggerPtr LoggerFactory::GetLogger(const std::string& type)
//*****************************************************************************
{
	std::cout << "LoggerFactory::GetLogger:" << std::endl;
	if (type == "stdout")
	{
		std::cout << "Creating stdout logger!" << std::endl;
		return ILoggerPtr(new StdOutLogger());
	}
	else if(type == "file")
	{
		std::cout << "Creating file logger!" << std::endl;
		return ILoggerPtr(new FileLogger(Options::g_GlobalOptions.sFileLoggerOutput));
	}
	return ILoggerPtr(new NullLogger());
}
