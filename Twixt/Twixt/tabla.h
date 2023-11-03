#pragma once

#include "pilon.h"

#include<cstdint>
#include<iostream>
#include<vector>
#include<optional>

class Tabla
	{
	public:
		Tabla(std::vector<std::optional<pilon>>tabla, int size);
		Tabla() = default;
		Tabla(const Tabla& other);
		~Tabla() = default;
		
	private:
		std::vector<std::optional<pilon>>m_tabla; //nu trebuie semantic moves
		int m_size;
	
};