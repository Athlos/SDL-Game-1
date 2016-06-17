// 717310 C++ SDL Framework
#ifndef __INPUTHANDER_H__
#define __INPUTHANDER_H__

// Library includes:
#include <SDL.h>
#include <string>

// Forward Declarations:
class Game;

class InputHandler
{
	//Member Methods:
public:
	InputHandler();
	~InputHandler();

	bool Initialise();
	void ProcessInput(Game& game);
	void ProcessMovement(Game& game);

protected:

private:
	InputHandler(const InputHandler& inputHandler);
	InputHandler& operator=(const InputHandler& inputHandler);

	//Member Data:
public:

protected:
	SDL_Joystick* m_pGameController;

private:
	bool m_consoleOpen;
	std::string m_consoleText;

};

#endif // __INPUTHANDER_H__
