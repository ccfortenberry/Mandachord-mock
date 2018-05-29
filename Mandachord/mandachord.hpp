#ifndef MANDACHORD_HPP_INCLUDED
#define MANDACHORD_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <string>
#include <array>

class Note {
private:
	using size_type = float;

	sf::RectangleShape _icon;
	sf::Color _color;
	sf::RectangleShape _noteBox;
	bool _toggled;

public:
	Note() = default;
	Note(const sf::Texture &, const sf::Color &);
	~Note() = default;

	sf::FloatRect getPos();

	void draw(sf::RenderWindow &, const size_type &, const size_type &);
	void toggle();
	bool isToggled();
	bool isColliding(const sf::RectangleShape &);
};

#endif //MANDACHORD_HPP_INCLUDED