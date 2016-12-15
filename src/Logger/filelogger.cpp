/*
 * filelogger.cpp
 *
 *  Created on: 21 Nov 2016
 *      Author: Bartek
 */

#include "filelogger.h"

//*****************************************************************************
FileLogger::FileLogger(const std::string& strFileName) :
	m_File()
//*****************************************************************************
{
	std::ios_base::iostate exceptionMask = m_File.exceptions() | std::ios::failbit;
	m_File.exceptions(exceptionMask);
	m_File.open(strFileName.c_str());
}

//*****************************************************************************
FileLogger::~FileLogger()
//*****************************************************************************
{
	m_File.close();
}

//*****************************************************************************
void FileLogger::Log(const std::string& text)
//*****************************************************************************
{
	m_File << text << std::endl;
}
