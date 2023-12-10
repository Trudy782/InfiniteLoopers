#include "Buldozerist.h"

Buldozerist::Buldozerist(Board& gameBoard) : board{ &gameBoard }
{
}

Buldozerist::Buldozerist(const Buldozerist& other)
	: board(other.board), currentPosition(other.currentPosition) {}

Buldozerist& Buldozerist::operator=(const Buldozerist& other)
{
	if (this != &other)
	{
		delete board;

		board = other.board;
		currentPosition = other.currentPosition;
	}

	return *this;
}

