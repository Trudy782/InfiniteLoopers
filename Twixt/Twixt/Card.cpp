#include "Card.h"

Card::Card(std::unordered_map<std::string, std::function<void()>> effects) :m_effects{ effects }
{
}


