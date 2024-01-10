#include "BoardChecker.h"

BoardChecker::State BoardChecker::Check(const Board& board, const Peg& peg)
{
    if (peg.GetColor() == Color::Black)
    {
        if (peg.GetPosition().second == 0)
        {
            std::vector<Peg> visited = peg.DFS();
            for (int i = 0; i < visited.size(); i++)
                if (visited[i].GetPosition().second == board.GetSize() - 1)
                {
                    return State::Win;
                }
        }
        if (peg.GetPosition().second == board.GetSize() - 1)
        {
            std::vector<Peg> visited = peg.DFS();
            for (int i = 0; i < visited.size(); i++)
                if (visited[i].GetPosition().second == 0)
                {
                    return State::Win;
                }
        }
    }
    else
    {
        if (peg.GetPosition().first == 0)
        {
            std::vector<Peg> visited = peg.DFS();
            for (int i = 0; i < visited.size(); i++)
                if (visited[i].GetPosition().first == board.GetSize() - 1)
                {
                    return State::Win;
                }
        }
        if (peg.GetPosition().first == board.GetSize() - 1)
        {
            std::vector<Peg> visited = peg.DFS();
            for (int i = 0; i < visited.size(); i++)
                if (visited[i].GetPosition().first == 0)
                {
                    return State::Win;
                }
        }
    }
    return State::None;
}
