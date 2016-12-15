/*
 * testrefstarsprovider.cpp
 *
 *  Created on: 29 Nov 2016
 *      Author: Bartek
 */

#include <fstream>
#include "testrefstarsprovider.h"
#include "Logger/ilogger.h"
#include "Options/options.h"
#include "common.h"

namespace
{
//*****************************************************************************
int is_big_endian(void)
//*****************************************************************************
{
    union {
        u32 i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1;
}

//*****************************************************************************
union Num
{
    char buffer[4];
    i32 num;
};

//*****************************************************************************
void swapChars(char* pChar1, char* pChar2)
//*****************************************************************************
{
    char temp = *pChar1;
    *pChar1 = *pChar2;
    *pChar2 = temp;
}

//*****************************************************************************
i32 swapOrder(Num& num)
//*****************************************************************************
{
    swapChars( &num.buffer[0], &num.buffer[3]);
    swapChars( &num.buffer[1], &num.buffer[2]);

    return num.num;
}

//*****************************************************************************
i32 ReadBigEndiani32FromBinaryFile(std::ifstream& file)
//*****************************************************************************
{
	Num num;
	file.read(num.buffer, sizeof(num.buffer));

	if (!is_big_endian())
	{
		swapOrder(num);
	}
	return num.num;
}

//*****************************************************************************
double GetMeanMag(i32 rawMag)
//*****************************************************************************
{
	i32 uRawMag = std::abs(rawMag);
	return double(uRawMag - (1000* (uRawMag/1000))) / 10.0;
//
//	rawMag /= 1000;
//	const i32 iBlueMag = rawMag % 1000;
//	return (iRedMag + iBlueMag) / 20.0;
}

} // namespace

//*****************************************************************************
TestRefStarsProvider::TestRefStarsProvider(const std::string& sFileName,
										   ILogger& logger,
										   const double fMaxMag) :
	m_sFileName(sFileName),
	m_Logger(logger),
	m_fMaxMagnitude(fMaxMag)
//*****************************************************************************
{}

//*****************************************************************************
void TestRefStarsProvider::ProvideRefStars(RefStarVector& vStars)
//*****************************************************************************
{
	std::ifstream inputFile(m_sFileName.c_str(), std::ios::in | std::ios::binary);

	if (!inputFile.good())
	{
		m_Logger.Log("Plik nie udalo sie otworzyc!: >>" + m_sFileName + "<<");
		return;
	}

	u32 counter = 0;

	while (inputFile.good())
	{
		i32 ra = ReadBigEndiani32FromBinaryFile(inputFile);
		i32 de = ReadBigEndiani32FromBinaryFile(inputFile);
		double ma = GetMeanMag(ReadBigEndiani32FromBinaryFile(inputFile));
		counter++;
		if (ma < m_fMaxMagnitude)
		{
			vStars.push_back(RefStar(ra, de, ma));
		}
	}
	m_Logger.Log((boost::format("Dodano wlasnie %d (total = %d) gwiazd z katalogu %s! (max magnitude = %f)")
			% vStars.size()
			% counter
			% m_sFileName
			% m_fMaxMagnitude).str());
}
