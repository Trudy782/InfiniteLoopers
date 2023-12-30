#include "player.h"

Player::Player(Color color, std::string name)
	:m_color{ color }, m_name{ name }, m_nr_pegs{ 0 }
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

void Player::SetNrPegs(int pegs)
{
	m_nr_pegs = pegs;
}

int Player::GetNrPegs() const
{
	return m_nr_pegs;
}



Player::Position Player::GetNextActionPeg()
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
		os << player.GetName() << " plays with Red" << "\n";
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


void Player::AddCard(std::string card)
{
	m_cards.push_back(card);
}

const std::vector<std::string>& Player::GetCards() const
{
	return m_cards;
}

void Player::IncrementNumber()
{
	m_nr_pegs++;
}



void Player::EraseCard()
{
	m_cards.erase(m_cards.begin());
}


