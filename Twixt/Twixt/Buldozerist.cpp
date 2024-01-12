#include "Buldozerist.h"

Buldozerist::Buldozerist(Color color, Position position) : Peg{ color,position }
{
}

Buldozerist::Buldozerist(const Buldozerist& other)
	: Peg{ other } {}


bool Buldozerist::ThrowCoin()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(0, 1);
	return distribution(gen) == 1;
	return 0;
}

size_t Buldozerist::random(size_t size)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<size_t> distribution(0, size - 1);
	return distribution(gen);
}



