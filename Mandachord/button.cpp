#include "button.hpp"
#include <iostream>
using std::cout;
using std::endl;

// Ctor from data
Button::Button(const text_type & text, const sf::Font & font, const unsigned int & size, const sf::Color & color)
	:_toggled(true) {
	_text.setString(text);
	_text.setFont(font);
	_text.setCharacterSize(size);
	_text.setFillColor(sf::Color::Green);
	_box = { sf::RectangleShape(sf::Vector2f(_text.getLocalBounds().width + 4, _text.getLocalBounds().height + 10)) };
	_box.setFillColor(color);
}

// Ctor from data with functional
Button::Button(const text_type & text, const sf::Font & font, const unsigned int & size, const sf::Color & color, const std::function<void()> & f)
	:_toggled(true), _f(f) {
	_text.setString(text);
	_text.setFont(font);
	_text.setCharacterSize(size);
	_text.setFillColor(sf::Color::Green);
	_box = { sf::RectangleShape(sf::Vector2f(_text.getLocalBounds().width + 4, _text.getLocalBounds().height + 10)) };
	_box.setFillColor(color);
}

// GetPos
sf::FloatRect Button::getPos() {
	return _box.getGlobalBounds();
}

// Toggle
void Button::toggle() {
	if (!_toggled) {
		_toggled = true;
		_text.setFillColor(sf::Color::Green);
	}
	else {
		_toggled = false;
		_text.setFillColor(sf::Color::Red);
	}
}

// IsToggled
bool Button::isToggled() {
	return _toggled;
}

// GetString
Button::text_type Button::getText() {
	return _text.getString();
}

// UpdateText
void Button::updateText(const text_type & text) {
	_text.setString(text);
	_box = { sf::RectangleShape(sf::Vector2f(_text.getLocalBounds().width + 4, _text.getLocalBounds().height + 10)) };
}

// Check mouse position on button
bool Button::checkMouse(sf::RenderWindow & window) {
	return getPos().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}

// Draw
void Button::draw(sf::RenderWindow & window, const size_type & posX, const size_type & posY) {
	_box.setPosition(posX, posY);
	_text.setPosition(_box.getPosition());
	window.draw(_box);
	window.draw(_text);
}

// Execute button function
void Button::execute() {
	_f();
}