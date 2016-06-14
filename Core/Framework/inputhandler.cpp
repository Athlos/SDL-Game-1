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
				{
					if (game.GetGameState() != INGAME)
					{
						return;
					}
					SDL_Log("Text input started");
					game.ShowDebugConsole(true);
					game.DrawDebugConsole("");
					//Open console
					SDL_StartTextInput();
					SDL_bool done = SDL_FALSE;
					std::string text = "";

					while (!done) 
					{
						SDL_Event event;
						if (SDL_PollEvent(&event)) {
							switch (event.type) {
							case SDL_KEYDOWN:
								/* Quit */
								if (event.key.keysym.sym == SDLK_RETURN)
								{
									done = SDL_TRUE;
									break;
								}
								//Backspace
								if (event.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0)
								{
									text.pop_back();
									game.DrawDebugConsole(text);
									break;
								}
								else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
								{
									SDL_SetClipboardText(text.c_str());
									game.DrawDebugConsole(text);
								}
								else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
								{
									text = SDL_GetClipboardText();
									game.DrawDebugConsole(text);
								}
							case SDL_TEXTINPUT:
								/* Add new text onto the end of our text */
								SDL_Log(text.c_str());
								if (*(event.text.text) >= 32)
								{
									text += event.text.text;
									game.DrawDebugConsole(text);
								}
								break;
							}
						}
						//SDL_StopTextInput();
					}
					SDL_Log(text.c_str());
					game.DebugCommand(text);
					game.ShowDebugConsole(false);
				}	
				SDL_Log("Text input over");
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
				for (int i = 0; i < 1; i++)
				{
					game.SpawnPickup(rand() % 1800, rand() % 1000, GOLD);
				}
				/*
				for (int i = 0; i < rand() % 10; i++)
				{
					game.SpawnPickup(rand() % 1800, rand() % 1000, HEALTH);
				}*/
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
			case SDLK_w:
				SDL_Log("up");
				game.UpdatePlayer(Direction::UP);
				break;
			case SDLK_s:
				SDL_Log("down");
				game.UpdatePlayer(Direction::DOWN);
				break;
			case SDLK_a:
				SDL_Log("left");
				game.UpdatePlayer(Direction::LEFT);
				break;
			case SDLK_d:
				SDL_Log("right");
				game.UpdatePlayer(Direction::RIGHT);
				break;
			case SDLK_ESCAPE:
				game.OpenMainMenu();
				break;
			case SDLK_HOME:
				game.UpdatePlayer(Direction::RESET);
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
			default:
				break;
			}
		
		default:
			break;
		}
	}
}
