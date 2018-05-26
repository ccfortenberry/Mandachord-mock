#ifndef MANDACHORD_HPP_INCLUDED
#define MANDACHORD_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>

class Note {
private:
	using size_type = size_t;
	using data_type = std::string;

	data_type _sound;
	data_type _icon;
	sf::Color _color;
	sf::RectangleShape _noteBox;
	bool _toggled;

public:
	Note() = default;
	Note(const data_type &, const data_type &, const sf::Color &);
	~Note() = default;

	data_type getSound();
	data_type getIcon();
	sf::Color getColor();
	sf::FloatRect getPos();

	void setSound(const data_type &);
	void setIcon(const data_type &);
	void setColor(const sf::Color &);
	//void setPos(const sf::Vector2f &);

	void draw(sf::RenderWindow &, const int &, const int &);
	void toggleNote();
	bool isToggled();
	bool isColliding(const sf::RectangleShape &);
	void play();
};

#endif //MANDACHORD_HPP_INCLUDED