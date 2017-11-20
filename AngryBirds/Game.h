// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Game.h
// Description	: A simple game class that manages the game loop and all game components within the world
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
	void GameLoop();
	void ProcessInput();
	void Update();
	void Render();
	void RestartGame();
	void SceneTwo();
	void Countdown();
	void ShortDelay();
	void LoadMainMenu();
	void LoadGame();

	sf::RenderWindow m_GameWindow;
	Ground m_Ground;
	Wall m_wall;
	Plank m_plank;
	Bird m_Birds[20];
	Chain m_Chain;
	Platform m_platform;
	CollisionDetector m_collisionDetector;
	Box m_Boxes[100];
	Enemy m_Enemy, m_EnemyTwo, m_EnemyThree;

	sf::Sprite m_BoxSprite, m_Chains, m_Background, m_Slingshot, m_plankSprite, m_mainMenuSprite;
	sf::Texture m_BoxTexture, m_BackgroundTexture, m_cherryBlossomBackgroundTexture, m_SlingshotTexture, m_platformTexture, m_ChainTexture, m_mainMenuTexture;
	
	// Text
	sf::Font m_Font;
	sf::Text m_userInputText, m_scoreText, m_levelClearedText, m_gameCompleteText, m_gameOverText;
	GameState State;
	
	// Audio
	sf::SoundBuffer m_soundBuffer[2];
	sf::Sound m_winLoseSounds[2];
	sf::Music m_ambient;

	b2World* m_World;
	Bird* m_currentBird;
	int m_birdIndex;
	bool m_swapBird;

	enum class CollidedState { NOT_COLLIDED, COLLIDED };
	int m_CollidedBoxes[16]{ 0 };
	int m_Width, m_Height;
	int m_score;
	int m_EnemyCount;
	int m_level;
	float m_platformUpDown;
	const unsigned short int m_TOTAL_NUMBER_OF_BOXES = 14;
	const float m_SCALE = 25.0f;

	bool m_levelComplete, m_secondLevel;
	bool m_doOnce[2];
	bool m_gameOver;
	bool m_gameLoaded;
	float m_countdown;
	float m_delayCounter;
};

#endif // !__GAME_H__