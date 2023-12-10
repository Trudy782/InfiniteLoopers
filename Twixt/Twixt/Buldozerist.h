#pragma once
#include "board.h"

class Buldozerist
{
public:
	Buldozerist(Board& gameBoard);
	Buldozerist() = default;
	~Buldozerist() = default;
private:
	Board* board;
	Board::Position currentPosition;
};

