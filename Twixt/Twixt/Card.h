#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include<functional>


class Card
{
public:
	Card(std::unordered_map<std::string, std::function<void()>> effects);
	Card() = default;
	~Card() = default;
private:
	std::unordered_map<std::string, std::function<void()>> m_effects;
};

