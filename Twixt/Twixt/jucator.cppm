module;
#include <cstdint>;


export module jucator;
export import pilon;
export import pod;
import <iostream>;
import <vector>;

namespace twixt {
	export class Jucator {
	public :
		enum class Color : uint8_t {
			Rosu, 
			Negru
		};
		

	private:
		Color m_color : 1;
		std::string_view m_nume;
		std::vector<Pilon> m_piloni;
		std::vector<Pod> m_poduri;
	};
}