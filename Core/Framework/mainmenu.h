#pragma once

class BackBuffer;
class Label;

enum MenuState
{
	ACTIVE,
	NEWGAME,
	LOADGAME,
	SAVEGAME,
	QUITGAME
};

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void MouseClicked(int x, int y);
	MenuState GetMenuState();
	void SetMenuState(MenuState state);


	//Member Data:
public:

protected:

private:
	MenuState m_menuState;
	Label* m_newGame;
	Label* m_saveGame;
	Label* m_loadGame;
	Label* m_quitGame;
};

