/*
 * testfeaturesextrator.cpp
 *
 *  Created on: 3 Dec 2016
 *      Author: Bartek
 */

#include "testfeaturesextractor.h"
#include <boost/foreach.hpp>
#include <limits>
#include <cmath>
#include <numeric>
#include <utility>
#include <iostream>
#include "Mathematics/distance.h"
#include "Logger/ilogger.h"
#include "Mathematics/distance.h"

namespace
{

const double UNINITIALIZED_DISTANCE = -1.0;
const double MAX_DISTANCE = std::numeric_limits<double>::max();

//*****************************************************************************
struct DistanceCalculator
{
	//*****************************************************************************
	explicit DistanceCalculator(const std::vector<IFeaturesCarrierPtr>& vInput) :
		 m_vInput(vInput),
		 m_N(vInput.size()),
		 m_vDistances()
	//*****************************************************************************
	{
		m_vDistances = new DistanceAndIndex * [m_N];
		for (u64 i = 0; i < m_N; ++i)
		{
			m_vDistances[i] = new DistanceAndIndex[m_N];

			for (u64 j = 0; j < m_N; ++j)
			{
				m_vDistances[i][j].m_uIndex1 = i;
				m_vDistances[i][j].m_uIndex2 = j;
			}
		}
	}

	//*****************************************************************************
	void CalculateDistances()
	//*****************************************************************************
	{
		for (u64 uRow = 0; uRow < m_N; ++uRow)
		{
			m_vDistances[uRow][uRow].SetDistance(MAX_DISTANCE);
			for (u64 uColl=0; uColl < uRow; ++uColl)
			{
				m_vDistances[uRow][uColl].SetDistance(distance::CalculateSquare2D_FC(*m_vInput[uRow], *m_vInput[uColl]));
				m_vDistances[uColl][uRow].SetDistance(m_vDistances[uRow][uColl].GetDistance()); // distance is symmetric
			}
		}
	}

	//*****************************************************************************
	DistanceAndIndex* GetDistancesForIndex(const u64 index)
	//*****************************************************************************
	{
		return m_vDistances[index];
	}

	//*****************************************************************************
	DistanceAndIndex GetDistanceForIndices(const u64 index1, const u64 index2)
	//*****************************************************************************
	{
		return m_vDistances[index1][index2];
	}


	//*****************************************************************************
	virtual ~DistanceCalculator()
	//*****************************************************************************
	{
		for (u64 i = 0; i < m_N; ++i)
		{
			delete [] m_vDistances[i];
		}
		delete [] m_vDistances;
	}
	const std::vector<IFeaturesCarrierPtr>& m_vInput;
	u64      								m_N;
	DistanceAndIndex** 						m_vDistances;
};

} // namespace

//*****************************************************************************
TestFeaturesExtractor::TestFeaturesExtractor(BrightnessLinearizer linearizer,
		 	 	 	 	 	 	 	 	 	 ILogger& logger) : m_Linearizer(linearizer), m_Logger(logger)
//*****************************************************************************
{}

//*****************************************************************************
void TestFeaturesExtractor::ExtractFeatures(const std::vector<IFeaturesCarrierPtr>& vInput,
						 	 	 	 	 	std::vector<FeaturePtr>& vOutput)
//*****************************************************************************
{
	// initialize distances:
	const u64 N = vInput.size();
	const u32 uCrowdnessParameterN = 10;

	DistanceCalculator distanceCalculator(vInput);
	distanceCalculator.CalculateDistances();

	u64 carrierIndex = 0;
	BOOST_FOREACH(const IFeaturesCarrierPtr carrier, vInput)
	{
		const IFeaturesCarrier& referenceObject = *carrier;
		vOutput.push_back(FeaturePtr(new Feature()));
		FeaturePtr currentFeature = vOutput.back();
		const DistanceAndIndex* vDistances = distanceCalculator.GetDistancesForIndex(carrierIndex++);
		DistanceAndIndex* vDistancesFromRef = new DistanceAndIndex [N];
		std::memcpy(vDistancesFromRef, vDistances, sizeof(DistanceAndIndex)*N);
		std::sort(&vDistancesFromRef[0], &vDistancesFromRef[N], DistanceAndIndexByDistance()); // ascending order

		if ( N < uCrowdnessParameterN)
		{
			continue;
		}

		const double fMostDistantFromN = vDistancesFromRef[uCrowdnessParameterN - 1].GetDistance();
		double fMeanDistanceFromN = 0.;
		for (u32 index = 0; index < uCrowdnessParameterN; ++index)
		{
			fMeanDistanceFromN += vDistancesFromRef[index].GetDistance();
		}
		fMeanDistanceFromN /= double(uCrowdnessParameterN);

		// First feature: ratio of mean distance to max distance for N closest stars:
		currentFeature->m_vValues[CROWDNESS_INDEX] = fMeanDistanceFromN / fMostDistantFromN; // this assures values from 0 to 1

		// second feature: angle to brighter of two closest neighbours
	    // third feature: angle to dimmer of two closest neighbours

		const u64 uFirstNeighbourIndex =vDistancesFromRef[0].GetSecondIndex();
		const u64 uSecondNeighbourIndex =vDistancesFromRef[1].GetSecondIndex();

		const IFeaturesCarrier& closestNeighbour1 = *vInput[uFirstNeighbourIndex];
		const IFeaturesCarrier& closestNeighbour2 = *vInput[uSecondNeighbourIndex];

		const double fClosestNeighbour1Brightness = m_Linearizer(closestNeighbour1.GetMagnitude());
		const double fClosestNeighbour2Brightness = m_Linearizer(closestNeighbour2.GetMagnitude());

		if (carrierIndex < 4)
		{
			std::cout<<"Magnitude 1 = "<<closestNeighbour1.GetMagnitude() << std::endl;
			std::cout<<"Magnitude 2 = "<<closestNeighbour2.GetMagnitude() << std::endl;

			std::cout<<"Lin. Magnitude 1 = "<<fClosestNeighbour1Brightness << std::endl;
			std::cout<<"Lin. Magnitude 2 = "<<fClosestNeighbour2Brightness << std::endl;

		}
		const bool N1brighterThanN2 = fClosestNeighbour1Brightness > fClosestNeighbour2Brightness;
		const u64 brighterNeighbourIndex = N1brighterThanN2 ? 0 : 1;
		const u64 dimmerNeighbourIndex = N1brighterThanN2 ? 1 : 0;

		const double fP12 = vDistancesFromRef[brighterNeighbourIndex].GetDistance();
		const double fP13 = vDistancesFromRef[dimmerNeighbourIndex].GetDistance();
		const double fP23 = distanceCalculator.GetDistanceForIndices(uFirstNeighbourIndex, uSecondNeighbourIndex).GetDistance();
		//arccos((P12^2+ P13^2- P23^2) / (2 * P12 * P13))

		currentFeature->m_vValues[ANGLE_B_R_D] = std::acos((fP13 + fP23 - fP12) / (2.0 * sqrt(fP13) * sqrt(fP23))) / M_PI; // so it is between 0 and 1
		currentFeature->m_vValues[ANGLE_B_D_R] = std::acos((fP13 + fP12 - fP23) / (2.0 * sqrt(fP13) * sqrt(fP12))) / M_PI;
		currentFeature->m_vValues[LENGTH_R_B] = fP12 / (fP12 + fP13 + fP23);


		const double fRefBrightness = m_Linearizer(referenceObject.GetMagnitude());
		const double fDimmest   = std::min(std::min(fClosestNeighbour1Brightness, fClosestNeighbour2Brightness), fRefBrightness);
		const double fBrightest = std::max(std::max(fClosestNeighbour2Brightness, fClosestNeighbour2Brightness), fRefBrightness);
		const double fSumOfBrightness = fClosestNeighbour1Brightness + fClosestNeighbour2Brightness + fRefBrightness - ( 3.0 * fDimmest);

		currentFeature->m_vValues[BRIGHTNESS_RATIO_R_TO_ALL] = (fBrightest - fDimmest) / fSumOfBrightness; // TODO: the same so far!
		currentFeature->m_vValues[BRIGHTNESS_RATIO_B_TO_ALL] = (fBrightest - fDimmest) / fSumOfBrightness;
		delete [] vDistancesFromRef;
	}
}
