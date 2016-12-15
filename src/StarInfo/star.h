// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef STARINFO_STAR_H_
#define STARINFO_STAR_H_

#include <boost/format.hpp>
#include "Mathematics/point.h"

typedef double (*BrightnessLinearizer)(const double);

double GetUnchangedBrightness(const double brightness);
double GetLogVsZeroBrightness(const double brightness);

//*****************************************************************************
class IFeaturesCarrier
{
public:
	virtual ~IFeaturesCarrier(){}
	virtual double GetXPosition() const = 0;
	virtual double GetYPosition() const = 0;
	virtual double GetMagnitude() const = 0;
	virtual std::string ToString() const = 0;
};

typedef boost::shared_ptr<IFeaturesCarrier> IFeaturesCarrierPtr;

//*****************************************************************************
struct Blob : public Point, IFeaturesCarrier
{
	Blob(u32 xx, u32 yy, u32 ss) : Point(xx, yy), sizeOfBlob(ss), brightnessOnImage(0) {}

	u32 sizeOfBlob;
	u32 brightnessOnImage;

	double GetXPosition() const { return x; }
	double GetYPosition() const { return y; }
	double GetMagnitude() const { return brightnessOnImage; }

	//*****************************************************************************
	virtual std::string ToString() const
	//*****************************************************************************
	{
		return Point::ToString() + (boost::format(", size = %d brightness = %d") % sizeOfBlob % brightnessOnImage).str();
	}
};

//*****************************************************************************
class ADUMag : public Blob
{
public:
	ADUMag(const Blob& blob, const double m) : Blob(blob), magnitude(m) {}
	ADUMag(const u32 adu, const double m) : Blob(0, 0, 0), magnitude(m)
	{
		Blob::brightnessOnImage = adu;
	}

	u32    GetADU() const { return brightnessOnImage; }
	double GetMag() const { return magnitude; }
	void   SetADU(const u32 a){ brightnessOnImage = a;}
	void   SetMag(const u32 m){ magnitude = m;}
	//*****************************************************************************
	virtual std::string ToString() const
	//*****************************************************************************
	{
		return Blob::ToString() + (boost::format("ADU = %d, mag = %f") % brightnessOnImage % magnitude).str();
	}
private:
	double magnitude;
};

const i32 iRA_Multiplier = 15*3600*100;
const i32 iDEC_Shift = 90;
const i32 iDEC_Multiplier = 3600*100;

i32 GetI32RAFromFloat(const double& fRA);
i32 GetI32DECFromFloat(const double& fDEC);

//*****************************************************************************
struct CelestialPoint
{
	virtual ~CelestialPoint(){}
	CelestialPoint(const double ra, const double de) : RA(ra), DE(de) {}
	virtual std::string ToString() const;
	double RA;
	double DE;
};

//*****************************************************************************
struct Star : public ADUMag
{
	Star(const ADUMag& adumag, const CelestialPoint& cpoint) : ADUMag(adumag), m_CPoint(cpoint) {}
	Star(const double ra, const double de, const double mag) : ADUMag(0, mag), m_CPoint(ra, de) {}
	std::string ToString() const { return ADUMag::ToString() + ", " + m_CPoint.ToString(); }

	double GetRA() const { return m_CPoint.RA; }
	double GetDE() const { return m_CPoint.DE; }

	CelestialPoint m_CPoint;
};

//*****************************************************************************
struct RefStar : public CelestialPoint, IFeaturesCarrier
{
	RefStar(const double ra, const double de, const double mag) : CelestialPoint(ra, de), m_Magnitude(mag) {}
	RefStar(const CelestialPoint& cp) : CelestialPoint(cp), m_Magnitude(0) {}

	double GetXPosition() const { return RA; }
	double GetYPosition() const { return DE; }
	double GetMagnitude() const { return m_Magnitude; }

	std::string ToString() const { return CelestialPoint::ToString() + (boost::format(" mag = %8.5f") % m_Magnitude).str(); }
	double m_Magnitude;
};

typedef std::vector<RefStar> RefStarVector;

#endif // STARINFO_STAR_H_ 
