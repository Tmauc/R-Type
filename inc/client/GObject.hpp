 /*
** EPITECH PROJECT, 2019
** RType
** File description:
** Game object
*/

#ifndef GOBJECT_HPP_
    #define GOBJECT_HPP_

#include "rtype.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Animation {
    public:
    Animation(int currentFrameX = 0, int currentFrameY = 0, int maxFrameX = 1, int maxFrameY = 1, float animSpeed = 0.2)
    {
        _currentFrameX = currentFrameX;
        _currentFrameY = currentFrameY;
        _maxFrameX = maxFrameX;
        _maxFrameY = maxFrameY;
        _animSpeed = animSpeed;
        _timeElasped = 0;
    }
    ~Animation() {}


    void update(float delta) {
        /* checking time */
        _timeElasped += delta;
        if (_timeElasped >= _animSpeed * 1000) {
            _timeElasped -= _animSpeed * 1000;

            /*Operate changing of sprites*/
            if (_currentFrameX < _maxFrameX - 1)
                _currentFrameX++;
            else {
                _currentFrameX = 0;
                if (_currentFrameY < _maxFrameY - 1) {
                    _currentFrameY++;
                } else
                    _currentFrameY = 0;
            }
        }
    }

    int _currentFrameX;
    int _currentFrameY;
    int _maxFrameX;
    int _maxFrameY;
    float _animSpeed;
    float _timeElasped;
};

class GObject {
    public:
        GObject(std::string path, sf::Vector2f pos, sf::IntRect rect, float sp);
        GObject(const GObject &object);
        ~GObject();
        GObject& operator=(const GObject& other);

        sf::IntRect getRect() { return _rect; }
        void setRect(sf::IntRect rect);
        sf::Vector2f getPos() { return _pos; }
        void setPos(sf::Vector2f pos);
        sf::Vector2f getActualPos() { return _actualpos; }
        void setActualPos(sf::Vector2f actualpos) { _actualpos = actualpos; }
        float getSpeed() { return _sp; }
        void setSpeed(float speed) { _sp = speed; }
        float getAngle() { return _angle; }
        void setAngle(float angle);
        float getWRatio() { return _wratio; }
        void setWRatio(float wratio) { _wratio = wratio; }
        sf::Sprite getSprite() { return _sprite; }
        void setSprite(sf::Sprite sprite) { _sprite = sprite; }
        sf::Texture getTexture() { return _texture; }
        void setTexture(sf::Texture texture);
        bool checkCollide(GObject &other);
        bool checkNextCollide(GObject &other);
        void scaleWithWindow(float);
        void dump();
        void setAnim(int currentFrameX, int currentFrameY, int maxFrameX, int maxFrameY, float animSpeed) {
            _anim._currentFrameX = currentFrameX;
            _anim._currentFrameX = currentFrameX;
            _anim._maxFrameX = maxFrameX;
            _anim._maxFrameY = maxFrameY;
            _anim._animSpeed = animSpeed;
        }
        void updateAnimFrame() {
            _rect.top = _offset.y + _anim._currentFrameY * _rect.height;
            _rect.left = _offset.x + _anim._currentFrameX * _rect.width;
            setRect(_rect);
        }

    protected:
        sf::Sprite _sprite;
        sf::Texture _texture;
        float _sp;
        float _angle;
        sf::Vector2i _offset;
        sf::Vector2f _pos;
        sf::Vector2f _actualpos;
        sf::IntRect _rect;
        float _wratio = 1;
        Animation _anim;
};

#endif /* !GOBJECT_HPP_ */
