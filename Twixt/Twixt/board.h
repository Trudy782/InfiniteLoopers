#pragma once

#include "peg.h"
#include "link.h"
#include "player.h"

#include<cstdint>
#include<iostream>
#include<vector>
#include<optional>
#include <unordered_map>
#include <ranges>

struct PairHash {
	size_t operator()(const std::pair<size_t, size_t>& p) const {
		auto hash1 = std::hash<size_t>{}(p.first);
		auto hash2 = std::hash<size_t>{}(p.second);
		return hash1 ^ hash2;
	}
};

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
		
		
		~Board() = default;

		const std::vector<std::optional<Peg>>& GetBoard() const;
		void SetBoard(const std::vector<std::optional<Peg>>& board);
		size_t GetSize() const;
		State GetState() const;
		void SetState(State state);
		void SetSize(size_t size);
		void Reset();
		void UpdateAdjacencyList(const Peg* pegToUpdate, const Peg& removedPeg);
		/*void RemovePeg(size_t destroyedRow, size_t destroyedCol, Player& player);*/

		const std::vector<Link>& GetLink() const;
		const std::vector<Peg>& GetPegs() const;
		std::pair<Position, Position> GetNextActionLink();
		void AddLink(const Link& link);
		void RemoveLink(const Link& link);
		void AddPeg(const Peg& peg);

		const std::optional<Peg>& operator[](const Position& index) const;
		std::optional<Peg>& operator[](const Position& index);
		bool IsPlaceOccupied(const size_t& row, const size_t& col);


		friend std::ostream& operator<<(std::ostream& os, const Board& board);

		void EraseLinkPeg(const size_t& row, const size_t& col);
		void RemovePeg(size_t destroyedRow, size_t destroyedCol);

	private:
		std::vector<std::optional<Peg>>m_board; //nu trebuie semantic moves
		size_t m_size;
		State m_state;
		std::vector<Link> m_links;
		std::unordered_map<Position, std::vector<Link*>, PairHash> m_links_map;
		std::vector<Peg> m_pegs;
};