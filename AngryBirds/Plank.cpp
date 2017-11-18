#include "Plank.h"
#include <iostream>
Plank::Plank() :
	m_PlankSalar(25.0f),
	m_PlankHeight(220.0f),
	m_PlankWidth(70.0f),
	m_collision(false)
{
}

Plank::~Plank()
{
}

/***********************
* CreatePlank
* @author: Rony Hanna  
* @parameter: b2World*, float, float
* @return: None
* @Information: Function that creates a plank rigid body and adds it to the world
********************/
void Plank::CreatePlank(b2World* _world, float _xPos, float _yPos, char* _texturePath)
{
	b2BodyDef plankBodyDef;
	plankBodyDef.type = b2_dynamicBody;
	ConvertPixelsToMeters(_xPos, _yPos);
	plankBodyDef.position.Set(_xPos, _yPos);
	m_plankBody = _world->CreateBody(&plankBodyDef);
	m_plankBody->SetUserData("Plank");

	b2PolygonShape shape;
	float width = m_PlankWidth / 2.0f;
	float height = m_PlankHeight / 2.0f;
	ConvertPixelsToMeters(width, height);
	shape.SetAsBox(width, height);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	
	m_plankBody->CreateFixture(&fixtureDef);

	m_Texture.loadFromFile(_texturePath);
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setOrigin(70 / 2, 220 / 2);
	m_Sprite.setPosition(m_plankBody->GetPosition().x * SCALE, m_plankBody->GetPosition().y * SCALE);
	m_Sprite.setRotation(m_plankBody->GetAngle() * 180 / b2_pi);
}

void Plank::Render(sf::RenderWindow& _window)
{
	m_Sprite.setPosition(m_plankBody->GetPosition().x * SCALE, m_plankBody->GetPosition().y * SCALE);
	m_Sprite.setRotation(m_plankBody->GetAngle() * 180 / b2_pi);
	_window.draw(m_Sprite);
}

void Plank::Reset(float _x, float _y)
{
	ConvertPixelsToMeters(_x, _y);
	m_plankBody->SetTransform(b2Vec2(_x, _y), 0.0f);
}