#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>

class Button {
private:
	using size_type = float;
	
	sf::Text _text;
	sf::RectangleShape _box;
	bool _toggled;

public:
	Button() = delete;
	Button(const sf::Text &, const sf::Color &);
	~Button() = default;

	sf::FloatRect getPos();

	void draw(sf::RenderWindow &, const size_type &, const size_type &);
	void toggle();
	bool isToggled();
};

#endif //BUTTON_HPP_INCLUDED