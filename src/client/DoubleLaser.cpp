#include "DoubleLaser.hpp"

DoubleLaser::DoubleLaser() : Projectile("../res/proj/r-typesheet2.gif", sf::Vector2f(0,0), sf::IntRect(36,470,66,32), 10, 5, 1000, false)
{
}

DoubleLaser::~DoubleLaser()
{

}

void DoubleLaser::launch(float angle, sf::Vector2f pos)
{
    _pos = pos;
    _alive = true;
    _angle = angle;
    _rangeDone = 0;
}

void DoubleLaser::update(float delta)
{
    _anim.update(delta);
    updateAnimFrame();
    if (_alive) {
        move(_sp, 0);
        _rangeDone += _sp;
        if (_rangeDone > _range) {
            launch(0, sf::Vector2f(200,200));
        }
    }
}