// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef MATHEMATICS_POINT_H_
#define MATHEMATICS_POINT_H_

#include "common.h"

//*****************************************************************************
struct Point
{
	Point(u32 xx, u32 yy) : x(xx), y(yy) {}
	int x;
	int y;

	virtual ~Point(){}

	//*****************************************************************************
	virtual std::string ToString() const
	//*****************************************************************************
	{
		return (boost::format("[%d, %d]") % x % y ).str();
	}
};

#endif // MATHEMATICS_POINT_H_ 
