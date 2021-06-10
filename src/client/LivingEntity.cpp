/*
** EPITECH PROJECT, 2019
** entity.cpp
** File description:
** rtype
*/

#include "LivingEntity.hpp"

namespace RType
{

    LivingEntity::LivingEntity(std::string path, sf::Vector2f pos, sf::IntRect rect, float sp) : Entity(path, pos, rect, sp) {}

    LivingEntity::LivingEntity(const LivingEntity& other) : Entity(other)
    {
        this->setAlive(other._alive);
        this->setLife(other._life);
    }

    LivingEntity& LivingEntity::operator=(const LivingEntity& other)
    {
        Entity::operator=(other);
        this->_alive = other._alive;
        this->_life = other._life;
        return (*this);
    }
}; // namespace