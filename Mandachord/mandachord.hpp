#ifndef MANDACHORD_HPP_INCLUDED
#define MANDACHORD_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <string>

class Note {
private:
	using size_type = float;

	sf::SoundBuffer _sound;
	sf::RectangleShape _icon;
	sf::Color _color;
	sf::RectangleShape _noteBox;
	bool _toggled;

public:
	Note() = default;
	Note(const sf::SoundBuffer &, const sf::Texture &, const sf::Color &);
	~Note() = default;

	sf::FloatRect getPos();

	void draw(sf::RenderWindow &, const size_type &, const size_type &);
	void toggleNote();
	bool isToggled();
	bool isColliding(const sf::RectangleShape &);
	void play(sf::Sound &);
};

#endif //MANDACHORD_HPP_INCLUDED