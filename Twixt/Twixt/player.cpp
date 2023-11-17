#include "player.h"

Player::Player(Color color, std::string name, std::vector<Peg> pegs, std::vector<Link> links)
	:m_color{ color }, m_name{ name }, m_pegs{ pegs }, m_links{ links }
{
}
Player::Player(const Player& other)
	:m_color{ other.m_color }, m_name{ other.m_name }, m_pegs{ other.m_pegs }, m_links{ other.m_links }
{
}
Player& Player::operator=(const Player& obj)
{
	if (this != &obj) {
		m_color = obj.m_color;
		m_name = obj.m_name;
		m_pegs = obj.m_pegs;
		m_links = obj.m_links;
	}
	return *this;
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
const std::vector<Link>& Player::GetLink() const
{
	return m_links;
}
Board::Position Player::GetNextAction()
{
	std::cout << m_name << ", unde vrei sa pozitionezi pilonul?\n";
	std::cout << "linie si coloana: ";

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
