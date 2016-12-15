/*
 * stdoutlogger.cpp
 *
 *  Created on: 21 Nov 2016
 *      Author: Bartek
 */

#include "stdoutlogger.h"
#include <iostream>

//*****************************************************************************
void StdOutLogger::Log(const std::string& text)
//*****************************************************************************
{
	std::cout << text << std::endl;
}
