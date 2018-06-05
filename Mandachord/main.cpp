#include "button.hpp"
#include "mandachord.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::fstream;
using std::ifstream;
using std::ofstream;
#include <array>
using std::array;
#include <deque>
using std::deque;

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
	/* ---------- Fan font ---------- */
	sf::Font font;
	if (!font.loadFromFile("fonts/DroidSans.ttf")) {
		cout << "Unable to load font" << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	/* ---------- Text caption ---------- */
	unsigned int captionSize = 30;
	
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(captionSize);
	text.setStyle(sf::Text::Bold);
	text.setString("MANDACHORD MOCK");

	unsigned int textSize = 20;

	/* ---------- Play button ---------- */
	Button play("PLAY", font, textSize, sf::Color::White);

	/* ---------- Save button ---------- */
	Button save("SAVE", font, textSize, sf::Color::White);

	/* ---------- Load button ---------- */
	Button load("LOAD", font, textSize, sf::Color::White);

	/* ---------- Mallets button ---------- */
	Button mallets("MALLETS", font, textSize, sf::Color::White);

	/* ---------- Resonator button ---------- */
	Button resonator("RESONATOR", font, textSize, sf::Color::White);

	/* ---------- Metronome button ---------- */
	Button metronome("METRONOME", font, textSize, sf::Color::White);

	/* ---------- Loop button ---------- */
	string measure = "FULL";
	Button loop("LOOP: " + measure, font, textSize, sf::Color::White);

	/* ---------- Toggle Screen ---------- */
	sf::RectangleShape screen(sf::Vector2f(view.getSize()));
	screen.setFillColor(sf::Color(0, 128, 128, 255));

	/* ---------- Measure 1 button ---------- */
	Button measure1Button("1", font, textSize, sf::Color::White);

	/* ---------- Measure 2 button ---------- */
	Button measure2Button("2", font, textSize, sf::Color::White);

	/* ---------- Measure 3 button ---------- */
	Button measure3Button("3", font, textSize, sf::Color::White);

	/* ---------- Measure 4 button ---------- */
	Button measure4Button("4", font, textSize, sf::Color::White);

	/* ---------- Full loop button ---------- */
	Button measureAllButton("FULL", font, textSize, sf::Color::White);

	/* ---------- Adau button ---------- */
	Button adauButton("ADAU", font, textSize, sf::Color::White);

	/* ---------- Alpha button ---------- */
	Button alphaButton("ALPHA", font, textSize, sf::Color::White);

	/* ---------- Beta button ---------- */
	Button betaButton("BETA", font, textSize, sf::Color::White);

	/* ---------- Delta button ---------- */
	Button deltaButton("DELTA", font, textSize, sf::Color::White);

	/* ---------- Druk button ---------- */
	Button drukButton("DRUK", font, textSize, sf::Color::White);

	/* ---------- Epsilon button ---------- */
	Button epsilonButton("EPSILON", font, textSize, sf::Color::White);

	/* ---------- Gamma button ---------- */
	Button gammaButton("GAMMA", font, textSize, sf::Color::White);

	/* ---------- Horos button ---------- */
	Button horosButton("HOROS", font, textSize, sf::Color::White);

	/* ---------- Plogg button ---------- */
	Button ploggButton("PLOGG", font, textSize, sf::Color::White);

	/* ---------- Cancel button ---------- */
	Button cancel("CANCEL", font, textSize, sf::Color::White);

	// ---------- Mandachord Megasection ----------
	Mandachord mandachord;
	unsigned int loopMeasure = 0;
	string currentMallets = "adau";
	string currentResonator = "adau";
	string currentMetronome = "adau";

	/* ---------- File IO stuff ---------- */
	sf::String input;
	sf::Text inputDisplay;
	inputDisplay.setFont(font);
	inputDisplay.setCharacterSize(captionSize);

	sf::Text inputPrompt;
	inputPrompt.setFont(font);
	inputPrompt.setCharacterSize(captionSize);
	inputPrompt.setStyle(sf::Text::Bold);
	inputPrompt.setString("FILENAME: ");

	/* ---------- Running application ---------- */
	while (window.isOpen())
	{
		mandachord.advance(play.isToggled(), loopMeasure);

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case (sf::Event::KeyPressed):
				if (event.key.code == sf::Keyboard::Space) {
					play.toggle();
				}
				break;
			case (sf::Event::MouseWheelScrolled):
				if (event.mouseWheelScroll.delta > 0) {
					view.move(-10, 0);
					window.setView(view);
				}
				else if (event.mouseWheelScroll.delta < 0) {
					view.move(10, 0);
					window.setView(view);
				}
				break;
			case (sf::Event::MouseButtonPressed):
				if (loop.isToggled() && mallets.isToggled() && resonator.isToggled() && metronome.isToggled() && save.isToggled() && load.isToggled()) {
					mandachord.checkMouse(window);
					play.checkMouse(window);
					save.checkMouse(window);
					load.checkMouse(window);
					loop.checkMouse(window);
					mallets.checkMouse(window);
					resonator.checkMouse(window);
					metronome.checkMouse(window);
				}
				else {
					measure1Button.checkMouse(window);
					measure2Button.checkMouse(window);
					measure3Button.checkMouse(window);
					measure4Button.checkMouse(window);
					measureAllButton.checkMouse(window);
					adauButton.checkMouse(window);
					alphaButton.checkMouse(window);
					betaButton.checkMouse(window);
					deltaButton.checkMouse(window);
					drukButton.checkMouse(window);
					epsilonButton.checkMouse(window);
					gammaButton.checkMouse(window);
					horosButton.checkMouse(window);
					ploggButton.checkMouse(window);
					cancel.checkMouse(window);
				}
				break;
			case (sf::Event::TextEntered):
				if (!save.isToggled()) {
					if (event.text.unicode == '\b' && input.getSize() > 0) {
						input.erase(input.getSize() - 1, 1);
						inputDisplay.setString(input);
					}
					else if (event.text.unicode < 128 && event.text.unicode != '\b' && event.text.unicode != '\r') {
						input += event.text.unicode;
						inputDisplay.setString(input);
					}
					else if (event.text.unicode == '\r' && input.getSize() > 0) {
						string path = "songs/" + input.toAnsiString() + ".uwu";
						ofstream outToFile;
						outToFile.open(path);
						if (outToFile.is_open()) {
							mandachord.saveToFile(outToFile, currentMallets, currentResonator, currentMetronome);
							outToFile.close();
						}
						else cout << "Could not write to file: " << path << endl;
						input.clear();
						inputDisplay.setString(input);
						save.toggle();
					}
				}
				else if (!load.isToggled()) {
					if (event.text.unicode == '\b' && input.getSize() > 0) {
						input.erase(input.getSize() - 1, 1);
						inputDisplay.setString(input);
					}
					else if (event.text.unicode < 128 && event.text.unicode != '\b' && event.text.unicode != '\r') {
						input += event.text.unicode;
						inputDisplay.setString(input);
					}
					else if (event.text.unicode == '\r' && input.getSize() > 0) {
						string path = "songs/" + input.toAnsiString() + ".uwu";
						ifstream inFromFile(path);
						if (inFromFile.is_open()) {
							mandachord.loadFmFile(inFromFile, currentMallets, currentResonator, currentMetronome);
							inFromFile.close();
						}
						else cout << "Could not open file: " << path << endl;
						input.clear();
						inputDisplay.setString(input);
						load.toggle();
					}
				}
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
		save.draw(window, 600, 5);
		load.draw(window, 700, 5);
		loop.draw(window, 800, 5);
		mallets.draw(window, 5, 820);
		resonator.draw(window, mallets.getPos().width + 10, 820);
		metronome.draw(window, mallets.getPos().width + resonator.getPos().width + 15, 820);
		float posX = 10, posY = 40;
		mandachord.draw(window, posX, posY);
		if (!loop.isToggled()) {
			window.draw(screen);
			measure1Button.draw(window, 10, 25);
			measure2Button.draw(window, 10, 55);
			measure3Button.draw(window, 10, 85);
			measure4Button.draw(window, 10, 115);
			measureAllButton.draw(window, 10, 145);
			cancel.draw(window, view.getSize().x - 140, view.getSize().y - 50);
			if (!measure1Button.isToggled()) {
				measure = "1";
				loop.updateText("LOOP: " + measure);
				loopMeasure = 1;
				loop.toggle();
				measure1Button.toggle();
			}
			else if (!measure2Button.isToggled()) {
				measure = "2";
				loop.updateText("LOOP: " + measure);
				loopMeasure = 2;
				loop.toggle();
				measure2Button.toggle();
			}
			else if (!measure3Button.isToggled()) {
				measure = "3";
				loop.updateText("LOOP: " + measure);
				loopMeasure = 3;
				loop.toggle();
				measure3Button.toggle();
			}
			else if (!measure4Button.isToggled()) {
				measure = "4";
				loop.updateText("LOOP: " + measure);
				loopMeasure = 4;
				loop.toggle();
				measure4Button.toggle();
			}
			else if (!measureAllButton.isToggled()) {
				measure = "FULL";
				loop.updateText("LOOP: " + measure);
				loopMeasure = 0;
				loop.toggle();
				measureAllButton.toggle();
			}
			else if (!cancel.isToggled()) {
				loop.toggle();
				cancel.toggle();
			}
		}
		if (!mallets.isToggled()) {
			window.draw(screen);
			adauButton.draw(window, 10, 25);
			alphaButton.draw(window, 10, 55);
			betaButton.draw(window, 10, 85);
			deltaButton.draw(window, 10, 115);
			drukButton.draw(window, 10, 145);
			epsilonButton.draw(window, 10, 175);
			gammaButton.draw(window, 10, 205);
			horosButton.draw(window, 10, 235);
			ploggButton.draw(window, 10, 265);
			cancel.draw(window, 10, 295);
			if (!adauButton.isToggled()) {
				mandachord.changeMallets("adau");
				currentMallets = "adau";
				mallets.toggle();
				adauButton.toggle();
			}
			else if (!alphaButton.isToggled()) {
				mandachord.changeMallets("alpha");
				currentMallets = "alpha";
				mallets.toggle();
				alphaButton.toggle();
			}
			else if (!betaButton.isToggled()) {
				mandachord.changeMallets("beta");
				currentMallets = "beta";
				mallets.toggle();
				betaButton.toggle();
			}
			else if (!deltaButton.isToggled()) {
				mandachord.changeMallets("delta");
				currentMallets = "delta";
				mallets.toggle();
				deltaButton.toggle();
			}
			else if (!drukButton.isToggled()) {
				mandachord.changeMallets("druk");
				currentMallets = "druk";
				mallets.toggle();
				drukButton.toggle();
			}
			else if (!epsilonButton.isToggled()) {
				mandachord.changeMallets("epsilon");
				currentMallets = "epsilon";
				mallets.toggle();
				epsilonButton.toggle();
			}
			else if (!gammaButton.isToggled()) {
				mandachord.changeMallets("gamma");
				currentMallets = "gamma";
				mallets.toggle();
				gammaButton.toggle();
			}
			else if (!horosButton.isToggled()) {
				mandachord.changeMallets("horos");
				currentMallets = "horos";
				mallets.toggle();
				horosButton.toggle();
			}
			else if (!ploggButton.isToggled()) {
				mandachord.changeMallets("plogg");
				currentMallets = "plogg";
				mallets.toggle();
				ploggButton.toggle();
			}
			else if (!cancel.isToggled()) {
				mallets.toggle();
				cancel.toggle();
			}
		}
		else if (!resonator.isToggled()) {
			window.draw(screen);
			adauButton.draw(window, 10, 25);
			alphaButton.draw(window, 10, 55);
			betaButton.draw(window, 10, 85);
			deltaButton.draw(window, 10, 115);
			drukButton.draw(window, 10, 145);
			epsilonButton.draw(window, 10, 175);
			gammaButton.draw(window, 10, 205);
			horosButton.draw(window, 10, 235);
			ploggButton.draw(window, 10, 265);
			cancel.draw(window, 10, 295);
			if (!adauButton.isToggled()) {
				mandachord.changeResonator("adau");
				currentResonator = "adau";
				resonator.toggle();
				adauButton.toggle();
			}
			else if (!alphaButton.isToggled()) {
				mandachord.changeResonator("alpha");
				currentResonator = "alpha";
				resonator.toggle();
				alphaButton.toggle();
			}
			else if (!betaButton.isToggled()) {
				mandachord.changeResonator("beta");
				currentResonator = "beta";
				resonator.toggle();
				betaButton.toggle();
			}
			else if (!deltaButton.isToggled()) {
				mandachord.changeResonator("delta");
				currentResonator = "delta";
				resonator.toggle();
				deltaButton.toggle();
			}
			else if (!drukButton.isToggled()) {
				mandachord.changeResonator("druk");
				currentResonator = "druk";
				resonator.toggle();
				drukButton.toggle();
			}
			else if (!epsilonButton.isToggled()) {
				mandachord.changeResonator("epsilon");
				currentResonator = "epsilon";
				resonator.toggle();
				epsilonButton.toggle();
			}
			else if (!gammaButton.isToggled()) {
				mandachord.changeResonator("gamma");
				currentResonator = "gamma";
				resonator.toggle();
				gammaButton.toggle();
			}
			else if (!horosButton.isToggled()) {
				mandachord.changeResonator("horos");
				currentResonator = "horos";
				resonator.toggle();
				horosButton.toggle();
			}
			else if (!ploggButton.isToggled()) {
				mandachord.changeResonator("plogg");
				currentResonator = "plogg";
				resonator.toggle();
				ploggButton.toggle();
			}
			else if (!cancel.isToggled()) {
				resonator.toggle();
				cancel.toggle();
			}
		}
		else if (!metronome.isToggled()) {
			window.draw(screen);
			adauButton.draw(window, 10, 25);
			alphaButton.draw(window, 10, 55);
			betaButton.draw(window, 10, 85);
			deltaButton.draw(window, 10, 115);
			drukButton.draw(window, 10, 145);
			epsilonButton.draw(window, 10, 175);
			gammaButton.draw(window, 10, 205);
			horosButton.draw(window, 10, 235);
			ploggButton.draw(window, 10, 265);
			cancel.draw(window, 10, 295);
			if (!adauButton.isToggled()) {
				mandachord.changeMetronome("adau");
				currentMetronome = "adau";
				metronome.toggle();
				adauButton.toggle();
			}
			else if (!alphaButton.isToggled()) {
				mandachord.changeMetronome("alpha");
				currentMetronome = "alpha";
				metronome.toggle();
				alphaButton.toggle();
			}
			else if (!betaButton.isToggled()) {
				mandachord.changeMetronome("beta");
				currentMetronome = "beta";
				metronome.toggle();
				betaButton.toggle();
			}
			else if (!deltaButton.isToggled()) {
				mandachord.changeMetronome("delta");
				currentMetronome = "delta";
				metronome.toggle();
				deltaButton.toggle();
			}
			else if (!drukButton.isToggled()) {
				mandachord.changeMetronome("druk");
				currentMetronome = "druk";
				metronome.toggle();
				drukButton.toggle();
			}
			else if (!epsilonButton.isToggled()) {
				mandachord.changeMetronome("epsilon");
				currentMetronome = "epsilon";
				metronome.toggle();
				epsilonButton.toggle();
			}
			else if (!gammaButton.isToggled()) {
				mandachord.changeMetronome("gamma");
				currentMetronome = "gamma";
				metronome.toggle();
				gammaButton.toggle();
			}
			else if (!horosButton.isToggled()) {
				mandachord.changeMetronome("horos");
				currentMetronome = "horos";
				metronome.toggle();
				horosButton.toggle();
			}
			else if (!ploggButton.isToggled()) {
				mandachord.changeMetronome("plogg");
				currentMetronome = "plogg";
				metronome.toggle();
				ploggButton.toggle();
			}
			else if (!cancel.isToggled()) {
				metronome.toggle();
				cancel.toggle();
			}
		}
		else if (!save.isToggled()) {
			window.draw(screen);
			inputPrompt.setPosition(100, 200);
			window.draw(inputPrompt);
			inputDisplay.setPosition(inputPrompt.getGlobalBounds().width + 100, 200);
			window.draw(inputDisplay);
			cancel.draw(window, view.getSize().x - 140, view.getSize().y - 50);
			if (!cancel.isToggled()) {
				save.toggle();
				cancel.toggle();
				input.clear();
				inputDisplay.setString(input);
			}
		}
		else if (!load.isToggled()) {
			window.draw(screen);
			inputPrompt.setPosition(100, 200);
			window.draw(inputPrompt);
			inputDisplay.setPosition(inputPrompt.getGlobalBounds().width + 100, 200);
			window.draw(inputDisplay);
			cancel.draw(window, view.getSize().x - 140, view.getSize().y - 50);
			if (!cancel.isToggled()) {
				load.toggle();
				cancel.toggle();
				input.clear();
				inputDisplay.setString(input);
			}
		}
		window.display();
	}

	/* ---------- Exit success ---------- */
	cout << "Exit success!" << endl;
	system("pause");
	return EXIT_SUCCESS;
}