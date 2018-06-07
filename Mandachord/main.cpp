#include "button.hpp"
#include "mandachord.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
using std::string;
using std::to_string;
#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <array>
using std::array;
#include <deque>
using std::deque;
#include <vector>
using std::vector;
#include <memory>
using std::shared_ptr;
using std::make_shared;

int main() {
	/* ---------- Initialize the window ---------- */
	float viewX = 160, viewY = 90;
	float widthf = 1280, heightf = 720;
	float viewOffsetX = 0.0f; // No need for a Y offset
	sf::View view(sf::FloatRect(viewX, viewY, widthf, heightf));
	view.zoom(1.25f);
	auto viewStartX = view.getCenter().x;
	unsigned int width = 1280, height = 720;
	sf::RenderWindow window(sf::VideoMode(width, height), "Mock Mandachord", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	window.setView(view);

	vector<shared_ptr<Button>> uiButtons;
	vector<shared_ptr<Button>> loopButtons;
	vector<shared_ptr<Button>> instrButtons;

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
	auto play = make_shared<Button>("PLAY", font, textSize, sf::Color::White);
	uiButtons.push_back(play);

	/* ---------- Save button ---------- */
	auto save = make_shared<Button>("SAVE", font, textSize, sf::Color::White);
	uiButtons.push_back(save);

	/* ---------- Load button ---------- */
	auto load = make_shared<Button>("LOAD", font, textSize, sf::Color::White);
	uiButtons.push_back(load);

	/* ---------- Mallets button ---------- */
	auto mallets = make_shared<Button>("MALLETS", font, textSize, sf::Color::White);
	uiButtons.push_back(mallets);

	/* ---------- Resonator button ---------- */
	auto resonator = make_shared<Button>("RESONATOR", font, textSize, sf::Color::White);
	uiButtons.push_back(resonator);

	/* ---------- Metronome button ---------- */
	auto metronome = make_shared<Button>("METRONOME", font, textSize, sf::Color::White);
	uiButtons.push_back(metronome);

	/* ---------- Loop button ---------- */
	string measure = "FULL";
	auto loop = make_shared<Button>("LOOP: " + measure, font, textSize, sf::Color::White);
	uiButtons.push_back(loop);

	/* ---------- Toggle Screen ---------- */
	sf::RectangleShape screen(sf::Vector2f(view.getSize()));
	screen.setFillColor(sf::Color(0, 128, 128, 255));

	/* ---------- Full loop button ---------- */
	auto measureAllButton = make_shared<Button>("FULL", font, textSize, sf::Color::White);
	loopButtons.push_back(measureAllButton);

	/* ---------- Measure 1 button ---------- */
	auto measure1Button = make_shared<Button>("1", font, textSize, sf::Color::White);
	loopButtons.push_back(measure1Button);

	/* ---------- Measure 2 button ---------- */
	auto measure2Button = make_shared<Button>("2", font, textSize, sf::Color::White);
	loopButtons.push_back(measure2Button);

	/* ---------- Measure 3 button ---------- */
	auto measure3Button = make_shared<Button>("3", font, textSize, sf::Color::White);
	loopButtons.push_back(measure3Button);

	/* ---------- Measure 4 button ---------- */
	auto measure4Button = make_shared<Button>("4", font, textSize, sf::Color::White);
	loopButtons.push_back(measure4Button);

	/* ---------- Adau button ---------- */
	auto adauButton = make_shared<Button>("ADAU", font, textSize, sf::Color::White);
	instrButtons.push_back(adauButton);

	/* ---------- Alpha button ---------- */
	auto alphaButton = make_shared<Button>("ALPHA", font, textSize, sf::Color::White);
	instrButtons.push_back(alphaButton);

	/* ---------- Beta button ---------- */
	auto betaButton = make_shared<Button>("BETA", font, textSize, sf::Color::White);
	instrButtons.push_back(betaButton);

	/* ---------- Delta button ---------- */
	auto deltaButton = make_shared<Button>("DELTA", font, textSize, sf::Color::White);
	instrButtons.push_back(deltaButton);

	/* ---------- Druk button ---------- */
	auto drukButton = make_shared<Button>("DRUK", font, textSize, sf::Color::White);
	instrButtons.push_back(drukButton);

	/* ---------- Epsilon button ---------- */
	auto epsilonButton = make_shared<Button>("EPSILON", font, textSize, sf::Color::White);
	instrButtons.push_back(epsilonButton);

	/* ---------- Gamma button ---------- */
	auto gammaButton = make_shared<Button>("GAMMA", font, textSize, sf::Color::White);
	instrButtons.push_back(gammaButton);

	/* ---------- Horos button ---------- */
	auto horosButton = make_shared<Button>("HOROS", font, textSize, sf::Color::White);
	instrButtons.push_back(horosButton);

	/* ---------- Plogg button ---------- */
	auto ploggButton = make_shared<Button>("PLOGG", font, textSize, sf::Color::White);
	instrButtons.push_back(ploggButton);

	/* ---------- Cancel button ---------- */
	auto cancel = make_shared<Button>("CANCEL", font, textSize, sf::Color::White);
	loopButtons.push_back(cancel);
	instrButtons.push_back(cancel);

	// ---------- Mandachord Megasection ----------
	Mandachord mandachord;
	unsigned int loopMeasure = 0;
	array<string, 10> instrTable = { "adau", "alpha", "beta", "delta", "druk", "epsilon", "gamma", "horos", "plogg", "cancel" };
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
		mandachord.advance(play->isToggled(), loopMeasure);

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case (sf::Event::KeyPressed):
				if (event.key.code == sf::Keyboard::Space) {
					play->toggle();
				}
				break;
			case (sf::Event::MouseWheelScrolled):
				if (event.mouseWheelScroll.delta > 0) {
					if (!(view.getCenter().x - 20 < viewStartX)) {
						view.move(-20, 0);
						window.setView(view);
						viewOffsetX -= 20;
					}
				}
				else if (event.mouseWheelScroll.delta < 0) {
					if (!(view.getCenter().x + 20 > (4 * 16 * 60 - 13 * 60))) {
						view.move(20, 0);
						window.setView(view);
						viewOffsetX += 20;
					}
				}
				break;
			case (sf::Event::MouseButtonPressed):
				if (loop->isToggled() && mallets->isToggled() && resonator->isToggled() && metronome->isToggled() && save->isToggled() && load->isToggled()) {
					mandachord.checkMouse(window);
					for (unsigned int i = 0; i < uiButtons.size(); i++)
						uiButtons[i]->checkMouse(window);
				}
				else if (!loop->isToggled()) {
					for (auto i : loopButtons)
						i->checkMouse(window);
				}
				else if (!mallets->isToggled() || !resonator->isToggled() || !metronome->isToggled()) {
					for (auto i : instrButtons)
						i->checkMouse(window);
				}
				else {
					cancel->checkMouse(window);
				}
				break;
			case (sf::Event::TextEntered):
				if (event.text.unicode == '\b' && input.getSize() > 0) {
					input.erase(input.getSize() - 1, 1);
					inputDisplay.setString(input);
				}
				else if (event.text.unicode < 128 && event.text.unicode != '\b' && event.text.unicode != '\r') {
					input += event.text.unicode;
					inputDisplay.setString(input);
				}
				else if (event.text.unicode == '\r' && input.getSize() > 0) {
					if (!save->isToggled() || !load->isToggled()) {
						string path = "songs/" + input.toAnsiString() + ".uwu";
						ofstream outToFile;
						if (!save->isToggled()) {
							outToFile.open(path, std::ios::binary);
							if (outToFile.is_open()) {
								mandachord.saveToFile(outToFile, currentMallets, currentResonator, currentMetronome);
								outToFile.close();
							}
							else cout << "Could not write to file: " << path << endl;
							save->toggle();
						}
						else if (!load->isToggled()) {
							ifstream inFromFile(path, std::ios::binary);
							if (inFromFile.is_open()) {
								mandachord.loadFmFile(inFromFile, currentMallets, currentResonator, currentMetronome);
								inFromFile.close();
							}
							else cout << "Could not open file: " << path << endl;
							load->toggle();
						}
						input.clear();
						inputDisplay.setString(input);
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
		float butposX = 5, butposY = 820;
		for (unsigned int i = 0; i < uiButtons.size(); i++) {
			uiButtons[i]->draw(window, butposX, butposY);
			butposX += uiButtons[i]->getPos().width + 15;
		}
		float manposX = 10, manposY = 40;
		mandachord.draw(window, manposX, manposY);
		if (!loop->isToggled()) {
			screen.setPosition(view.getViewport().left + viewOffsetX, view.getViewport().top);
			window.draw(screen);
			float loopposX = 10, loopposY = 25;
			for (unsigned int i = 0; i < loopButtons.size(); i++) {
				loopButtons[i]->draw(window, loopposX + viewOffsetX, loopposY);
				loopposY += loopButtons[i]->getPos().height + 25;
			}
			for (unsigned int i = 0; i < loopButtons.size(); i++) {
				if (!loopButtons[i]->isToggled()) {
					if (i < loopButtons.size() - 1) {
						if (i == 0) measure = "FULL";
						else measure = to_string(i);
						loop->updateText("LOOP: " + measure);
						loopMeasure = i;
						loop->toggle();
						loopButtons[i]->toggle();
					}
					else {
						loop->toggle();
						cancel->toggle();
					}
				}
			}
		}
		if (!mallets->isToggled() || !resonator->isToggled() || !metronome->isToggled()) {
			screen.setPosition(view.getViewport().left + viewOffsetX, view.getViewport().top);
			window.draw(screen);
			float loopposX = 10, loopposY = 25;
			for (unsigned int i = 0; i < instrButtons.size(); i++) {
				instrButtons[i]->draw(window, loopposX, loopposY);
				loopposY += instrButtons[i]->getPos().height + 30;
			}
			if (!mallets->isToggled()) {
				for (unsigned int i = 0; i < instrButtons.size(); i++) {
					if (!instrButtons[i]->isToggled()) {
						if (i < instrButtons.size() - 1) {
							mandachord.changeMallets(instrTable[i]);
							currentMallets = instrTable[i];
							mallets->toggle();
							instrButtons[i]->toggle();
						}
						else {
							mallets->toggle();
							cancel->toggle();
						}
					}
				}
			}
			else if (!resonator->isToggled()) {
				for (unsigned int i = 0; i < instrButtons.size(); i++) {
					if (!instrButtons[i]->isToggled()) {
						if (i < instrButtons.size() - 1) {
							mandachord.changeResonator(instrTable[i]);
							currentResonator = instrTable[i];
							resonator->toggle();
							instrButtons[i]->toggle();
						}
						else {
							resonator->toggle();
							cancel->toggle();
						}
					}
				}
			}
			else if (!metronome->isToggled()) {
				for (unsigned int i = 0; i < instrButtons.size(); i++) {
					if (!instrButtons[i]->isToggled()) {
						if (i < instrButtons.size() - 1) {
							mandachord.changeMetronome(instrTable[i]);
							currentMetronome = instrTable[i];
							metronome->toggle();
							instrButtons[i]->toggle();
						}
						else {
							metronome->toggle();
							cancel->toggle();
						}
					}
				}
			}
		}
		else if (!save->isToggled()) {
			screen.setPosition(view.getViewport().left + viewOffsetX, view.getViewport().top);
			window.draw(screen);
			inputPrompt.setPosition(100, 200);
			window.draw(inputPrompt);
			inputDisplay.setPosition(inputPrompt.getGlobalBounds().width + 100, 200);
			window.draw(inputDisplay);
			cancel->draw(window, view.getSize().x - 140, view.getSize().y - 50);
			if (!cancel->isToggled()) {
				save->toggle();
				cancel->toggle();
				input.clear();
				inputDisplay.setString(input);
			}
		}
		else if (!load->isToggled()) {
			screen.setPosition(view.getViewport().left + viewOffsetX, view.getViewport().top);
			window.draw(screen);
			inputPrompt.setPosition(100, 200);
			window.draw(inputPrompt);
			inputDisplay.setPosition(inputPrompt.getGlobalBounds().width + 100, 200);
			window.draw(inputDisplay);
			cancel->draw(window, view.getSize().x - 140, view.getSize().y - 50);
			if (!cancel->isToggled()) {
				load->toggle();
				cancel->toggle();
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