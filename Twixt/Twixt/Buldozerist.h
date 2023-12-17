#pragma once
#include "board.h"
#include<random>

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

	Board::Position RandomPosition();
private:
	Board* board;
	Board::Position currentPosition;

	size_t random(size_t size);
};

