#include "button.hpp"
#include "mandachord.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <algorithm>
using std::transform;
#include <string>
using std::string;
using std::to_string;
#include <cctype>
using std::toupper;
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
#include <functional>
using std::bind;

void mandachordThread(sf::RenderWindow * window,
					sf::View * view,
					array<sf::View, 3> * viewPresets,
					float * viewOffsetX,
					sf::Event * event, 
					Mandachord * mandachord, 
					unsigned int * loopMeasure, 
					string * currentMallets, 
					string * currentResonator,
					string * currentMetronome,
					array<string, 10> * instrTable,
					sf::RectangleShape * screen, 
					sf::RectangleShape * inputField,
					sf::Text * text, 
					sf::Text * inputPrompt, 
					sf::Text * inputDisplay, 
					sf::Text * errorPrompt,
					sf::Text * clearPrompt, 
					sf::String * input, 
					bool * isOverMaxNotes, 
					vector<shared_ptr<Button>> * uiButtons, 
					vector<shared_ptr<Button>> * loopButtons, 
					vector<shared_ptr<Button>> * instrButtons, 
					vector<shared_ptr<Button>> * clearButtons, 
					vector<shared_ptr<Button>> * optionButtons) {
	/* ---------- Initialize the window ---------- */
	window->setActive(true);
	window->setView(*view);
	window->setFramerateLimit(60);

	/* ---------- Running application ---------- */
	while (window->isOpen()) {
		mandachord->advance(uiButtons->at(0)->isToggled(), *loopMeasure);
		
		mandachord->play();

		window->clear();
		window->draw(*text);
		float butposX = 5, butposY = 820;
		for (unsigned int i = 0; i < uiButtons->size(); i++) {
			uiButtons->at(i)->draw(*window, butposX + *viewOffsetX, butposY);
			butposX += uiButtons->at(i)->getPos().width + 15;
		}
		float manposX = 10, manposY = 40;
		mandachord->draw(*window, manposX, manposY);
		if (!uiButtons->at(1)->isToggled() || !uiButtons->at(2)->isToggled()) {
			screen->setPosition(view->getViewport().left + *viewOffsetX, view->getViewport().top);
			window->draw(*screen);
			inputPrompt->setPosition(100 + *viewOffsetX, 200);
			window->draw(*inputPrompt);
			inputField->setPosition(inputPrompt->getGlobalBounds().width + 95 + *viewOffsetX, 200);
			window->draw(*inputField);
			inputDisplay->setPosition(inputPrompt->getGlobalBounds().width + 100 + *viewOffsetX, 200);
			window->draw(*inputDisplay);
			clearButtons->at(1)->draw(*window, view->getSize().x - 140 + *viewOffsetX, view->getSize().y - 50);
			if (!clearButtons->at(1)->isToggled()) {
				if (!uiButtons->at(1)->isToggled())
					uiButtons->at(1)->toggle();
				else if (!uiButtons->at(2)->isToggled())
					uiButtons->at(2)->toggle();
				clearButtons->at(1)->toggle();
				input->clear();
				inputDisplay->setString(*input);
			}
		}
		else if (!uiButtons->at(3)->isToggled() || !uiButtons->at(4)->isToggled() || !uiButtons->at(5)->isToggled()) {
			screen->setPosition(view->getViewport().left + *viewOffsetX, view->getViewport().top);
			window->draw(*screen);
			float loopposX = 10, loopposY = 25;
			for (unsigned int i = 0; i < instrButtons->size(); i++) {
				instrButtons->at(i)->draw(*window, loopposX + *viewOffsetX, loopposY);
				loopposY += instrButtons->at(i)->getPos().height + 30;
			}
			if (!uiButtons->at(3)->isToggled()) {
				for (unsigned int i = 0; i < instrButtons->size(); i++) {
					if (!instrButtons->at(i)->isToggled()) {
						if (i < instrButtons->size() - 1) {
							mandachord->changeMallets(instrTable->at(i));
							*currentMallets = instrTable->at(i);
							transform(currentMallets->begin(), currentMallets->end(), currentMallets->begin(), [&](unsigned char c) { return toupper(c); });
							uiButtons->at(3)->updateText("MALLETS: " + *currentMallets);
							uiButtons->at(3)->toggle();
							instrButtons->at(i)->toggle();
						}
						else {
							uiButtons->at(3)->toggle();
							instrButtons->at(i)->toggle();
						}
					}
				}
			}
			else if (!uiButtons->at(4)->isToggled()) {
				for (unsigned int i = 0; i < instrButtons->size(); i++) {
					if (!instrButtons->at(i)->isToggled()) {
						if (i < instrButtons->size() - 1) {
							mandachord->changeResonator(instrTable->at(i));
							*currentResonator = instrTable->at(i);
							transform(currentResonator->begin(), currentResonator->end(), currentResonator->begin(), [&](unsigned char c) { return toupper(c); });
							uiButtons->at(4)->updateText("RESONATOR: " + *currentResonator);
							uiButtons->at(4)->toggle();
							instrButtons->at(i)->toggle();
						}
						else {
							uiButtons->at(4)->toggle();
							instrButtons->at(i)->toggle();
						}
					}
				}
			}
			else if (!uiButtons->at(5)->isToggled()) {
				for (unsigned int i = 0; i < instrButtons->size(); i++) {
					if (!instrButtons->at(i)->isToggled()) {
						if (i < instrButtons->size() - 1) {
							mandachord->changeMetronome(instrTable->at(i));
							*currentMetronome = instrTable->at(i);
							transform(currentMetronome->begin(), currentMetronome->end(), currentMetronome->begin(), [&](unsigned char c) { return toupper(c); });
							uiButtons->at(5)->updateText("METRONOME: " + *currentMetronome);
							uiButtons->at(5)->toggle();
							instrButtons->at(i)->toggle();
						}
						else {
							uiButtons->at(5)->toggle();
							instrButtons->at(i)->toggle();
						}
					}
				}
			}
		}
		else if (!uiButtons->at(6)->isToggled()) {
			screen->setPosition(view->getViewport().left + *viewOffsetX, view->getViewport().top);
			window->draw(*screen);
			float loopposX = 10, loopposY = 25;
			for (unsigned int i = 0; i < loopButtons->size(); i++) {
				loopButtons->at(i)->draw(*window, loopposX + *viewOffsetX, loopposY);
				loopposY += loopButtons->at(i)->getPos().height + 25;
			}
			for (unsigned int i = 0; i < loopButtons->size(); i++) {
				if (!loopButtons->at(i)->isToggled()) {
					if (i < loopButtons->size() - 1) {
						uiButtons->at(6)->updateText("LOOP: " + loopButtons->at(i)->getText());
						*loopMeasure = i;
						uiButtons->at(6)->toggle();
						loopButtons->at(i)->toggle();
					}
					else {
						uiButtons->at(6)->toggle();
						loopButtons->at(i)->toggle();
					}
				}
			}
		}
		else if (!uiButtons->at(7)->isToggled()) {
			screen->setPosition(view->getViewport().left + *viewOffsetX, view->getViewport().top);
			window->draw(*screen);
			clearPrompt->setPosition((view->getViewport().left + *viewOffsetX) + window->getSize().x / 2, view->getViewport().top + window->getSize().y / 2);
			window->draw(*clearPrompt);
			clearButtons->at(0)->draw(*window, view->getSize().x - clearButtons->at(0)->getPos().width - 160 + *viewOffsetX, view->getSize().y - 50);
			clearButtons->at(1)->draw(*window, view->getSize().x - 140 + *viewOffsetX, view->getSize().y - 50);
			if (!clearButtons->at(0)->isToggled()) {
				mandachord->clear();
				uiButtons->at(7)->toggle();
				clearButtons->at(0)->toggle();
			}
			else if (!clearButtons->at(1)->isToggled()) {
				uiButtons->at(7)->toggle();
				clearButtons->at(1)->toggle();
			}
		}
		else if (!uiButtons->at(8)->isToggled()) {
			screen->setPosition(view->getViewport().left + *viewOffsetX, view->getViewport().top);
			window->draw(*screen);
			float loopposX = 10, loopposY = 25;
			for (unsigned int i = 0; i < optionButtons->size(); i++) {
				optionButtons->at(i)->draw(*window, loopposX + *viewOffsetX, loopposY);
				loopposY += optionButtons->at(i)->getPos().height + 30;
			}
			if (!optionButtons->at(0)->isToggled()) {
				window->setSize(sf::Vector2u(1280, 720));
				*view = viewPresets->at(0);
				view->zoom(1.25f);
				window->setView(*view);
				screen->setSize(view->getSize());
				uiButtons->at(8)->toggle();
				optionButtons->at(0)->toggle();
			}
			else if (!optionButtons->at(1)->isToggled()) {
				window->setSize(sf::Vector2u(1600, 900));
				*view = viewPresets->at(1);
				view->zoom(1.0f);
				window->setView(*view);
				screen->setSize(view->getSize());
				uiButtons->at(8)->toggle();
				optionButtons->at(1)->toggle();
			}
			else if (!optionButtons->at(2)->isToggled()) {
				window->setSize(sf::Vector2u(1920, 1080));
				*view = viewPresets->at(2);
				view->zoom(0.875f);
				window->setView(*view);
				screen->setSize(view->getSize());
				uiButtons->at(8)->toggle();
				optionButtons->at(2)->toggle();
			}
			else if (!optionButtons->at(3)->isToggled()) {
				uiButtons->at(8)->toggle();
				optionButtons->at(3)->toggle();
			}
		}
		else if (*isOverMaxNotes) {
			screen->setPosition(view->getViewport().left + *viewOffsetX, view->getViewport().top);
			window->draw(*screen);
			errorPrompt->setPosition((view->getViewport().left + *viewOffsetX) + window->getSize().x / 2, view->getViewport().top + window->getSize().y / 2);
			window->draw(*errorPrompt);
			clearButtons->at(0)->draw(*window, view->getSize().x - 140 + *viewOffsetX, view->getSize().y - 50);
			if (!clearButtons->at(0)->isToggled()) {
				*isOverMaxNotes = false;
				clearButtons->at(0)->toggle();
			}
		}
		window->display();
	}
}

int WinMain() {
	array<sf::View, 3> viewPresets = { sf::View(sf::FloatRect(160, 90, 1280, 720)), sf::View(sf::FloatRect(0, 0, 1600, 900)), sf::View(sf::FloatRect(-120, -65, 1920, 1080)) };
	sf::View view;
	view = viewPresets[0];
	view.zoom(1.25f);
	float viewOffsetX = 0.0f; // No need for a Y offset
	
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Mock Mandachord", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	vector<shared_ptr<Button>> uiButtons;
	vector<shared_ptr<Button>> loopButtons;
	vector<shared_ptr<Button>> instrButtons;
	vector<shared_ptr<Button>> clearButtons;
	vector<shared_ptr<Button>> optionButtons;

	/* ---------- Generate the stuff that goes on the screen ---------- */
	/* ---------- Fan font ---------- */
	sf::Font font;
	if (!font.loadFromFile("fonts/DroidSans.ttf")) {
		cout << "Unable to load font" << endl;
		system("pause");
		throw EXIT_FAILURE;
	}

	/* ---------- Text caption ---------- */
	unsigned int captionSize = 30;

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(captionSize);
	text.setStyle(sf::Text::Bold);
	text.setString("MANDACHORD MOCK");

	unsigned int textSize = 20;

	// ---------- Mandachord Megasection ----------
	Mandachord mandachord;
	unsigned int loopMeasure = 0;
	array<string, 10> instrTable = { "adau", "alpha", "beta", "delta", "druk", "epsilon", "gamma", "horos", "plogg", "cancel" };
	string currentMallets = "ADAU";
	string currentResonator = "ADAU";
	string currentMetronome = "ADAU";

	/* ---------- Play button ---------- */
	auto play = make_shared<Button>("PAUSE", font, textSize, sf::Color::White);
	uiButtons.push_back(play);

	/* ---------- Save button ---------- */
	auto save = make_shared<Button>("SAVE", font, textSize, sf::Color::White);
	uiButtons.push_back(save);

	/* ---------- Load button ---------- */
	auto load = make_shared<Button>("LOAD", font, textSize, sf::Color::White);
	uiButtons.push_back(load);

	/* ---------- Mallets button ---------- */
	auto mallets = make_shared<Button>("MALLETS: " + currentMallets, font, textSize, sf::Color::White);
	uiButtons.push_back(mallets);

	/* ---------- Resonator button ---------- */
	auto resonator = make_shared<Button>("RESONATOR: " + currentResonator, font, textSize, sf::Color::White);
	uiButtons.push_back(resonator);

	/* ---------- Metronome button ---------- */
	auto metronome = make_shared<Button>("METRONOME: " + currentMetronome, font, textSize, sf::Color::White);
	uiButtons.push_back(metronome);

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

	/* ---------- Loop button ---------- */
	auto loop = make_shared<Button>("LOOP: FULL", font, textSize, sf::Color::White);
	uiButtons.push_back(loop);

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

	/* ---------- Measures 1 - 2 button ---------- */
	auto measure12Button = make_shared<Button>("1 - 2", font, textSize, sf::Color::White);
	loopButtons.push_back(measure12Button);

	/* ---------- Measures 2 - 3 button ---------- */
	auto measure23Button = make_shared<Button>("2 - 3", font, textSize, sf::Color::White);
	loopButtons.push_back(measure23Button);

	/* ---------- Measures 3 - 4 button ---------- */
	auto measure34Button = make_shared<Button>("3 - 4", font, textSize, sf::Color::White);
	loopButtons.push_back(measure34Button);

	/* ---------- Measures 1 - 2 - 3 button ---------- */
	auto measure123Button = make_shared<Button>("1 - 2 - 3", font, textSize, sf::Color::White);
	loopButtons.push_back(measure123Button);

	/* ---------- Measures 2 - 3 - 4 button ---------- */
	auto measure234Button = make_shared<Button>("2 - 3 - 4", font, textSize, sf::Color::White);
	loopButtons.push_back(measure234Button);

	/* ---------- Clear button ---------- */
	auto clear = make_shared<Button>("CLEAR", font, textSize, sf::Color::White);
	uiButtons.push_back(clear);

	/* ---------- Confirm button ---------- */
	auto confirm = make_shared<Button>("CONFIRM", font, textSize, sf::Color::White);
	clearButtons.push_back(confirm);

	/* ---------- Options button ---------- */
	auto options = make_shared<Button>("OPTIONS", font, textSize, sf::Color::White);
	uiButtons.push_back(options);

	/* ---------- 720 button ---------- */
	auto small = make_shared<Button>("1280x720", font, textSize, sf::Color::White);
	optionButtons.push_back(small);

	/* ---------- 900 button ---------- */
	auto medium = make_shared<Button>("1600x900", font, textSize, sf::Color::White);
	optionButtons.push_back(medium);

	/* ---------- 1080 button ---------- */
	auto large = make_shared<Button>("1920x1080", font, textSize, sf::Color::White);
	optionButtons.push_back(large);

	/* ---------- Cancel button ---------- */
	auto cancel = make_shared<Button>("CANCEL", font, textSize, sf::Color::White);
	loopButtons.push_back(cancel);
	instrButtons.push_back(cancel);
	clearButtons.push_back(cancel);
	optionButtons.push_back(cancel);

	/* ---------- Toggle Screen ---------- */
	sf::RectangleShape screen(sf::Vector2f(view.getSize()));
	screen.setFillColor(sf::Color(0, 128, 128, 255));

	sf::RectangleShape inputField(sf::Vector2f(view.getSize().x * 0.8, view.getSize().y * 0.05));
	inputField.setFillColor(sf::Color(0, 108, 108, 235));

	/* ---------- Text prompts ---------- */
	sf::String input;
	sf::Text inputDisplay;
	inputDisplay.setFont(font);
	inputDisplay.setCharacterSize(captionSize);

	sf::Text inputPrompt;
	inputPrompt.setFont(font);
	inputPrompt.setCharacterSize(captionSize);
	inputPrompt.setStyle(sf::Text::Bold);
	inputPrompt.setString("FILENAME: ");

	sf::Text clearPrompt;
	clearPrompt.setFont(font);
	clearPrompt.setCharacterSize(captionSize);
	clearPrompt.setStyle(sf::Text::Bold);
	clearPrompt.setString("Clear all notes? (No undo)");

	sf::Text errorPrompt;
	errorPrompt.setFont(font);
	errorPrompt.setCharacterSize(captionSize);
	errorPrompt.setStyle(sf::Text::Bold);
	errorPrompt.setString("");
	bool isOverMaxNotes = false;

	sf::Thread mandachordThread(std::bind(&mandachordThread, 
		&window,
		&view,
		&viewPresets,
		&viewOffsetX,
		&event,
		&mandachord,
		&loopMeasure,
		&currentMallets,
		&currentResonator,
		&currentMetronome,
		&instrTable,
		&screen,
		&inputField,
		&text,
		&inputPrompt,
		&inputDisplay,
		&errorPrompt,
		&clearPrompt,
		&input,
		&isOverMaxNotes,
		&uiButtons,
		&loopButtons,
		&instrButtons,
		&clearButtons,
		&optionButtons));

	window.setActive(false);

	mandachordThread.launch();

	while (window.waitEvent(event)) {
		switch (event.type) {
		case (sf::Event::KeyPressed):
			if (event.key.code == sf::Keyboard::Space) {
				play->toggle();
				if (play->isToggled())
					play->updateText("PAUSE");
				else
					play->updateText("PLAY");
			}
			break;
		case (sf::Event::MouseWheelScrolled):
			if (save->isToggled() && load->isToggled() && mallets->isToggled() && resonator->isToggled() && metronome->isToggled() && loop->isToggled() && clear->isToggled() && options->isToggled() && !isOverMaxNotes) {
				if (event.mouseWheelScroll.delta < 0) {
					if (!(view.getCenter().x + 20 > 4 * 16 * 60 - 13 * 60)) {
						view.move(20, 0);
						window.setView(view);
						viewOffsetX += 20;
					}
				}
				else if (event.mouseWheelScroll.delta > 0) {
					if (!(view.getCenter().x - 20 < 13.25 * 60)) {
						view.move(-20, 0);
						window.setView(view);
						viewOffsetX -= 20;
					}
				}
			}
			break;
		case (sf::Event::MouseButtonPressed):
			if (save->isToggled() && load->isToggled() && mallets->isToggled() && resonator->isToggled() && metronome->isToggled() && loop->isToggled() && clear->isToggled() && options->isToggled()) {
				mandachord.checkMouse(window, isOverMaxNotes, errorPrompt);
				for (auto i : uiButtons)
					i->checkMouse(window);
				if (play->isToggled())
					play->updateText("PAUSE");
				else
					play->updateText("PLAY");
				if (isOverMaxNotes)
					confirm->checkMouse(window);
			}
			else if (!save->isToggled() || !load->isToggled()) {
				cancel->checkMouse(window);
			}
			else if (!mallets->isToggled() || !resonator->isToggled() || !metronome->isToggled()) {
				for (auto i : instrButtons)
					i->checkMouse(window);
			}
			else if (!loop->isToggled()) {
				for (auto i : loopButtons)
					i->checkMouse(window);
			}
			else if (!clear->isToggled()) {
				for (auto i : clearButtons)
					i->checkMouse(window);
			}
			else if (!options->isToggled()) {
				for (auto i : optionButtons)
					i->checkMouse(window);
			}
			break;
		case (sf::Event::TextEntered):
			if (!save->isToggled() || !load->isToggled()) {
				if (event.text.unicode == '\b' && input.getSize() > 0) {
					input.erase(input.getSize() - 1, 1);
					inputDisplay.setString(input);
				}
				else if (event.text.unicode < 128 && event.text.unicode != '\b' && event.text.unicode != '\r') {
					input += event.text.unicode;
					inputDisplay.setString(input);
				}
				else if (event.text.unicode == '\r' && input.getSize() > 0) {
					string filepath = "songs/" + input.toAnsiString() + ".uwu";
					ofstream outToFile;
					if (!save->isToggled()) {
						outToFile.open(filepath, std::ios::binary);
						if (outToFile.is_open()) {
							mandachord.saveToFile(outToFile, currentMallets, currentResonator, currentMetronome);
							outToFile.close();
						}
						else cout << "Could not write to file: " << filepath << endl;
						save->toggle();
					}
					else if (!load->isToggled()) {
						ifstream inFromFile(filepath, std::ios::binary);
						if (inFromFile.is_open()) {
							mandachord.loadFmFile(inFromFile, currentMallets, currentResonator, currentMetronome);
							inFromFile.close();
							mallets->updateText("MALLETS: " + currentMallets);
							resonator->updateText("RESONATOR: " + currentResonator);
							metronome->updateText("METRONOME: " + currentMetronome);
						}
						else cout << "Could not open file: " << filepath << endl;
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

	mandachordThread.wait();

	/* ---------- Exit success ---------- */
	/*cout << "Exit success!" << endl;
	system("pause");*/
	return EXIT_SUCCESS;
}