#include "button.hpp"

Button::Button(const sf::Text & text, const sf::Color & color)
	:_text(text), _box(sf::Vector2f(_text.getCharacterSize()*5, _text.getCharacterSize()*1.5f)), _toggled(true)  {
	_box.setFillColor(color);
	_text.setFillColor(sf::Color::Green);
}

sf::FloatRect Button::getPos() {
	return _box.getGlobalBounds();
}

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

bool Button::isToggled() {
	return _toggled;
}

void Button::checkMouse(sf::RenderWindow & window, Button & button) {
	if (button.getPos().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
		button.toggle();
		//cout << "Toggled Play" << endl;
	}
}

void Button::draw(sf::RenderWindow & window, const size_type & posX, const size_type & posY) {
	_box.setPosition(posX, posY);
	_text.setPosition(posX, posY);
	window.draw(_box);
	window.draw(_text);
}