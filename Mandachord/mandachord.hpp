#ifndef MANDACHORD_HPP_INCLUDED
#define MANDACHORD_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <deque>
#include <utility>
#include <string>
#include <fstream>
#include <functional>

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
	using pos_type = float;
	using inst_type = std::string;

	// Size consts
	const static size_type MALSIZE = 3 * 64;
	const static size_type RESSIZE = 5 * 64;
	const static size_type METSIZE = RESSIZE;
	const static size_type MANSIZE = MALSIZE + RESSIZE + METSIZE;
	const pos_type MEASURE = 16 * 60;
	const pos_type BOARD = 4 * 16 * 60;
	pos_type _posmin = 0;
	pos_type _posmax = BOARD;

	// Colors
	sf::Color _gray = { sf::Color(91, 91, 91, 225) };
	sf::Color _blue = { sf::Color(39, 89, 114, 225) };
	sf::Color _pink = { sf::Color(107, 58, 113, 225) };

	// Icon textures
	sf::Texture _malTexture1;
	sf::Texture _malTexture2;
	sf::Texture _malTexture3;
	sf::Texture _resTexture;
	sf::Texture _metTexture;

	// Containers
	std::array<Note, MANSIZE> _mandachord;
	std::array<sf::Sound, 13> _mandachordSounds;
	std::array<sf::SoundBuffer, 13> _mandachordSoundsBuffer;
	std::deque<std::pair<size_type, sf::Sound>> _nowPlaying;
	size_type _npindex;

	// Line
	sf::RectangleShape _line;
	sf::RectangleShape _m1;
	sf::RectangleShape _m2;
	sf::RectangleShape _m3;
	sf::RectangleShape _m4;

	// Note limits
	size_type _malLimit = 26;
	size_type _resLimit = 16;
	size_type _metLimit = 16;

	std::array<size_type, 12> _noteTotal;

	// Private member utilities
	void resetLine();

	// Other, to be renamed
	bool _isPlaying;

public:
	Mandachord();
	~Mandachord() = default;

	void advance(const unsigned int &);
	void checkMouse(sf::RenderWindow &, bool &, sf::Text &);
	void changeMallets(const inst_type &);
	void changeResonator(const inst_type &);
	void changeMetronome(const inst_type &);
	void clear();
	void draw(sf::RenderWindow &, float &, float &);
	void play();
	void saveToFile(std::ofstream &, const inst_type &, const inst_type &, const inst_type &);
	void loadFmFile(std::ifstream &, inst_type &, inst_type &, inst_type &, bool &, const std::array<inst_type, 10> &, sf::Text &);

	// to implement as buttons
	std::function<void()> togglePlaying = [&]() {
		if (_isPlaying) _isPlaying = false;
		else _isPlaying = true;
	};

	bool isMandachordPlaying();

	// TODO: save
	// TODO: load

};

#endif //MANDACHORD_HPP_INCLUDED