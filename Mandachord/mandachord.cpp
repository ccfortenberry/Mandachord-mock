#include "mandachord.hpp"
#include <iostream>
using std::cout;
using std::endl;


// ------ Note ------
Note::Note(const data_type & sound, const data_type & icon, const sf::Color & color)
	:_sound(sound), _icon(icon), _color(color), _noteBox(sf::Vector2f(50, 50)), _toggled(false) {
	_noteBox.setOutlineThickness(2);
	_noteBox.setOutlineColor(color);
	_noteBox.setFillColor(sf::Color::Transparent);
}

Note::data_type Note::getSound() {
	return _sound;
}

Note::data_type Note::getIcon() {
	return _icon;
}

sf::Color Note::getColor() {
	return _color;
}

sf::FloatRect Note::getPos() {
	return _noteBox.getGlobalBounds();
}

void Note::setSound(const data_type & sound) {
	_sound = sound;
}

void Note::setIcon(const data_type & icon) {
	_icon = icon;
}

void Note::setColor(const sf::Color & color) {
	_color = color;
}

//void Note::setPos(const sf::Vector2f & position) {
//	_position = position;
//}

void Note::draw(sf::RenderWindow & window, const int & posX, const int & posY) {
	_noteBox.setPosition(posX, posY);
	window.draw(_noteBox);
}

void Note::toggleNote() {
	if (!_toggled) {
		_toggled = true;
		_noteBox.setFillColor(_color);
		cout << "Toggled!" << endl;
	}
	else {
		_toggled = false;
		_noteBox.setFillColor(sf::Color::Transparent);
		cout << "Un-Toggled!" << endl;
	}
}

bool Note::isToggled() {
	return _toggled;
}

bool Note::isColliding(const sf::RectangleShape & line) {
	return _noteBox.getPosition() == line.getPosition();
}

void Note::play() {
	cout << "Playing :" << _sound << endl;
}