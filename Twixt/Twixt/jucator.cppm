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
		Jucator(Color color, std::string_view nume, std::vector<Pilon> piloni, std::vector<Pod> poduri);
		Jucator();
		Jucator(const Jucator& other);
		
		~Jucator();

	private:
		Color m_color : 1;
		std::string_view m_nume;
		std::vector<Pilon> m_piloni;
		std::vector<Pod> m_poduri;

	};
	Jucator::Jucator(Color color, std::string_view nume, std::vector<Pilon> piloni, std::vector<Pod> poduri)
		:m_color{ color }, m_nume{ nume }, m_piloni{ piloni }, m_poduri{ poduri }
	{
	}
	Jucator::Jucator()
	{
	}
	Jucator::Jucator(const Jucator& other)
		:m_color{ other.m_color }, m_nume{ other.m_nume }, m_piloni{ other.m_piloni }, m_poduri{ other.m_poduri }
	{
	}
	Jucator::~Jucator()
	{
		
	}
}