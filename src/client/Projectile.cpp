#include "Projectile.hpp"

Projectile::Projectile(std::string path, sf::Vector2f pos, sf::IntRect rect, float sp, int damage, float range, bool bounce) : Entity(path, pos, rect, sp)
{
    _damage = damage;
    _range = range;
}

Projectile::~Projectile()
{

}

void Projectile::launch(float angle, sf::Vector2f pos)
{
    _pos = pos;
    _alive = true;
    _angle = angle;
    _rangeDone = 0;
}

void Projectile::update()
{
    if (_alive) {
        move(_sp, 0);
        _rangeDone += _sp;
        if (_rangeDone > _range)
            _alive = false;
    }
}