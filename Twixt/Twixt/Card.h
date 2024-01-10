#pragma once
#include<iostream>
#include<string>
#include<random>
#include<vector>



class Card
{
public:
	Card(std::vector<std::string> effects);
	Card() = default;
	~Card() = default;
	std::string getRandomEffect(const std::vector<std::string>& m_effects);
	const std::vector<std::string>& GetEffects() const;
private:
	std::vector<std::string> m_effects;
	void addEffects();
};

