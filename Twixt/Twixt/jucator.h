#pragma once

#include "pilon.h"
#include "pod.h"
#include <iostream>
#include <vector>
#include <cstdint>


class Jucator {
	public :
		enum class Color : uint8_t {
			Rosu, 
			Negru
		};
		Jucator(Color color, std::string_view nume, std::vector<pilon> piloni, std::vector<Pod> poduri);
		Jucator() = default;
		Jucator(const Jucator& other);
		Jucator& operator=(const Jucator& obj);
		friend std::istream& operator>>(std::istream& is, Jucator& jucator);
		void setColor(Color color);
		void setNume(std::string_view nume);
		Color getColor() const;
		const std::string_view& getNume() const;

		~Jucator() = default;

	private:
		Color m_color : 1;
		std::string_view m_nume;
		std::vector<pilon> m_piloni;//nu necesita move semantics
		std::vector<Pod> m_poduri;

	
};