#pragma once
#include "board.h"

class Buldozerist
{
public:
	Buldozerist(Board& gameBoard);
	Buldozerist() = default;
	~Buldozerist() = default;
	Buldozerist(const Buldozerist& other);
	Buldozerist& operator=(const Buldozerist& other);

private:
	Board* board;
	Board::Position currentPosition;
};

