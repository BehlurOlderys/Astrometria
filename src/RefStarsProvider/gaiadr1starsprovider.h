// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef REFSTARSPROVIDER_GAIADR1STARSPROVIDER_H_
#define REFSTARSPROVIDER_GAIADR1STARSPROVIDER_H_

#include "irefstarsprovider.h"

class ILogger;

class GaiaDR1StarsProvider : public IRefStarsProvider
{
public:
	GaiaDR1StarsProvider(const std::string& sFileName,
				 		 ILogger& logger,
				 		 const double fMaxMag,
						 const u64 uMaxStars);
	void ProvideRefStars(RefStarVector& vStars);
private:
	const std::string& m_sFileName;
    ILogger&		   m_Logger;
    const double 	   m_fMaxMagnitude;
    u64 			   m_uMaxStars;
};

#endif // REFSTARSPROVIDER_GAIADR1STARSPROVIDER_H_ 
