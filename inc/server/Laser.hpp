/*
** EPITECH PROJECT, 2019
** laser
** File description:
** phpp
*/

#ifndef LASER_HPP_
#define LASER_HPP_

#include "rtype.hpp"

namespace RType
{

    class Laser {
    public:
    	Laser(pos_t begPos, uint64_t owner, float speed) {
            _begPos = begPos;
            _curPos = begPos;
            _owner = owner;
            _speed = speed;
            _dir = Direction::Left;
        }
        
        std::string getLaserString(void) { return (std::to_string(_curPos.x) + "," + std::to_string(_curPos.y) + "," + std::to_string(static_cast<int>(_dir))); };
        
        bool isLaserGone(void) {
            if (_curPos.x > SCREEN_WIDTH)
                return true;
            return false;
        }
        
        uint64_t _owner;
        pos_t _begPos;
        pos_t _curPos;
        float _speed;
        Direction _dir;
    };

}; // namespace RType

#endif /* !LASER_HPP_ */
