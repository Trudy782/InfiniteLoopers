#pragma once
#include "Board.h";
#include "Peg.h";
class BoardChecker
{
public:
    enum class State : std::uint8_t
    {
        None,
        Win,
        Draw
    };

    static State Check(const Board& board, const Peg& peg);
};

