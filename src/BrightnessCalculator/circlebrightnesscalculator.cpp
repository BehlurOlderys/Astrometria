/*
 * circlebrightnesscalculator.cpp
 *
 *  Created on: 29 Nov 2016
 *      Author: Bartek
 */


#include "circlebrightnesscalculator.h"
#include <StarInfo/star.h>
#include <iostream>
//*****************************************************************************
CircleBrightnessCalculator::CircleBrightnessCalculator(const uint32 radius) :
	m_Radius(radius),
	m_R2(radius*radius)
//*****************************************************************************
{}

//*****************************************************************************
uint32 CircleBrightnessCalculator::CalculateBrightnessForPixel(const RasterImagePtr pImage, const Point& center)
//*****************************************************************************
{
	uint32 brightness = 0;
	const int w = pImage->Width;
	const int h = pImage->Height;

	const int xx = center.x;
	const int yy = center.y;

	std::cout <<" w= " <<w<<", h="<<h<<", xx="<<xx<<", yy="<<yy;

	for (int j = std::max(0, yy - m_Radius); j < std::min(h - 1, yy + m_Radius); ++j)
	{
		for (int i = std::max(0, xx - m_Radius); i < std::min(w, xx + m_Radius); ++i)
		{
			const int distance2 = (xx - i)*(xx - i) + (yy - j)*(yy - j);
			if (distance2 < m_R2)
			{
				brightness += pImage->GetLum(j * w + i);
			}
		}
	}
	std::cout <<", b= "<<brightness<<std::endl;
	return brightness;
}
