#include "button.hpp"
#include "mandachord.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;

int main() {
	// Initialize the window
	float viewX = 0, viewY = 0;
	float widthf = 1280, heightf = 720;
	sf::View view(sf::FloatRect(viewX, viewY, widthf, heightf));
	size_t width = 1280, height = 720;
	sf::RenderWindow window(sf::VideoMode(width, height), "Mock Mandachord", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	window.setView(view);

	// Generate the stuff that goes on the screen
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

	sf::Sound sound;
	const size_t MALSIZE = 3 * 64;
	sf::Color gray(91, 91, 91, 225);
	sf::Texture malletTexture;
	if (!malletTexture.loadFromFile("icons/mallets_icon.png")) {
		cout << "Unable to load mallet texture" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	sf::SoundBuffer malletRow1;
	if (!malletRow1.loadFromFile("instruments/adau/adau_mal_1.wav")) {
		cout << "Unable to load mallet sound 1" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	sf::SoundBuffer malletRow2;
	if (!malletRow2.loadFromFile("instruments/adau/adau_mal_2.wav")) {
		cout << "Unable to load mallet sound 2" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	sf::SoundBuffer malletRow3;
	if (!malletRow3.loadFromFile("instruments/adau/adau_mal_3.wav")) {
		cout << "Unable to load mallet sound 3" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	Note malletNote1(malletRow1, malletTexture, gray);
	Note malletNote2(malletRow2, malletTexture, gray);
	Note malletNote3(malletRow3, malletTexture, gray);
	
	const size_t RESSIZE = 5 * 64;
	sf::Color blue(39, 89, 114, 225);
	sf::Texture resTexture;
	if (!resTexture.loadFromFile("icons/resonator_icon.png")) {
		cout << "Unable to load resonator texture" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	sf::SoundBuffer resRow1;
	if (!malletRow1.loadFromFile("instruments/adau/adau_res_1.wav")) {
		cout << "Unable to load resonator sound 1" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	sf::SoundBuffer resRow2;
	if (!malletRow2.loadFromFile("instruments/adau/adau_res_2.wav")) {
		cout << "Unable to load resonator sound 2" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	sf::SoundBuffer resRow3;
	if (!malletRow3.loadFromFile("instruments/adau/adau_res_3.wav")) {
		cout << "Unable to load resonator sound 3" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	sf::SoundBuffer resRow4;
	if (!malletRow1.loadFromFile("instruments/adau/adau_res_4.wav")) {
		cout << "Unable to load resonator sound 4" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	sf::SoundBuffer resRow5;
	if (!malletRow2.loadFromFile("instruments/adau/adau_res_5.wav")) {
		cout << "Unable to load resonator sound 5" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	Note resNote1(resRow1, resTexture, blue);
	Note resNote2(resRow2, resTexture, blue);
	Note resNote3(resRow3, resTexture, blue);
	Note resNote4(resRow4, resTexture, blue);
	Note resNote5(resRow5, resTexture, blue);

	const size_t METSIZE = RESSIZE;
	sf::Color pink(107, 58, 113, 225);
	sf::Texture metTexture;
	if (!metTexture.loadFromFile("icons/metronome_icon.png")) {
		cout << "Unable to load metronome texture" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	sf::SoundBuffer metRow1;
	if (!malletRow1.loadFromFile("instruments/adau/adau_met_1.wav")) {
		cout << "Unable to load metronome sound 1" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	sf::SoundBuffer metRow2;
	if (!malletRow2.loadFromFile("instruments/adau/adau_met_2.wav")) {
		cout << "Unable to load metronome sound 2" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	sf::SoundBuffer metRow3;
	if (!malletRow3.loadFromFile("instruments/adau/adau_met_3.wav")) {
		cout << "Unable to load metronome sound 3" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	sf::SoundBuffer metRow4;
	if (!malletRow1.loadFromFile("instruments/adau/adau_met_4.wav")) {
		cout << "Unable to load metronome sound 4" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	sf::SoundBuffer metRow5;
	if (!malletRow2.loadFromFile("instruments/adau/adau_met_5.wav")) {
		cout << "Unable to load metronome sound 5" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	Note metNote1(metRow1, metTexture, pink);
	Note metNote2(metRow2, metTexture, pink);
	Note metNote3(metRow3, metTexture, pink);
	Note metNote4(metRow4, metTexture, pink);
	Note metNote5(metRow5, metTexture, pink);

	const size_t MANSIZE = 13 * 64;
	vector<Note> mandachord;
	for (size_t i = 0; i < MANSIZE; i++) {
		if (i < MALSIZE) {
			if (i < 64) mandachord.push_back(malletNote1);
			else if (i < 2 * 64) mandachord.push_back(malletNote2);
			else mandachord.push_back(malletNote3);
		}
		else if (i < MALSIZE + RESSIZE) {
			if (i < 4 * 64) mandachord.push_back(resNote1);
			else if (i < 5 * 64) mandachord.push_back(resNote2);
			else if (i < 6 * 64) mandachord.push_back(resNote3);
			else if (i < 7 * 64) mandachord.push_back(resNote4);
			else mandachord.push_back(resNote5);
		}
		else {
			if (i < 9 * 64) mandachord.push_back(metNote1);
			else if (i < 10 * 64) mandachord.push_back(metNote2);
			else if (i < 11 * 64) mandachord.push_back(metNote3);
			else if (i < 12 * 64) mandachord.push_back(metNote4);
			else mandachord.push_back(metNote5);
		}
	}
	/*cout << "Mandachord size: " << mandachord.size() << endl;
	for (size_t i = 0; i < MANSIZE; i++) {
		cout << "Mandachord data at" << i << ": (";
		cout << mandachord[i].getSound() << ", ";
		cout << mandachord[i].getIcon() << ", ";
		cout << mandachord[i].getColor().toInteger() << ")" << endl;
	}*/

	const size_t BAR = 16;
	const size_t MEASURE = 4 * BAR;

	sf::RectangleShape line(sf::Vector2f(780, 2));
	line.rotate(90);
	line.setPosition(10, 35);

	sf::Text textPlay;
	textPlay.setFont(font);
	textPlay.setString("PLAY");
	textPlay.setCharacterSize(18);
	Button play(textPlay, sf::Color::White);

	// Running application
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
					// cout << "Toggling?" << endl;
					for (size_t i = 0; i < MANSIZE; i++) {
						if (mandachord[i].getPos().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
							mandachord[i].toggleNote();
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

		for (size_t i = 0; i < MANSIZE; i++) {
			if (mandachord[i].isColliding(line) && mandachord[i].isToggled()) {
				cout << "Collision!" << endl;
				mandachord[i].play(sound);
			}
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

	// Exit success
	cout << "Exit success!" << endl;
	system("pause");
	return EXIT_SUCCESS;
}