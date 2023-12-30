#pragma once

#include "peg.h"
#include "link.h"
#include <iostream>
#include <vector>
#include <cstdint>


//de adaugat un vector de carti speciale
class Player {
public:
	using Position = std::pair<size_t, size_t>;
	Player(Color color, std::string name);
	Player() = default;
	Player(const Player& other) = default;
	Player& operator=(const Player& obj) = default;
	~Player() = default;

	friend std::istream& operator>>(std::istream& is, Player& player);
	friend std::ostream& operator<<(std::ostream& os, const Player& player);

	void SetColor(Color color);
	void SetName(std::string name);
	Color GetColor() const;
	const std::string& GetName() const;
	void SetNrPegs(int pegs);

	int GetNrPegs() const;

	Position GetNextActionPeg();

	void AddCard(std::string card);
	const std::vector<std::string>& GetCards()const;
	void EraseCard();
	void IncrementNumber();

private:
	Color m_color : 1;
	std::string m_name;
	std::vector<std::string> m_cards;
	int m_nr_pegs;
};