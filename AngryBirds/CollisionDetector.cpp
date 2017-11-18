// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: CollisionDetector.cpp
// Description	: CollisionDetector class implementation
// Author		: Rony Hanna 
// Mail			: Rony.han7006@mediadesign.school.nz

#include "CollisionDetector.h"
#include "Ground.h"

/***********************
* CollisionDetector
* @author: Rony Hanna 
* @parameter: None
* @return: None
* @Information: None
********************/
CollisionDetector::CollisionDetector()
{
}

/***********************
* ~CollisionDetector
* @author: Rony Hanna 
* @parameter: None
* @return: None
* @Information: None
********************/
CollisionDetector::~CollisionDetector()
{
}

/***********************
* BeginContact
* @author: Rony Hanna 
* @parameter: b2Contact*
* @return: None
* @Information: Function that checks for collision
********************/
void CollisionDetector::BeginContact(b2Contact* _contact)
{
	auto bodyUserDataOne = _contact->GetFixtureA()->GetBody()->GetUserData();
	auto bodyUserDataTwo = _contact->GetFixtureB()->GetBody()->GetUserData();
	
	if (bodyUserDataOne && bodyUserDataTwo == "Ground")
	{
		if (bodyUserDataOne != "Plank")
			static_cast<Box*>(bodyUserDataOne)->BeginContact();
	}
	if (bodyUserDataOne == "Player" && bodyUserDataTwo)
	{
		if (bodyUserDataTwo != "Player")
			static_cast<Enemy*>(bodyUserDataTwo)->PlayerCollision();
	}
	if (bodyUserDataOne == "Ground" && bodyUserDataTwo)
	{
		if (bodyUserDataTwo != "Player")
			static_cast<Enemy*>(bodyUserDataTwo)->GroundCollision();
	}
}

/***********************
* EndContact
* @author: Rony Hanna  
* @parameter: b2Contact*
* @return: None
* @Information: Function that checks for end of collision
********************/
void CollisionDetector::EndContact(b2Contact* _contact)
{
	auto bodyUserDataOne = _contact->GetFixtureA()->GetBody()->GetUserData();
	auto bodyUserDataTwo = _contact->GetFixtureB()->GetBody()->GetUserData();
}