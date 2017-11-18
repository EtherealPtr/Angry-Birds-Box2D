// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Game.h
// Description	: A simple game class to handle the game loop
// Author		: Rony Hanna 
// Mail			: Rony.han7006@mediadesign.school.nz

#pragma once
#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>

#include "Box.h"
#include "Ground.h"
#include "Bird.h"
#include "Chain.h"
#include "CollisionDetector.h"
#include "Wall.h"
#include "Platform.h"
#include "Plank.h"
#include "Enemy.h"

#include "Dependencies\SFML\include\SFML\Graphics.hpp"
#include "Dependencies\Box2D\include\Box2D\Box2D.h"

enum class GameState { MENU, PLAY, EXIT, TOTAL_STATES };

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	void InitGameComponents();
	void GameLoop();
	void ProcessInput();
	void Update();
	void Render();
	void RestartGame();
	void SceneTwo();
	void Countdown();
	void ShortDelay();

	sf::RenderWindow m_GameWindow;
	Ground m_Ground;
	Wall m_wall;
	Plank m_plank;
	Bird m_Birds[20];
	Chain m_Chain;
	Platform m_platform;
	std::string m_Username;
	CollisionDetector m_collisionDetector;
	Box m_Boxes[100];
	Enemy m_Enemy, m_EnemyTwo, m_EnemyThree;

	sf::Sprite  m_BoxSprite, m_Chains, m_Background, m_Slingshot, m_plankSprite;
	sf::Texture m_BoxTexture, m_BackgroundTexture, m_cherryBlossomBackgroundTexture, m_SlingshotTexture, m_platformTexture, m_ChainTexture;
	sf::Font m_Font;
	sf::Text m_userInputText, m_scoreText, m_levelClearedText, m_gameCompleteText, m_gameOverText;
	GameState State;

	b2World* m_World;
	Bird* m_currentBird;
	int m_birdIndex;
	bool m_swapBird;

	enum class CollidedState { NOT_COLLIDED, COLLIDED };
	int m_CollidedBoxes[16]{ 0 };
	int m_Width, m_Height;
	int m_score;
	int m_EnemyCount;
	float m_platformUpDown;
	const unsigned int m_TOTAL_NUMBER_OF_BOXES = 14;
	const float m_SCALE = 25.0f;
	int m_level;

	bool m_levelComplete, m_secondLevel;
	float m_countdown;
	float m_delayCounter;
	bool m_doOnce[2];
	bool m_gameOver;
};

#endif // !__GAME_H__