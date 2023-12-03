#pragma once

#include "peg.h"
#include "link.h"
#include "board.h"
#include <iostream>
#include <vector>
#include <cstdint>



class Player {
	public :
		Player(Color color, std::string name, std::vector<Peg> pegs);
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
		const std::vector<Peg>& GetPeg() const;

		Board::Position GetNextActionPeg();
		void AddPeg(const Peg& peg);

		



	private:
		Color m_color : 1;
		std::string m_name;
		std::vector<Peg> m_pegs;//nu necesita move semantics

	
};