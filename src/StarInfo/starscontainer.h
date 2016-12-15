// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef STARINFO_STARSCONTAINER_H_
#define STARINFO_STARSCONTAINER_H_

#include <boost/foreach.hpp>
#include <StarInfo/star.h>
#include <vector>
#include "Logger/ilogger.h"

//*****************************************************************************
class StarsContainer : public std::vector<Star>
{
public:
	StarsContainer() : std::vector<Star>() {}
	void AddStar(const Star& star){ push_back(star); }
	void LogStars(ILoggerPtr logger)
	{
		BOOST_FOREACH(Star& star, *this)
		{
			logger->Log(star.ToString());
		}
	}
};

typedef boost::shared_ptr<StarsContainer> StarsContainerPtr;

#endif // STARINFO_STARSCONTAINER_H_ 
