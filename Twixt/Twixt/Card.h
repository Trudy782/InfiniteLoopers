#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include<functional>
#include<random>
#include "player.h"


class Card
{
public:
	Card(std::unordered_map<std::string, std::function<void()>> effects);
	Card() = default;
	~Card() = default;
	std::function<void()> getRandomEffect(const std::unordered_map<std::string, std::function<void()>>& m_effects);
private:
	std::unordered_map<std::string, std::function<void()>> m_effects;
	//void addEffects(Player p);
};

