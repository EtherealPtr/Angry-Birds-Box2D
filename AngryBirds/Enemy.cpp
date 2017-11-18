// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Bird.cpp
// Description	: Bird class implementation
// Author		: Rony Hanna  
// Mail			: Rony.han7006@mediadesign.school.nz

#include "Enemy.h"

/***********************
* Enemy Constructor
* @author: Rony Hanna 
* @parameter: None
* @return: None
* @Information: Constructor that initializes enemy components
********************/
Enemy::Enemy()
	: m_destroyed(false)
	, m_dead(false)
{
	m_EnemyWidth = 60.0f;
	m_EnemyHeight = 60.0f;
	m_pPointer = nullptr;
}

/***********************
* Init
* @author: Rony Hanna  
* @parameter: b2World*
* @return: None
* @Information: Function that creates a static ground body
********************/
void Enemy::Init(b2World* TheWorld, char* _texturePath, int* _score, int* _enemyCount, float* _playerVel)
{
	m_score = _score;
	m_enemyCount = _enemyCount;
	m_playerVel = _playerVel;
	*m_enemyCount += 1;

	m_Texture.loadFromFile(_texturePath);
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setScale(sf::Vector2f(0.5f, 0.5f));
	m_Sprite.setOrigin(30.0f, 54.0f);

	b2BodyDef bodyDef;
	m_Groundbody = TheWorld->CreateBody(&bodyDef);
	b2Vec2 tmp(100.0f, 100.0f);
	m_Groundbody->SetTransform(tmp, 80.0f); // Set it far away from camera space
}

/***********************
* CreateEnemy
* @author: Rony Hanna  
* @parameter: b2World*, float, float
* @return: None
* @Information: Function that creates a enemy body and adds it to the world
********************/
void Enemy::CreateEnemy(b2World * TheWorld, float PosX, float PosY)
{
	b2BodyDef EnemyBodyDef;
	ConvertPixelsToMeters(PosX, PosY);
	m_EnemyPos.Set(PosX, PosY);
	EnemyBodyDef.position.Set(PosX, PosY);
	EnemyBodyDef.type = b2_dynamicBody;
	m_TheEnemyBody = TheWorld->CreateBody(&EnemyBodyDef);
	this->m_pPointer = this;
	m_TheEnemyBody->SetUserData(this);

	b2CircleShape BirdShape;
	float BirdWidth = m_EnemyWidth / 2.0f;
	float BirdHeight = m_EnemyHeight / 2.0f;
	ConvertPixelsToMeters(BirdWidth, BirdHeight);
	BirdShape.m_p.Set(BirdWidth, BirdHeight);
	BirdShape.m_radius = 1.25f;

	b2FixtureDef Fixture;
	Fixture.shape = &BirdShape;
	Fixture.density = 1.0f;
	Fixture.friction = 0.3f;
	Fixture.restitution = 0.3f;
	m_TheEnemyBody->CreateFixture(&Fixture);
}

/***********************
* UpdateEnemyPosition
* @author: Rony Hanna 
* @parameter: b2Body*
* @return: None
* @Information: Function that updates the enemy's position
********************/
void Enemy::UpdateEnemyPosition(b2Body* Pos)
{
	m_EnemyPos.Set(Pos->GetPosition().x, Pos->GetPosition().y);
}

/***********************
* SetDestroyed
* @author: Rony Hanna  
* @parameter: bool
* @return: None
* @Information: increases the score and sets the enemy to destroyed
********************/
void Enemy::SetDestroyed(bool _destroyed)
{
	m_destroyed = _destroyed; 
}

/***********************
* SetEnemyPos
* @author: Rony Hanna  
* @parameter: float
* @return: None
* @Information: set the position of the enemy
********************/
void Enemy::SetEnemyPos(float _x, float _y)
{
	ConvertPixelsToMeters(_x, _y);
	m_EnemyPos.Set(_x, _y);
	m_TheEnemyBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	m_TheEnemyBody->SetAngularVelocity(0.0f);
	m_TheEnemyBody->SetTransform(m_EnemyPos, 0);
}

/***********************
* GroundCollision
* @author: Rony Hanna  
* @parameter: None
* @return: None
* @Information: Checks for collision with the ground
********************/
void Enemy::GroundCollision()
{
	if (m_velocity > 3.0f)
		m_destroyed = true;
}

/***********************
* PlayerCollision
* @author: Rony Hanna  
* @parameter: None
* @return: None
* @Information: Checks for collision with the player entities (birds)
********************/
void Enemy::PlayerCollision()
{
	if (*m_playerVel >= 15.0f)
		m_destroyed = true;
}

/***********************
* Render
* @author: Rony Hanna  
* @parameter: sf::RenderWindow&
* @return: None
* @Information: Render the enemy on screen
********************/
void Enemy::Render(sf::RenderWindow& _gameWindow)
{
	m_Sprite.setPosition(m_EnemyPos.x * SCALE, m_EnemyPos.y * SCALE);
	m_Sprite.setRotation(m_TheEnemyBody->GetAngle() * 180 / b2_pi);
	_gameWindow.draw(m_Sprite);
}

/***********************
* Update
* @author: Rony Hanna 
* @parameter: None
* @return: None
* @Information: Function that updates the enemy's body
********************/
void Enemy::Update()
{
	m_velocity = sqrtf((m_TheEnemyBody->GetLinearVelocity().x * m_TheEnemyBody->GetLinearVelocity().x) + (m_TheEnemyBody->GetLinearVelocity().y + m_TheEnemyBody->GetLinearVelocity().y));
	UpdateEnemyPosition(m_TheEnemyBody);

	if (m_destroyed)
	{
		m_dead = true;
		*m_score += 2500;
		*m_enemyCount -= 1;
		m_TheEnemyBody->SetTransform(b2Vec2(100.0f, 100.0f), 0.0f);	// teleport off screen
		m_destroyed = false;
	}
}

/***********************
* Reset
* @author: Rony Hanna  
* @parameter: None
* @return: None
* @Information: Function that restarts the bird's position
********************/
void Enemy::Reset(float _x, float _y)
{
	if (m_dead)
	{
		m_dead = false;
		*m_enemyCount += 1;
	}

	SetEnemyPos(_x, _y);
}