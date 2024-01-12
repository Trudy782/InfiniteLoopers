#pragma once
#include "Peg.h"
#include<random>

class Buldozerist : public Peg
{
public:
	Buldozerist(Color color, Position position);
	Buldozerist() = default;
	~Buldozerist() = default;

	Buldozerist(const Buldozerist& other);

	size_t random(size_t size);

	bool ThrowCoin();

};

