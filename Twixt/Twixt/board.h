#pragma once

#include "peg.h"
#include "link.h"

#include<cstdint>
#include<iostream>
#include<vector>
#include<optional>

class Board
	{
	public:

		enum class State
		{
			None,
			Win,
			Draw
		};
		using Position = std::pair<size_t, size_t>;

		Board(std::vector<std::optional<Peg>>board, size_t size, std::vector<Link> links);
		Board();
		Board(const Board& other) = default;
		Board& operator=(const Board& obj) = default;
		~Board() = default;

		const std::vector<std::optional<Peg>>& GetBoard() const;
		void SetBoard(const std::vector<std::optional<Peg>>& board);
		size_t GetSize() const;
		State GetState() const;
		void SetState(State state);
		void SetSize(size_t size);
		void Reset();

		const std::vector<Link>& GetLink() const;
		std::pair<Position, Position> GetNextActionLink();
		void AddLink(const Link& link);

		const std::optional<Peg>& operator[](const Position& index) const;
		std::optional<Peg>& operator[](const Position& index);

		friend std::istream& operator>>(std::istream& is, Board& board);
		friend std::ostream& operator<<(std::ostream& os, const Board& board);

	private:
		std::vector<std::optional<Peg>>m_board; //nu trebuie semantic moves
		size_t m_size;
		State m_state;
		std::vector<Link> m_links;

};