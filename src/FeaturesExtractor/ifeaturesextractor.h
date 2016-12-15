// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef FEATURESEXTRACTOR_IFEATURESEXTRACTOR_H_
#define FEATURESEXTRACTOR_IFEATURESEXTRACTOR_H_

#define NUMBER_OF_FEATURES 6
#define CROWDNESS_INDEX 0
// R = star referenced, B = brighter of 2 closest neighbours, D = dimmer of two closest neighbours
#define ANGLE_B_R_D 1
#define ANGLE_B_D_R 2
#define LENGTH_R_B 3
#define BRIGHTNESS_RATIO_R_TO_ALL 4
#define BRIGHTNESS_RATIO_B_TO_ALL 5

#include <cstring>
#include "common.h"
#include "StarInfo/star.h"

struct Feature
{
	Feature() : m_vValues() { std::memset(m_vValues, 0, sizeof(m_vValues)); }

	std::string ToString() const { return (boost::format("Crowdness = %f,"
			" Angle BRD = %f, "
			"Angle BDR = %f, "
			"Length RB = %f, "
			"Ratio R to all = %f, "
			"Ratio B to all = %f") % m_vValues[CROWDNESS_INDEX]
								   % m_vValues[ANGLE_B_R_D]
								   % m_vValues[ANGLE_B_D_R]
								   % m_vValues[LENGTH_R_B]
								   % m_vValues[BRIGHTNESS_RATIO_R_TO_ALL]
								   % m_vValues[BRIGHTNESS_RATIO_B_TO_ALL]).str(); }
	double m_vValues[NUMBER_OF_FEATURES];
};

typedef boost::shared_ptr<Feature> FeaturePtr;

class IFeaturesExtractor
{
public:
	virtual ~IFeaturesExtractor(){}
	virtual void ExtractFeatures(const std::vector<IFeaturesCarrierPtr>& vInputFeaturesCarriers,
							     std::vector<FeaturePtr>& vOutputFeatures) = 0;
};

class NullFeaturesExtractor : public IFeaturesExtractor
{
public:
	NullFeaturesExtractor(){}
	void ExtractFeatures(const std::vector<IFeaturesCarrierPtr>&,
						 std::vector<FeaturePtr>&){}
};

typedef boost::shared_ptr<IFeaturesExtractor> IFeaturesExtractorPtr;

#endif // FEATURESEXTRACTOR_IFEATURESEXTRACTOR_H_ 
