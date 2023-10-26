module;

#include<cstdint>

export module pilon;

export import pod;
import<iostream>;
import<vector>;

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
		std::vector<Pod>poduri;
	};
}