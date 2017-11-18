// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Plank.h
// Description	: A class that represents a Plank object in the scene 
// Author		: Rony Hanna
// Mail			: Rony.han7006@mediadesign.school.nz

#pragma once
#ifndef __PLANK_H__
#define __PLANK_H__

#include "Dependencies\Box2D\include\Box2D\Box2D.h"
#include "utils.h"

class Plank 
{
public:
	Plank();
	~Plank();

	void StartContact() { m_collision = true; };
	void TerminateContact() { m_collision = false; };

	void CreatePlank(b2World*, float _posX, float _posY, char* _texturePath);

	void SetCollisionStatus(bool _collisionStatusReset) { m_collision = _collisionStatusReset; };
	inline bool GetCollisionStatus() { return m_collision; };

	void Render(sf::RenderWindow& _window);
	void Reset(float _x, float _y);

private:
	b2Body* m_plankBody;

	float m_PlankSalar;
	float m_PlankWidth;
	float m_PlankHeight;

	bool m_collision = false;

	sf::Sprite m_Sprite;
	sf::Texture m_Texture;
};

#endif // !__PLANK_H__