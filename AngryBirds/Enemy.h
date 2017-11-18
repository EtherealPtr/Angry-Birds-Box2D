// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Enemy.h
// Description	: Enemy class setup
// Author		: Rony Hanna 
// Mail			: Rony.han7006@mediadesign.school.nz

#pragma once
#ifndef __ENEMY_H__	
#define __ENEMY_H__

#include "QueryCallback.h"
#include "utils.h"

class Enemy
{
public:
	Enemy();
	~Enemy() {};

	void Init(b2World*, char* _texturePath, int* _score, int* _enemyCount, float* _playerVel);

	void CreateEnemy(b2World*, float, float);

	void UpdateEnemyPosition(b2Body*);
	inline b2Vec2 GetEnemyPos() { return m_EnemyPos; };

	inline bool GetDestroyed() const { return m_destroyed; };
	void SetDestroyed(bool _destroyed);

	void SetEnemyPos(float _x, float _y);
	void GroundCollision();
	void PlayerCollision();

	void Render(sf::RenderWindow& _gameWindow);
	void Update();

	void Reset(float _x, float _y);
	void SetPlayerVel(float* _playerVel) { m_playerVel = _playerVel; };

	Enemy* GetMemoryLoc() { return m_pPointer; };

private:
	Enemy* m_pPointer;
	float m_EnemyWidth;
	float m_EnemyHeight;
	float m_velocity;
	bool m_destroyed;
	bool m_dead;
	int* m_score;
	int* m_enemyCount;
	float* m_playerVel;

	b2MouseJoint* m_MouseJoint = nullptr;
	b2Body* m_TheEnemyBody = nullptr, *m_Groundbody = nullptr;
	b2Vec2 m_EnemyPos;
	b2Vec2 m_StartPoint, m_MouseMoveCoord;

	sf::Sprite m_Sprite;
	sf::Texture m_Texture;
};

#endif // __ENEMY_H__