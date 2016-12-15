/*
 * gaiadr1starsprovider.cpp
 *
 *  Created on: 1 Dec 2016
 *      Author: Bartek
 */

#include "gaiadr1starsprovider.h"


#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include "common.h"

#include <iostream>

#include "Logger/ilogger.h"


namespace
{

const u32 uRA_Index_InCsv = 0;
const u32 uDEC_Index_InCsv = 1;
const u32 uMAG_Index_InCsv = 2;

} // namespace

//*****************************************************************************
GaiaDR1StarsProvider::GaiaDR1StarsProvider(const std::string& sFileName,
										   ILogger& logger,
										   const double fMaxMag,
										   const u64 uMaxStars) :
	m_sFileName(sFileName),
	m_Logger(logger),
	m_fMaxMagnitude(fMaxMag),
	m_uMaxStars(uMaxStars)
//*****************************************************************************
{}

//*****************************************************************************
void GaiaDR1StarsProvider::ProvideRefStars(RefStarVector& vStars)
//*****************************************************************************
{
	std::ifstream inputFile(m_sFileName.c_str(), std::ios::in);

	if (!inputFile.good())
	{
		m_Logger.Log("GaiaDR1StarsProvider:: Plik nie udalo sie otworzyc!: >>" + m_sFileName + "<<");
		return;
	}

	m_Logger.Log((boost::format("Max stars = %d") % m_uMaxStars).str());

	u64 counter = 0;
	std::string sLine;
	std::getline(inputFile, sLine); // file header
	while(sLine.empty() || sLine[0] == '#')
	{
		std::getline(inputFile, sLine);
	}
	std::getline(inputFile, sLine); // headers
	std::getline(inputFile, sLine); // value types

	while (inputFile.good() && counter < m_uMaxStars)
	{
		counter++;
		std::string sLine;
		std::getline(inputFile, sLine);

		std::vector<std::string> sRows;
		boost::algorithm::split(sRows, sLine, boost::is_any_of(";"));

		try
		{
			double ra = boost::lexical_cast<double>(boost::trim_left_copy(sRows[uRA_Index_InCsv]));
			double de = boost::lexical_cast<double>(boost::trim_left_copy(sRows[uDEC_Index_InCsv]));
			double ma =boost::lexical_cast<double>(boost::trim_left_copy(sRows[uMAG_Index_InCsv]));

			if (ma < m_fMaxMagnitude)
			{
				vStars.push_back(RefStar(ra, de, ma));
			}
		}
		catch
		(...)
		{
			m_Logger.Log((boost::format("Parsowanie pliku sie nie udalo w linii %d!") % counter).str());
			return;
		}

	}
	m_Logger.Log((boost::format("Dodano wlasnie %d (total = %d) gwiazd z katalogu %s! (max magnitude = %f)")
			% vStars.size()
			% counter
			% m_sFileName
			% m_fMaxMagnitude).str());
}


