// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"
#include "texture.h"
#include "animatedsprite.h"
#include "player.h"
#include "entity.h"
#include "label.h"
#include "pickup.h"
#include "gamemap.h"
#include "enemy.h"
#include "mainmenu.h"
#include "shop.h"

// Library includes:
#include <cassert>
#include <cmath>
#include <ctime>
#include <SDL.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
//Box2D includes:
#include <box2d.h>

// Static Members:
Game* Game::sm_pInstance = 0;

Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{ 
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void 
Game::DestroyInstance()
{
	delete sm_pInstance; 
	sm_pInstance = 0;
}

Game::Game()
: m_pBackBuffer(0)
, m_pInputHandler(0)
, m_looping(true)
, m_executionTime(0)
, m_elapsedSeconds(0)
, m_frameCount(0)
, m_FPS(0)
, m_numUpdates(0)
, m_lastTime(0)
, m_lag(0)
, m_width(0)
, m_height(0)
, m_velocityIterations(0)
, m_positionIterations(0)
, m_timeStep(0.0f)
, m_gravity()
, m_toggleDebug(false)
, m_gold(0)
, m_world(m_gravity)
, m_waypointMode(false)
, m_enemySelectedIndex(0)
, m_pathToLoadCounter(0)
, m_pathToSaveCounter(0)
, m_inMainMenu(true)
, m_isGameRunning(false)
, m_debugConsoleOpen(false)
, m_debugString("")
{
	srand(time(0));
}

Game::~Game()
{
	delete m_pBackBuffer;
	delete m_pInputHandler;
	m_pBackBuffer = 0;
}

bool 
Game::Initialise()
{
	m_width = 1366;
	m_height = 768;

	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(m_width, m_height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}
	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	//Run main menu
	m_mainMenu = new MainMenu();
	m_gameState = MAINMENU;

	m_shop = new Shop();
	
	InitialiseData();

	return (true);
}

void
Game::InitialiseData()
{
	//Health Sprites
	m_HealthSprite = m_pBackBuffer->CreateSprite("Assets\\Health_Heart.png");
	m_HealthLostSprite = m_pBackBuffer->CreateSprite("Assets\\Health_Heart_Depleted.png");
	m_HealthSprite->SetWidth(64);
	m_HealthSprite->SetHeight(64);
	m_HealthLostSprite->SetWidth(64);
	m_HealthLostSprite->SetHeight(64);

	//Set up player
	PlayerSpriteInit();
	m_player = new Player();
	m_player->Initialise(m_playerAnim, m_world);
	m_player->SetCurrentHealth(5);
	m_player->SetMaxHealth(5);

	//Game map setup
	m_gameMap = new GameMap();
	m_gameMap->Initialise("Assets\\map.txt", "Assets\\object.txt");
	m_gameMap->GenerateMap(*m_pBackBuffer, m_world);

	//Box2D world setup
	m_velocityIterations = 10;
	m_positionIterations = 10;
	m_timeStep = 1.0f / 20.0f;
	b2Vec2 gravity(0.0f, 0.0f);
	m_world.SetGravity(gravity);
	m_world.SetContactListener(&m_collisionListener);

	//Gold label - using a stringstream to concat strings
	std::ostringstream labelStream;
	labelStream << "Gold: " << m_gold;
	m_goldLabel = new Label(labelStream.str());
	m_goldLabel->SetColour(218, 165, 32, 0);

	m_shopLabel = new Label("Shop");
	m_shopLabel->SetBounds(0, 30, 100, 30);
	m_shopLabel->SetColour(0, 0, 0, 0);

	//Game over labels
	m_gameOver = new Label("GAME OVER!");
	m_gameOver->SetBounds(440, 290, 400, 100);
	m_gameOver->SetColour(255, 0, 0, 0);

	//Restart game label
	m_restartGame = new Label("press f5 to restart");
	m_restartGame->SetBounds(440, 390, 400, 30);
	m_restartGame->SetColour(0, 0, 0, 0);

	//Debug - Waypoint mode label
	m_waypointModeLabel = new Label("Waypoint Mode");
	m_waypointModeLabel->SetBounds(440, 100, 400, 30);
	m_waypointModeLabel->SetColour(0, 0, 255, 0);

	//Debug - enemy selected for waypoints
	labelStream.str("");
	labelStream << "Enemy " << m_enemySelectedIndex << " Selected";
	m_enemySelectedLabel = new Label(labelStream.str());
	m_enemySelectedLabel->SetBounds(440, 150, 400, 30);
	m_enemySelectedLabel->SetColour(0, 0, 230, 0);

	//Debug - console
	m_debugText = new Label("");
	m_debugText->SetBounds(0, 600, 0, 100);
	m_debugText->SetColour(255, 255, 255, 0);

	//Loading waypoints, check current counter
	std::string line;
	
	bool run = true;
	while(run)
	{
		line = "patrol" + std::to_string(m_pathToSaveCounter) + ".txt";
		std::ifstream myfile(line);
		if (myfile.is_open())
		{
			m_pathToSaveCounter++;
		}
		else
		{
			run = false;
		}
	}
	//Sword Setup
	m_swordSprite = m_pBackBuffer->CreateAnimatedSprite("Assets\\weaponanim.png");
	m_swordSprite->LoadFrames(64, 64);
	m_swordSprite->StartAnimating();
	m_sword = new Sword(*m_player);
	m_sword->Initialise(m_swordSprite, m_world);

	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;
}

bool 
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput(*this);
	
	if (m_looping)
	{
		int current = SDL_GetTicks();
		float deltaTime = (current - m_lastTime) / 1000.0f;
		m_lastTime = current;

		m_executionTime += deltaTime;

		m_lag += deltaTime;

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
		}
		
		Draw(*m_pBackBuffer);
	}

	SDL_Delay(1);

	return (m_looping);
}

void 
Game::Process(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	//Check game states

	//Process main menu
	if (m_gameState == MAINMENU)
	{
		m_mainMenu->Process(deltaTime);
		if (m_mainMenu->GetMenuState() == NEWGAME)
		{
			m_inMainMenu = false;
			if (m_isGameRunning)
			{
				m_gameState = INGAME;
				RestartGame();
			}
			m_isGameRunning = true;
		}
		else if (m_mainMenu->GetMenuState() == QUITGAME)
		{
			Quit();
		}
		else if (m_mainMenu->GetMenuState() == LOADGAME)
		{
			LoadGame("save.txt");
			m_mainMenu->SetMenuState(ACTIVE);
		}
		else if (m_mainMenu->GetMenuState() == SAVEGAME)
		{
			SaveGame("save.txt");
			m_mainMenu->SetMenuState(ACTIVE);
		}
		return;
	}


	//Process shop screen
	if (m_gameState == SHOP)
	{
		return;
	}


	//Check if the player is alive and game is running
	if (GameOver())
	{
		return;
	}

	//Process keyboard movement input
	//Processing keyboard input
	m_pInputHandler->ProcessMovement(*this);

	//Box2D simulation loop
	m_world.Step(m_timeStep, m_velocityIterations, m_positionIterations);
	m_player->Process(deltaTime);
	m_sword->Process(deltaTime);
	//Process Pickups
	//Create iterator to loop through and delete pickups that have been picked up
	std::vector<Pickup*>::iterator pickupI = m_pickups.begin();

	//Loop through all pickups
	while (pickupI != m_pickups.end()) {
		Pickup* current = *pickupI;

		//If pickup has been used, delete
		if (current->IsPickedUp())
		{
			pickupI = m_pickups.erase(pickupI);
			delete current;
			current = 0;
		}
		else
		{
			//Check if player can pickup, and apply rewards if they do
			if (m_player->CheckPickup(*current))
			{
				//Sort out reward
				if (current->GetPickupType() == HEALTH)
				{
					UpdatePlayerHealth(1);
				}
				else if (current->GetPickupType() == GOLD)
				{
					UpdateGold(10);
				}
			}
			current->Process(deltaTime);
			pickupI++;
		}
	}

	//Process enemies
	//Create iterator to loop through and delete enemies that have died
	std::vector<Enemy*>::iterator enemyI = m_enemies.begin();

	//Loop through all enemies
	while (enemyI != m_enemies.end()) {
		Enemy* current = *enemyI;

		//If enemy is dead
		if (current->IsDead())
		{
			//Drop Pickups 
			for (int i = 0; i < rand() % 5; i++)
			{
				SpawnPickup(current->GetPositionX() + (rand() % 64) - 32, current->GetPositionY() + (rand() % 64) - 32, GOLD);
			}
			for (int i = 0; i < rand() % 2; i++)
			{
				SpawnPickup(current->GetPositionX() + (rand() % 64) - 32, current->GetPositionY() + (rand() % 64) - 32, HEALTH);
			}

			//Remove from game
			enemyI = m_enemies.erase(enemyI);
			delete current;
			current = 0;
		}
		else
		{
			//Process enemy
			current->Process(deltaTime, m_player);
			enemyI++;
		}
	}

	m_gameMap->Process(deltaTime);
}

void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	//Check if in main menu
	if (m_gameState == MAINMENU)
	{
		m_mainMenu->Draw(backBuffer);
	}
	else  //Draw normal game
	{

		int x = m_width - 130;
		//Draw Map
		m_gameMap->Draw(backBuffer);

		//Draw Pickups
		for each (Pickup* p in m_pickups)
		{
			p->Draw(backBuffer);
		}

		//Draw Enemies
		for each (Enemy* e in m_enemies)
		{
			e->Draw(backBuffer);
		}

		//Draw player
		m_player->Draw(backBuffer);
		//Draw Sword
		m_sword->Draw(backBuffer);


		//Draw gold
		m_goldLabel->Draw(backBuffer);
		m_shopLabel->Draw(backBuffer);

		//Draw health
		for (int i = 0; i < m_player->GetMaxHealth(); i++)
		{

			if (i < m_player->GetCurrentHealth())
			{
				m_HealthSprite->SetX(x);
				m_HealthSprite->SetY(0);
				m_HealthSprite->Draw(backBuffer);
			}
			else
			{
				m_HealthLostSprite->SetX(x);
				m_HealthLostSprite->SetY(0);
				m_HealthLostSprite->Draw(backBuffer);
			}

			x -= 70;
		}

		//If game is over
		if (GameOver())
		{
			m_gameOver->Draw(backBuffer);
			m_restartGame->Draw(backBuffer);
		}

		//Debug labels

		//Waypoint mode
		if (m_waypointMode)
		{
			//Draw label
			m_waypointModeLabel->Draw(backBuffer);
			m_enemySelectedLabel->Draw(backBuffer);

			//Draw waypoints of selected enemy
			if (!m_enemies.empty())
			{
				m_enemies.at(m_enemySelectedIndex)->DrawWaypoints(backBuffer);
			}
		}

		if (m_debugConsoleOpen)
		{
			backBuffer.SetDrawColour(0,0,0,100);
			backBuffer.DrawRectangle(0, 600, 1366, 700);
			m_debugText->Draw(backBuffer);
		}

		//If shop is open, draw shop over game
		if (m_gameState == SHOP)
		{
			m_shop->Draw(backBuffer);
		}

	}
	backBuffer.Present();
}

void 
Game::Quit()
{
	m_looping = false;
}

void Game::UpdatePlayerHealth(int amount)
{
	m_player->UpdatePlayerHealth(amount);

}

void
Game::PlayerSpriteInit()
{
	//will add in more sprites later
	m_playerAnim = m_pBackBuffer->CreateAnimatedSprite("Assets//character.png");

	//Default load of sprite sheet
	m_playerAnim->LoadFrames(64, 64);
	m_playerAnim->StartAnimating();
}

void
Game::UpdatePlayer(Direction direction)
{	
	//for multiple sprites, sprites will change
	//move the player sprite on screen
	switch (direction)
	{
	case Direction::UP:
		m_player->SetPlayerCollisionVelocity(b2Vec2(0.0f,-200.0f));
		break;
	case Direction::DOWN:
		m_player->SetPlayerCollisionVelocity(b2Vec2(0.0f, 200.0f));
		break;
	case Direction::LEFT:
		m_player->SetPlayerCollisionVelocity(b2Vec2(-200.0f, 0.0f));
		break;
	case Direction::RIGHT:
		m_player->SetPlayerCollisionVelocity(b2Vec2(200.0f, 0.0f));
		break;
	case Direction::STOP:
		m_player->SetPlayerCollisionVelocity(b2Vec2_zero);
		break;
	case Direction::RESET://Debug, reset position to middle of screen
		break;
	}

	
	m_player->UpdatePlayerDirection(direction);
	/*
	switch (direction)
	{
	case Direction::UP:
	case Direction::DOWN:
	case Direction::LEFT:
	case Direction::RIGHT:
		m_sword->ChangeSwordDirection(direction, m_world);
		break;
	}*/
}

void
Game::ToggleDebug()
{
	m_toggleDebug = !m_toggleDebug;
	if (m_toggleDebug)
	{
		SDL_Log("Debug on");
	}
	else
	{
		SDL_Log("Debug off");
	}
}

void Game::UpdateGold(int amount)
{
	m_gold += amount;
	if (m_gold < 0)
	{
		m_gold = 0;
	}
	std::ostringstream labelStream;
	labelStream << "Gold: " << m_gold;
	m_goldLabel->SetText(labelStream.str());

	//Adjust label size with gold counter
	int lengthen = 10;
	for (int i = 10; i <= m_gold; i *= 10)
	{
		m_goldLabel->SetBounds(0, 0, 100 + lengthen, 30);
		lengthen += 10;
	}
}

void Game::SpawnPickup(int x, int y, PickupType type)
{
	if (type == GOLD)
	{
		AnimatedSprite* goldAnim = m_pBackBuffer->CreateAnimatedSprite("Assets//Gold_Spin.png");
		Pickup* goldPickup = new Pickup(m_world);
		goldAnim->LoadFrames(64, 64);
		goldAnim->SetFrameSpeed(0.12f);
		goldPickup->Initialise(goldAnim);
		goldPickup->SetPickupType(GOLD);
		goldPickup->SetPosition(x, y);
		m_pickups.push_back(goldPickup);
	}
	else if (type == HEALTH)
	{
		AnimatedSprite* heartAnim = m_pBackBuffer->CreateAnimatedSprite("Assets//Health_Heart_Pickup.png");
		Pickup* heartPickup = new Pickup(m_world);
		heartAnim->LoadFrames(64, 64);
		heartAnim->SetFrameSpeed(0.12f);
		heartPickup->Initialise(heartAnim);
		heartPickup->SetPosition(x, y);
		m_pickups.push_back(heartPickup);
	}

}

void
Game::CheckForCollision()
{

}

void
Game::SpawnEnemy(int x, int y)
{
	Enemy* newEnemy = new Enemy();
	AnimatedSprite* enemySprite = m_pBackBuffer->CreateAnimatedSprite("Assets//enemyPlaceholder.png");

	//Default load of sprite sheet
	enemySprite->LoadFrames(64, 64);
	enemySprite->StartAnimating();
	newEnemy->Initialise(enemySprite, m_world);
	newEnemy->SetPosition(x, y);
	newEnemy->SetCurrentHealth(3);
	newEnemy->SetMaxHealth(3);
	m_enemies.push_back(newEnemy);
}

void
Game::PlayerAttack()
{
	//kill any enemies within 128 pixels of player
	for each (Enemy* e in m_enemies)
	{
		int xDifference = e->GetPositionX() - m_player->GetPositionX();
		int yDifference = e->GetPositionY() - m_player->GetPositionY();

		if (xDifference < 0) {
			xDifference *= -1;
		}

		if (yDifference < 0) {
			yDifference *= -1;
		}

		if (xDifference < 128 && yDifference < 128)
		{
			e->UpdateEnemyHealth(-1);
		}
	}
}

bool
Game::GameOver()
{
	if (m_player->GetCurrentHealth() <= 0)
	{
		return true;
	}
	return false;
}

void
Game::RestartGame()
{
	//SO MANY LEAKS
	//Clean up data
	m_enemies.clear();
	m_pickups.clear();
	m_gold = 0;

	//clear out pointers
	
	delete(m_HealthSprite);
	m_HealthSprite = 0;

	delete(m_player);
	m_player = 0;

	delete(m_gameMap);
	m_gameMap = 0;

	delete(m_goldLabel);
	m_goldLabel = 0;

	delete(m_gameOver);
	m_gameOver = 0;

	delete(m_restartGame);
	m_restartGame = 0;

	InitialiseData();
}

void
Game::SaveGame(std::string fileName)
{
	SDL_Log("Saving Game");
	std::ofstream myfile;
	myfile.open(fileName);

	std::ostringstream saveStream;
	//Save Player data
	myfile << "==========Player==========\n";
	//Save position
	myfile << m_player->GetPositionX() << "," << m_player->GetPositionY() << "\n";
	//Save health
	myfile << m_player->GetCurrentHealth() << "," << m_player->GetMaxHealth() << "\n";

	//Saving game data
	myfile << "==========Game==========\n";
	//Save gold
	myfile << "Gold=" << m_gold << "\n";

	//Saving pickup data
	myfile << "==========Pickups==========\n";
	for each (Pickup* p in m_pickups)
	{
		myfile << "Position=" << p->GetPositionX() << "," << p->GetPositionY() << "\n";
		myfile << "Type=" << p->GetPickupType() << "\n";
	}

	//Saving enemy data
	myfile << "==========Enemies==========\n";
	for each (Enemy* e in m_enemies)
	{
		myfile << "Position=" << e->GetPositionX() << "," << e->GetPositionY() << "\n";
		myfile << "Health=" << e->GetCurrentHealth() << "," << e->GetMaxHealth() << "\n";
	}

	myfile.close();
	SDL_Log("Game Saved");
}

void
Game::LoadGame(std::string fileName)
{
	std::string line;
	std::ifstream myfile(fileName);
	bool readPlayer = false;

	delete(m_player);
	m_player = 0;

	PlayerSpriteInit();
	m_player = new Player();

	if (myfile.is_open())
	{
		//skip line 
		getline(myfile, line);
		getline(myfile, line);

		//Load position
		std::string posString = "";
		int x = 0;
		int y = 0;
		for (int i = 0; i < line.size(); i++)
		{
			//Check token
			if (line.at(i) != ',') {
				//Add to string
				posString += line.at(i);
			}
			else
			{
				//Token reached, push into point x
				x = atoi(posString.c_str());
				posString.clear();
			}
		}
		//End of line, push into point y
		y = atoi(posString.c_str());
		posString.clear();

		//Load data into player
		m_player->SetPositionX(x);
		m_player->SetPositionY(y);
		m_player->Initialise(m_playerAnim, m_world);

		myfile.close();
	}
}

void Game::DynamicLoad(std::string fileName)
{
	//Dynaimc load system, currently a pain in the ass
	//Open file
	std::string line;
	std::ifstream myfile(fileName);
	if (myfile.is_open())
	{
		SDL_Log("Loading");
		//clear all current data
		//Clean up data
		/*
		delete(m_HealthSprite);
		m_HealthSprite = 0;

		delete(m_gameMap);
		m_gameMap = 0;

		delete(m_goldLabel);
		m_goldLabel = 0;

		delete(m_gameOver);
		m_gameOver = 0;

		delete(m_restartGame);
		m_restartGame = 0;*/
		//m_enemies.clear();
		//m_pickups.clear();
		//m_gold = 0;

		//clear out pointers

		delete(m_player);
		m_player = 0;



		//seperate words using : and , delimiters
		std::string classType;
		bool classEntered;


		//Read current line
		getline(myfile, line);

		//Read in the class type
		for (int i = 0; i < line.size(); i++)
		{
			//Read keyword for class type
			if (line.at(i) != '=')
			{
				//Add to string
				classType += line.at(i);
			}
		}
		SDL_Log(classType.c_str());

		std::string dataType;
		bool dataTypeRead = false;
		std::string data;

		//Check the type of data we are reading

		//Load player info
		if (classType == "Player")
		{
			//Loading player info - read next line
			PlayerSpriteInit();
			m_player = new Player();
			m_player->Initialise(m_playerAnim, m_world);

			getline(myfile, line);
			//Read in the data type
			for (int i = 0; i < line.size(); i++)
			{
				//Read keyword for class type
				if (line.at(i) != '=' && !dataTypeRead)
				{
					//Add to string
					dataType += line.at(i);
				}
				else
				{
					dataTypeRead = true;
				}

				//Once the type of data is registered, load up appropriate info
				if (dataTypeRead)
				{
					//Data type all read in, check what it is
					if (dataType == "Position")
					{
						if (line.at(i) == ',')
						{

							//save x position
							m_player->SetPositionX(atoi(data.c_str()));

							//switch to y position
							data = "";
						}
						else
						{
							//load up the position
							data += line.at(i);

							//if this is the last item read in the line, save it into the second data slot
							if (i = line.size() - 1)
							{
								m_player->SetPositionY(atoi(data.c_str()));
							}
						}
					}
					else if (dataType == "Health")
					{
						//load up the health

						if (line.at(i) == ',')
						{

							//save x position
							m_player->SetCurrentHealth(atoi(data.c_str()));

							//switch to y position
							data = "";
						}
						else
						{
							//load up the position
							data += line.at(i);

							//if this is the last item read in the line, save it into the second data slot
							if (i = line.size() - 1)
							{
								m_player->SetMaxHealth(atoi(data.c_str()));
							}
						}
					}
				}
			}


		}

		//while (getline(myfile, line))
		//{


		//}
		myfile.close();
	}

	/*//Health Sprites
	m_HealthSprite = m_pBackBuffer->CreateSprite("Assets\\Health_Heart.png");
	m_HealthLostSprite = m_pBackBuffer->CreateSprite("Assets\\Health_Heart_Depleted.png");
	m_HealthSprite->SetWidth(64);
	m_HealthSprite->SetHeight(64);
	m_HealthLostSprite->SetWidth(64);
	m_HealthLostSprite->SetHeight(64);

	//Set up player
	PlayerSpriteInit();
	m_player = new Player();
	m_player->Initialise(m_playerAnim, m_world);
	m_player->SetCurrentHealth(5);
	m_player->SetMaxHealth(5);

	//Game map setup
	m_gameMap = new GameMap();
	m_gameMap->Initialise("Assets\\map.txt", "Assets\\object.txt");
	m_gameMap->GenerateMap(*m_pBackBuffer, m_world);

	//Box2D world setup
	m_velocityIterations = 10;
	m_positionIterations = 10;
	m_timeStep = 1.0f / 20.0f;
	b2Vec2 gravity(0.0f, 0.0f);
	m_world.SetGravity(gravity);
	m_world.SetContactListener(&m_collisionListener);

	//Gold label - using a stringstream to concat strings
	std::ostringstream labelStream;
	labelStream << "Gold: " << m_gold;
	m_goldLabel = new Label(labelStream.str());
	m_goldLabel->SetColour(218, 165, 32, 0);

	//Game over labels
	m_gameOver = new Label("GAME OVER!");
	m_gameOver->SetBounds(440, 290, 400, 100);
	m_gameOver->SetColour(255, 0, 0, 0);

	//Restart game label
	m_restartGame = new Label("press f5 to restart");
	m_restartGame->SetBounds(440, 390, 400, 30);
	m_restartGame->SetColour(0, 0, 0, 0);

	//Debug - Waypoint mode label
	m_waypointModeLabel = new Label("Waypoint Mode");
	m_waypointModeLabel->SetBounds(440, 100, 400, 30);
	m_waypointModeLabel->SetColour(0, 0, 255, 0);

	//Debug - enemy selected for waypoints
	labelStream.str("");
	labelStream << "Enemy " << m_enemySelectedIndex << " Selected";
	m_enemySelectedLabel = new Label(labelStream.str());
	m_enemySelectedLabel->SetBounds(440, 150, 400, 30);
	m_enemySelectedLabel->SetColour(0, 0, 230, 0);

	//Debug - console
	m_debugText = new Label("");
	m_debugText->SetBounds(0, 600, 0, 100);
	m_debugText->SetColour(255, 255, 255, 0);

	//Loading waypoints, check current counter
	std::string line;

	bool run = true;
	while(run)
	{
	line = "patrol" + std::to_string(m_pathToSaveCounter) + ".txt";
	std::ifstream myfile(line);
	if (myfile.is_open())
	{
	m_pathToSaveCounter++;
	}
	else
	{
	run = false;
	}
	}
	//Sword Setup
	m_swordSprite = m_pBackBuffer->CreateAnimatedSprite("Assets\\weaponanim.png");
	m_swordSprite->LoadFrames(64, 64);
	m_swordSprite->StartAnimating();
	m_sword = new Sword(*m_player);
	m_sword->Initialise(m_swordSprite, m_world);*/
}

void Game::OpenMainMenu()
{
	if (!m_isGameRunning)
	{
		return;
	}

	m_inMainMenu = !m_inMainMenu;
	if (m_inMainMenu)
	{
		m_mainMenu->SetMenuState(ACTIVE);
		m_gameState = MAINMENU;
	}
	else
	{
		m_gameState = INGAME;
	}
}

void
Game::MouseClicked(int x, int y)
{
	//Mouse behaviour for main menu
	if (m_inMainMenu)
	{
		m_mainMenu->MouseClicked(x, y);
	}
	
	//Mouse behaviour ingame
	if (m_shopLabel->WasClickedOn(x, y))
	{
		if (m_gameState == SHOP)
		{
			m_gameState = INGAME;
		}
		else
		{
			m_gameState = SHOP;
		}
	}

	//Mouse behaviour with shop open
	if (m_gameState == SHOP)
	{
		UpdateGold(-(m_shop->MouseClicked(x, y, m_gold, m_player)));
	}

	//Mouse behaviour for waypoint mode
	if (m_waypointMode)
	{
		PlaceWaypoint(x, y);
	}
}

void
Game::WaypointMode()
{
	m_waypointMode = !m_waypointMode;
	if (m_waypointMode)
	{
		m_enemySelectedIndex = 0;
	}
}

void
Game::PlaceWaypoint(int x, int y)
{
	//Only place in waypoint mode, and if 1 enemy at least is on the map
	if (!m_waypointMode || m_enemies.size() == 0)
	{
		return;
	}
	m_enemies.at(m_enemySelectedIndex)->AddWaypoint(x, y);
}

void
Game::ChangeSelectedEnemy()
{
	if (!m_waypointMode)
	{
		return;
	}

	//change which enemy is selected in waypoint mode
	if (m_enemySelectedIndex < m_enemies.size() - 1)
	{
		m_enemySelectedIndex++;
	}
	else
	{
		m_enemySelectedIndex = 0;
	}

	//Update label
	std::ostringstream labelStream;
	labelStream.str("");
	labelStream << "Enemy " << m_enemySelectedIndex << " Selected";
	m_enemySelectedLabel->SetText(labelStream.str());
}

void
Game::SaveCurrentPatrol()
{
	if (!m_waypointMode)
	{
		return;
	}
	std::string saveString = "patrol" + std::to_string(m_pathToSaveCounter) + ".txt";
	m_enemies.at(m_enemySelectedIndex)->SavePatrolToDisk(saveString.c_str());
	m_pathToSaveCounter++;
}

void
Game::LoadPatrol()
{
	if (!m_waypointMode) 
	{
		return;
	}
	std::string saveString = "patrol" + std::to_string(m_pathToLoadCounter) + ".txt";
	if (m_enemies.at(m_enemySelectedIndex)->LoadPatrolFromDisk(saveString.c_str()))
	{
		m_pathToLoadCounter++;
	}
	else
	{
		m_pathToLoadCounter = 0;
		std::string saveString = "patrol" + std::to_string(m_pathToLoadCounter) + ".txt";
		m_enemies.at(m_enemySelectedIndex)->LoadPatrolFromDisk(saveString.c_str());
	}
}

void
Game::ClearPatrol()
{
	if (!m_waypointMode)
	{
		return;
	}
	m_enemies.at(m_enemySelectedIndex)->ClearWaypoints();
}

void Game::DebugCommand(std::string consoleCommand)
{
	//SDL_Log(consoleCommand.c_str());
	//Debug Console commands, enter them here for debugging
	if (consoleCommand == "waypointmode")
	{
		SDL_Log("Switching waypoint mode");
		WaypointMode();
	}
	if (consoleCommand == "spawnenemy")
	{
		SDL_Log("Spawning enemy");
		SpawnEnemy(rand() % 1366, rand() % 768);
	}
	//if (consoleCommand.find("giveplayergold", 0))
	//{
	//	std::string st = consoleCommand.substr(14, consoleCommand.size());
	//	SDL_Log(st.c_str());
	//}

}

void 
Game::DrawDebugConsole(std::string text)
{
	m_debugString = text;
	m_debugText->SetText(text);
	int length = text.size() * 15;
	if (length > 1366)
	{
		length = 1366;
	}
	m_debugText->SetBounds(0, 600, length, 100);
	//Draw(*m_pBackBuffer);
}

void 
Game::ShowDebugConsole(bool open)
{
	m_debugConsoleOpen = open;
}

void 
Game::SetConsoleText(std::string text)
{
	m_debugString = text;
	m_debugText->SetText(text);
	int length = text.size() * 15;
	if (length > 1366)
	{
		length = 1366;
	}
	m_debugText->SetBounds(0, 600, length, 100);
}

GameState Game::GetGameState()
{
	return m_gameState;
}

void
Game::SwordAttack(bool isAttacking)
{
	m_sword->SetAttacking(isAttacking);
}
