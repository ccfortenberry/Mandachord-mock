#ifndef MANDACHORD_HPP_INCLUDED
#define MANDACHORD_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <deque>
#include <string>
#include <fstream>

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

	// Colors
	sf::Color _gray = {sf::Color(91, 91, 91, 225)};
	sf::Color _blue = {sf::Color(39, 89, 114, 225)};
	sf::Color _pink = {sf::Color(107, 58, 113, 225)};

	// Icon textures
	sf::Texture _malTexture;
	sf::Texture _resTexture;
	sf::Texture _metTexture;

	// Sounds and sound buffers
	sf::Sound _malRow1Note;
	sf::Sound _malRow2Note;
	sf::Sound _malRow3Note;
	sf::Sound _resRow1Note;
	sf::Sound _resRow2Note;
	sf::Sound _resRow3Note;
	sf::Sound _resRow4Note;
	sf::Sound _resRow5Note;
	sf::Sound _metRow1Note;
	sf::Sound _metRow2Note;
	sf::Sound _metRow3Note;
	sf::Sound _metRow4Note;
	sf::Sound _metRow5Note;
	sf::SoundBuffer _malRow1Buffer;
	sf::SoundBuffer _malRow2Buffer;
	sf::SoundBuffer _malRow3Buffer;
	sf::SoundBuffer _resRow1Buffer;
	sf::SoundBuffer _resRow2Buffer;
	sf::SoundBuffer _resRow3Buffer;
	sf::SoundBuffer _resRow4Buffer;
	sf::SoundBuffer _resRow5Buffer;
	sf::SoundBuffer _metRow1Buffer;
	sf::SoundBuffer _metRow2Buffer;
	sf::SoundBuffer _metRow3Buffer;
	sf::SoundBuffer _metRow4Buffer;
	sf::SoundBuffer _metRow5Buffer;
	
	// Containers
	std::array<Note, MANSIZE> _mandachord;
	std::array<sf::Sound, 13> _mandachordSounds;
	std::deque<sf::Sound> _nowPlaying;
	unsigned int _NPIndex = 0;

	// Line
	sf::RectangleShape _line;

public:
	Mandachord();
	~Mandachord() = default;

	void advance(const bool &, const unsigned int &);
	void checkMouse(sf::RenderWindow &);
	void changeMallets(const inst_type &);
	void changeResonator(const inst_type &);
	void changeMetronome(const inst_type &);
	void draw(sf::RenderWindow &, float &, float &);
	void play();
	void saveToFile(std::ofstream &, const inst_type &, const inst_type &, const inst_type &);
	void loadFmFile(std::ifstream &, inst_type &, inst_type &, inst_type &);
};

#endif //MANDACHORD_HPP_INCLUDED