/*
 * featuresextractorfactory.h
 *
 *  Created on: 3 Dec 2016
 *      Author: Bartek
 */

#ifndef FEATURESEXTRACTOR_FEATURESEXTRACTORFACTORY_H_
#define FEATURESEXTRACTOR_FEATURESEXTRACTORFACTORY_H_

#include "ifeaturesextractor.h"

class ILogger;

class FeaturesExtractorFactory
{
public:
	FeaturesExtractorFactory(ILogger& logger);
	IFeaturesExtractorPtr GetFeaturesExtractor(BrightnessLinearizer linearizer);
private:
	ILogger& m_Logger;
};

#endif /* FEATURESEXTRACTOR_FEATURESEXTRACTORFACTORY_H_ */
