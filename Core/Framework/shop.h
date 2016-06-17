#pragma once

class Label;
class BackBuffer;
class Label;
class Player;

class Shop
{
public:
	Shop();
	~Shop();

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	int MouseClicked(int x, int y, int gold, Player* player);

	//Member Data:
public:

protected:

private:
	//Labels of items to buy
	Label* m_buyHealthUpgrade;
	Label* m_buyHeal;
	Label* m_buyWatch;

	//Prices of items to buy
	int m_healthUpgradePrice;
	int m_healPrice;
	int m_watchPrice;
};

