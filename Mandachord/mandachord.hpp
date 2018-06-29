#ifndef MANDACHORD_HPP_INCLUDED
#define MANDACHORD_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <deque>
#include <utility>
#include <string>
#include <fstream>

class Note {
private:
	using size_type = float;

	sf::RectangleShape _icon;
	sf::Color _color;
	sf::RectangleShape _noteBox;
	bool _toggled;
	bool _playable;

public:
	Note() = default;
	Note(const sf::Texture &, const sf::Color &);
	~Note() = default;

	sf::FloatRect getPos();
	void toggle();
	bool isToggled();
	void togglePlayable();
	bool isPlayable();
	bool isColliding(const sf::RectangleShape &);
	void draw(sf::RenderWindow &, const size_type &, const size_type &);
};

class Mandachord {
private:
	// Types
	using size_type = unsigned int;
	using inst_type = std::string;
	
	// Size consts
	const static size_type MALSIZE = 3 * 64;
	const static size_type RESSIZE = 5 * 64;
	const static size_type METSIZE = RESSIZE;
	const static size_type MANSIZE = MALSIZE + RESSIZE + METSIZE;
	const size_type MEASURE = 16 * 60;
	const size_type BOARD = 4 * 16 * 60;
	size_type _posmin = 0;
	size_type _posmax = BOARD;

	// Colors
	sf::Color _gray = {sf::Color(91, 91, 91, 225)};
	sf::Color _blue = {sf::Color(39, 89, 114, 225)};
	sf::Color _pink = {sf::Color(107, 58, 113, 225)};

	// Icon textures
	sf::Texture _malTexture;
	sf::Texture _resTexture;
	sf::Texture _metTexture;
	
	// Containers
	std::array<Note, MANSIZE> _mandachord;
	std::array<sf::Sound, 13> _mandachordSounds;
	std::array<sf::SoundBuffer, 13> _mandachordSoundsBuffer;
	std::deque<std::pair<unsigned int ,sf::Sound>> _nowPlaying;
	unsigned int _npindex;

	// Line
	sf::RectangleShape _line;
	sf::RectangleShape _m1;
	sf::RectangleShape _m2;
	sf::RectangleShape _m3;
	sf::RectangleShape _m4;

	// Note limits: TODO at some point
	size_type _malLimit = 26;
	size_type _resLimit = 16;
	size_type _metLimit = 16;

	std::array<size_type, 12> _noteTotal;

public:
	Mandachord();
	~Mandachord() = default;

	void advance(const bool &, const unsigned int &);
	void checkMouse(sf::RenderWindow &, bool &, sf::Text &);
	void changeMallets(const inst_type &);
	void changeResonator(const inst_type &);
	void changeMetronome(const inst_type &);
	void clear();
	void draw(sf::RenderWindow &, float &, float &);
	void play();
	void saveToFile(std::ofstream &, const inst_type &, const inst_type &, const inst_type &);
	void loadFmFile(std::ifstream &, inst_type &, inst_type &, inst_type &, bool &, const std::array<inst_type, 10> &, sf::Text &);
};

#endif //MANDACHORD_HPP_INCLUDED