#pragma once
#include "Player.h"
#include "Board.h"
#include "Card.h"
#include "Buldozerist.h"
#include "BoardChecker.h"
#include<functional>
#include <fstream>
#include <regex>
class Game
{
public:
	Game();
	void Initialize(int size, const std::string& redPlayerName, const std::string& blackPlayerName);

	void SaveGame();
	void NewGame();
	void RestoreGame();
	void RestoreLinks(std::vector<std::string> link_strings);

	void StartGame();
	void StartAdvancedGameMode4();
	void ChangePlayer();
	bool LinkValidation(const Peg& pStart, const Peg& pEnd);
	bool PegValidation(const size_t& row, const size_t& col);
	bool MovePeg(const size_t row, const size_t col);
	bool MoveLink(bool& castig);
	Player& currentPlayer();
	void showLinks(const Player& player);

	void SwitchColorMenu(bool& validMove);
	void MainMenu(bool& validMove, bool& castig);


	bool CheckOwnPegs(const Peg& pStart, const Peg& pEnd);
	bool CheckPositionsPegs(const Peg& pStart, const Peg& pEnd, int xStart, int yStart, int xEnd, int yEnd);
	bool CheckIntersectionsLinks(const Peg& pStart, const Peg& pEnd, int xStart, int yStart, int xEnd, int yEnd);

	bool CheckCorners(const size_t& row, const size_t& col, const size_t& size);
	bool CheckPerimeter(const size_t& row, const size_t& col, const size_t& size);
	bool CheckEnemyZone(const size_t& row, const size_t& col, const size_t& size);

	bool GetIsRedTurn() const;



	//implementari Mode 4

	std::string PickCard();
	bool PlayCard();

	//Refferal System

	/*void RefferalSystemHint1();
	void RefferalSystemHint2(size_t firstPosition, size_t secondPosition);
	bool CheckPositionForHint2(size_t firstPosition, size_t secondPosition, std::vector<Peg>resultDfs); */

private:
	Player m_redPlayer;
	Player m_blackPlayer;
	Board m_board;
	bool m_isRedTurn;
	Card m_card;
};

