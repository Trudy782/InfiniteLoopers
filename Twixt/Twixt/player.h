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
	Player(Color color, std::string name, std::vector<Peg*> pegs);
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
	const std::vector<Peg*>& GetPeg() const;

	Position GetNextActionPeg();
	void AddPeg(Peg* peg);
	void RemovePeg(const Peg& peg);

	void AddCard(std::string card);
	const std::vector<std::string>& GetCards()const;

private:
	Color m_color : 1;
	std::string m_name;
	std::vector<Peg*> m_pegs;//nu necesita move semantics
	std::vector<std::string> m_cards;

};