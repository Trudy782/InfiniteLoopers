#pragma once

#include "Peg.h"
#include "Link.h"
#include "Player.h"
#include "Buldozerist.h"

#include<cstdint>
#include<iostream>
#include<vector>
#include<optional>
#include <unordered_map>
#include <ranges>


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
	void CreateFilteredBoard();
	bool Occupied(const size_t& row, const size_t& col);

	Position RandomEmptyPosition();
	Board::Position RandomPeg();
	void MoveBuldozer();

	const std::optional<Peg>& operator[](const Position& index) const;
	std::optional<Peg>& operator[](const Position& index);
	bool IsPlaceOccupied(const size_t& row, const size_t& col);


	friend std::ostream& operator<<(std::ostream& os, const Board& board);

	void EraseLinkPeg(const size_t& row, const size_t& col);
	void RemovePeg(size_t destroyedRow, size_t destroyedCol);
	void RemoveLink(size_t destroyedRow1, size_t destroyedCol1, size_t destroyedRow2, size_t destroyedCol2);

private:
	std::vector<std::optional<Peg>>m_board; //nu trebuie semantic moves
	size_t m_size;
	State m_state;
	std::vector<Link> m_links;
	std::vector<Peg> m_pegs;
	Buldozerist m_buldozerist;
};