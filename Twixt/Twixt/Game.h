#pragma once
#include "player.h"
#include "board.h"
#include "card.h"
#include "Buldozerist.h"
#include "BoardChecker.h"
#include<functional>
class Game
{
public:
	Game();
	void StartGame();
	void StartAdvancedGameMode4();
private:
	void ChangePlayer();
	bool LinkValidation(const Peg& pStart, const Peg& pEnd);
	bool PegValidation(const size_t& row, const size_t& col);
	bool MovePeg();
	bool MoveLink(bool& castig);
	void MoveBuldozer();
	Player& currentPlayer();
	void showLinks(const Player& player);
	/*void showAdjacency();*/

	void SwitchColorMenu(bool& validMove);
	void MainMenu(bool& validMove, bool& castig);


	/*bool WinConditionsRed();
	bool WinConditionsBlack();*/

	bool CheckOwnPegs(const Peg& pStart, const Peg& pEnd);
	bool CheckPositionsPegs(const Peg& pStart, const Peg& pEnd, int xStart, int yStart, int xEnd, int yEnd);
	bool CheckIntersectionsLinks(const Peg& pStart, const Peg& pEnd, int xStart, int yStart, int xEnd, int yEnd);

	bool CheckCorners(const size_t& row, const size_t& col, const size_t& size);
	bool CheckPerimeter(const size_t& row, const size_t& col, const size_t& size);
	bool CheckEnemyZone(const size_t& row, const size_t& col, const size_t& size);


	//implementari Mode 4

	std::string PickCard();
	bool PlayCard();

	//Refferal System

	void RefferalSystemHint1();
	void RefferalSystemHint2(int firstPosition, int secondPosition);

private:
	Player m_redPlayer;
	Player m_blackPlayer;
	Board m_board;
	bool m_isRedTurn;
	Buldozerist m_buldozer;
	Card m_card;
};

