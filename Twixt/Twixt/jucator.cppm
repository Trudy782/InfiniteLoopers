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
		Jucator& operator=(const Jucator& obj);
		friend std::istream& operator>>(std::istream& is, Jucator& jucator);
		void setColor(Color color);
		void setNume(std::string_view nume);
		Color getColor() const;
		std::string_view getNume() const;

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
	Jucator& Jucator::operator=(const Jucator& obj)
	{
			if (this != &obj) { 
				m_color = obj.m_color;
				m_nume = obj.m_nume;
				m_piloni = obj.m_piloni;
				m_poduri = obj.m_poduri;
			}
			return *this;
	}
	void Jucator::setColor(Color color)
	{
		m_color = color;
	}
	void Jucator::setNume(std::string_view nume)
	{
		m_nume = nume;
	}
	Jucator::Color Jucator::getColor() const
	{
		return m_color;
	}
	std::string_view Jucator::getNume() const
	{
		return m_nume;
	}
	Jucator::~Jucator()
	{
		
	}
	std::istream& operator>>(std::istream& is, Jucator& jucator)
	{
		std::string nume;
		is >> nume;
		jucator.m_nume = nume;
		return is;
	}
}