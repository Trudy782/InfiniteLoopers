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
	private:
		std::vector<std::optional<Pilon>, 576>m_tabla;
		int m_size;
	};
}