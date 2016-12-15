// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef LOGGER_FILELOGGER_H_
#define LOGGER_FILELOGGER_H_

#include "ilogger.h"
#include <fstream>

//*****************************************************************************
class FileLogger : public ILogger
{
public:
	FileLogger(const std::string& strFileName);
	~FileLogger();
	void Log(const std::string& text);
private:
	std::ofstream m_File;
};
#endif // LOGGER_FILELOGGER_H_ 
