#include "Card.h"

Card::Card(std::unordered_map<std::string, std::function<void()>> effects) :m_effects{ effects }
{
}

std::function<void()> Card::getRandomEffect(const std::unordered_map<std::string, std::function<void()>>& m_effects)
{
    if (m_effects.empty()) {
        std::cerr << "Map is empty." << std::endl;
        return []() {}; //returneaza o functie goala
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> distribution(0, m_effects.size() - 1);
    size_t randomIndex = distribution(gen);

    auto it = std::begin(m_effects);
    std::advance(it, randomIndex);

    return it->second;
}

//void Card::addEffects(Player p)
//{
//	m_effects["Remove1opponentPillar"] = p.RemovePeg(const Peg & peg);
//}


