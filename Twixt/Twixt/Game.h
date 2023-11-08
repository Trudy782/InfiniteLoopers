#pragma once
#include "player.h"
#include "board.h"
class Game
{
public:
	Game();
	void startGame();
	void changePlayer();
	bool Validation(const Peg& pStart, const Peg& pEnd);
	bool PegValidation(const size_t& row, const size_t& col);
private:
	Player m_redPlayer;
	Player m_blackPlayer;
	Board m_board;
	bool m_isRedTurn;
};

