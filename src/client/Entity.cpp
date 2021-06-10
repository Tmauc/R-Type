#include "Entity.hpp"

Entity::Entity(std::string path, sf::Vector2f pos, sf::IntRect rect, float sp) : GObject(path, pos, rect, sp) {}

Entity::Entity(const Entity& other) : GObject(other) {}

Entity::~Entity() {}

void Entity::move(float x, float y)
{
    setPos(sf::Vector2f(getPos().x + x, getPos().y + y));
}

int Entity::load()
{
    return 0;
}

int Entity::spawn()
{
    return 0;
}

int Entity::destroy()
{
    return 0;
}

Entity& Entity::operator=(const Entity& other)
{
    GObject::operator=(other);
    return (*this);
}