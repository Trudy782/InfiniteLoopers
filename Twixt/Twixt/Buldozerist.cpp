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

Buldozerist::Buldozerist(Buldozerist&& other) noexcept
	: board(other.board), currentPosition(other.currentPosition)
{
}

Buldozerist& Buldozerist::operator=(Buldozerist&& other) noexcept
{
	
		delete board;
		currentPosition.first = NULL;
		currentPosition.second = NULL;

		board = other.board;
		currentPosition = other.currentPosition;

		other.board = nullptr;
		other.currentPosition.first = NULL;
		other.currentPosition.second = NULL;
	

		return *this;

}

void Buldozerist::setBoard(Board& gameBoard)
{
	board = &gameBoard;
}

Board& Buldozerist::getBoard() const
{
	return *board;
}

void Buldozerist::setCurrentPosition(Board::Position newPosition)
{
	currentPosition = newPosition;
}

Board::Position Buldozerist::getCurrentPosition() const
{
	return currentPosition;
}

size_t Buldozerist::random(size_t size)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<size_t> distribution(0, size - 1);
	return distribution(gen);
}



