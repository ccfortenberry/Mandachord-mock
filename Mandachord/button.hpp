#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>

class Button {
private:
	using size_type = float;
	using text_type = std::string;
	
	sf::Text _text;
	sf::RectangleShape _box;
	bool _toggled;

public:
	Button() = delete;
	Button(const text_type &, const sf::Font &, const unsigned int &, const sf::Color &);
	~Button() = default;

	sf::FloatRect getPos();
	void toggle();
	bool isToggled();
	void checkMouse(sf::RenderWindow &);
	void draw(sf::RenderWindow &, const size_type &, const size_type &);
};

#endif //BUTTON_HPP_INCLUDED