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
	Player& currentPlayer();
	void showLinks(const Player& player);
	void showAdjacency();

	bool WinConditionsRed();
	bool WinConditionsBlack();

	bool CheckOwnPegs(const Peg& pStart, const Peg& pEnd);
	bool CheckPositionsPegs(const Peg& pStart, const Peg& pEnd, int xStart, int yStart, int xEnd, int yEnd);
	bool CheckIntersectionsLinks(const Peg& pStart, const Peg& pEnd, int xStart, int yStart, int xEnd, int yEnd);

	bool CheckCorners(const size_t& row, const size_t& col, const size_t& size);
	bool CheckPerimeter(const size_t& row, const size_t& col, const size_t& size);
	bool IsPlaceOccupied(const size_t& row, const size_t& col);
	bool CheckEnemyZone(const size_t& row, const size_t& col, const size_t& size);

private:
	Player m_redPlayer;
	Player m_blackPlayer;
	Board m_board;
	bool m_isRedTurn;
};

