#pragma once
#include "player.h"
#include "board.h"
class Game
{
public:
	Game();
	void StartGame();
	void ChangePlayer();
	bool LinkValidation(const Peg& pStart, const Peg& pEnd);
	bool PegValidation(const size_t& row, const size_t& col);
	void move();
	Player currentPlayer();
private:
	Player m_redPlayer;
	Player m_blackPlayer;
	Board m_board;
	bool m_isRedTurn;
};

