// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef REFSTARSPROVIDER_TESTREFSTARSPROVIDER_H_
#define REFSTARSPROVIDER_TESTREFSTARSPROVIDER_H_

#include "irefstarsprovider.h"

class ILogger;

class TestRefStarsProvider : public IRefStarsProvider
{
public:
	TestRefStarsProvider(const std::string& sFileName, ILogger& logger, const double fMaxMag);
	void ProvideRefStars(RefStarVector& vStars);
private:
	const std::string& m_sFileName;
    ILogger&		   m_Logger;
    const double 	   m_fMaxMagnitude;
};

#endif // REFSTARSPROVIDER_TESTREFSTARSPROVIDER_H_ 
