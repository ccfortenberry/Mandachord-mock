#include "button.hpp"
#include "mandachord.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;
#include <array>
using std::array;
#include <deque>
using std::deque;

/* -------------- TODO --------------
	* Add a structure for live sounds
	* Add a structure for instrument packs
	* Fix mallet drum sample
		- Well make them all better really...
	* Clean this shit up
*/

int main() {
	/* ---------- Initialize the window ---------- */
	float viewX = 0, viewY = 0;
	float widthf = 1280, heightf = 720;
	sf::View view(sf::FloatRect(viewX, viewY, widthf, heightf));
	unsigned int width = 1280, height = 720;
	sf::RenderWindow window(sf::VideoMode(width, height), "Mock Mandachord", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	window.setView(view);

	/* ---------- Generate the stuff that goes on the screen ---------- */
	// ---------- Text caption ----------
	sf::Font font; // font source (u: Pitchers): https://forums.warframe.com/topic/880893-warframe-logo-fan-font/
	if (!font.loadFromFile("fonts/WarframeFanFont_b1.ttf")) {
		cout << "Unable to load font" << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	sf::Text text;
	text.setFont(font);
	text.setString("MANDACHORD MOCK");
	text.setCharacterSize(24);
	text.setStyle(sf::Text::Bold);

	// ---------- Mallets section ----------
	const size_t MALSIZE = 3 * 64;		// Size
	sf::Color gray(91, 91, 91, 225);	// Color

	// Icon
	sf::Texture malletTexture;
	if (!malletTexture.loadFromFile("icons/mallets_icon.png")) {
		cout << "Unable to load mallet texture" << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// Sound for first row
	sf::Sound malletRow1Note;
	sf::SoundBuffer malletRow1;
	if (!malletRow1.loadFromFile("instruments/adau/adau_mal_1.wav")) {
		cout << "Unable to load mallet sound 1" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	else malletRow1Note.setBuffer(malletRow1);

	// Sound for second row
	sf::Sound malletRow2Note;
	sf::SoundBuffer malletRow2;
	if (!malletRow2.loadFromFile("instruments/adau/adau_mal_2.wav")) {
		cout << "Unable to load mallet sound 2" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	else malletRow2Note.setBuffer(malletRow2);

	// Sound for third row
	sf::Sound malletRow3Note;
	sf::SoundBuffer malletRow3;
	if (!malletRow3.loadFromFile("instruments/adau/adau_mal_3.wav")) {
		cout << "Unable to load mallet sound 3" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	else malletRow3Note.setBuffer(malletRow3);

	// Mallet notes
	Note malletNote1(malletTexture, gray);
	Note malletNote2(malletTexture, gray);
	Note malletNote3(malletTexture, gray);
	
	// ---------- Resonator section ----------
	const size_t RESSIZE = 5 * 64;		// Size
	sf::Color blue(39, 89, 114, 225);	// Color

	// Icon
	sf::Texture resTexture;
	if (!resTexture.loadFromFile("icons/resonator_icon.png")) {
		cout << "Unable to load resonator texture" << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// Sound for first row
	sf::Sound resRow1Note;
	sf::SoundBuffer resRow1;
	if (!resRow1.loadFromFile("instruments/adau/adau_res_1.wav")) {
		cout << "Unable to load resonator sound 1" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	else resRow1Note.setBuffer(resRow1);

	// Sound for second row
	sf::Sound resRow2Note;
	sf::SoundBuffer resRow2;
	if (!resRow2.loadFromFile("instruments/adau/adau_res_2.wav")) {
		cout << "Unable to load resonator sound 2" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	else resRow2Note.setBuffer(resRow2);

	// Sound for third row
	sf::Sound resRow3Note;
	sf::SoundBuffer resRow3;
	if (!resRow3.loadFromFile("instruments/adau/adau_res_3.wav")) {
		cout << "Unable to load resonator sound 3" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	else resRow3Note.setBuffer(resRow3);

	// Sound for fourth row
	sf::Sound resRow4Note;
	sf::SoundBuffer resRow4;
	if (!resRow4.loadFromFile("instruments/adau/adau_res_4.wav")) {
		cout << "Unable to load resonator sound 4" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	else resRow4Note.setBuffer(resRow4);

	// Sound for fifth row
	sf::Sound resRow5Note;
	sf::SoundBuffer resRow5;
	if (!resRow5.loadFromFile("instruments/adau/adau_res_5.wav")) {
		cout << "Unable to load resonator sound 5" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	else resRow5Note.setBuffer(resRow5);

	// Resonator notes
	Note resNote1(resTexture, blue);
	Note resNote2(resTexture, blue);
	Note resNote3(resTexture, blue);
	Note resNote4(resTexture, blue);
	Note resNote5(resTexture, blue);

	// ---------- Metronome section ----------
	const size_t METSIZE = RESSIZE;		// Size
	sf::Color pink(107, 58, 113, 225);	// Color

	// Icon
	sf::Texture metTexture;
	if (!metTexture.loadFromFile("icons/metronome_icon.png")) {
		cout << "Unable to load metronome texture" << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// Sound for first row
	sf::Sound metRow1Note;
	sf::SoundBuffer metRow1;
	if (!metRow1.loadFromFile("instruments/adau/adau_met_1.wav")) {
		cout << "Unable to load metronome sound 1" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	else metRow1Note.setBuffer(metRow1);

	// Sound for second row
	sf::Sound metRow2Note;
	sf::SoundBuffer metRow2;
	if (!metRow2.loadFromFile("instruments/adau/adau_met_2.wav")) {
		cout << "Unable to load metronome sound 2" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	else metRow2Note.setBuffer(metRow2);

	// Sound for third row
	sf::Sound metRow3Note;
	sf::SoundBuffer metRow3;
	if (!metRow3.loadFromFile("instruments/adau/adau_met_3.wav")) {
		cout << "Unable to load metronome sound 3" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	else metRow3Note.setBuffer(metRow3);

	// Sound for fourth row
	sf::Sound metRow4Note;
	sf::SoundBuffer metRow4;
	if (!metRow4.loadFromFile("instruments/adau/adau_met_4.wav")) {
		cout << "Unable to load metronome sound 4" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	else metRow4Note.setBuffer(metRow4);

	// Sound for fifth row
	sf::Sound metRow5Note;
	sf::SoundBuffer metRow5;
	if (!metRow5.loadFromFile("instruments/adau/adau_met_5.wav")) {
		cout << "Unable to load metronome sound 5" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	else metRow5Note.setBuffer(metRow5);

	// Metronome notes
	Note metNote1(metTexture, pink);
	Note metNote2(metTexture, pink);
	Note metNote3(metTexture, pink);
	Note metNote4(metTexture, pink);
	Note metNote5(metTexture, pink);


	/* ---------- The Mandachord ---------- */
	const size_t MANSIZE = 13 * 64;
	array<Note, MANSIZE> mandachord;
	for (size_t i = 0; i < MANSIZE; i++) {
		if (i < MALSIZE) {
			if (i < 64) mandachord[i] = malletNote1;
			else if (i < 2 * 64) mandachord[i] = malletNote2;
			else mandachord[i] = malletNote3;
		}
		else if (i < MALSIZE + RESSIZE) {
			if (i < 4 * 64) mandachord[i] = resNote1;
			else if (i < 5 * 64) mandachord[i] = resNote2;
			else if (i < 6 * 64) mandachord[i] = resNote3;
			else if (i < 7 * 64) mandachord[i] = resNote4;
			else mandachord[i] = resNote5;
		}
		else {
			if (i < 9 * 64) mandachord[i] = metNote1;
			else if (i < 10 * 64) mandachord[i] = metNote2;
			else if (i < 11 * 64) mandachord[i] = metNote3;
			else if (i < 12 * 64) mandachord[i] = metNote4;
			else mandachord[i] = metNote5;
		}
	}

	// Need to make a sound table to hold the note sounds since
	// loading 832 sounds into memory is a bad idea...
	array<sf::Sound, 13> mandachordSounds = {malletRow1Note,
											malletRow2Note, 
											malletRow3Note, 
											resRow1Note, 
											resRow2Note, 
											resRow3Note, 
											resRow4Note,
											resRow5Note, 
											metRow1Note, 
											metRow2Note, 
											metRow3Note, 
											metRow4Note, 
											metRow5Note};

	// A map for live notes so they don't get cutoff
	deque<sf::Sound> nowPlaying;
	unsigned int NPIndex = 0;

	// A couple consts for board size
	const size_t BAR = 16;
	const size_t MEASURE = 4 * BAR;

	// The line that passes over the notes to play them
	sf::RectangleShape line(sf::Vector2f(780, 2));
	line.rotate(90);
	line.setPosition(10, 35);

	/* ---------- Play button ---------- */
	sf::Text textPlay;
	textPlay.setFont(font);
	textPlay.setString("PLAY");
	textPlay.setCharacterSize(18);
	Button play(textPlay, sf::Color::White);

	/* ---------- Running application ---------- */
	while (window.isOpen())
	{
		if (play.isToggled()) {
			if (line.getPosition().x < BAR * 60)
				line.move(sf::Vector2f(5, 0));
			else
				line.setPosition(10, 35);
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case (sf::Event::KeyPressed):
				if (event.key.code == sf::Keyboard::Right) {
					view.move(10, 0);
					window.setView(view);
				}
				if (event.key.code == sf::Keyboard::Left) {
					view.move(-10, 0);
					window.setView(view);
				}
				if (event.key.code == sf::Keyboard::Up) {
					view.move(0, -10);
					window.setView(view);
				}
				if (event.key.code == sf::Keyboard::Down) {
					view.move(0, 10);
					window.setView(view);
				}
				break;
			case (sf::Event::MouseButtonPressed):
				if (event.key.code == sf::Mouse::Left) {
					for (size_t i = 0; i < MANSIZE; i++) {
						// Chugga chugga here comes the trainwreck of an if statement :^)
						if (mandachord[i].getPos().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
							mandachord[i].toggle();
							cout << "Toggled note: " << i << endl;
						}
					}
					if (play.getPos().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
						play.toggle();
						cout << "Toggled Play" << endl;
					}
				}
				break;
			case (sf::Event::Closed):
				window.close();
			default:
				break;
			}
		}

		// This makes me physically sick but I'll clean it up later...
		for (unsigned int i = 0; i < MANSIZE; i++) {
			if (mandachord[i].isToggled() && mandachord[i].isColliding(line)) {
				cout << "Collision!" << endl;
				if (i < 64) {
					nowPlaying.emplace_back(mandachordSounds[0]);
					NPIndex++;
					nowPlaying[NPIndex - 1].play();
				}
				else if (i < 2 * 64) {
					nowPlaying.emplace_back(mandachordSounds[1]);
					NPIndex++;
					nowPlaying[NPIndex - 1].play();
				}
				else if (i < 3 * 64) {
					nowPlaying.emplace_back(mandachordSounds[2]);
					NPIndex++;
					nowPlaying[NPIndex - 1].play();
				}
				else if (i < 4 * 64) {
					nowPlaying.emplace_back(mandachordSounds[3]);
					NPIndex++;
					nowPlaying[NPIndex - 1].play();
				}
				else if (i < 5 * 64) {
					nowPlaying.emplace_back(mandachordSounds[4]);
					NPIndex++;
					nowPlaying[NPIndex - 1].play();
				}
				else if (i < 6 * 64) {
					nowPlaying.emplace_back(mandachordSounds[5]);
					NPIndex++;
					nowPlaying[NPIndex - 1].play();
				}
				else if (i < 7 * 64) {
					nowPlaying.emplace_back(mandachordSounds[6]);
					NPIndex++;
					nowPlaying[NPIndex - 1].play();
				}
				else if (i < 8 * 64) {
					nowPlaying.emplace_back(mandachordSounds[7]);
					NPIndex++;
					nowPlaying[NPIndex - 1].play();
				}
				else if (i < 9 * 64) {
					nowPlaying.emplace_back(mandachordSounds[8]);
					NPIndex++;
					nowPlaying[NPIndex - 1].play();
				}
				else if (i < 10 * 64) {
					nowPlaying.emplace_back(mandachordSounds[9]);
					NPIndex++;
					nowPlaying[NPIndex - 1].play();
				}
				else if (i < 11 * 64) {
					nowPlaying.emplace_back(mandachordSounds[10]);
					NPIndex++;
					nowPlaying[NPIndex - 1].play();
				}
				else if (i < 12 * 64) {
					nowPlaying.emplace_back(mandachordSounds[11]);
					NPIndex++;
					nowPlaying[NPIndex - 1].play();
				}
				else {
					nowPlaying.emplace_back(mandachordSounds[12]);
					NPIndex++;
					nowPlaying[NPIndex - 1].play();
				}
			}
		}

		if (!nowPlaying.empty() && nowPlaying.front().getStatus() == sf::Sound::Status::Stopped) {
			nowPlaying.pop_front();
			NPIndex--;
		}

		window.clear();
		window.draw(text);
		play.draw(window, 500, 5);
		float posX=10, posY=40;
		for (size_t i = 0; i < MANSIZE; i++) {
			mandachord[i].draw(window, posX, posY);
			if ((i+1) % 64 != 0)
				posX += 60;
			else {
				posX = 10;
				posY += 60;
			}
		}
		window.draw(line);
		window.display();
	}

	/* ---------- Exit success ---------- */
	cout << "Exit success!" << endl;
	system("pause");
	return EXIT_SUCCESS;
}