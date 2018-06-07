#include "mandachord.hpp"
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
using std::getline;


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
}

void loadSound(sf::Sound & sound, sf::SoundBuffer & buffer, const string & path) {
	if (!buffer.loadFromFile(path)) {
		cout << "Unable to load " << path << endl;
		system("pause");
		throw EXIT_FAILURE;
	}
	else sound.setBuffer(buffer);
}

// Default Ctor
Mandachord::Mandachord() {
	// ---------- Mallets section ----------
	// Icon
	loadIcon(_malTexture, "icons/mallets_icon.png");

	// Sound for first row
	loadSound(_malRow1Note, _malRow1Buffer, "instruments/adau/adau_mal_1.wav");

	// Sound for second row
	loadSound(_malRow2Note, _malRow2Buffer, "instruments/adau/adau_mal_2.wav");

	// Sound for third row
	loadSound(_malRow3Note, _malRow3Buffer, "instruments/adau/adau_mal_3.wav");

	// Mallet notes
	Note malNote1(_malTexture, _gray);
	Note malNote2(_malTexture, _gray);
	Note malNote3(_malTexture, _gray);

	// ---------- Resonator section ----------
	// Icon
	loadIcon(_resTexture, "icons/resonator_icon.png");

	// Sound for first row
	loadSound(_resRow1Note, _resRow1Buffer, "instruments/adau/adau_res_1.wav");

	// Sound for second row
	loadSound(_resRow2Note, _resRow2Buffer, "instruments/adau/adau_res_2.wav");

	// Sound for third row
	loadSound(_resRow3Note, _resRow3Buffer, "instruments/adau/adau_res_3.wav");

	// Sound for fourth row
	loadSound(_resRow4Note, _resRow4Buffer, "instruments/adau/adau_res_4.wav");

	// Sound for fifth row
	loadSound(_resRow5Note, _resRow5Buffer, "instruments/adau/adau_res_5.wav");

	// Resonator notes
	Note resNote1(_resTexture, _blue);
	Note resNote2(_resTexture, _blue);
	Note resNote3(_resTexture, _blue);
	Note resNote4(_resTexture, _blue);
	Note resNote5(_resTexture, _blue);

	// ---------- Metronome section ----------
	// Icon
	loadIcon(_metTexture, "icons/metronome_icon.png");

	// Sound for first row
	loadSound(_metRow1Note, _metRow1Buffer, "instruments/adau/adau_met_1.wav");

	// Sound for second row
	loadSound(_metRow2Note, _metRow2Buffer, "instruments/adau/adau_met_2.wav");

	// Sound for third row
	loadSound(_metRow3Note, _metRow3Buffer, "instruments/adau/adau_met_3.wav");

	// Sound for fourth row
	loadSound(_metRow4Note, _metRow4Buffer, "instruments/adau/adau_met_4.wav");

	// Sound for fifth row
	loadSound(_metRow5Note, _metRow5Buffer, "instruments/adau/adau_met_5.wav");

	// Metronome notes
	Note metNote1(_metTexture, _pink);
	Note metNote2(_metTexture, _pink);
	Note metNote3(_metTexture, _pink);
	Note metNote4(_metTexture, _pink);
	Note metNote5(_metTexture, _pink);

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
	_mandachordSounds = { _malRow1Note,
						_malRow2Note,
						_malRow3Note,
						_resRow1Note,
						_resRow2Note,
						_resRow3Note,
						_resRow4Note,
						_resRow5Note,
						_metRow1Note,
						_metRow2Note,
						_metRow3Note,
						_metRow4Note,
						_metRow5Note };

	// Setup the line that passes over the notes
	_line = { sf::RectangleShape(sf::Vector2f(780, 2)) };
	_line.rotate(90);
	_line.setPosition(10, 35);

	// Setup the bars
	_m1 = _line;
	_m2 = _line;
	_m3 = _line;
	_m4 = _line;
	_m1.setPosition(MEASURE + 6, 35);
	_m2.setPosition(2 * MEASURE + 6, 35);
	_m3.setPosition(3 * MEASURE + 6, 35);
	_m4.setPosition(4 * MEASURE + 6, 35);
}

// Advance
void Mandachord::advance(const bool & toggled, const unsigned int & loopMeasure) {
	if (toggled) {
		if (loopMeasure == 0) {
			if (_line.getPosition().x < BOARD)
				_line.move(sf::Vector2f(5, 0));
			else
				_line.setPosition(10, 35);
		}
		else if (loopMeasure == 1) {
			if (_line.getPosition().x < MEASURE)
				_line.move(sf::Vector2f(5, 0));
			else
				_line.setPosition(10, 35);
		}
		else if (loopMeasure == 2) {
			if (_line.getPosition().x > MEASURE && _line.getPosition().x < 2 * MEASURE)
				_line.move(sf::Vector2f(5, 0));
			else
				_line.setPosition(10 + MEASURE, 35);
		}
		else if (loopMeasure == 3) {
			if (_line.getPosition().x > 2 * MEASURE && _line.getPosition().x < 3 * MEASURE)
				_line.move(sf::Vector2f(5, 0));
			else
				_line.setPosition(10 + 2 * MEASURE, 35);
		}
		else if (loopMeasure == 4) {
			if (_line.getPosition().x > 3 * MEASURE && _line.getPosition().x < 4 * MEASURE)
				_line.move(sf::Vector2f(5, 0));
			else
				_line.setPosition(10 + 3 * MEASURE, 35);
		}
	}
}

// Check mouse for clicking on the mandachord
void Mandachord::checkMouse(sf::RenderWindow & window) {
	for (size_t i = 0; i < MANSIZE; i++) {
		// Chugga chugga here comes the trainwreck of an if statement :^)
		if (_mandachord[i].getPos().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			_mandachord[i].toggle();
	}
}

void Mandachord::changeMallets(const inst_type & instrument) {
	// Sound for first row
	loadSound(_malRow1Note, _malRow1Buffer, "instruments/" + instrument + "/" + instrument + "_mal_1.wav");

	// Sound for second row
	loadSound(_malRow2Note, _malRow2Buffer, "instruments/" + instrument + "/" + instrument + "_mal_2.wav");

	// Sound for third row
	loadSound(_malRow3Note, _malRow3Buffer, "instruments/" + instrument + "/" + instrument + "_mal_3.wav");
}

void Mandachord::changeResonator(const inst_type & instrument) {
	// Sound for first row
	loadSound(_resRow1Note, _resRow1Buffer, "instruments/" + instrument + "/" + instrument + "_res_1.wav");

	// Sound for second row
	loadSound(_resRow2Note, _resRow2Buffer, "instruments/" + instrument + "/" + instrument + "_res_2.wav");

	// Sound for third row
	loadSound(_resRow3Note, _resRow3Buffer, "instruments/" + instrument + "/" + instrument + "_res_3.wav");

	// Sound for fourth row
	loadSound(_resRow4Note, _resRow4Buffer, "instruments/" + instrument + "/" + instrument + "_res_4.wav");

	// Sound for fifth row
	loadSound(_resRow5Note, _resRow5Buffer, "instruments/" + instrument + "/" + instrument + "_res_5.wav");
}

void Mandachord::changeMetronome(const inst_type & instrument) {
	// Sound for first row
	loadSound(_metRow1Note, _metRow1Buffer, "instruments/" + instrument + "/" + instrument + "_met_1.wav");

	// Sound for second row
	loadSound(_metRow2Note, _metRow2Buffer, "instruments/" + instrument + "/" + instrument + "_met_2.wav");

	// Sound for third row
	loadSound(_metRow3Note, _metRow3Buffer, "instruments/" + instrument + "/" + instrument + "_met_3.wav");

	// Sound for fourth row
	loadSound(_metRow4Note, _metRow4Buffer, "instruments/" + instrument + "/" + instrument + "_met_4.wav");

	// Sound for fifth row
	loadSound(_metRow5Note, _metRow5Buffer, "instruments/" + instrument + "/" + instrument + "_met_5.wav");
}

// Draw
void Mandachord::draw(sf::RenderWindow & window, float & posX, float & posY) {
	for (size_t i = 0; i < MANSIZE; i++) {
		_mandachord[i].draw(window, posX, posY);
		if ((i + 1) % 64 != 0)
			posX += 60;
		else {
			posX = 10;
			posY += 60;
		}
	}
	window.draw(_m1);
	window.draw(_m2);
	window.draw(_m3);
	window.draw(_m4);
	window.draw(_line);
}

// Play
void Mandachord::play() {
	// This makes me physically sick but I'll clean it up later...
	for (unsigned int i = 0; i < MANSIZE; i++) {
		if (_mandachord[i].isToggled() && _mandachord[i].isColliding(_line)) {
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

void Mandachord::saveToFile(std::ofstream & out, const inst_type & mallets, const inst_type & resonator, const inst_type & metronome) {
	out << mallets << endl;
	out << resonator << endl;
	out << metronome << endl;
	for (unsigned int i = 0; i < MANSIZE; i++) {
		out << _mandachord[i].isToggled() << endl;
	}
}

void Mandachord::loadFmFile(std::ifstream & in, inst_type & mallets, inst_type & resonator, inst_type & metronome) {
	getline(in, mallets);
	getline(in, resonator);
	getline(in, metronome);
	changeMallets(mallets);
	changeResonator(resonator);
	changeMetronome(metronome);
	string buffer;
	for (unsigned int i = 0; i < MANSIZE; i++) {
		getline(in, buffer);
		if (buffer == "1") {
			if (!_mandachord[i].isToggled()) _mandachord[i].toggle();
		}
		else {
			if (_mandachord[i].isToggled()) _mandachord[i].toggle();
		}
	}
}