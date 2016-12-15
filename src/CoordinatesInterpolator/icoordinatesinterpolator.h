// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef COORDINATESINTERPOLATOR_ICOORDINATESINTERPOLATOR_H_
#define COORDINATESINTERPOLATOR_ICOORDINATESINTERPOLATOR_H_

#include "StarInfo/starscontainer.h"
#include "Mathematics/area.h"
#include "Logger/ilogger.h"

class ICoordinatesInterpolator
{
public:
	virtual ~ICoordinatesInterpolator(){}
	virtual CelestialPoint InterpolateCoordinates(const Blob&) = 0;
};

class NullCoordinatesInterpolator : public ICoordinatesInterpolator
{
public:
	NullCoordinatesInterpolator(){}
	CelestialPoint InterpolateCoordinates(const Blob&){ return CelestialPoint(0, 0); }
};

class BarycentricCoordinatesInterpolator : ICoordinatesInterpolator
{
public:
	BarycentricCoordinatesInterpolator(ILogger& pLogger, const StarsContainer& stars) : m_Logger(pLogger), m_Stars(stars){}
	CelestialPoint InterpolateCoordinates(const Blob& blob)
	{
		if (m_Stars.size() < 3)
		{
			m_Logger.Log("InterpolateCoordinates: Too few stars to interpolate!");
			return CelestialPoint(0, 0);
		}

		const Point& D(blob);

		const Star& A = m_Stars[0];
		const Star& B = m_Stars[1];
		const Star& C = m_Stars[2];

		if (!PointInTriangle(D, A, B, C))
		{
			m_Logger.Log("InterpolateCoordinates: Point doesn't lie inside triangle!");
			return CelestialPoint(0, 0);
		}

		const double areaTotal = TriangleArea(A, B, C);
		const double areaForA = TriangleArea(B, C, D);
		const double areaForB = TriangleArea(A, C, D);
		const double areaForC = TriangleArea(A, B, D);

		const double ra = A.GetRA() * (areaForA / areaTotal) + B.GetRA() * (areaForB / areaTotal) + C.GetRA() * (areaForC / areaTotal);
		const double de = A.GetDE() * (areaForA / areaTotal) + B.GetDE() * (areaForB / areaTotal) + C.GetDE() * (areaForC / areaTotal);
		return CelestialPoint(i32(ra), i32(de));
	}
private:
	ILogger& m_Logger;
	const StarsContainer& m_Stars;
};

#endif // COORDINATESINTERPOLATOR_ICOORDINATESINTERPOLATOR_H_ 
