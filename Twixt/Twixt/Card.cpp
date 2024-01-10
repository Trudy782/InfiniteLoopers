#include "Card.h"

Card::Card(std::vector<std::string> effects) :m_effects{ effects }
{
}

std::string Card::getRandomEffect(const std::vector<std::string>& m_effects)
{
    if (m_effects.empty()) {
        std::cerr << "Don't exists any card" << std::endl;
        return ""; //returneaza o functie goala
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> distribution(0, m_effects.size() - 1);
    int randomIndex = distribution(gen);

    return m_effects[randomIndex];
}

const std::vector<std::string>& Card::GetEffects() const
{
    return m_effects;
}

void Card::addEffects()
{
    m_effects.push_back("Get2Cards");
    m_effects.push_back("Loses2Cards");
    m_effects.push_back("PlayExtraTurn");
    m_effects.push_back("Remove1OpponentPillar");
    m_effects.push_back("Remove1OpponentLink");
    m_effects.push_back("Place2Pillars");
    m_effects.push_back("Place2Links");
    m_effects.push_back("Place2Links");
    m_effects.push_back("Place2Links");
    m_effects.push_back("MoveBulldozer");
}




