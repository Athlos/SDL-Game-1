// 717310 C++ SDL Framework

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"
#include "direction.h"
#include "SDL.h"

// Library includes:
#include <cassert>
#include <string>
#include "ostream"

InputHandler::InputHandler()
	: m_pGameController(0)
	, m_consoleOpen(false)
	, m_consoleText("")
{

}

InputHandler::~InputHandler()
{
	if (m_pGameController)
	{
		//SDL_JoystickClose(m_pGameController);
		//m_pGameController = 0;
	}
}

bool 
InputHandler::Initialise()
{
	//int numControllesr = SDL_NumJoysticks();

	//m_pGameController = SDL_JoystickOpen(0);
	//assert(m_pGameController);

	return (true);
}

void 
InputHandler::ProcessInput(Game& game)
{
	// Ex006.2: Receive Input Events below...
	SDL_Event e;
	SDL_PumpEvents();
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	std::string debugString = "";
	while (SDL_PollEvent(&e) != 0)
	{
		//Use different function if the console is open
		if (m_consoleOpen)
		{
			SDL_StartTextInput();
			SDL_bool done = SDL_FALSE;
			
			//All input sent to console instead
			switch (e.type)
			{
			case SDL_KEYDOWN:
				/* Quit */
				if (e.key.keysym.sym == SDLK_RETURN)
				{
					//Close console, clear text
					m_consoleOpen = false;
					game.DebugCommand(m_consoleText);
					m_consoleText = "";
					game.ShowDebugConsole(m_consoleOpen);
					break;
				}
				//Backspace
				if (e.key.keysym.sym == SDLK_BACKSPACE && m_consoleText.length() > 0)
				{
					m_consoleText.pop_back();
					game.SetConsoleText(m_consoleText);
					break;
				}
			case SDL_TEXTINPUT:
				/* Add new text onto the end of our text */
				if (*(e.text.text) >= 32)
				{
					m_consoleText += e.text.text;
					game.SetConsoleText(m_consoleText);
				}
				SDL_Log(m_consoleText.c_str());
				break;
			}
			//SDL_StopTextInput();
		}
		else 
		{
			switch (e.type)
			{
			case SDL_MOUSEBUTTONDOWN:
				//print the position to command line
				int x, y;
				SDL_GetMouseState(&x, &y);
				debugString = "X: " + std::to_string(x) + ", Y: " + std::to_string(y);
				SDL_Log(debugString.c_str());
				game.MouseClicked(x, y);
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_RETURN:
					//Open console
					m_consoleOpen = true;
					game.ShowDebugConsole(m_consoleOpen);
					game.SetConsoleText("");
					break;
				case SDLK_1:
					//Damage Player by 1 point
					game.UpdatePlayerHealth(-1);
					break;
				case SDLK_2:
					//Heal Player by 1 point
					game.UpdatePlayerHealth(1);
					break;
				case SDLK_3:
					//Add 10 Gold
					game.UpdateGold(-10);
					break;
				case SDLK_4:
					//Remove 10 Gold
					game.UpdateGold(10);
					break;
				case SDLK_5:
					//Spawn random pickups
					for (int i = 0; i < rand() % 5; i++)
					{
						game.SpawnPickup(rand() % 1280, rand() % 720, GOLD);
					}

					for (int i = 0; i < rand() % 2; i++)
					{
						game.SpawnPickup(rand() % 1280, rand() % 720, HEALTH);
					}
					break;
				case SDLK_6:
				{
					//Spawn an enemy
					int enemyX = rand() % 1280;
					int enemyY = rand() % 720;
					game.SpawnEnemy(enemyX, enemyY);
					debugString = "Enemy spawned at: " + std::to_string(enemyX) + ", " + std::to_string(enemyY);
					SDL_Log(debugString.c_str());
				}
				break;
				case SDLK_SPACE:
				{
					//Kill an enemy
					game.PlayerAttack();
				}
				break;
				case SDLK_F5:
					//Restart Game
					game.RestartGame();
					break;
				case SDLK_F1:
					//Waypoint mode
					game.WaypointMode();
					break;
				case SDLK_RIGHT:
					//Waypoint mode
					game.ChangeSelectedEnemy();
					break;
				case SDLK_LEFT:
					//Save patrol
					game.SaveCurrentPatrol();
					break;
				case SDLK_UP:
					//Load patrol
					game.LoadPatrol();
					break;
				case SDLK_DOWN:
					//clear patrol
					game.ClearPatrol();
					break;
				case SDLK_ESCAPE:
					game.OpenMainMenu();
					break;
				case SDLK_HOME:
					game.SwordAttack(true);
					break;
					//case SDLK_INSERT:
					//	game.ToggleDebug();
					//	break;
				}
				break;
			case SDL_KEYUP:
				switch (e.key.keysym.sym)
				{
				case SDLK_w:
				case SDLK_a:
				case SDLK_d:
				case SDLK_s:
					game.UpdatePlayer(Direction::STOP);
					break;
				case SDLK_HOME:
					game.SwordAttack(false);
					break;
				default:
					break;
				}

			default:
				break;
			}
		}
	}
		
}

void 
InputHandler::ProcessMovement(Game & game)
{
	//Processing movement input
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	Direction newDir = Direction::STOP;

	//continuous-response keys
	if (keystate[SDL_SCANCODE_W])
	{
		SDL_Log("up");
		newDir = Direction::UP;
	}
	if (keystate[SDL_SCANCODE_S])
	{
		SDL_Log("down");
		newDir = Direction::DOWN;
	}
	if (keystate[SDL_SCANCODE_A])
	{
		SDL_Log("left");
		newDir = Direction::LEFT;
	}
	if (keystate[SDL_SCANCODE_D])
	{
		SDL_Log("right");
		newDir = Direction::RIGHT;
	}
	
	if (newDir != Direction::STOP)
	{
		game.UpdatePlayer(newDir);
	}
}
