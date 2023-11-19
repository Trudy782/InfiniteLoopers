#pragma once
#include<cstdint>
#include<iostream>
#include<vector>


enum class Color :uint8_t {
	Red,
	Black
};
class Peg {
	public:
		using Position = std::pair<int, int>;
		Peg(Color color,Position position);
		Peg() = default;
		Peg(const Peg& other);
		Peg(Peg&& peg) noexcept;
		Peg& operator=(const Peg& obj);
		~Peg() = default;

		void SetColor(Color color);
		void SetPosition(Position position);
		const Color& GetColor() const;
		const Position& GetPosition() const;
		const std::vector<Peg> GetAdjacencyPegs() const;
		friend std::ostream& operator<<(std::ostream& os, const Peg& peg);

		void swap(Peg& peg);
		void addAdjacentPeg(const Peg& peg);

	private:
		Color m_color : 1;
		Position m_position;
		std::vector<Peg>m_adjacencyPegs;
		
};

