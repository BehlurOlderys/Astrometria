/*
 * testfeaturesextractor.h
 *
 *  Created on: 3 Dec 2016
 *      Author: Bartek
 */

#ifndef FEATURESEXTRACTOR_TESTFEATURESEXTRACTOR_H_
#define FEATURESEXTRACTOR_TESTFEATURESEXTRACTOR_H_

#include "ifeaturesextractor.h"

class ILogger;

class TestFeaturesExtractor : public IFeaturesExtractor
{
public:
	TestFeaturesExtractor(BrightnessLinearizer linearizer,
						  ILogger& logger);
	void ExtractFeatures(const std::vector<IFeaturesCarrierPtr>& vInput,
						 std::vector<FeaturePtr>& vOutput);
private:
	BrightnessLinearizer m_Linearizer;
	ILogger&			 m_Logger;
};

#endif /* FEATURESEXTRACTOR_TESTFEATURESEXTRACTOR_H_ */
