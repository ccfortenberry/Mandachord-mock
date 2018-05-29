#include "mandachord.hpp"
#include <iostream>
using std::cout;
using std::endl;


// ------ Note ------
Note::Note(const sf::Texture & icon, const sf::Color & color)
	: _icon(sf::Vector2f(50, 50)), _color(color), _noteBox(sf::Vector2f(50, 50)), _toggled(false) {
	_noteBox.setOutlineThickness(2);
	_noteBox.setOutlineColor(color);
	_noteBox.setFillColor(sf::Color::Transparent);
	_icon.setTexture(&icon);
}

sf::FloatRect Note::getPos() {
	return _noteBox.getGlobalBounds();
}

void Note::draw(sf::RenderWindow & window, const size_type & posX, const size_type & posY) {
	_noteBox.setPosition(posX, posY);
	_icon.setPosition(posX, posY);
	window.draw(_noteBox);
	window.draw(_icon);
}

void Note::toggle() {
	if (!_toggled) {
		_toggled = true;
		_noteBox.setFillColor(_color);
	}
	else {
		_toggled = false;
		_noteBox.setFillColor(sf::Color::Transparent);
	}
}

bool Note::isToggled() {
	return _toggled;
}

bool Note::isColliding(const sf::RectangleShape & line) {
	return _noteBox.getPosition().x == line.getPosition().x;
}