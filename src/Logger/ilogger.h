// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef LOGGER_ILOGGER_H_
#define LOGGER_ILOGGER_H_

#include <string>
#include <boost/shared_ptr.hpp>

//*****************************************************************************
class ILogger
{
public:
	virtual ~ILogger(){}
	virtual void Log(const std::string& text) = 0;
};

class NullLogger : public ILogger
{
public:
	NullLogger(){}
	void Log(const std::string&){}
};

typedef boost::shared_ptr<ILogger> ILoggerPtr;

#endif // LOGGER_ILOGGER_H_ 
