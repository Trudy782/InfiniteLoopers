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

	Buldozerist(Buldozerist&& other) noexcept;
	Buldozerist& operator=(Buldozerist&& other) noexcept;

	void setBoard(Board& gameBoard);
	Board& getBoard() const;

	void setCurrentPosition(Board::Position newPosition);
	Board::Position getCurrentPosition() const;
private:
	Board* board;
	Board::Position currentPosition;
};

