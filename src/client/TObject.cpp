/*
** EPITECH PROJECT, 2019
** RType
** File description:
** Text Object
*/

#include "TObject.hpp"

TObject::TObject(std::string &str, std::string &fontpath, sf::Vector2f pos, unsigned int size)
{
    _str = str;
    _size = size;
    _color = new sf::Color(255, 255, 255, 255);
    _font = new sf::Font();
    _font->loadFromFile(fontpath);
    _text = new sf::Text(_str, *_font, _size);
    _text->setColor(*_color);
    _text->setPosition(pos);
}

TObject::~TObject()
{
    delete _font;
    delete _text;
}

void TObject::setPos(sf::Vector2f pos)
{
    _pos = pos;
    _text->setPosition(_pos);
}

void TObject::setFont(sf::Font &font)
{
    _font = &font;
    _text->setFont(*_font);
}

void TObject::setColor(sf::Color &color)
{
    _color = &color;
    _text->setColor(*_color);
}

void TObject::setString(std::string str)
{
    _str = str;
    _text->setString(_str);
}

void TObject::setSize(int size)
{
    _size = size;
    _text->setCharacterSize(_size);
}