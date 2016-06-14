#include "mainmenu.h"
#include "backbuffer.h"
#include "label.h"


MainMenu::MainMenu()
{
	m_newGame = new Label("New Game");
	m_newGame->SetBounds(440, 190, 400, 100);
	m_newGame->SetColour(0, 0, 0, 0);

	m_loadGame = new Label("Load Game");
	m_loadGame->SetBounds(440, 320, 400, 100);
	m_loadGame->SetColour(0, 0, 0, 0);

	m_saveGame = new Label("Save Game");
	m_saveGame->SetBounds(440, 450, 400, 100);
	m_saveGame->SetColour(0, 0, 0, 0);

	m_quitGame = new Label("Quit Game");
	m_quitGame->SetBounds(440, 600, 400, 100);
	m_quitGame->SetColour(0, 0, 0, 0);

}


MainMenu::~MainMenu()
{
}

void 
MainMenu::Process(float deltaTime)
{

}

void 
MainMenu::Draw(BackBuffer& backBuffer)
{
	m_newGame->Draw(backBuffer);
	m_quitGame->Draw(backBuffer);
	m_loadGame->Draw(backBuffer);
	m_saveGame->Draw(backBuffer);
}

void
MainMenu::MouseClicked(int x, int y)
{
	if (m_newGame->WasClickedOn(x, y))
	{
		m_menuState = NEWGAME;
	}

	if (m_quitGame->WasClickedOn(x, y))
	{
		m_menuState = QUITGAME;
	}

	if (m_loadGame->WasClickedOn(x, y))
	{
		m_menuState = LOADGAME;
	}

	if (m_saveGame->WasClickedOn(x, y))
	{
		m_menuState = SAVEGAME;
	}
}

MenuState MainMenu::GetMenuState()
{
	return m_menuState;
}

void 
MainMenu::SetMenuState(MenuState state)
{
	m_menuState = state;
}

