// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Box.cpp
// Description	: Box class implementation
// Author		: Rony Hanna  
// Mail			: Rony.han7006@mediadesign.school.nz

#include "Box.h"
#include <iostream>

/***********************
* Box Constructor
* @author: Rony Hanna  
* @parameter: None
* @return: None
* @Information: Constructor that initializes box components
********************/
Box::Box()
{
	m_BoxScalingFactor = 25.0f;
	m_BoxHeight = 60.0f;
	m_BoxWidth = 60.0f;
	m_collision = false;
	m_pPointer = nullptr;

	if (!m_soundBuffer.loadFromFile("Assets/Sounds/BoxShatters.wav"))
	{
		std::cerr << "ERROR: Unable to load sounds.\n";
	}

	m_boxShatterSound.setBuffer(m_soundBuffer);
}

/***********************
* CreateBird
* @author: Rony Hanna 
* @parameter: b2World*, float, float
* @return: None
* @Information: Function that creates a box body and adds it to the world
********************/
void Box::CreateBox(b2World* MagicWorld, float PosX, float PosY)
{
	b2BodyDef BoxBodyDefinition;
	ConvertPixelsToMeters(PosX, PosY);
	BoxBodyDefinition.position.Set(PosX, PosY);
	BoxBodyDefinition.type = b2_dynamicBody;
	TheBoxBody = MagicWorld->CreateBody(&BoxBodyDefinition);
	this->m_pPointer = this;
	TheBoxBody->SetUserData(this);

	b2PolygonShape Shape;
	float BoxWidth = m_BoxWidth / 2.0f; // Because in box2D the width is the distance from the center 
	float BoxHeight = m_BoxHeight / 2.0f;
	ConvertPixelsToMeters(BoxWidth, BoxHeight);
	Shape.SetAsBox(BoxWidth, BoxHeight);

	b2FixtureDef Fixture;
	Fixture.shape = &Shape;
	Fixture.density = 1.0f;
	Fixture.friction = 0.3f;
	Fixture.restitution = 0.3f;

	TheBoxBody->CreateFixture(&Fixture);
}

void Box::Update()
{
	m_velocity = sqrtf((TheBoxBody->GetLinearVelocity().x * TheBoxBody->GetLinearVelocity().x) + (TheBoxBody->GetLinearVelocity().y * TheBoxBody->GetLinearVelocity().y));
	if (m_collision)
		if (m_velocity > 4.0f)
		{
			if (m_playOnce)
			{
				m_playOnce = false;
				m_boxShatterSound.setVolume(60.0f);
				m_boxShatterSound.play();
			}

			TheBoxBody->SetTransform(b2Vec2(-100.0f, -100.0f), 0.0f);
		}
}

void Box::Reset(float _x, float _y)
{
	ConvertPixelsToMeters(_x, _y);
	TheBoxBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	TheBoxBody->SetAngularVelocity(0);
	TheBoxBody->SetTransform(b2Vec2(_x, _y), b2_pi);
}