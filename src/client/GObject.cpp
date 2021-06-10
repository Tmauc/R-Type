/*
** EPITECH PROJECT, 2019
** RType
** File description:
** Game Object
*/

#include "GObject.hpp"
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

GObject::GObject(std::string path, sf::Vector2f pos, sf::IntRect rect, float sp)
{
    _texture.loadFromFile(path);
    _sprite = sf::Sprite(_texture);
    _pos = pos;
    _actualpos = _pos;
    _rect = rect;
    _sp = sp;
    _sprite.setPosition(_pos);
    _sprite.setTextureRect(_rect);
    _angle = 0;
    _anim;
    _offset.x = _rect.left;
    _offset.y = _rect.top;
}

GObject::GObject(const GObject &object)
{
    _texture = object._texture;
    _sprite = sf::Sprite(_texture);
    _pos = object._pos;
    _actualpos = object._actualpos;
    _rect = object._rect;
    _sp = object._sp;
    _sprite.setPosition(_pos);
    _sprite.setTextureRect(_rect);
    _angle = object._angle;
    _wratio = object._wratio;
    _sprite.setScale(_wratio, _wratio);
}

GObject::~GObject()
{
}

GObject& GObject::operator=(const GObject& other)
{
    this->_actualpos = other._actualpos;
    this->_angle = other._angle;
    setAnim(other._anim._currentFrameX, other._anim._currentFrameY, other._anim._maxFrameX, other._anim._maxFrameY, other._anim._animSpeed);
    this->_pos = other._pos;
    this->_rect = other._rect;
    this->_sp = other._sp;
    this->_sprite = other._sprite;
    this->_texture = other._texture;
    this->_wratio = other._wratio;
    _sprite.setPosition(_pos);
    _sprite.setTextureRect(_rect);
    return (*this);
}

void GObject::setPos(sf::Vector2f pos)
{
    _pos = pos;
    _sprite.setPosition(_pos);
}

void GObject::setRect(sf::IntRect rect)
{
    _rect = rect;
    _sprite.setTextureRect(_rect);
}

void GObject::setTexture(sf::Texture texture)
{
    _sprite.setTexture(_texture);
}

void GObject::setAngle(float angle)
{
    _angle = angle;
    _sprite.setRotation(angle);
}

sf::Vector2f get_ratios(float angle)
{
	float val = 3.14159265 / 180;
	sf::Vector2f ratios;

	ratios.x = cos(angle * val);
	ratios.y = sin(angle * val);
	return (ratios);
}

void get_object_ends(GObject *object, sf::Vector2f points[4])
{
	sf::Vector2f ratios = get_ratios(object->getAngle());
    int width = object->getRect().width;
    int height = object->getRect().height;
    float x = object->getPos().x;
    float y = object->getPos().y;

	points[0] = sf::Vector2f(x + 0.1 * (ratios.x * width + ratios.y *
	height), y + 0.1 * (ratios.x * height + ratios.y * width));
	points[1] = sf::Vector2f(x + 0.9 * ratios.x * width + 0.1 * ratios.y
	* height, y + 0.9 * ratios.y * width + 0.1 * ratios.x * height);
	points[2] = sf::Vector2f(x + 0.9 * ratios.y * height + 0.1 * ratios.x
	* width, y + 0.9 * ratios.x * height + 0.1 * ratios.y * width);
	points[3] = sf::Vector2f(x + 0.9 * (ratios.x * width + ratios.y *
	height), y + 0.9 * (ratios.x * height + ratios.y * width));
}

int check_inside_target(sf::Vector2f *coord1, sf::Vector2f *coord2)
{
	for (int i = 0; i != 4; i += 1) {
		if (coord1[i].x >= coord2[0].x && coord1[i].x <= coord2[1].x &&
			coord1[i].y >= coord2[0].y && coord1[i].y <= coord2[2].y)
			return (1);
	}
	return (0);
}

bool GObject::checkCollide(GObject &other)
{
    sf::Vector2f coord1[4];
	sf::Vector2f coord2[4];

	get_object_ends(this, coord1);
	get_object_ends(&other, coord2);
    if (check_inside_target(coord1, coord2)) {
		return true;
	}
	return false;
}

bool GObject::checkNextCollide(GObject &other)
{
    sf::Vector2f coord1[4];
	sf::Vector2f coord2[4];

	get_object_ends(this, coord1);
	get_object_ends(&other, coord2);
    if (check_inside_target(coord1, coord2)) {
		return true;
	}
	return false;
}

void GObject::scaleWithWindow(float wratio = 1)
{
    _wratio = wratio;
    _sprite.setScale(wratio, wratio);
    _sprite.setPosition(_pos.x * wratio, _pos.y * wratio);
    setPos(sf::Vector2f(_pos.x * wratio, _pos.y * wratio));
}

void GObject::dump()
{
    std::cout << "Sprite Position (x,y) : " << _sprite.getPosition().x <<
    ", " << _sprite.getPosition().y << std::endl; 
    std::cout << "Position (x,y) : " << _pos.x << ", " << _pos.y << std::endl; 
    std::cout << "ActualPosition (x,y) : " << _actualpos.x << ", " << _actualpos.y << std::endl; 
    std::cout << "Rect (w,h,t,l) : " << _rect.width << ", " << _rect.height
    << ", " << _rect.top << ", " << _rect.left << std::endl;
    std::cout << "Speed : " << _sp << std::endl;
    std::cout << "Angle : " << _angle << std::endl;
}