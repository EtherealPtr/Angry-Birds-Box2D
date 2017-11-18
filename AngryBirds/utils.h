//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: util.h
// Description	: utility functions
// Author		: Rony Hanna 
// Mail			: ron.han7006@mediadesign.school.nz | aleandro.val6884@mediadesign.school.nz
//

#pragma once

#include "Dependencies\SFML\include\SFML\Graphics.hpp"

namespace
{
	constexpr float SCALE = 25.0f;

	/***********************
	* ConvertPixelsToMeters
	* @author: Rony Hanna | Aleandro Valancia
	* @parameter: float&, float&
	* @return: None
	* @Information: Function that converts 2 given values from pixel coordinate to Box2d's meters
	********************/
	void ConvertPixelsToMeters(float &a, float &b)
	{
		a /= 25.0f;
		b /= 25.0f;
	}

	/***********************
	* ConvertMetersToPixels
	* @author: Rony Hanna | Aleandro Valancia
	* @parameter: float&, float&
	* @return: None
	* @Information: Function that converts 2 given values from Box2d's meters to pixel coordinate
	********************/
	void ConvertMetersToPixels(float& a, float& b)
	{
		a *= 25.0f;
		b *= 25.0f;
	}

}