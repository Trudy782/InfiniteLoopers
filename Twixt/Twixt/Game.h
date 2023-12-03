#pragma once
#include "player.h"
#include "board.h"
class Game
{
public:
	Game();
	void StartGame();
private:
	void ChangePlayer();
	bool LinkValidation(const Peg& pStart, const Peg& pEnd);
	bool PegValidation(const size_t& row, const size_t& col);
    bool MovePeg();
	bool MoveLink();
	Player &currentPlayer();
	void showLinks(const Player& player);
	void ShowAdjacentPegs(const Peg& peg);

	bool WinConditionsRed();
	bool WinConditionsBlack();

	bool CheckOwnPegs(const Peg& pStart, const Peg& pEnd);
	bool CheckPositionsPegs(const Peg& pStart, const Peg& pEnd, int xStart, int yStart, int xEnd, int yEnd);
	bool CheckIntersectionsLinks(const Peg& pStart, const Peg& pEnd, int xStart, int yStart, int xEnd, int yEnd);
private:
	Player m_redPlayer;
	Player m_blackPlayer;
	Board m_board;
	bool m_isRedTurn;
};

