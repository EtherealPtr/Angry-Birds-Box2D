// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Ground.cpp
// Description	: Ground class implementation
// Author		: Rony Hanna  
// Mail			: Rony.han7006@mediadesign.school.nz

#include "Ground.h"

/***********************
* Ground Constructor
* @author: Rony Hanna  
* @parameter: None
* @return: None
* @Information: Constructor that initializes Ground components
********************/
Ground::Ground()
{
	m_GroundWidth = 2000.0f;
	m_GroundHeight = 60.0f;
	m_GroundSalar = 25.0f;
}

/***********************
* CreateGround
* @author: Rony Hanna  
* @parameter: b2World*, float, float
* @return: None
* @Information: Function that creates a ground static body and adds it to the world
********************/
void Ground::CreateGround(b2World* TheWorld, float PosX, float PosY, char* _texturePath)
{
	b2BodyDef GroundBodyDef;
	ConvertPixelsToMeters(PosX, PosY);
	GroundBodyDef.position.Set(PosX, PosY);
	GroundBodyDef.type = b2_staticBody;
	b2Body* TheGround = TheWorld->CreateBody(&GroundBodyDef);
	TheGround->SetUserData("Ground");

	b2PolygonShape GroundShape;
	float GroundWidth = m_GroundWidth / 2.0f;
	float GroundHeight = m_GroundHeight / 2.0f;
	ConvertPixelsToMeters(GroundWidth, GroundHeight);
	GroundShape.SetAsBox(GroundWidth, GroundHeight);

	b2FixtureDef Fixture;
	Fixture.shape = &GroundShape;
	Fixture.density = 0.0f;
	Fixture.friction = 10.0f;
	Fixture.restitution = 0.5f;

	TheGround->CreateFixture(&GroundShape, 0.0f);

	m_Texture.loadFromFile(_texturePath);
	m_Sprite.setTexture(m_Texture);
	m_Sprite.scale(sf::Vector2f(35.0f, 1.0f));
	m_Sprite.setOrigin(30.0f, 30.0f);
	m_Sprite.setPosition(TheGround->GetPosition().x * SCALE, TheGround->GetPosition().y * SCALE);
	m_Sprite.setRotation(TheGround->GetAngle() * 180 / b2_pi);
}

void Ground::Render(sf::RenderWindow& _window)
{
	_window.draw(m_Sprite);
}