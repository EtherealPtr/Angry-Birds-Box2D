// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: Game.cpp
// Description	: Game class implementation
// Author		: Rony Hanna  
// Mail			: Rony.han7006@mediadesign.school.nz

#include "Game.h"

/***********************
* Game Constructor
* @author: Rony Hanna 
* @parameter: None
* @return: None
* @Information: Constructor that initializes Game components (creates window, sets the framerate, creates gravity, sets the current state of the game)
********************/
Game::Game() :
	m_Width(1540),
	m_Height(800),
	m_levelComplete(false),
	m_secondLevel(false),
	m_platformUpDown(1.0f),
	m_EnemyCount(0),
	m_birdIndex(0),
	m_currentBird(nullptr),
	m_swapBird(false),
	m_level(1),
	m_delayCounter(0.0f),
	m_gameOver(false),
	m_gameLoaded(false)
{
	m_GameWindow.create(sf::VideoMode(m_Width, m_Height), "Angry Birds Clone - Rony Hanna", sf::Style::Default);
	m_GameWindow.setFramerateLimit(60);

	b2Vec2 Gravity(0.0f, 9.8f);
	m_World = new b2World(Gravity);
	m_World->SetContactListener(&m_collisionDetector);

	State = GameState::MENU;
}

/***********************
* Game Destructor
* @author: Rony Hanna  
* @parameter: None
* @return: None
* @Information: Destructor that deallocates memory allocated on the heap (or freestore) 
********************/
Game::~Game()
{
	delete m_World;
	m_World = nullptr;
}

/***********************
* Run
* @author: Rony Hanna  
* @parameter: None
* @return: None
* @Information: Function that loads the main menu
********************/
void Game::Run()
{
	LoadMainMenu();
}

/***********************
* LoadMainMenu
* @author: Rony Hanna
* @parameter: None
* @return: None
* @Information: Function that sets up the main menu and activates the game loop
********************/
void Game::LoadMainMenu()
{
	bool m_componentLoadStatus = m_mainMenuTexture.loadFromFile("Assets/Textures/MainMenuScreen.png");
	assert(m_componentLoadStatus);
	
	m_mainMenuSprite.setTexture(m_mainMenuTexture);
	m_mainMenuSprite.setScale(sf::Vector2f(0.41f, 0.37f));
	GameLoop();
}

/***********************
* LoadGame
* @author: Rony Hanna
* @parameter: None
* @return: None
* @Information: Function that create and load game components (creates box2D rigid bodies, load sounds, music, textures, and score)
********************/
void Game::LoadGame()
{
	m_doOnce[0] = true;
	m_doOnce[1] = true;

	if (!m_soundBuffer[0].loadFromFile("Assets/Sounds/Lose.wav") || (!m_soundBuffer[1].loadFromFile("Assets/Sounds/Win.wav")))
	{
		std::cerr << "ERROR: Unable to load sounds.\n";
	}

	if (!m_ambient.openFromFile("Assets/Sounds/BackgroundMusic.wav"))
	{
		std::cerr << "ERROR: Unable to open music file\n";
	}

	m_winLoseSounds[0].setBuffer(m_soundBuffer[0]);
	m_winLoseSounds[1].setBuffer(m_soundBuffer[1]);

	m_ambient.setVolume(50);
	m_ambient.setLoop(true);
	m_ambient.play();

	m_score = 0;

	// Create boxes 
	m_Boxes[0].CreateBox(m_World, 950.0f, 425.0f);
	m_Boxes[1].CreateBox(m_World, 950.0f, 475.0f);
	m_Boxes[2].CreateBox(m_World, 950.0f, 525.0f);
	m_Boxes[3].CreateBox(m_World, 950.0f, 575.0f);
	m_Boxes[4].CreateBox(m_World, 1020.0f, 625.0f);
	m_Boxes[5].CreateBox(m_World, 1020.0f, 675.0f);
	m_Boxes[6].CreateBox(m_World, 1020.0f, 750.0f);

	m_Boxes[7].CreateBox(m_World, 1100.0f, 425.0f);
	m_Boxes[8].CreateBox(m_World, 1100.0f, 475.0f);
	m_Boxes[9].CreateBox(m_World, 1100.0f, 525.0f);
	m_Boxes[10].CreateBox(m_World, 1100.0f, 575.0f);
	m_Boxes[11].CreateBox(m_World, 1100.0f, 625.0f);
	m_Boxes[12].CreateBox(m_World, 1100.0f, 675.0f);
	m_Boxes[13].CreateBox(m_World, 1100.0f, 750.0f);

	// Create plank
	m_plank.CreatePlank(m_World, 800.0f, 650.0f, "Assets/Textures/Plank.png");

	// Create platform
	m_platform.CreatePlatform(m_World, 1300.0f, 500.0f);

	// Create boundaries
	m_Ground.CreateGround(m_World, 790, 800, "Assets/Textures/Grass.png");
	m_wall.CreateWall(m_World, 1550, 500);

	// Create birds
	m_Birds[0].Init(m_World, "Assets/Textures/BirdOne.png", 1.5f, 1.5f);
	m_Birds[0].CreateBird(m_World, 275.0f, 550.0f, 4.5f, 0.5f, 0.5f, 100.0f);

	m_Birds[1].Init(m_World, "Assets/Textures/BirdTwoTransparent.png", 1.0f, 1.0f);
	m_Birds[1].CreateBird(m_World, 245.0f, 730.0f, 2.0f, 0.2f, 0.5f, 30.0f);

	m_Birds[2].Init(m_World, "Assets/Textures/BirdThreeTransparent.png", 1.0f, 1.0f);
	m_Birds[2].CreateBird(m_World, 170.0f, 730.0f, 3.5f, 0.75f, 1.0f);

	m_Birds[3].Init(m_World, "Assets/Textures/BirdThreeTransparent.png", 0.5f, 0.5f);
	m_Birds[3].CreateBird(m_World, 150.0f, 730.0f, 3.5f, 0.75f, 1.0f);

	m_currentBird = &m_Birds[0];

	// Create chain
	m_Chain.InitChain(m_World);
	m_Chain.CreateChain(m_World, 800.0f, 110.0f);

	// Create Enemy
	m_Enemy.Init(m_World, "Assets/Textures/King_pig_2.png", &m_score, &m_EnemyCount, m_Birds[0].GetVelocityPtr());
	m_Enemy.CreateEnemy(m_World, 775.0f, 450.0f);
	m_EnemyTwo.Init(m_World, "Assets/Textures/King_pig_2.png", &m_score, &m_EnemyCount, m_Birds[0].GetVelocityPtr());
	m_EnemyTwo.CreateEnemy(m_World, 1275.0f, 200.0f);
	m_EnemyThree.Init(m_World, "Assets/Textures/King_pig_2.png", &m_score, &m_EnemyCount, m_Birds[0].GetVelocityPtr());
	m_EnemyThree.CreateEnemy(m_World, 1275.0f, 400.0f);

	// Load textures
	m_BoxTexture.loadFromFile("Assets/Textures/Box.png");
	m_BackgroundTexture.loadFromFile("Assets/Textures/background.png");
	m_cherryBlossomBackgroundTexture.loadFromFile("Assets/Textures/CherryBlossomBackground.png");
	m_SlingshotTexture.loadFromFile("Assets/Textures/slingshot.png");
	m_ChainTexture.loadFromFile("Assets/Textures/Chain.png");
	m_platformTexture.loadFromFile("Assets/Textures/Platform.png");
	m_Font.loadFromFile("Assets/Fonts/AppleGaramond.ttf");

	m_scoreText.setFont(m_Font);
	m_scoreText.setScale(2.0f, 2.0f);
	m_scoreText.setString("Score: " + std::to_string(m_score));
	m_scoreText.setFillColor(sf::Color(44, 127, 255));
	m_scoreText.setStyle(sf::Text::Italic);

	m_levelClearedText.setFont(m_Font);
	m_levelClearedText.setScale(2.5f, 2.5f);
	m_levelClearedText.setString("Level Complete!");
	m_levelClearedText.setFillColor(sf::Color(0, 0, 255));
	m_levelClearedText.setStyle(sf::Text::Italic);
	m_levelClearedText.setPosition(m_GameWindow.getSize().x / 2.0f - 225.0f, 100.0f);

	m_gameCompleteText.setFont(m_Font);
	m_gameCompleteText.setScale(2.0f, 2.0f);
	m_gameCompleteText.setString("You win! Well Done!");
	m_gameCompleteText.setFillColor(sf::Color(0, 0, 255));
	m_gameCompleteText.setStyle(sf::Text::Italic);
	m_gameCompleteText.setPosition(m_GameWindow.getSize().x / 2.0f - 190.0f, 200.0f);

	m_gameOverText.setFont(m_Font);
	m_gameOverText.setScale(2.0f, 2.0f);
	m_gameOverText.setString("Game Over! Press 'R' to try again");
	m_gameOverText.setFillColor(sf::Color(255, 0, 0));
	m_gameOverText.setStyle(sf::Text::Italic);
	m_gameOverText.setPosition(m_GameWindow.getSize().x / 2.0f - 310.0f, 100.0f);

	// Assign textures
	m_Background.setTexture(m_BackgroundTexture);
	m_Slingshot.setTexture(m_SlingshotTexture);
	m_Chains.setTexture(m_ChainTexture);

	// -----------------------------------------------
	// Set positions and scales for game components 
	// -----------------------------------------------

	// Background
	m_Background.setPosition(0.0f, 0.0f);
	m_Background.setScale(3.5f, 2.0f);

	// Slingshot
	m_Slingshot.setPosition(250.0f, 520.0f);
	m_Slingshot.setScale(1.2f, 1.0f);

	// Mark game as loaded 
	m_gameLoaded = true;
}


/***********************
* GameLoop
* @author: Rony Hanna  
* @parameter: None
* @return: None
* @Information: Function that checks for user input, updates game components, and render the current frame
********************/
void Game::GameLoop()
{
	while (State != GameState::EXIT)
	{
		ProcessInput();
		Update();
		Render();
	}
}

/***********************
* ProcessInput
* @author: Rony Hanna  
* @parameter: None
* @return: None
* @Information: Function that processes user input
********************/
void Game::ProcessInput()
{
	double xd, yd;
	b2Vec2 MouseP;

	sf::Vector2i MousePos = sf::Mouse::getPosition();
	xd = MousePos.x;
	yd = MousePos.y;
	static b2Vec2 mp(0.0f, 0.0f);

	sf::Event _event;
	while (m_GameWindow.pollEvent(_event))
	{
		if (State == GameState::PLAY)
		{
			switch (_event.type)
			{
			case sf::Event::MouseMoved:
			{
				mp.Set(static_cast<float>(_event.mouseMove.x), static_cast<float>(_event.mouseMove.y));
				m_currentBird->MouseMove(mp);
				if (m_birdIndex == 2)
					m_Birds[3].MouseMove(mp);

				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (_event.mouseButton.button == sf::Mouse::Left)
				{
					m_currentBird->MouseDown(m_World, mp);
					if (m_birdIndex == 1)
						m_currentBird->YellowBird(mp);
					if (m_birdIndex == 2)
					{
						m_Birds[3].MouseDown(m_World, mp);
						m_Birds[3].WhiteBird();
					}

				}
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				m_currentBird->MouseUp(m_World, mp);
				if (m_birdIndex == 2)
					m_Birds[3].MouseUp(m_World, mp);
				m_swapBird = true;

				break;
			}
			case sf::Event::KeyPressed:
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					RestartGame();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					m_GameWindow.close();
					exit(0);
				}
				break;
			}
			case sf::Event::Closed:
			{
				m_GameWindow.close();
				exit(0);
				break;
			}
			}
		}
		// Check if the main menu is active 
		else if (State == GameState::MENU)
		{
			switch (_event.type)
			{
				case sf::Event::KeyPressed:
				{
					// Check if the start button has been selected
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					{
						// Load game and set the game state to play
						if (!m_gameLoaded)
						{
							LoadGame();
						}

						State = GameState::PLAY;
					}
				}
			}
		}
	}
}

/***********************
* Update
* @author: Rony Hanna
* @parameter: None
* @return: None
* @Information: Function that updates the game components every frame
********************/
void Game::Update()
{
	if (State == GameState::PLAY)
	{
		if (m_swapBird)
		{
			if (m_birdIndex < 3)
			{
				if ((m_currentBird->GetBirdPos().x > 50.0f && *m_currentBird->GetVelocityPtr() < 5.0f) || m_currentBird->OutOfBounds())
				{
					m_birdIndex++;
					m_currentBird = &m_Birds[m_birdIndex];

					m_currentBird->Reset(12.0f, 22.0f);

					if (m_birdIndex == 2)
						m_Birds[3].Reset(12.0f, 22.0f);

					m_swapBird = false;
				}
			}
		}

		m_Birds[0].Update();
		m_Birds[1].Update();
		m_Birds[2].Update();
		m_Birds[3].Update();

		m_Enemy.Update();
		m_EnemyTwo.Update();
		m_EnemyThree.Update();

		m_Enemy.SetPlayerVel(m_currentBird->GetVelocityPtr());
		m_EnemyTwo.SetPlayerVel(m_currentBird->GetVelocityPtr());
		m_EnemyThree.SetPlayerVel(m_currentBird->GetVelocityPtr());

		m_scoreText.setString("Score: " + std::to_string(m_score));

		// Check collision between boxes and ground
		for (unsigned int i = 0; i < m_TOTAL_NUMBER_OF_BOXES; ++i)
		{
			m_Boxes[i].Update();
			if (m_Boxes[i].GetCollisionStatus() && m_CollidedBoxes[i] == (int)CollidedState::NOT_COLLIDED)
			{
				m_CollidedBoxes[i] = (int)CollidedState::COLLIDED;
				if (m_Boxes[i].GetVelocity() > 4.0f)
					m_score += 1200;
				m_scoreText.setString("Score: " + std::to_string(m_score));
			}
		}

		if (m_EnemyCount == 0)
		{
			if (m_doOnce[0])
			{
				m_winLoseSounds[1].setVolume(70.0f);
				m_winLoseSounds[1].play();

				std::thread countdownWorkerThread(&Game::Countdown, this);
				countdownWorkerThread.detach(); // Daemon thread

				m_doOnce[0] = false;
			}
		}

		if (m_levelComplete)
		{
			m_levelComplete = false;
			m_score = 0;

			// Restart all boxes collision states to not collided
			for (unsigned int i = 0; i < m_TOTAL_NUMBER_OF_BOXES; ++i)
			{
				if (m_CollidedBoxes[i] == (int)CollidedState::COLLIDED)
				{
					m_CollidedBoxes[i] = (int)CollidedState::NOT_COLLIDED;
					m_Boxes[i].SetCollisionStatus(false);
					m_scoreText.setString("Score: " + std::to_string(m_score));
				}
			}

			if (m_level != 2)
				SceneTwo();
			else
			{
				RestartGame();
				m_level = 1;
				RestartGame();
				m_Background.setTexture(m_BackgroundTexture);
				State = GameState::MENU;
			}
		}
	}
}

/***********************
* Render
* @author: Rony Hanna 
* @parameter: None
* @return: None
* @Information: Function that draws everything to the window
********************/
void Game::Render()
{
	if (State == GameState::PLAY)
	{
		m_GameWindow.clear();
		m_GameWindow.draw(m_Background);
		m_GameWindow.draw(m_Slingshot);
		m_GameWindow.draw(m_userInputText);
		m_GameWindow.draw(m_scoreText);
		m_GameWindow.draw(m_currentBird->GetLine());

		if (m_EnemyCount == 0)
		{
			if (m_secondLevel)
			{
				m_GameWindow.draw(m_gameCompleteText);
			}
			else
			{
				m_GameWindow.draw(m_levelClearedText);
			}
		}

		// Check if player lost 1st level
		if (m_EnemyCount > 0 && m_level == 1 && m_birdIndex >= 3)
		{
			if (m_doOnce[1])
			{
				std::thread delayCounterThread(&Game::ShortDelay, this);
				delayCounterThread.detach(); // Daemon thread

				m_doOnce[1] = false;
			}

			if (m_gameOver)
				m_GameWindow.draw(m_gameOverText);
		}
		// Check if player lost 2nd level
		if (m_EnemyCount > 0 && m_level == 2 && m_birdIndex >= 3)
		{
			if (m_doOnce[1])
			{
				std::thread delayCounterThread(&Game::ShortDelay, this);
				delayCounterThread.detach(); // Daemon thread

				m_doOnce[1] = false;
			}

			if (m_gameOver)
				m_GameWindow.draw(m_gameOverText);
		}

		// Draw platforms
		for (b2Body* bodyIter = m_World->GetBodyList(); bodyIter != 0; bodyIter = bodyIter->GetNext())
		{
			if (bodyIter->GetUserData() == "lowerPlatform" || bodyIter->GetUserData() == "upperPlatform")
			{
				if (bodyIter->GetPosition().y > 25 && bodyIter->GetPosition().y > 15)
				{
					m_platformUpDown = -1.0f;
				}
				if (bodyIter->GetPosition().y < 20 && bodyIter->GetPosition().y < 10)
				{
					m_platformUpDown = 1.0f;
				}
				bodyIter->SetLinearVelocity(b2Vec2(0.0f, m_platformUpDown));

				sf::Sprite platformSprite;
				platformSprite.setTexture(m_platformTexture);
				platformSprite.setOrigin(50.0f, 10.0f);
				platformSprite.setPosition(m_SCALE * bodyIter->GetPosition().x, m_SCALE * bodyIter->GetPosition().y);
				platformSprite.setRotation(bodyIter->GetAngle() * 180 / b2_pi);
				platformSprite.setScale(1.0f, 1.0f);
				m_GameWindow.draw(platformSprite);
			}
		}

		// Draw boxes
		for (b2Body* bodyIter = m_World->GetBodyList(); bodyIter != 0; bodyIter = bodyIter->GetNext())
		{
			for (unsigned int i = 0; i < m_TOTAL_NUMBER_OF_BOXES; ++i)
			{
				if (bodyIter->GetUserData() == &m_Boxes[i] && i <= 13)
				{
					m_BoxSprite.setTexture(m_BoxTexture);
					m_BoxSprite.setOrigin(30.0f, 30.0f);
					m_BoxSprite.setPosition(m_SCALE * bodyIter->GetPosition().x, m_SCALE * bodyIter->GetPosition().y);
					m_BoxSprite.setRotation(bodyIter->GetAngle() * 180 / b2_pi);
					m_GameWindow.draw(m_BoxSprite);
				}
			}
		}

		for (b2Body* bodyIter = m_World->GetBodyList(); bodyIter != 0; bodyIter = bodyIter->GetNext())
		{
			// Draw chain
			if (bodyIter->GetType() == b2_dynamicBody
				&& bodyIter->GetUserData() != "Player"
				&& bodyIter->GetUserData() != &m_Enemy
				&& bodyIter->GetUserData() != &m_EnemyTwo
				&& bodyIter->GetUserData() != &m_EnemyThree
				&& bodyIter->GetUserData() != &m_Boxes[0] // Visual fix
				&& bodyIter->GetUserData() != &m_Boxes[1]
				&& bodyIter->GetUserData() != &m_Boxes[2]
				&& bodyIter->GetUserData() != &m_Boxes[3]
				&& bodyIter->GetUserData() != &m_Boxes[4]
				&& bodyIter->GetUserData() != &m_Boxes[5]
				&& bodyIter->GetUserData() != &m_Boxes[6]
				&& bodyIter->GetUserData() != &m_Boxes[7]
				&& bodyIter->GetUserData() != &m_Boxes[8]
				&& bodyIter->GetUserData() != &m_Boxes[9]
				&& bodyIter->GetUserData() != &m_Boxes[10]
				&& bodyIter->GetUserData() != &m_Boxes[11]
				&& bodyIter->GetUserData() != &m_Boxes[12]
				&& bodyIter->GetUserData() != &m_Boxes[13])
			{
				m_Chains.setScale(1.7f, 1.7f);
				m_Chains.setOrigin(7.0f, 7.0f);
				m_Chains.setPosition(m_SCALE * bodyIter->GetPosition().x, m_SCALE * bodyIter->GetPosition().y);
				m_Chains.setRotation(bodyIter->GetAngle() * 180 / b2_pi);
				m_GameWindow.draw(m_Chains);
			}
			else if (bodyIter->GetUserData() == "Wall")
			{
				sf::Sprite wallSprite;
				wallSprite.scale(sf::Vector2f(35.0f, 1.0f));
				wallSprite.setOrigin(30.0f, 30.0f);
				wallSprite.setPosition(bodyIter->GetPosition().x * m_SCALE, bodyIter->GetPosition().y * m_SCALE);
				wallSprite.setRotation(90.0f);
				m_GameWindow.draw(wallSprite);
			}
		}

		m_Birds[0].Render(m_GameWindow);
		m_Birds[1].Render(m_GameWindow);
		m_Birds[3].Render(m_GameWindow);
		m_Birds[2].Render(m_GameWindow);
		m_Enemy.Render(m_GameWindow);
		m_EnemyTwo.Render(m_GameWindow);
		m_EnemyThree.Render(m_GameWindow);
		m_Ground.Render(m_GameWindow);
		m_plank.Render(m_GameWindow);

		// Advance frame in box2D
		m_World->Step(1 / 60.0f, 8, 3);
	}
	else if (State == GameState::MENU)
	{
		m_GameWindow.clear();
		m_GameWindow.draw(m_mainMenuSprite);
	}

	m_GameWindow.display();
}

/***********************
* RestartGame
* @author: Rony Hanna 
* @parameter: None
* @return: None
* @Information: Function that restarts the game components 
********************/
void Game::RestartGame()
{
	m_gameOver = false; 
	m_swapBird = false;
	m_birdIndex = 0;
	m_currentBird = &m_Birds[m_birdIndex];

	m_Birds[0].Reset(11.0f, 22.0f);
	m_Birds[1].Reset(245.0f / SCALE, 730.0f / SCALE);
	m_Birds[2].Reset(170.0f / SCALE, 730.0f / SCALE);
	m_Birds[3].Reset(150.0f / SCALE, 730.0f / SCALE);

	m_score = 0;

	// Enable birds' special abilities upon game restart 
	for (unsigned int i = 0; i < 4; ++i)
	{
		m_Birds[i].SetSpecialAbility(true);
	}

	if (m_level == 1)
	{
		m_doOnce[0] = true;
		m_doOnce[1] = true;

		for (unsigned int i = 0; i < 14; ++i)
		{
			m_Boxes[i].SetCollisionStatus(false);
			m_Boxes[i].SetPlayOnce(true);
		}

		m_Boxes[0].Reset(950.0f, 425.0f);
		m_Boxes[1].Reset(950.0f, 480.0f);
		m_Boxes[2].Reset(950.0f, 530.0f);
		m_Boxes[3].Reset(950.0f, 580.0f);

		m_Boxes[4].Reset(1020.0f, 480.0f);
		m_Boxes[5].Reset(1020.0f, 530.0f);
		m_Boxes[6].Reset(1020.0f, 580.0f);
			 
		m_Boxes[7].Reset(1100.0f, 425.0f);
		m_Boxes[8].Reset(1100.0f, 480.0f);
		m_Boxes[9].Reset(1100.0f, 530.0f);
		m_Boxes[10].Reset(1100.0f, 580.0f);
		m_Boxes[11].Reset(1100.0f, 630.0f);
		m_Boxes[12].Reset(1100.0f, 680.0f);
		m_Boxes[13].Reset(1100.0f, 735.0f);

		m_Enemy.Reset(775.0f, 300.0f);
		m_EnemyTwo.Reset(1275.0f, 200.0f);
		m_EnemyThree.Reset(1275.0f, 400.0f);
		m_plank.Reset(800.0f, 650.0f);
	}
	else
	{
		m_doOnce[0] = true;
		m_doOnce[1] = true;

		m_Enemy.Reset(820.0f, 650.0f);
		m_EnemyTwo.Reset(1275.0f, 400.0f);
		m_EnemyThree.Reset(750.0f, 650.0f);
		m_plank.Reset(1100.0f, 650.0f);

		for (unsigned int i = 0; i < 13; ++i)
		{
			m_Boxes[i].SetCollisionStatus(false);
			m_Boxes[i].SetPlayOnce(true);
		}

		m_Boxes[0].Reset(700.0f, 500.0f);
		m_Boxes[1].Reset(700.0f, 540.0f);
		m_Boxes[2].Reset(700.0f, 590.0f);
		m_Boxes[3].Reset(700.0f, 640.0f);
		m_Boxes[4].Reset(700.0f, 700.0f);

		m_Boxes[5].Reset(950.0f, 500.0f);
		m_Boxes[6].Reset(950.0f, 540.0f);
		m_Boxes[7].Reset(950.0f, 590.0f);
		m_Boxes[8].Reset(950.0f, 630.0f);
		m_Boxes[9].Reset(950.0f, 700.0f);

		m_Boxes[10].Reset(765.0f, 720.0f);
		m_Boxes[11].Reset(825.0f, 720.0f);
		m_Boxes[12].Reset(875.0f, 720.0f);
	}
}

/***********************
* SceneTwo
* @author: Rony Hanna 
* @parameter: None
* @return: None
* @Information: Function that starts the second level 
********************/
void Game::SceneTwo()
{
	m_level++;
	m_gameOver = false;
	m_doOnce[1] = true;
	m_Background.setTexture(m_cherryBlossomBackgroundTexture);
	RestartGame();
}

/***********************
* Countdown
* @author: Rony Hanna 
* @parameter: None
* @return: None
* @Information: Function that counts down in the background of the program to the next level on an independent thread 
********************/
void Game::Countdown()
{
	sf::Clock countdown;

	for (;;)
	{
		m_countdown = countdown.getElapsedTime().asSeconds();
		if (m_countdown >= 4.0f)
		{
			m_levelComplete = true;
			m_secondLevel = true;
			break;
		}
	}
}

/***********************
* ShortDelay
* @author: Rony Hanna
* @parameter: None
* @return: None
* @Information: Function that creates a short delay on an independent thread
********************/
void Game::ShortDelay()
{
	sf::Clock clockCount;

	for (;;)
	{
		m_delayCounter = clockCount.getElapsedTime().asSeconds();
		if (m_delayCounter >= 2.5f)
		{
			if (!m_levelComplete)
			{
				m_winLoseSounds[0].setVolume(70.0f);
				m_winLoseSounds[0].play();
				m_gameOver = true;
			}
			break;
		}
	}
}
