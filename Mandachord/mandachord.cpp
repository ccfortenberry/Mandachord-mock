#include "mandachord.hpp"
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
using std::getline;
using std::to_string;
#include <array>
using std::array;
#include <algorithm>
using std::equal;
#include <utility>
using std::pair;


/* ------ Note ------ */
// Ctor from data
Note::Note(const sf::Texture & icon, const sf::Color & color)
	: _icon(sf::Vector2f(50, 50)), _color(color), _noteBox(sf::Vector2f(50, 50)), _toggled(false), _playable(false) {
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
		_playable = true;
	}
	else {
		_toggled = false;
		_noteBox.setFillColor(sf::Color::Transparent);
		_playable = false;
	}
}

// IsToggled
bool Note::isToggled() {
	return _toggled;
}

// TogglePlayable
void Note::togglePlayable() {
	if (!_playable) _playable = true;
	else _playable = false;
}

// IsPlayable
bool Note::isPlayable() {
	return _playable;
}

// IsColliding
bool Note::isColliding(const sf::RectangleShape & line) {
	return _noteBox.getGlobalBounds().intersects(line.getGlobalBounds());
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

void loadSound(sf::Sound & sound, sf::SoundBuffer & buffer, const string & soundpath) {
	if (!buffer.loadFromFile(soundpath)) {
		cout << "Unable to load " << soundpath << endl;
		system("pause");
		throw EXIT_FAILURE;
	}
	else sound.setBuffer(buffer);
}

// Default Ctor
Mandachord::Mandachord() {
	// ---------- Mallets section ----------
	// Icon
	loadIcon(_malTexture1, "icons/mallets-1_icon.png");
	loadIcon(_malTexture2, "icons/mallets-2_icon.png");
	loadIcon(_malTexture3, "icons/mallets-3_icon.png");

	// Sound for first row
	loadSound(_mandachordSounds[0], _mandachordSoundsBuffer[0], "instruments/adau/adau_mal_1.wav");

	// Sound for second row
	loadSound(_mandachordSounds[1], _mandachordSoundsBuffer[1], "instruments/adau/adau_mal_2.wav");

	// Sound for third row
	loadSound(_mandachordSounds[2], _mandachordSoundsBuffer[2], "instruments/adau/adau_mal_3.wav");

	// Mallet notes
	Note malNote1(_malTexture1, _gray);
	Note malNote2(_malTexture2, _gray);
	Note malNote3(_malTexture3, _gray);

	// ---------- Resonator section ----------
	// Icon
	loadIcon(_resTexture, "icons/resonator_icon.png");

	// Sound for first row
	loadSound(_mandachordSounds[3], _mandachordSoundsBuffer[3], "instruments/adau/adau_res_1.wav");

	// Sound for second row
	loadSound(_mandachordSounds[4], _mandachordSoundsBuffer[4], "instruments/adau/adau_res_2.wav");

	// Sound for third row
	loadSound(_mandachordSounds[5], _mandachordSoundsBuffer[5], "instruments/adau/adau_res_3.wav");

	// Sound for fourth row
	loadSound(_mandachordSounds[6], _mandachordSoundsBuffer[6], "instruments/adau/adau_res_4.wav");

	// Sound for fifth row
	loadSound(_mandachordSounds[7], _mandachordSoundsBuffer[7], "instruments/adau/adau_res_5.wav");

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
	loadSound(_mandachordSounds[8], _mandachordSoundsBuffer[8], "instruments/adau/adau_met_1.wav");

	// Sound for second row
	loadSound(_mandachordSounds[9], _mandachordSoundsBuffer[9], "instruments/adau/adau_met_2.wav");

	// Sound for third row
	loadSound(_mandachordSounds[10], _mandachordSoundsBuffer[10], "instruments/adau/adau_met_3.wav");

	// Sound for fourth row
	loadSound(_mandachordSounds[11], _mandachordSoundsBuffer[11], "instruments/adau/adau_met_4.wav");

	// Sound for fifth row
	loadSound(_mandachordSounds[12], _mandachordSoundsBuffer[12], "instruments/adau/adau_met_5.wav");

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

	// Setup the line that passes over the notes
	_line = { sf::RectangleShape(sf::Vector2f(780, 2)) };
	_line.rotate(90);
	_line.setPosition(5, 35);

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
	if (loopMeasure == 0) {
		_posmin = 0, _posmax = BOARD;
	}
	else if (loopMeasure == 1) {
		_posmin = 0, _posmax = MEASURE;
	}
	else if (loopMeasure == 2) {
		_posmin = MEASURE, _posmax = 2 * MEASURE;
	}
	else if (loopMeasure == 3) {
		_posmin = 2 * MEASURE, _posmax = 3 * MEASURE;
	}
	else if (loopMeasure == 4) {
		_posmin = 3 * MEASURE, _posmax = 4 * MEASURE;
	}
	else if (loopMeasure == 5) {
		_posmin = 0, _posmax = 2 * MEASURE;
	}
	else if (loopMeasure == 6) {
		_posmin = MEASURE, _posmax = 3 * MEASURE;
	}
	else if (loopMeasure == 7) {
		_posmin = 2 * MEASURE, _posmax = 4 * MEASURE;
	}
	else if (loopMeasure == 8) {
		_posmin = 0, _posmax = 3 * MEASURE;
	}
	else if (loopMeasure == 9) {
		_posmin = MEASURE, _posmax = 4 * MEASURE;
	}
	if (toggled) {
		if (_line.getPosition().x > _posmin && _line.getPosition().x < _posmax)
			_line.move(sf::Vector2f(8, 0));
		else {
			_line.setPosition(5 + _posmin, 35);
			for (auto i : _mandachord) {
				if (!i.isPlayable()) i.togglePlayable();
			}
		}
	}
}

// Increment total utility
void incTotal(unsigned int & i, array<unsigned int, 12> & _noteTotal) {
	// Mallet total inc
	if (i < 16 || (i >= 4 * 16 && i < 5 * 16) || (i >= 8 * 16 && i < 9 * 16)) {
		_noteTotal[0]++;
	}
	else if (i < 2 * 16 || (i >= 5 * 16 && i < 6 * 16) || (i >= 9 * 16 && i < 10 * 16)) {
		_noteTotal[1]++;
	}
	else if (i < 3 * 16 || (i >= 6 * 16 && i < 7 * 16) || (i >= 10 * 16 && i < 11 * 16)) {
		_noteTotal[2]++;
	}
	else if (i < 4 * 16 || (i >= 7 * 16 && i < 8 * 16) || (i >= 11 * 16 && i < 12 * 16)) {
		_noteTotal[3]++;
	}
	// Res total inc
	else if (i < 13 * 16 || (i >= 16 * 16 && i < 17 * 16) || (i >= 20 * 16 && i < 21 * 16) || (i >= 24 * 16 && i < 25 * 16) || (i >= 28 * 16 && i < 29 * 16)) {
		_noteTotal[4]++;
	}
	else if (i < 14 * 16 || (i >= 17 * 16 && i < 18 * 16) || (i >= 21 * 16 && i < 22 * 16) || (i >= 25 * 16 && i < 26 * 16) || (i >= 29 * 16 && i < 30 * 16)) {
		_noteTotal[5]++;
	}
	else if (i < 15 * 16 || (i >= 18 * 16 && i < 19 * 16) || (i >= 22 * 16 && i < 23 * 16) || (i >= 26 * 16 && i < 27 * 16) || (i >= 30 * 16 && i < 31 * 16)) {
		_noteTotal[6]++;
	}
	else if (i < 16 * 16 || (i >= 19 * 16 && i < 20 * 16) || (i >= 23 * 16 && i < 24 * 16) || (i >= 27 * 16 && i < 28 * 16) || (i >= 31 * 16 && i < 32 * 16)) {
		_noteTotal[7]++;
	}
	// Met total inc
	else if (i < 33 * 16 || (i >= 36 * 16 && i < 37 * 16) || (i >= 40 * 16 && i < 41 * 16) || (i >= 44 * 16 && i < 45 * 16) || (i >= 48 * 16 && i < 49 * 16)) {
		_noteTotal[8]++;
	}
	else if (i < 34 * 16 || (i >= 37 * 16 && i < 38 * 16) || (i >= 41 * 16 && i < 42 * 16) || (i >= 45 * 16 && i < 46 * 16) || (i >= 49 * 16 && i < 50 * 16)) {
		_noteTotal[9]++;
	}
	else if (i < 35 * 16 || (i >= 38 * 16 && i < 39 * 16) || (i >= 42 * 16 && i < 43 * 16) || (i >= 46 * 16 && i < 47 * 16) || (i >= 50 * 16 && i < 51 * 16)) {
		_noteTotal[10]++;
	}
	else if (i < 36 * 16 || (i >= 39 * 16 && i < 40 * 16) || (i >= 43 * 16 && i < 44 * 16) || (i >= 47 * 16 && i < 48 * 16) || (i >= 51 * 16 && i < 52 * 16)) {
		_noteTotal[11]++;
	}
}

// Decrement total utility
void decTotal(unsigned int & i, array<unsigned int, 12> & _noteTotal) {
	// Mallet total dec
	if (i < 16 || (i > 4 * 16 && i < 5 * 16) || (i > 8 * 16 && i < 9 * 16)) {
		_noteTotal[0]--;
	}
	else if (i < 2 * 16 || (i > 5 * 16 && i < 6 * 16) || (i > 9 * 16 && i < 10 * 16)) {
		_noteTotal[1]--;
	}
	else if (i < 3 * 16 || (i > 6 * 16 && i < 7 * 16) || (i > 10 * 16 && i < 11 * 16)) {
		_noteTotal[2]--;
	}
	else if (i < 4 * 16 || (i > 7 * 16 && i < 8 * 16) || (i > 11 * 16 && i < 12 * 16)) {
		_noteTotal[3]--;
	}
	// Res total dec
	else if (i < 13 * 16 || (i > 16 * 16 && i < 17 * 16) || (i > 20 * 16 && i < 21 * 16) || (i > 24 * 16 && i < 25 * 16) || (i > 28 * 16 && i < 29 * 16)) {
		_noteTotal[4]--;
	}
	else if (i < 14 * 16 || (i > 17 * 16 && i < 18 * 16) || (i > 21 * 16 && i < 22 * 16) || (i > 25 * 16 && i < 26 * 16) || (i > 29 * 16 && i < 30 * 16)) {
		_noteTotal[5]--;
	}
	else if (i < 15 * 16 || (i > 18 * 16 && i < 19 * 16) || (i > 22 * 16 && i < 23 * 16) || (i > 26 * 16 && i < 27 * 16) || (i > 30 * 16 && i < 31 * 16)) {
		_noteTotal[6]--;
	}
	else if (i < 16 * 16 || (i > 19 * 16 && i < 20 * 16) || (i > 24 * 16 && i < 25 * 16) || (i > 27 * 16 && i < 28 * 16) || (i > 31 * 16 && i < 32 * 16)) {
		_noteTotal[7]--;
	}
	// Met total dec
	else if (i < 33 * 16 || (i > 36 * 16 && i < 37 * 16) || (i > 40 * 16 && i < 41 * 16) || (i > 44 * 16 && i < 45 * 16) || (i > 48 * 16 && i < 49 * 16)) {
		_noteTotal[8]--;
	}
	else if (i < 34 * 16 || (i > 37 * 16 && i < 38 * 16) || (i > 41 * 16 && i < 42 * 16) || (i > 45 * 16 && i < 46 * 16) || (i > 47 * 16 && i < 50 * 16)) {
		_noteTotal[9]--;
	}
	else if (i < 35 * 16 || (i > 38 * 16 && i < 39 * 16) || (i > 42 * 16 && i < 43 * 16) || (i > 46 * 16 && i < 47 * 16) || (i > 50 * 16 && i < 51 * 16)) {
		_noteTotal[10]--;
	}
	else if (i < 36 * 16 || (i > 39 * 16 && i < 40 * 16) || (i > 43 * 16 && i < 44 * 16) || (i > 47 * 16 && i < 48 * 16) || (i > 51 * 16 && i < 52 * 16)) {
		_noteTotal[11]--;
	}
}

// Check mouse for clicking on the mandachord
void Mandachord::checkMouse(sf::RenderWindow & window, bool & isOverMaxNotes, sf::Text & errorPrompt) {
	for (unsigned int i = 0; i < MANSIZE; i++) {
		if (_mandachord[i].getPos().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
			_mandachord[i].toggle();
			if (_mandachord[i].isToggled()) {
				incTotal(i, _noteTotal);
				for (unsigned int j = 0; j < _noteTotal.size(); j++) {
					if (j < 4) {
						if (_noteTotal[j] > _malLimit) {
							_mandachord[i].toggle();
							decTotal(i, _noteTotal);
							isOverMaxNotes = true;
							errorPrompt.setString("Only 26 mallet notes allowed per measure");
						}
					}
					else if (j < 8) {
						if (_noteTotal[j] > _resLimit) {
							_mandachord[i].toggle();
							decTotal(i, _noteTotal);
							isOverMaxNotes = true;
							errorPrompt.setString("Only 16 resonator notes allowed per measure");
						}
					}
					else {
						if (_noteTotal[j] > _metLimit) {
							_mandachord[i].toggle();
							decTotal(i, _noteTotal);
							isOverMaxNotes = true;
							errorPrompt.setString("Only 16 metronome notes allowed per measure");
						}
					}
				}
			}
			else {
				decTotal(i, _noteTotal);
			}
		}
	}
}

// ChangeMallets
void Mandachord::changeMallets(const inst_type & instrument) {
	for (unsigned int i = 0; i < 3; i++)
		loadSound(_mandachordSounds[i], _mandachordSoundsBuffer[i], "instruments/" + instrument + "/" + instrument + "_mal_" + to_string(i + 1) + ".wav");
}

// ChangeResonator
void Mandachord::changeResonator(const inst_type & instrument) {
	for (unsigned int i = 3; i < 8; i++)
		loadSound(_mandachordSounds[i], _mandachordSoundsBuffer[i], "instruments/" + instrument + "/" + instrument + "_res_" + to_string(i - 2) + ".wav");
}

// ChangeMetronome
void Mandachord::changeMetronome(const inst_type & instrument) {
	for (unsigned int i = 8; i < 13; i++)
		loadSound(_mandachordSounds[i], _mandachordSoundsBuffer[i], "instruments/" + instrument + "/" + instrument + "_met_" + to_string(i - 7) + ".wav");
}

// Clear
void Mandachord::clear() {
	for (auto & i : _mandachord) {
		if (i.isToggled()) i.toggle();
	}
}

// Draw
void Mandachord::draw(sf::RenderWindow & window, float & posX, float & posY) {
	for (unsigned int i = 0; i < MANSIZE; i++) {
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
	for (unsigned int i = 0; i < MANSIZE; i++) {
		if (_mandachord[i].isToggled() && _mandachord[i].isPlayable() && _mandachord[i].isColliding(_line)) {
			_mandachord[i].togglePlayable();
			if (i < 64) _nowPlaying.emplace_back(i, _mandachordSounds[0]);
			else if (i < 2 * 64) _nowPlaying.emplace_back(i, _mandachordSounds[1]);
			else if (i < 3 * 64) _nowPlaying.emplace_back(i, _mandachordSounds[2]);
			else if (i < 4 * 64) _nowPlaying.emplace_back(i, _mandachordSounds[3]);
			else if (i < 5 * 64) _nowPlaying.emplace_back(i, _mandachordSounds[4]);
			else if (i < 6 * 64) _nowPlaying.emplace_back(i, _mandachordSounds[5]);
			else if (i < 7 * 64) _nowPlaying.emplace_back(i, _mandachordSounds[6]);
			else if (i < 8 * 64) _nowPlaying.emplace_back(i, _mandachordSounds[7]);
			else if (i < 9 * 64) _nowPlaying.emplace_back(i, _mandachordSounds[8]);
			else if (i < 10 * 64) _nowPlaying.emplace_back(i, _mandachordSounds[9]);
			else if (i < 11 * 64) _nowPlaying.emplace_back(i, _mandachordSounds[10]);
			else if (i < 12 * 64) _nowPlaying.emplace_back(i, _mandachordSounds[11]);
			else _nowPlaying.emplace_back(i, _mandachordSounds[12]);
			_nowPlaying[_npindex].second.play();
			_npindex++;
		}
	}
	
	if (!_nowPlaying.empty())
		for (auto i = 0; i < _nowPlaying.size(); i++) {
			if (_nowPlaying[i].second.getStatus() == sf::Sound::Status::Stopped) {
				if (!_mandachord[_nowPlaying[i].first].isColliding(_line) && !_mandachord[_nowPlaying[i].first].isPlayable())
					_mandachord[_nowPlaying[i].first].togglePlayable();
				auto temp = _nowPlaying[0];
				_nowPlaying[0] = _nowPlaying[i];
				_nowPlaying[i] = temp;
				_nowPlaying.pop_front();
				_npindex--;
		}
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

bool ignoreCaseCompare(const string & s1, const string & s2) {
	return equal(s1.begin(), s1.end(), s2.begin(), s2.end(), [](char c1, char c2) { return tolower(c1) == tolower(c2); });
}

void Mandachord::loadFmFile(std::ifstream & in, inst_type & mallets, inst_type & resonator, inst_type & metronome, 
							bool & isFileGood, const array<inst_type, 10> & instrTable, sf::Text & errorPrompt) {
	getline(in, mallets);
	for (unsigned int i = 0; i <= instrTable.size(); i++) {
		if (i == instrTable.size()) {
			errorPrompt.setString("FILE ERROR: Not a valid mallets!");
			isFileGood = false;
			return;
		}
		else if (ignoreCaseCompare(mallets, instrTable[i])) break;
	}

	getline(in, resonator);
	for (unsigned int i = 0; i <= instrTable.size(); i++) {
		if (i == instrTable.size()) {
			errorPrompt.setString("FILE ERROR: Not a valid resonator!");
			isFileGood = false;
			return;
		}
		else if (ignoreCaseCompare(resonator, instrTable[i])) break;
	}

	getline(in, metronome);
	for (unsigned int i = 0; i <= instrTable.size(); i++) {
		if (i == instrTable.size()) {
			errorPrompt.setString("FILE ERROR: Not a valid metronome!");
			isFileGood = false;
			return;
		}
		else if (ignoreCaseCompare(metronome, instrTable[i])) break;
	}

	string buffer;
	array<unsigned int, MANSIZE> test;
	for (unsigned int i = 0; i < MANSIZE; i++) {
		getline(in, buffer);
		if (buffer == "1") 
			test[i] = 1;
		else if (buffer == "0") 
			test[i] = 0;
		else {
			errorPrompt.setString("ERROR: Bad note at " + to_string(i) + "!");
			isFileGood = false;
			return;
		}
	}

	changeMallets(mallets);
	changeResonator(resonator);
	changeMetronome(metronome);
	for (unsigned int i = 0; i < MANSIZE; i++) {
		if (test[i] == 1) {
			if (!_mandachord[i].isToggled()) {
				_mandachord[i].toggle();
				incTotal(i, _noteTotal);
			}
		}
		else {
			if (_mandachord[i].isToggled()) {
				_mandachord[i].toggle();
				decTotal(i, _noteTotal);
			}
		}
	}
	_line.setPosition(5 + _posmin, 35);
}