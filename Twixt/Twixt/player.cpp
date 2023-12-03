#include "player.h"

Player::Player(Color color, std::string name, std::vector<Peg> pegs)
	:m_color{ color }, m_name{ name }, m_pegs{ std::move(pegs) }
{
}



void Player::SetColor(Color color)
{
	m_color = color;
}

void Player::SetName(std::string name)
{
	m_name = name;
}

Color Player::GetColor() const
{
	return m_color;
}
const std::string& Player::GetName() const
{
	return m_name;
}

const std::vector<Peg>& Player::GetPeg() const
{
	return m_pegs;
}


Board::Position Player::GetNextActionPeg()
{
	std::cout << m_name << ", where do you want to position the peg?\n";  
	std::cout << "row && column: ";

	int row;
	std::cin >> row;
	int column;
	std::cin >> column;

	return { row,column };

}


std::istream& operator>>(std::istream& is, Player& player)
{
	is >> player.m_name;
	return is;
}


std::ostream& operator<<(std::ostream& os, const Player& player)
{
	switch (player.m_color)
	{
	case Color::Red:
	{
		os << player.GetName() << " plays with Red"<< "\n";
		break;
	}
	case Color::Black:
	{
		os << player.GetName() << " plays with Black" << "\n";
		break;
	}
	default:
		break;
	}
	return os;
}

void Player::AddPeg(const Peg& peg)
{
	m_pegs.push_back(peg);
}


