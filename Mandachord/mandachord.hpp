#ifndef MANDACHORD_HPP_INCLUDED
#define MANDACHORD_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>

class Note {
private:
	using size_type = float;
	using data_type = std::string;

	data_type _sound;
	sf::RectangleShape _icon;
	sf::Color _color;
	sf::RectangleShape _noteBox;
	bool _toggled;

public:
	Note() = default;
	Note(const data_type &, const sf::Texture &, const sf::Color &);
	~Note() = default;

	data_type getSound();
	sf::Texture getIcon();
	sf::FloatRect getPos();

	void draw(sf::RenderWindow &, const size_type &, const size_type &);
	void toggleNote();
	bool isToggled();
	bool isColliding(const sf::RectangleShape &);
	void play();
};

#endif //MANDACHORD_HPP_INCLUDED