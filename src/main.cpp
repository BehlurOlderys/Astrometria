//============================================================================
// Name        : Test.cpp
// Author      : Bart³omiej Hnatio
// Version     :
// Copyright   : copyright Bart³omiej Hnatio 2016
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "BrightnessCalculator/brightnesscalculatorfactory.h"
#include "Logger/loggerfactory.h"
#include "FileOpener/fileopenerfactory.h"
#include "StarsExtractor/starsextractorfactory.h"
#include "MagnitudeCalculator/imagnitudecalculator.h"
#include "CoordinatesInterpolator/icoordinatesinterpolator.h"
#include "FeaturesExtractor/ifeaturesextractor.h"
#include "RefStarsProvider/refstarsproviderfactory.h"
#include "FeaturesExtractor/featuresextractorfactory.h"
#include "ImageSaver/imagesaverfactory.h"
#include "configreader.h"
#include "Mathematics/distance.h"

const int iMinArguments = 2;
const std::string sOutputFileName = "wynik.log";

struct RefStarByRA
{
    inline bool operator() (const RefStar& struct1, const RefStar& struct2)
    {
        return (struct1.RA < struct2.RA);
    }
};

struct RefStarByDEC
{
    inline bool operator() (const RefStar& struct1, const RefStar& struct2)
    {
        return (struct1.DE < struct2.DE);
    }
};

struct RefStarByMag
{
    inline bool operator() (const RefStar& struct1, const RefStar& struct2)
    {
        return (struct1.m_Magnitude < struct2.m_Magnitude);
    }
};

//*****************************************************************************
void FilterStarsFromRectangularRange(std::vector<RefStar>& input,
									 std::vector<RefStar>& output,
									 const RefStar& lowEnd,
									 const RefStar& highEnd)
//*****************************************************************************
{
	typedef std::vector<RefStar>::iterator vRefIt;
	std::cout << (boost::format("Size of input by RA = %d") % input.size()).str() << std::endl;

	std::sort(input.begin(), input.end(), RefStarByRA());
	std::cout<< "Lowest = " << (input.front().ToString()) << std::endl;
	std::cout<< "Highest = " << (input.back().ToString()) << std::endl;

	vRefIt RAlow = std::lower_bound(input.begin(), input.end(), lowEnd, RefStarByRA());
	vRefIt RAup  = std::upper_bound(input.begin(), input.end(), highEnd, RefStarByRA());

	std::vector<RefStar> vRASorted(RAlow, RAup);

	if (vRASorted.empty())
	{
		std::cout<< "vRASorted EMPTY!" << std::endl;
		return;
	}
	std::cout<< "RAlow = " << vRASorted.front().ToString() << std::endl;
	std::cout<< "RAup = " << vRASorted.back().ToString() << std::endl;
	std::cout << (boost::format("Size of sorted by RA = %d") % vRASorted.size()).str() << std::endl;

	std::sort(vRASorted.begin(), vRASorted.end(), RefStarByDEC());
	std::cout<< "Lowest = " << (vRASorted.front().ToString()) << std::endl;
	std::cout<< "Highest = " << (vRASorted.back().ToString()) << std::endl;

	std::cout<< "Low DEC = " << (lowEnd.ToString()) << std::endl;
	std::cout<< "High DEC = " << (highEnd.ToString()) << std::endl;

	vRefIt DEClow = std::lower_bound(vRASorted.begin(), vRASorted.end(), lowEnd, RefStarByDEC());
	vRefIt DECup  = std::upper_bound(vRASorted.begin(), vRASorted.end(), highEnd, RefStarByDEC());

	output.insert(output.begin(), DEClow, DECup);
	if (output.empty())
	{
		std::cout<< "output EMPTY!" << std::endl;
		return;
	}
	std::cout<< "DEClow = " << output.front().ToString() << std::endl;
	std::cout<< "DECup = " << output.back().ToString() << std::endl;

	std::sort(output.begin(), output.end(), RefStarByMag());
}

std::vector< RasterImagePtr > g_vImages;

//*****************************************************************************
void TestAlgorithms(const ILoggerPtr& pLogger)
//*****************************************************************************
{
	pLogger->Log((boost::format("Za malo argumentow (potrzeba przynajmniej %d!)") % iMinArguments).str());
	pLogger->Log("Tryb testowy!");
	std::vector<ADUMag> testSet;
	testSet.push_back(ADUMag(1, 3));
	testSet.push_back(ADUMag(2, 3));
	testSet.push_back(ADUMag(6, 4));
	testSet.push_back(ADUMag(12, 7));
	testSet.push_back(ADUMag(14, 7));
	const u32 adu = 9;
	SimplestMagnitudeCalculator magnitudeCalculator(testSet);
	const double mag = magnitudeCalculator.CalculateMagnitudeFromADU(adu);
	ADUMag result(adu, mag);
	pLogger->Log(result.ToString());
	testSet[0].x = 1;
	testSet[0].y = 1;
	testSet[1].x = 1;
	testSet[1].y = 6;
	testSet[2].x = 8;
	testSet[2].y = 6;
	StarsContainer vStars;
	vStars.push_back(Star(testSet[0], CelestialPoint(5000, 1700)));
	vStars.push_back(Star(testSet[1], CelestialPoint(5000, 1705)));
	vStars.push_back(Star(testSet[2], CelestialPoint(5007, 1705)));
	Blob blobZly(4, 2, 0);
	Blob blobDobry(4, 4, 0);
	BarycentricCoordinatesInterpolator interpolator(*pLogger, vStars);
	pLogger->Log( "Blob zly: " + interpolator.InterpolateCoordinates(blobZly).ToString());
	pLogger->Log( "Blob dobry: " + interpolator.InterpolateCoordinates(blobDobry).ToString());
}

//*****************************************************************************
int main(int argc, char* argv[])
{
	std::cout << " Hello, world!" << std::endl;

	LoggerFactory loggerFactory;
	ILoggerPtr pLogger = loggerFactory.GetLogger("stdout");

	if (argc < iMinArguments)
	{
		TestAlgorithms(pLogger);
		return 0;
	}

	const char* sImageFileName = argv[1];
	ReadConfigFile(pLogger);

	// Here logger is switched to file:
	pLogger.reset();
	pLogger = loggerFactory.GetLogger(Options::g_GlobalOptions.sLoggerType);

	// Getting reference stars:
	std::vector<RefStar> referenceStars;
	RefStarsProviderFactory providerFactory(*pLogger);
	IRefStarsProviderPtr starsProvider = providerFactory.GetRefStarsProvider();
	starsProvider->ProvideRefStars(referenceStars);

	// Sort and get stars from certain area:
	std::sort(referenceStars.begin(), referenceStars.end(), RefStarByMag());
	pLogger->Log("+++++++++++++REFERENCE STARS+++++++++++++++");
	for (u32 i=0; i < std::min(referenceStars.size(), 30u); ++i)
	{
		pLogger->Log(referenceStars[i].ToString());
	}

	pLogger->Log("+++++++++++++FILTERED STARS+++++++++++++++");
	std::vector<RefStar> filtered;
	FilterStarsFromRectangularRange(referenceStars, filtered,
									RefStar(CelestialPoint(79.0, 34.0)),
									RefStar(CelestialPoint(80.0, 35.0)));

	pLogger->Log((boost::format("Size of filtered = %d") % filtered.size()).str());

	for (u32 i=0; i < std::min(filtered.size(), 1000u); ++i)
	{
		pLogger->Log((boost::format("%d: ") % i).str() + filtered[i].ToString());
	}

	// Get features carriers pointers from vector:
	std::vector<IFeaturesCarrierPtr> vFeatureCarriersFromRefStars;
	BOOST_FOREACH(RefStar& refStar, filtered)
	{
		vFeatureCarriersFromRefStars.push_back(IFeaturesCarrierPtr(new RefStar(refStar)));
	}

	//=======================IMAGE PART=============================
	// This part deals with image file:
	FileOpenerFactory fileOpenerFactory(*pLogger);
	IFileOpenerPtr fileOpener = fileOpenerFactory.GetFileOpener();
	RasterImagePtr pImage = fileOpener->OpenFile(sImageFileName);

	if (!pImage)
	{
		pLogger->Log("Nie udalo sie stworzyc obrazu!");
		return -1;
	}

	// THIS IS ONLY A TEST: save monochromatic image
	ImageSaverFactory imageSaverFactory;
	IImageSaverPtr intermediateImageSaver = imageSaverFactory.GetImageSaver("intermediate");
	intermediateImageSaver->SaveImage(RasterImagePtr(ConvertToGreyscale(pImage)), "initial_greyscale");

	pLogger->Log((boost::format("Zostalo skopiowane %d pikseli a rozmiar wektora obrazow wynosi %d") % pImage->GetPixelNumber() % g_vImages.size()).str());

	// Here we extract stars from image:
	StarsExtractorFactory starsExtractorFactory(*pLogger);
	IStarsExtractorPtr starsExtractor = starsExtractorFactory.GetStarExtractor(*intermediateImageSaver);
	std::vector<IFeaturesCarrierPtr> vFeatureCarriersFromImage;
	starsExtractor->ExtractStars(pImage, vFeatureCarriersFromImage);

	// Log stars:
	u32 counter = 0;
	BOOST_FOREACH(IFeaturesCarrierPtr pFeatCarrier, vFeatureCarriersFromImage)
	{
		pLogger->Log((boost::format("%d: ") % counter++).str() + pFeatCarrier->ToString());
	}

	// Extract features from image stars:
	FeaturesExtractorFactory featuresExtractorFactory(*pLogger);
	IFeaturesExtractorPtr pImageFeatureExtractor = featuresExtractorFactory.GetFeaturesExtractor(GetUnchangedBrightness);
	std::vector<FeaturePtr> vImageFeatures;
	pImageFeatureExtractor->ExtractFeatures(vFeatureCarriersFromImage, vImageFeatures);

	// print
	counter = 0;
	pLogger->Log("+++++++++FEATURES from REFERENCE STARS++++++++++");
	BOOST_FOREACH(FeaturePtr feat, vImageFeatures)
	{
		if (counter++ > 1000)
		{
			break;
		}
		pLogger->Log((boost::format("%d: ") % counter).str() + feat->ToString());
	}

	// Extract and print features from ref stars:
	std::vector<FeaturePtr> vRefStarsFeatures;
	IFeaturesExtractorPtr pRefFeatureExtractor = featuresExtractorFactory.GetFeaturesExtractor(GetLogVsZeroBrightness);
	pRefFeatureExtractor->ExtractFeatures(vFeatureCarriersFromRefStars, vRefStarsFeatures);
	pLogger->Log("+++++++++FEATURES from IMAGE STARS++++++++++");

	counter = 0;
	BOOST_FOREACH(FeaturePtr feat, vRefStarsFeatures)
	{
		if (counter++ > 1000)
		{
			break;
		}
		pLogger->Log((boost::format("%d: ") % counter).str() + feat->ToString());
	}
	pLogger->Log((boost::format("Number of ref feats: %d, number of image feats: %d ") % vImageFeatures.size() % vRefStarsFeatures.size()).str());

	counter = 0;
	BOOST_FOREACH(FeaturePtr pImageFeat, vImageFeatures)
	{
		counter++;
		std::vector< DistanceAndIndex > vDistancesAndIndices;
		u64 refCounter = 0;
		BOOST_FOREACH(FeaturePtr pRefFeat, vRefStarsFeatures)
		{
			refCounter++;
			vDistancesAndIndices.push_back(DistanceAndIndex(distance::CalculateSquare_Feat(*pImageFeat, *pRefFeat), counter, refCounter));
		}

		std::sort(vDistancesAndIndices.begin(), vDistancesAndIndices.end(), DistanceAndIndexByDistance());
		pLogger->Log(vDistancesAndIndices[0].ToString());
	}
	//TODO:
	// Get distance 6D between features, sort them and check which are OK

}
