#include "button.hpp"
#include "mandachord.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;
#include <array>
using std::array;
#include <deque>
using std::deque;

/* -------------- TODO --------------
	* Add a structure for instrument packs
*/

int main() {
	/* ---------- Initialize the window ---------- */
	float viewX = 160, viewY = 90;
	float widthf = 1280, heightf = 720;
	sf::View view(sf::FloatRect(viewX, viewY, widthf, heightf));
	view.zoom(1.25f);
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

	/* ---------- Play button ---------- */
	sf::Text textPlay;
	textPlay.setFont(font);
	textPlay.setString("PLAY");
	textPlay.setCharacterSize(18);
	Button play(textPlay, sf::Color::White);

	// Instruments
	// TODO

	// ---------- Mandachord Megasection ----------
	Mandachord mandachord;

	/* ---------- Running application ---------- */
	while (window.isOpen())
	{
		mandachord.advance(play.isToggled());

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
				mandachord.checkMouse(window);
				play.checkMouse(window);
				break;
			case (sf::Event::Closed):
				window.close();
			default:
				break;
			}
		}

		mandachord.play();

		window.clear();
		window.draw(text);
		play.draw(window, 500, 5);
		float posX = 10, posY = 40;
		mandachord.draw(window, posX, posY);
		window.display();
	}

	/* ---------- Exit success ---------- */
	cout << "Exit success!" << endl;
	system("pause");
	return EXIT_SUCCESS;
}