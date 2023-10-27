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
		Tabla();
		
	private:
		std::vector<std::optional<Pilon>>m_tabla;
		int m_size;
	};
	Tabla::Tabla(std::vector<std::optional<Pilon>>tabla, int size)
		:m_tabla{tabla}, m_size{size}
	{
	}
	Tabla::Tabla()
	{
	}
}