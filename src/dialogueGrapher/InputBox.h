#ifndef INPUTBOX_H
#define INPUTBOX_H
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
class InputBox : public sf::RectangleShape
{
	public:
		InputBox(){}
		InputBox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font);
		~InputBox();
		void addCharacter(const char& character);
		void addCharacter(const std::string& character);
		void removeCharacter();

		void render(sf::RenderWindow& window);
		bool checkClicked(const sf::Vector2f& mousePos);
		void setSelected(bool val); 
		inline bool isSelected() { return selected; }
		inline void setActive(bool active) { this->active = active; }
		inline std::string getString() { return text.getString(); }
		inline void clear() { text.setString("");}

		// Overriding sf::RectangleShape's move functions
		void move(const sf::Vector2f& offset);
		void move(float offsetX, float offsetY);
	private:
		sf::Text text;
		bool selected;
		bool active;
};
#endif//INPUTBOX_H
