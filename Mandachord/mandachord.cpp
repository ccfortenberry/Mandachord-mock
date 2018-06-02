#include "mandachord.hpp"
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;


/* ------ Note ------ */
// Ctor from data
Note::Note(const sf::Texture & icon, const sf::Color & color)
	: _icon(sf::Vector2f(50, 50)), _color(color), _noteBox(sf::Vector2f(50, 50)), _toggled(false) {
	_noteBox.setOutlineThickness(2);
	_noteBox.setOutlineColor(color);
	_noteBox.setFillColor(sf::Color::Transparent);
	_icon.setTexture(&icon);
}

// GetPos
sf::FloatRect Note::getPos() {
	return _noteBox.getGlobalBounds();
}

// Toggle
void Note::toggle() {
	if (!_toggled) {
		_toggled = true;
		_noteBox.setFillColor(_color);
	}
	else {
		_toggled = false;
		_noteBox.setFillColor(sf::Color::Transparent);
	}
}

// IsToggled
bool Note::isToggled() {
	return _toggled;
}

// IsColliding
bool Note::isColliding(const sf::RectangleShape & line) {
	return _noteBox.getPosition().x == line.getPosition().x;
}

// Draw
void Note::draw(sf::RenderWindow & window, const size_type & posX, const size_type & posY) {
	_noteBox.setPosition(posX, posY);
	_icon.setPosition(posX, posY);
	window.draw(_noteBox);
	window.draw(_icon);
}

/* ------ Mandachord ------ */
// Helper functions
void loadIcon(sf::Texture & icon, const string & path) {
	if (!icon.loadFromFile(path)) {
		cout << "Unable to load " << path << endl;
		system("pause");
		throw EXIT_FAILURE;
	}
	//cout << "Icon loaded" << endl;
}

void loadSound(sf::Sound & sound, sf::SoundBuffer & buffer, const string & path) {
	if (!buffer.loadFromFile(path)) {
		cout << "Unable to load " << path << endl;
		system("pause");
		throw EXIT_FAILURE;
	}
	else sound.setBuffer(buffer);
	//cout << "Sound loaded" << endl;
}

// Default Ctor
Mandachord::Mandachord() {
	// ---------- Mallets section ----------
	// Color
	static sf::Color gray(91, 91, 91, 225);

	// Icon
	static sf::Texture malTexture;
	loadIcon(malTexture, "icons/mallets_icon.png");

	// Sound for first row
	static sf::Sound malRow1Note;
	static sf::SoundBuffer malRow1Buffer;
	loadSound(malRow1Note, malRow1Buffer, "instruments/adau/adau_mal_1.wav");

	// Sound for second row
	static sf::Sound malRow2Note;
	static sf::SoundBuffer malRow2Buffer;
	loadSound(malRow2Note, malRow2Buffer, "instruments/adau/adau_mal_2.wav");

	// Sound for third row
	static sf::Sound malRow3Note;
	static sf::SoundBuffer malRow3Buffer;
	loadSound(malRow3Note, malRow3Buffer, "instruments/adau/adau_mal_3.wav");

	// Mallet notes
	Note malNote1(malTexture, gray);
	Note malNote2(malTexture, gray);
	Note malNote3(malTexture, gray);

	// ---------- Resonator section ----------
	// Color
	static sf::Color blue(39, 89, 114, 225);

	// Icon
	static sf::Texture resTexture;
	loadIcon(resTexture, "icons/resonator_icon.png");

	// Sound for first row
	static sf::Sound resRow1Note;
	static sf::SoundBuffer resRow1Buffer;
	loadSound(resRow1Note, resRow1Buffer, "instruments/adau/adau_res_1.wav");

	// Sound for second row
	static sf::Sound resRow2Note;
	static sf::SoundBuffer resRow2Buffer;
	loadSound(resRow2Note, resRow2Buffer, "instruments/adau/adau_res_2.wav");

	// Sound for third row
	static sf::Sound resRow3Note;
	static sf::SoundBuffer resRow3Buffer;
	loadSound(resRow3Note, resRow3Buffer, "instruments/adau/adau_res_3.wav");

	// Sound for fourth row
	static sf::Sound resRow4Note;
	static sf::SoundBuffer resRow4Buffer;
	loadSound(resRow4Note, resRow4Buffer, "instruments/adau/adau_res_4.wav");

	// Sound for fifth row
	static sf::Sound resRow5Note;
	static sf::SoundBuffer resRow5Buffer;
	loadSound(resRow5Note, resRow5Buffer, "instruments/adau/adau_res_5.wav");

	// Resonator notes
	Note resNote1(resTexture, blue);
	Note resNote2(resTexture, blue);
	Note resNote3(resTexture, blue);
	Note resNote4(resTexture, blue);
	Note resNote5(resTexture, blue);

	// ---------- Metronome section ----------
	// Color
	static sf::Color pink(107, 58, 113, 225);

	// Icon
	static sf::Texture metTexture;
	loadIcon(metTexture, "icons/metronome_icon.png");

	// Sound for first row
	static sf::Sound metRow1Note;
	static sf::SoundBuffer metRow1Buffer;
	loadSound(metRow1Note, metRow1Buffer, "instruments/adau/adau_met_1.wav");

	// Sound for second row
	static sf::Sound metRow2Note;
	static sf::SoundBuffer metRow2Buffer;
	loadSound(metRow2Note, metRow2Buffer, "instruments/adau/adau_met_2.wav");

	// Sound for third row
	static sf::Sound metRow3Note;
	static sf::SoundBuffer metRow3Buffer;
	loadSound(metRow3Note, metRow3Buffer, "instruments/adau/adau_met_3.wav");

	// Sound for fourth row
	static sf::Sound metRow4Note;
	static sf::SoundBuffer metRow4Buffer;
	loadSound(metRow4Note, metRow4Buffer, "instruments/adau/adau_met_4.wav");

	// Sound for fifth row
	static sf::Sound metRow5Note;
	static sf::SoundBuffer metRow5Buffer;
	loadSound(metRow5Note, metRow5Buffer, "instruments/adau/adau_met_5.wav");

	// Metronome notes
	Note metNote1(metTexture, pink);
	Note metNote2(metTexture, pink);
	Note metNote3(metTexture, pink);
	Note metNote4(metTexture, pink);
	Note metNote5(metTexture, pink);

	// Setup the instrument
	for (unsigned int i = 0; i < MANSIZE; i++) {
		if (i < MALSIZE) {
			if (i < 64) _mandachord[i] = malNote1;
			else if (i < 2 * 64) _mandachord[i] = malNote2;
			else _mandachord[i] = malNote3;
		}
		else if (i < MALSIZE + RESSIZE) {
			if (i < 4 * 64) _mandachord[i] = resNote1;
			else if (i < 5 * 64) _mandachord[i] = resNote2;
			else if (i < 6 * 64) _mandachord[i] = resNote3;
			else if (i < 7 * 64) _mandachord[i] = resNote4;
			else _mandachord[i] = resNote5;
		}
		else {
			if (i < 9 * 64) _mandachord[i] = metNote1;
			else if (i < 10 * 64) _mandachord[i] = metNote2;
			else if (i < 11 * 64) _mandachord[i] = metNote3;
			else if (i < 12 * 64) _mandachord[i] = metNote4;
			else _mandachord[i] = metNote5;
		}
	}

	// Setup the sounds
	_mandachordSounds = { malRow1Note,
						malRow2Note,
						malRow3Note,
						resRow1Note,
						resRow2Note,
						resRow3Note,
						resRow4Note,
						resRow5Note,
						metRow1Note,
						metRow2Note,
						metRow3Note,
						metRow4Note,
						metRow5Note };

	// Setup the line that passes over the notes
	_line = { sf::RectangleShape(sf::Vector2f(780, 2)) };
	_line.rotate(90);
	_line.setPosition(10, 35);
}

// Advance
void Mandachord::advance(const bool & toggled) {
	if (toggled) {
		if (_line.getPosition().x < MEASURE * 60)
			_line.move(sf::Vector2f(5, 0));
		else
			_line.setPosition(10, 35);
	}
}

// Check mouse for clicking on the mandachord
void Mandachord::checkMouse(sf::RenderWindow & window) {
	for (size_t i = 0; i < MANSIZE; i++) {
		// Chugga chugga here comes the trainwreck of an if statement :^)
		if (_mandachord[i].getPos().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
			_mandachord[i].toggle();
			cout << "Toggled note: " << i << endl;
		}
	}
}

void Mandachord::changeMallets(const inst_type & instrument) {
	// Sound for first row
	static sf::Sound malRow1Note;
	static sf::SoundBuffer malRow1Buffer;
	loadSound(malRow1Note, malRow1Buffer, "instruments/" + instrument + "/" + instrument + "_mal_1.wav");
	_mandachordSounds[0] = malRow1Note;

	// Sound for second row
	static sf::Sound malRow2Note;
	static sf::SoundBuffer malRow2Buffer;
	loadSound(malRow2Note, malRow2Buffer, "instruments/" + instrument + "/" + instrument + "_mal_2.wav");
	_mandachordSounds[1] = malRow2Note;

	// Sound for third row
	static sf::Sound malRow3Note;
	static sf::SoundBuffer malRow3Buffer;
	loadSound(malRow3Note, malRow3Buffer, "instruments/" + instrument + "/" + instrument + "_mal_3.wav");
	_mandachordSounds[2] = malRow3Note;
}

void Mandachord::changeResonator(const inst_type & instrument) {
	// Sound for first row
	static sf::Sound resRow1Note;
	static sf::SoundBuffer resRow1Buffer;
	loadSound(resRow1Note, resRow1Buffer, "instruments/" + instrument + "/" + instrument + "_res_1.wav");
	_mandachordSounds[3] = resRow1Note;

	// Sound for second row
	static sf::Sound resRow2Note;
	static sf::SoundBuffer resRow2Buffer;
	loadSound(resRow2Note, resRow2Buffer, "instruments/" + instrument + "/" + instrument + "_res_2.wav");
	_mandachordSounds[4] = resRow2Note;

	// Sound for third row
	static sf::Sound resRow3Note;
	static sf::SoundBuffer resRow3Buffer;
	loadSound(resRow3Note, resRow3Buffer, "instruments/" + instrument + "/" + instrument + "_res_3.wav");
	_mandachordSounds[5] = resRow3Note;

	// Sound for fourth row
	static sf::Sound resRow4Note;
	static sf::SoundBuffer resRow4Buffer;
	loadSound(resRow4Note, resRow4Buffer, "instruments/" + instrument + "/" + instrument + "_res_4.wav");
	_mandachordSounds[6] = resRow4Note;

	// Sound for fifth row
	static sf::Sound resRow5Note;
	static sf::SoundBuffer resRow5Buffer;
	loadSound(resRow5Note, resRow5Buffer, "instruments/" + instrument + "/" + instrument + "_res_5.wav");
	_mandachordSounds[7] = resRow5Note;
}

void Mandachord::changeMetronome(const inst_type & instrument) {
	// Sound for first row
	static sf::Sound metRow1Note;
	static sf::SoundBuffer metRow1Buffer;
	loadSound(metRow1Note, metRow1Buffer, "instruments/" + instrument + "/" + instrument + "_met_1.wav");
	_mandachordSounds[8] = metRow1Note;

	// Sound for second row
	static sf::Sound metRow2Note;
	static sf::SoundBuffer metRow2Buffer;
	loadSound(metRow2Note, metRow2Buffer, "instruments/" + instrument + "/" + instrument + "_met_2.wav");
	_mandachordSounds[9] = metRow2Note;

	// Sound for third row
	static sf::Sound metRow3Note;
	static sf::SoundBuffer metRow3Buffer;
	loadSound(metRow3Note, metRow3Buffer, "instruments/" + instrument + "/" + instrument + "_met_3.wav");
	_mandachordSounds[10] = metRow3Note;

	// Sound for fourth row
	static sf::Sound metRow4Note;
	static sf::SoundBuffer metRow4Buffer;
	loadSound(metRow4Note, metRow4Buffer, "instruments/" + instrument + "/" + instrument + "_met_4.wav");
	_mandachordSounds[11] = metRow4Note;

	// Sound for fifth row
	static sf::Sound metRow5Note;
	static sf::SoundBuffer metRow5Buffer;
	loadSound(metRow5Note, metRow5Buffer, "instruments/" + instrument + "/" + instrument + "_met_5.wav");
	_mandachordSounds[12] = metRow5Note;
}

// Draw
void Mandachord::draw(sf::RenderWindow & window, size_type & posX, size_type & posY) {
	for (size_t i = 0; i < MANSIZE; i++) {
		_mandachord[i].draw(window, posX, posY);
		if ((i + 1) % 64 != 0)
			posX += 60;
		else {
			posX = 10;
			posY += 60;
		}
	}
	window.draw(_line);
}

// Play
void Mandachord::play() {
	// This makes me physically sick but I'll clean it up later...
	for (unsigned int i = 0; i < MANSIZE; i++) {
		if (_mandachord[i].isToggled() && _mandachord[i].isColliding(_line)) {
			cout << "Collision!" << endl;
			if (i < 64) {
				_nowPlaying.emplace_back(_mandachordSounds[0]);
				_NPIndex++;
				_nowPlaying[_NPIndex - 1].play();
			}
			else if (i < 2 * 64) {
				_nowPlaying.emplace_back(_mandachordSounds[1]);
				_NPIndex++;
				_nowPlaying[_NPIndex - 1].play();
			}
			else if (i < 3 * 64) {
				_nowPlaying.emplace_back(_mandachordSounds[2]);
				_NPIndex++;
				_nowPlaying[_NPIndex - 1].play();
			}
			else if (i < 4 * 64) {
				_nowPlaying.emplace_back(_mandachordSounds[3]);
				_NPIndex++;
				_nowPlaying[_NPIndex - 1].play();
			}
			else if (i < 5 * 64) {
				_nowPlaying.emplace_back(_mandachordSounds[4]);
				_NPIndex++;
				_nowPlaying[_NPIndex - 1].play();
			}
			else if (i < 6 * 64) {
				_nowPlaying.emplace_back(_mandachordSounds[5]);
				_NPIndex++;
				_nowPlaying[_NPIndex - 1].play();
			}
			else if (i < 7 * 64) {
				_nowPlaying.emplace_back(_mandachordSounds[6]);
				_NPIndex++;
				_nowPlaying[_NPIndex - 1].play();
			}
			else if (i < 8 * 64) {
				_nowPlaying.emplace_back(_mandachordSounds[7]);
				_NPIndex++;
				_nowPlaying[_NPIndex - 1].play();
			}
			else if (i < 9 * 64) {
				_nowPlaying.emplace_back(_mandachordSounds[8]);
				_NPIndex++;
				_nowPlaying[_NPIndex - 1].play();
			}
			else if (i < 10 * 64) {
				_nowPlaying.emplace_back(_mandachordSounds[9]);
				_NPIndex++;
				_nowPlaying[_NPIndex - 1].play();
			}
			else if (i < 11 * 64) {
				_nowPlaying.emplace_back(_mandachordSounds[10]);
				_NPIndex++;
				_nowPlaying[_NPIndex - 1].play();
			}
			else if (i < 12 * 64) {
				_nowPlaying.emplace_back(_mandachordSounds[11]);
				_NPIndex++;
				_nowPlaying[_NPIndex - 1].play();
			}
			else {
				_nowPlaying.emplace_back(_mandachordSounds[12]);
				_NPIndex++;
				_nowPlaying[_NPIndex - 1].play();
			}
		}
	}

	if (!_nowPlaying.empty() && _nowPlaying.front().getStatus() == sf::Sound::Status::Stopped) {
		_nowPlaying.pop_front();
		_NPIndex--;
	}
}