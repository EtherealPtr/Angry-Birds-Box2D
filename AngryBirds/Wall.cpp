// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Wall.cpp
// Description	: Wall class implementation
// Author		: Rony Hanna 
// Mail			: Rony.han7006@mediadesign.school.nz

#include "Wall.h"

/***********************
* Ground Constructor
* @author: Rony Hanna 
* @parameter: None
* @return: None
* @Information: Constructor that initializes wall components
********************/
Wall::Wall()
{
	m_WallWidth = 60.0f;
	m_WallHeight = 1000.0f;
	m_WallSalar = 25.0f;
}

/***********************
* CreateWall
* @author: Rony Hanna 
* @parameter: b2World*, float, float
* @return: None
* @Information: Function that creates a wall static body and adds it to the world
********************/
void Wall::CreateWall(b2World* TheWorld, float PosX, float PosY)
{
	b2BodyDef wallBodyDef;
	ConvertPixelsToMeters(PosX, PosY);
	wallBodyDef.position.Set(PosX, PosY);
	wallBodyDef.type = b2_staticBody;
	b2Body* wall = TheWorld->CreateBody(&wallBodyDef);
	wall->SetUserData("Wall");

	b2PolygonShape wallShape;
	float GroundWidth = m_WallWidth / 2.0f;
	float GroundHeight = m_WallHeight / 2.0f;
	ConvertPixelsToMeters(GroundWidth, GroundHeight);
	wallShape.SetAsBox(GroundWidth, GroundHeight);

	b2FixtureDef Fixture;
	Fixture.shape = &wallShape;
	Fixture.density = 0.0f;
	Fixture.friction = 10.0f;
	Fixture.restitution = 0.5f;

	wall->CreateFixture(&Fixture);
}

/***********************
* ConvertPixelsToMeters
* @author: Rony Hanna 
* @parameter: float&, float&
* @return: None
* @Information: Function that converts 2 given values from pixel coordinate to Box2d's meters
********************/
void Wall::ConvertPixelsToMeters(float& a, float& b)
{
	a /= m_WallSalar;
	b /= m_WallSalar;
}