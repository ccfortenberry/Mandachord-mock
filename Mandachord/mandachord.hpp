#ifndef MANDACHORD_HPP_INCLUDED
#define MANDACHORD_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <deque>
#include <string>

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
	void toggle();
	bool isToggled();
	bool isColliding(const sf::RectangleShape &);
	void draw(sf::RenderWindow &, const size_type &, const size_type &);
};

class Mandachord {
private:
	using size_type = float;
	using inst_type = std::string;
	
	const size_t MALSIZE = 3 * 64;
	const size_t RESSIZE = 5 * 64;
	const size_t METSIZE = RESSIZE;
	const static size_t MANSIZE = 13 * 64;
	const size_t MEASURE = 16;
	const size_t BOARD = 4 * MEASURE;
	
	std::array<Note, MANSIZE> _mandachord;
	std::array<sf::Sound, 13> _mandachordSounds;
	std::deque<sf::Sound> _nowPlaying;
	unsigned int _NPIndex = 0;
	sf::RectangleShape _line;

public:
	Mandachord();
	~Mandachord() = default;

	void advance(const bool &);
	void checkMouse(sf::RenderWindow &);
	void changeMallets(const inst_type &);
	void changeResonator(const inst_type &);
	void changeMetronome(const inst_type &);
	void draw(sf::RenderWindow &, size_type &, size_type &);
	void play();
};

#endif //MANDACHORD_HPP_INCLUDED