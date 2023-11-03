#include "tabla.h"

Tabla::Tabla(std::vector<std::optional<pilon>>tabla, int size)
	:m_tabla{ tabla }, m_size{ size }
{
}

Tabla::Tabla(const Tabla& other)
	: m_tabla{ other.m_tabla }, m_size{ other.m_size }
{
}