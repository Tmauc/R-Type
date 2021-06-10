/*
** EPITECH PROJECT, 2019
** ennemy
** File description:
** hpp
*/

#ifndef ENNEMY_HPP_
#define ENNEMY_HPP_

#include "rtype.hpp"

namespace RType
{

    class Ennemy
    {
    public:
    	Ennemy(float spawn)
        {
            _pos.x = spawn;
            _pos.y = static_cast<float>((ENNEMY_SIN * sin(_pos.x)) + (SCREEN_HEIGHT / 2));
            _dir = Direction::Left;
        };
    
        std::string getEnnemyString(void) { return std::to_string(_pos.x) + "," + std::to_string(_pos.y) + "," + std::to_string(static_cast<int>(_dir)); };

        pos_t _pos;
        Direction _dir;
    };

};

#endif /* !ENNEMY_HPP_ */
