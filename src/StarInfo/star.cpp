/*
 * star.cpp
 *
 *  Created on: 30 Nov 2016
 *      Author: Bartek
 */

#include "star.h"
#include <cmath>

//*****************************************************************************
double GetUnchangedBrightness(const double brightness)
//*****************************************************************************
{ return brightness; }

//*****************************************************************************
double GetLogVsZeroBrightness(const double brightness)
//*****************************************************************************
{ return std::pow(10, brightness / -2.5); }

//*****************************************************************************
i32 GetI32RAFromFloat(const double& fRA)
//*****************************************************************************
{
	return i32(fRA * iRA_Multiplier);
}

//*****************************************************************************
i32 GetI32DECFromFloat(const double& fDEC)
//*****************************************************************************
{
	return i32((fDEC + iDEC_Shift) * iDEC_Multiplier);
}

//*****************************************************************************
std::string CelestialPoint::ToString() const
//*****************************************************************************
{
	double tmp = RA;
	u32 RAhours = u32(tmp / 15);
	tmp -= double(RAhours * 15);
	u32 RAminutes = u32(tmp * 4);
	tmp -= double(RAminutes) / 4.0;
	double RAseconds = tmp * 240.0;

	tmp = DE;
	u32 DEdegrees = u32(tmp);
	tmp -= double(DEdegrees);
	u32 DEminutes = u32(tmp * 60);
	tmp -= double(DEminutes) / 60.0;
	double DEseconds = tmp * 3600.0;

	return (boost::format("RA = %dh%dm%fs, DEC degrees = %ddeg%d\'%f\"") % RAhours % RAminutes % RAseconds % DEdegrees % DEminutes % DEseconds).str();
}
