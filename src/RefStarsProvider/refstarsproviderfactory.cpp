/*
 * refstarsproviderfactory.cpp
 *
 *  Created on: 29 Nov 2016
 *      Author: Bartek
 */

#include "refstarsproviderfactory.h"
#include "testrefstarsprovider.h"
#include "gaiadr1starsprovider.h"
#include "Options/options.h"
#include "Logger/ilogger.h"

//*****************************************************************************
RefStarsProviderFactory::RefStarsProviderFactory(ILogger& logger) :
	m_Logger(logger)
//*****************************************************************************
{}

//*****************************************************************************
IRefStarsProviderPtr RefStarsProviderFactory::GetRefStarsProvider()
//*****************************************************************************
{
	m_Logger.Log("GetRefStarsProvider");
	if (Options::g_GlobalOptions.sRefStarsProvider == "test")
	{
		m_Logger.Log("Chosen: test provider!");
		return IRefStarsProviderPtr(new TestRefStarsProvider(Options::g_GlobalOptions.sCatalogueFilePath,
															 m_Logger,
															 Options::g_GlobalOptions.fMaximalMagnitude));
	}
	else if (Options::g_GlobalOptions.sRefStarsProvider == "gaia")
	{
		m_Logger.Log("Chosen: Gaia DR1 stars catalogue with parameters:");

		m_Logger.Log((boost::format("sCatalogueFilePath = %s") % Options::g_GlobalOptions.sCatalogueFilePath).str());
		m_Logger.Log((boost::format("fMaximalMagnitude = %f") % Options::g_GlobalOptions.fMaximalMagnitude).str());
		m_Logger.Log((boost::format("uMaxStarsLoaded = %d") % Options::g_GlobalOptions.uMaxStarsLoaded).str());

		return IRefStarsProviderPtr(new GaiaDR1StarsProvider(Options::g_GlobalOptions.sCatalogueFilePath,
															 m_Logger,
															 Options::g_GlobalOptions.fMaximalMagnitude,
															 Options::g_GlobalOptions.uMaxStarsLoaded));
	}
	m_Logger.Log("Chosen: test provider!");
	return IRefStarsProviderPtr(new NullRefStarsProvider());
}
