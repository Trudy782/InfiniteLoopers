#pragma once
#include "player.h"
#include "board.h"
class Game
{
public:
	Game();
	void startGame();
	void changePlayer();
private:
	Player m_redPlayer;
	Player m_blackPlayer;
	Board m_board;
	bool m_isRedTurn;
};

