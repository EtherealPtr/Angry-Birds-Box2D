// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: CollisionDetector.h
// Description	: A subclass of b2ContactListener to tell us when the contact state of an object changes
// Author		: Rony Hanna  
// Mail			: Rony.han7006@mediadesign.school.nz

#pragma once
#ifndef __COLLISIONDETECTOR_H__
#define __COLLISIONDETECTOR_H__

#include "Box.h"
#include "Enemy.h"
#include "Plank.h"
#include "Dependencies\Box2D\include\Box2D\Box2D.h"

class CollisionDetector : public b2ContactListener
{
public:
	CollisionDetector();
	~CollisionDetector();

	void BeginContact(b2Contact* _contact);
	void EndContact(b2Contact* _contact);

private:
	int m_score;
};

#endif // !__COLLISIONDETECTOR_H__