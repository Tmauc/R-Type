/*
** EPITECH PROJECT, 2019
** map.hpp
** File description:
** rtype
*/

#pragma once

#include "rtype.hpp"
#include "Entity.hpp"

namespace RType
{

    class LivingEntity : public Entity
    {
    
    private:
        float _life;
        bool _alive;
    public:
        LivingEntity(std::string path, sf::Vector2f pos, sf::IntRect rect, float sp = 1);
        LivingEntity(const LivingEntity& other);
        ~LivingEntity() {};
        
        float getLife() { return _life; }
        bool getAlive() { return _alive; }
        void setLife(float life)    { _life = life; }
        void setAlive(bool alive)   { _alive = alive; } 
    
        LivingEntity& operator=(const LivingEntity& other);
    };

};
