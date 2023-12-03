#pragma once
#include<cstdint>
#include<iostream>
#include<vector>
#include <stack>


enum class Color :uint8_t {
    Red,
    Black
};
class Peg {
public:
    using Position = std::pair<size_t, size_t>;
    Peg(Color color, Position position);
    Peg() = default;
    
    bool operator==(const Peg& obj);

    void SetColor(Color color);
    void SetPosition(Position position);
    const Color& GetColor() const;
    const Position& GetPosition() const;
    const std::vector<Peg*>& GetAdjacencyPegs() const;

    void swap(Peg& peg);
    void AddAdjacentPeg(Peg* peg);

    std::vector<Peg> DFS();

private:
    Color m_color : 1;
    Position m_position;
    std::vector<Peg*>m_adjacencyPegs;

};
std::ostream& operator<<(std::ostream& os, const Peg& peg);