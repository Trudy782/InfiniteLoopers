#pragma once

#include "peg.h"
#include "link.h"
#include <iostream>
#include <vector>
#include <cstdint>


class Player {
	public :
		Player(Color color, std::string_view name, std::vector<Peg> pegs, std::vector<Link> links);
		Player() = default;
		Player(const Player& other);
		Player& operator=(const Player& obj);
		friend std::istream& operator>>(std::istream& is, Player& player);
		friend std::ostream& operator<<(std::ostream& os, const Player& player);

		void SetColor(Color color);
		void SetName(std::string_view name);
		Color GetColor() const;
		const std::string_view& GetName() const;
		const std::vector<Peg>& GetPeg() const;
		const std::vector<Link>& GetLink() const;

		~Player() = default;

	private:
		Color m_color : 1;
		std::string_view m_name;
		std::vector<Peg> m_pegs;//nu necesita move semantics
		std::vector<Link> m_links;

	
};