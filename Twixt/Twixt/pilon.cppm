module;

#include<cstdint>

export module pilon;
import<iostream>;

namespace twixt {
	export class Pilon {
	public:
		enum class Color :uint8_t {
			Rosu,
			Negru
		};
	private:
		Color m_color : 1;
		std::pair<int, int>pozitie;
	};
}