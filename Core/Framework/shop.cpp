#include "shop.h"
#include "backbuffer.h"
#include "label.h"
#include "player.h"

#include <iostream>
#include <sstream>


Shop::Shop()
{
	//Setup Prices
	m_healthUpgradePrice = 100;
	m_healPrice = 20;
	m_watchPrice = 250;

	//Setup Labels
	std::stringstream priceStream;
	priceStream << "Buy Health Upgrade : " << m_healthUpgradePrice << " Gold";
	m_buyHealthUpgrade = new Label(priceStream.str());
	m_buyHealthUpgrade->SetBounds(120, 90, 350, 50);
	m_buyHealthUpgrade->SetColour(0, 0, 0, 0);

	priceStream.str("");
	priceStream << "Buy Refil Hearts : " << m_healPrice << " Gold";
	m_buyHeal = new Label(priceStream.str());
	m_buyHeal->SetBounds(120, 150, 350, 50);
	m_buyHeal->SetColour(0, 0, 0, 0);

	priceStream.str("");
	priceStream << "Buy Timemaster Watch : " << m_watchPrice << " Gold";
	m_buyWatch = new Label(priceStream.str());
	m_buyWatch->SetBounds(120, 210, 350, 50);
	m_buyWatch->SetColour(0, 0, 0, 0);
}


Shop::~Shop()
{
}

void
Shop::Draw(BackBuffer & backBuffer)
{
	//Draw shop background
	backBuffer.SetDrawColour(255, 255, 255);
	backBuffer.DrawRectangle(100, 70, 500, 400);

	//Draw shop Labels
	m_buyHealthUpgrade->Draw(backBuffer);
	m_buyHeal->Draw(backBuffer);
	m_buyWatch->Draw(backBuffer);
}

int
Shop::MouseClicked(int x, int y, int gold, Player* player)
{
	//Check which label was clicked
	if (m_buyHealthUpgrade->WasClickedOn(x, y))
	{
		//Check can afford
		if (gold >= m_healthUpgradePrice)
		{
			player->SetMaxHealth(player->GetMaxHealth() +1);
			player->SetCurrentHealth(player->GetCurrentHealth() + 1);
			return m_healthUpgradePrice;
		}
	}

	if (m_buyHeal->WasClickedOn(x, y))
	{
		//Check can afford
		if (gold >= m_healPrice)
		{
			player->SetCurrentHealth(player->GetMaxHealth());
			return m_healPrice;
		}
	}

	if (m_buyWatch->WasClickedOn(x, y))
	{
		//Check can afford
		if (gold >= m_watchPrice)
		{
			//TODO add watch to player
			return m_watchPrice;
		}
	}

	//Return 0 if player cannot afford
	return 0;
}
