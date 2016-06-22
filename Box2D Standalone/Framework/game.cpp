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

	//Setup Backbuffer
	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(m_width, m_height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}
	//Setup input handler
	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	//Set up player
	PlayerSpriteInit();
	m_player = new Player();
	m_player->Initialise(m_playerAnim, m_world);
	m_player->SetCurrentHealth(5);
	m_player->SetMaxHealth(5);
	m_player->SetPosition(50.0f,350.0f);
	m_player->m_classType = ClassType::PLAYER;

	//Box2D world setup
	m_velocityIterations = 10;
	m_positionIterations = 10;
	m_timeStep = 1.0f / 20.0f;
	m_world.SetGravity(b2Vec2_zero);
	m_world.SetContactListener(&m_collisionListener);

	//setup for box2d test stuff
	m_testSprite = m_pBackBuffer->CreateSprite("assets//pot.png");
	m_testEntity = new Entity();
	m_testEntity->Initialise(m_testSprite, m_world);
	m_testEntity->SetPosition(1300, 350);
	m_testEntity->SetEntityDensity(30.0f);
	m_testEntity->m_classType = ClassType::PADDLE;

	//test ball setup
	m_ballSprite = m_pBackBuffer->CreateSprite("assets//rock.png");
	m_ballEntity = new Entity();
	m_ballEntity->Initialise(m_ballSprite, m_world);
	m_ballEntity->SetPosition(750,400);
	m_ballEntity->SetEntityCollisionVelocity(b2Vec2(200.0f,30.0f));
	m_ballEntity->m_classType = ClassType::BALL;

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
	//Process game entities
	m_player->Process(deltaTime);
	m_testEntity->Process(deltaTime);
	m_ballEntity->Process(deltaTime);
}

void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	int x = m_width - 130;

	//Draw player
	m_player->Draw(backBuffer);
	//test entity draw
	m_testEntity->Draw(backBuffer);
	m_ballEntity->Draw(backBuffer);
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
		m_player->SetPlayerCollisionVelocity(b2Vec2(0.0f, -200.0f));
		//m_testBody->SetLinearVelocity(velocity);
		break;
	case Direction::DOWN:
		m_player->SetPlayerCollisionVelocity(b2Vec2(0.0f, 200.0f));
		break;
	case Direction::LEFT:
		//m_player->SetPlayerCollisionVelocity(b2Vec2(-200.0f, 0.0f));
		m_ballEntity->RotateEntity(90.0f);
		break;
	case Direction::RIGHT:
		//m_player->SetPlayerCollisionVelocity(b2Vec2(200.0f, 0.0f));
		break;
	case Direction::STOP:
		m_player->SetPlayerCollisionVelocity(b2Vec2_zero);
		break;
	}

	m_player->UpdatePlayerDirection(direction);
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

void
Game::CheckForCollision()
{

}

void
Game::MoveTestObject(Direction direction)
{
	switch (direction)
	{
	case Direction::UP:
		m_testEntity->SetEntityCollisionVelocity(b2Vec2(0.0f, -200.0f));
		break;
	case Direction::DOWN:
		m_testEntity->SetEntityCollisionVelocity(b2Vec2(0.0f, 200.0f));
		break;
	case Direction::LEFT:
		//m_testEntity->SetEntityCollisionVelocity(b2Vec2(-200.0f, 0.0f));
		break;
	case Direction::RIGHT:
		//m_testEntity->SetEntityCollisionVelocity(b2Vec2(200.0f, 0.0f));
		break;
	case Direction::STOP:
		m_testEntity->SetEntityCollisionVelocity(b2Vec2_zero);
		break;
	}
}