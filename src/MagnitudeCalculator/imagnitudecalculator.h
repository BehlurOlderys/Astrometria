// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef MAGNITUDECALCULATOR_IMAGNITUDECALCULATOR_H_
#define MAGNITUDECALCULATOR_IMAGNITUDECALCULATOR_H_



//*****************************************************************************
class IMagnitudeCalculator
{
public:
	virtual ~IMagnitudeCalculator(){}
	virtual double CalculateMagnitudeFromADU(const u32) = 0;
};

//*****************************************************************************
class NullMagnitudeCalculator : public IMagnitudeCalculator
{
public:
	NullMagnitudeCalculator(){}
	double CalculateMagnitudeFromADU(const u32){ return 0.; }
};

//*****************************************************************************
struct ADUMagByAduComparator
{
	//*****************************************************************************
	inline bool operator() (const ADUMag& am1, const ADUMag& am2)
    //*****************************************************************************
    {
        return (am1.GetADU() < am2.GetADU());
    }
};

//*****************************************************************************
class SimplestMagnitudeCalculator : public IMagnitudeCalculator
{
public:
	//*****************************************************************************
	SimplestMagnitudeCalculator(const std::vector<ADUMag>& vStars) :
		m_vStars(vStars)
	//*****************************************************************************
	{
	}
	//*****************************************************************************
	double CalculateMagnitudeFromADU(const u32 adu)
	//*****************************************************************************
	{
		std::sort(m_vStars.begin(), m_vStars.end(), ADUMagByAduComparator());
		const ADUMag Lowest = m_vStars.front();
		const ADUMag Highest = m_vStars.back();

		const double a = double(Highest.GetMag() - Lowest.GetMag()) / double(Highest.GetADU() - Lowest.GetADU());
		const double b = Highest.GetMag() - double(Highest.GetADU()) * a;

		return adu * a + b;
	}
private:
	std::vector<ADUMag> m_vStars;
};

#endif // MAGNITUDECALCULATOR_IMAGNITUDECALCULATOR_H_ 
