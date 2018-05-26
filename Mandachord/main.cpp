#include "button.hpp"
#include "mandachord.hpp"
#include <SFML/Graphics.hpp>
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

	const size_t MALSIZE = 3 * 64;
	sf::Color gray(91, 91, 91, 225);
	sf::Texture malletTexture;
	if (!malletTexture.loadFromFile("icons/mallets_icon.png")) {
		cout << "Unable to load mallet texture" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	Note malletNote("Mallet sound", malletTexture, gray);
	
	const size_t RESSIZE = 5 * 64;
	sf::Color blue(39, 89, 114, 225);
	sf::Texture resTexture;
	if (!resTexture.loadFromFile("icons/resonator_icon.png")) {
		cout << "Unable to load resonator texture" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	Note resNote("Resonator sound", resTexture, blue);

	const size_t METSIZE = RESSIZE;
	sf::Color pink(107, 58, 113, 225);
	sf::Texture metTexture;
	if (!metTexture.loadFromFile("icons/metronome_icon.png")) {
		cout << "Unable to load metronome texture" << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	Note metNote("Metronome sound", metTexture, pink);

	const size_t MANSIZE = 13 * 64;
	vector<Note> mandachord;
	for (size_t i = 0; i < MANSIZE; i++) {
		if (i < MALSIZE) mandachord.push_back(malletNote);
		else if (i < MALSIZE + RESSIZE) mandachord.push_back(resNote);
		else mandachord.push_back(metNote);
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
				mandachord[i].play();
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