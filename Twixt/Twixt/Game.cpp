#include "Game.h"

Game::Game()
{
	std::string redPlayerName;
    std::string blackPlayerName;

    std::cout << "Enter the name of the Red Player: ";
    std::cin >> redPlayerName;

    std::cout << "Enter the name of the Black Player: ";
    std::cin >> blackPlayerName;

    m_redPlayer = Player{ Color::Red, redPlayerName, {}, {} };
    m_blackPlayer = Player{Color::Black, blackPlayerName, {}, {}};

    std::cin >> m_board;
    m_isRedTurn = true;
}
