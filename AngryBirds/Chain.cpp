// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Chain.cpp
// Description	: Chain class implementation
// Author		: Rony Hanna  
// Mail			: Rony.han7006@mediadesign.school.nz

#include "Chain.h"

/***********************
* Chain Constructor
* @author: Rony Hanna  
* @parameter: None
* @return: None
* @Information: Constructor that initializes Chain components
********************/
Chain::Chain()
{
	m_ChainScalingFactor = 25.0f;
	m_ChainHeight = 60.0f;
	m_ChainWidth = 60.0f;
}

/***********************
* InitChain
* @author: Rony Hanna  
* @parameter: b2World*
* @return: None
* @Information: Function that creates a static ground body
********************/
void Chain::InitChain(b2World* _world)
{
	b2BodyDef bodyDef;
	m_Groundbody = _world->CreateBody(&bodyDef);
	b2Vec2 tmp(5.0f, -2.0f);
	m_Groundbody->SetTransform(tmp, 0.0f); // Set it far away from camera space
}

/***********************
* CreateChain
* @author: Rony Hanna  
* @parameter: b2World*, float, float
* @return: None
* @Information: Function that creates a chain body (revolute joint) and adds it to the world
********************/
void Chain::CreateChain(b2World* _world, float _positionX, float _positionY)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(10.0f, 10.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.density = 0.5f;
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(1.0f, 0.25f);
	fixtureDef.shape = &polygonShape;

	// Create the first link
	link = _world->CreateBody(&bodyDef);
	link->CreateFixture(&fixtureDef);

	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.localAnchorA.Set(0.5f, 0.0f);
	revoluteJointDef.localAnchorB.Set(-0.5f, 0.0f);

	for (unsigned int i = 0; i < 15; ++i)
	{
		b2Body* newLink = _world->CreateBody(&bodyDef);
		newLink->CreateFixture(&fixtureDef);

		revoluteJointDef.bodyA = link;
		revoluteJointDef.bodyB = newLink;
		_world->CreateJoint(&revoluteJointDef);

		link = newLink;
	}

	revoluteJointDef.bodyA = m_Groundbody;
	revoluteJointDef.bodyB = link;
	revoluteJointDef.localAnchorA.Set(22.0f, -2.0f);
	revoluteJointDef.localAnchorB.Set(0.0f, 0.0f);
	_world->CreateJoint(&revoluteJointDef);
}

/***********************
* ConvertPixelsToMeters
* @author: Rony Hanna  
* @parameter: float&, float&
* @return: None
* @Information: Function that converts 2 given values from pixel coordinate to Box2d's meters
********************/
void Chain::ConvertPixelsToMeters(float& a, float& b)
{
	a /= m_ChainScalingFactor;
	b /= m_ChainScalingFactor;
}
