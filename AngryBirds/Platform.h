// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Platform.h
// Description	: A class that represents a Platform   
// Author		: Rony Hanna 
// Mail			: Rony.han7006@mediadesign.school.nz

#pragma once
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "Box.h"
#include "utils.h"

class Platform
{
public:
	Platform();
	~Platform() { /* Do Nothing */ };

	void CreatePlatform(b2World*, float, float);

private:
	float m_platformScalingFactor;
	float m_platformWidth;
	float m_platformHeight;
};

#endif // !__PLATFORM_H__