#include "Laser.hpp"

Laser::Laser(RType::pos_t pos) : Projectile("../res/proj/laser.png", sf::Vector2f(pos.x,pos.y), sf::IntRect(0,0,512,128), 10, 5, 1000, false)
{
}

Laser::~Laser()
{

}

void Laser::launch(float angle, sf::Vector2f pos)
{
    _pos = pos;
    _alive = true;
    _angle = angle;
    _rangeDone = 0;
}

void Laser::update(float delta)
{
    _anim.update(delta);
    updateAnimFrame();
    if (_alive) {
        move(_sp, 0);
        _rangeDone += _sp;
        if (_rangeDone > _range)
            _alive = false;
    }
}