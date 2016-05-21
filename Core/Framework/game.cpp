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
#include "physics.h"
#include "entity.h"
#include "label.h"
#include "pickup.h"
#include "gamemap.h"

// Library includes:
#include <cassert>
#include <cmath>
#include <ctime>
#include <SDL.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <fstream>
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
, m_gameMap()
, m_world(m_gravity)
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

	//Health Sprites
	m_HealthSprite = m_pBackBuffer->CreateSprite("Assets\\Health_Heart.png");
	m_HealthLostSprite = m_pBackBuffer->CreateSprite("Assets\\Health_Heart_Depleted.png");
	m_HealthSprite->SetWidth(64);
	m_HealthSprite->SetHeight(64);
	m_HealthLostSprite->SetWidth(64);
	m_HealthLostSprite->SetHeight(64);

	//Set up player
	PlayerSpriteInit();
	m_Player = new Player();
	m_Player->Initialise(m_playerAnim);
	m_Player->SetCurrentHealth(5);
	m_Player->SetMaxHealth(5);

	//Box2D world setup
	//velocityIterations 
	m_velocityIterations = 10;
	m_positionIterations = 10;
	m_timeStep = 1.0f / 60.0f;
	b2Vec2 gravity(0.0f, 0.0f);
	m_world.SetGravity(gravity);
	//Box2D TESTING PURPOSES ONLY
	m_testBodyDef.type = b2_dynamicBody;
	m_testBodyDef.position.Set(0, 20);
	m_testBodyDef.angle = 0;
	m_testBody = m_world.CreateBody(&m_testBodyDef);
	m_textShape.SetAsBox(1, 1);
	m_testFixtureDef.shape = &m_textShape;
	m_testFixtureDef.density = 1;
	m_testBody->CreateFixture(&m_testFixtureDef);
	m_testSprite = m_pBackBuffer->CreateSprite("Assets\\pot.png");
	//Bottom screen collider test
	m_bottomWorldDef.type = b2_staticBody;
	m_bottomWorldDef.position.Set(-5.0f, static_cast<float>(m_height) - 20.0f);//32 is the half size of the pot, should be changed to the size of the player
	m_bottomWorldDef.angle = 0;
	m_bottomWorldColliderBody = m_world.CreateBody(&m_bottomWorldDef);
	m_bottomWorldShape.SetAsBox(static_cast<float>(m_width), 2);
	m_bottomWorldFixtureDef.shape = &m_bottomWorldShape;
	m_bottomWorldFixtureDef.density = 1;
	m_bottomWorldColliderBody->CreateFixture(&m_bottomWorldFixtureDef);

	//Gold label - using a stringstream to concat strings
	std::ostringstream goldStream;
	goldStream << "Gold: " << m_gold;
	m_goldLabel = new Label(goldStream.str());
	m_goldLabel->SetColour(218, 165, 32, 0);

	//Testing Pickups
	for (int i = 0; i < rand() % 30; i++)
	{
		SpawnPickup(rand() % 1800, rand() % 1000, GOLD);
	}
	for (int i = 0; i < rand() % 10; i++)
	{
		SpawnPickup(rand() % 1800, rand() % 1000, HEALTH);
	}
	m_gameMap = new GameMap();
	m_gameMap->Initialise("Assets\\map.txt", "Assets\\object.txt");
	m_gameMap->GenerateMap(*m_pBackBuffer);


	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;

	return (true);
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
	//Box2D simulation loop
	m_world.Step(m_timeStep, m_velocityIterations, m_positionIterations);
	b2Vec2 testObjPosition = m_testBody->GetPosition();	std::string debug = "Dynamic Body::Position X: " + (std::to_string(testObjPosition.x)) + ", Position Y: " + (std::to_string(testObjPosition.y));
	SDL_Log(debug.c_str());
	m_Player->Process(deltaTime);
	m_testSprite->Process(deltaTime);

	b2Vec2 worldColliderPosition = m_bottomWorldColliderBody->GetPosition();
	std::string debugWorld = "World bottom Collider Pos X: " + (std::to_string(worldColliderPosition.x) + ", Pos Y: " + (std::to_string(worldColliderPosition.y)));
	SDL_Log(debugWorld.c_str());
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
		}
		else 
		{
			//Check if player can pickup, and apply rewards if they do
			if (m_Player->CheckPickup(*current))
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

	//m_gameMap->Process(deltaTime);
}

void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	int x = m_width - 130;
	m_gameMap->Draw(backBuffer);
	//TESTING PURPOSES
	//test drawing a box2d box body on screen with a pot as the sprite representation
	b2Vec2 position = m_testBody->GetPosition();
	m_testSprite->SetX(position.x);
	m_testSprite->SetY(position.y);
	m_testSprite->Draw(backBuffer);

	for (int i = 0; i < m_Player->GetMaxHealth(); i++)
	{
		if (i < m_Player->GetCurrentHealth()) 
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
	m_Player->Draw(backBuffer);

	//Draw test label
	m_goldLabel->Draw(backBuffer);

	//Draw Pickups
	for each (Pickup* p in m_pickups) 
	{
		p->Draw(backBuffer);
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
	m_Player->UpdatePlayerHealth(amount);
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
	b2Vec2 velocity;
	switch (direction)
	{
	case Direction::UP:
		m_Player->SetVerticalVelocity(-200.0f);
		
		velocity.x = 0.0f;
		velocity.y = -200.0f;
		m_testBody->SetLinearVelocity(velocity);
		break;
	case Direction::DOWN:
		m_Player->SetVerticalVelocity(200.0f);
		velocity.x = 0.0f;
		velocity.y = 200.0f;
		m_testBody->SetLinearVelocity(velocity);
		break;
	case Direction::LEFT:
		m_Player->SetHorizontalVelocity(-200.0f);
		velocity.x = -200.0f;
		velocity.y = 0.0f;
		m_testBody->SetLinearVelocity(velocity);
		break;
	case Direction::RIGHT:
		m_Player->SetHorizontalVelocity(200.0f);
		velocity.x = 200.0f;
		velocity.y = 0.0f;
		m_testBody->SetLinearVelocity(velocity);
		break;
	case Direction::STOP:
		m_Player->SetVerticalVelocity(0.0f);
		m_Player->SetHorizontalVelocity(0.0f);
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		m_testBody->SetLinearVelocity(velocity);
		break;
	case Direction::RESET://Debug, reset position to middle of screen
		m_Player->SetVerticalVelocity(0.0f);
		m_Player->SetHorizontalVelocity(0.0f);
		m_Player->SetPositionX(m_width/2);
		m_Player->SetPositionY(m_height /2);
		break;
	}

	m_Player->UpdatePlayerDirection(direction);
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
	std::ostringstream goldStream;
	goldStream << "Gold: " << m_gold;
	m_goldLabel->SetText(goldStream.str());

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
		Pickup* goldPickup = new Pickup();
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
		Pickup* heartPickup = new Pickup();
		heartAnim->LoadFrames(64, 64);
		heartAnim->SetFrameSpeed(0.12f);
		heartPickup->Initialise(heartAnim);
		heartPickup->SetPosition(x, y);
		m_pickups.push_back(heartPickup);
	}
}
