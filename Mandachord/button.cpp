#include "button.hpp"

// Ctor from data
Button::Button(const sf::Text & text, const sf::Color & color)
	:_text(text), _box(sf::Vector2f(_text.getLocalBounds().width+2, _text.getLocalBounds().height+8)), _toggled(true)  {
	_box.setFillColor(color);
	_text.setFillColor(sf::Color::Green);
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

// Check mouse position on button
void Button::checkMouse(sf::RenderWindow & window) {
	if (getPos().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) 
		toggle();
}

// Draw
void Button::draw(sf::RenderWindow & window, const size_type & posX, const size_type & posY) {
	_box.setPosition(posX, posY);
	_text.setPosition(_box.getPosition());
	window.draw(_box);
	window.draw(_text);
}