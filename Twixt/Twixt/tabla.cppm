module;

#include<cstdint>

export module tabla;
export import pilon;
import<iostream>;
import<vector>;
import<optional>;

namespace twixt
{
	export class Tabla
	{
	public:
		Tabla(std::vector<std::optional<Pilon>>tabla, int size);
		Tabla() = default;
		Tabla(const Tabla& other);
		~Tabla() = default;
		
	private:
		std::vector<std::optional<Pilon>>m_tabla; //nu trebuie semantic moves
		int m_size;
	};
	Tabla::Tabla(std::vector<std::optional<Pilon>>tabla, int size)
		:m_tabla{tabla}, m_size{size}
	{
	}
	
	Tabla::Tabla(const Tabla& other)
		: m_tabla{other.m_tabla}, m_size{other.m_size}
	{
	}
}