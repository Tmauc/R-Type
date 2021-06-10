/*
** EPITECH PROJECT, 2019
** player
** File description:
** hpp
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "rtype.hpp"

namespace RType
{

    class Player
    {
    public:
    	Player(uint64_t clientId, pos_t pos = DEFAULT_PLAYER_POSITION, Direction dir = Direction::Right) : _clientId(clientId), _pos(pos), _realPos(pos), _dir(dir) {};
        
        std::string getPlayerString(void) { return std::to_string(_pos.x) + "," + std::to_string(_pos.y) + "," + std::to_string(static_cast<int>(_dir)); };
        
        void move(std::vector<std::string> map, std::string dir)
        {
            if (dir.find("UP") != std::string::npos) {
                size_t block_posx_left = _realPos.x / (BLOCK_SIZE * BLOCK_SCALE);
                size_t block_posx_right = (_realPos.x + (PLAYER_SIZE * PLAYER_SCALE)) / (BLOCK_SIZE * BLOCK_SCALE);
        	    size_t block_posy = (_realPos.y - PLAYER_SPEED) / (BLOCK_SIZE * BLOCK_SCALE);
                if (_pos.y - PLAYER_SPEED >= 0 && map[block_posy][block_posx_left] == 'O' && map[block_posy][block_posx_right] == 'O') {
				    _pos.y -= PLAYER_SPEED;
                    _realPos.y -= PLAYER_SPEED;
                }
            }
            if (dir.find("DOWN") != std::string::npos) {
                size_t block_posx_left = _realPos.x / (BLOCK_SIZE * BLOCK_SCALE);
                size_t block_posx_right = (_realPos.x + (PLAYER_SIZE * PLAYER_SCALE)) / (BLOCK_SIZE * BLOCK_SCALE);
        	    size_t block_posy = (_realPos.y + (PLAYER_SIZE * PLAYER_SCALE) + PLAYER_SPEED) / (BLOCK_SIZE * BLOCK_SCALE);
                if (_pos.y + PLAYER_SPEED <= SCREEN_HEIGHT && map[block_posy][block_posx_left] == 'O' && map[block_posy][block_posx_right] == 'O') {
				    _pos.y += PLAYER_SPEED;
                    _realPos.y += PLAYER_SPEED;
                }
            }
            if (dir.find("LEFT") != std::string::npos) {
                size_t block_posx = (_realPos.x - PLAYER_SPEED) / (BLOCK_SIZE * BLOCK_SCALE);
        	    size_t block_posy_up = _realPos.y / (BLOCK_SIZE * BLOCK_SCALE);
                size_t block_posy_down = (_realPos.y + (PLAYER_SIZE * PLAYER_SCALE) + PLAYER_SPEED) / (BLOCK_SIZE * BLOCK_SCALE);
                if (_pos.x - PLAYER_SPEED >= 0 && map[block_posy_up][block_posx] == 'O' && map[block_posy_down][block_posx] == 'O') {
				    _pos.x -= PLAYER_SPEED;
                    _realPos.x -= PLAYER_SPEED;
                }
            }
            if (dir.find("RIGHT") != std::string::npos) {
				size_t block_posx = (_realPos.x + (PLAYER_SIZE * PLAYER_SCALE) + PLAYER_SPEED) / (BLOCK_SIZE * BLOCK_SCALE);
        	    size_t block_posy_up = _realPos.y / (BLOCK_SIZE * BLOCK_SCALE);
                size_t block_posy_down = (_realPos.y + (PLAYER_SIZE * PLAYER_SCALE) + PLAYER_SPEED) / (BLOCK_SIZE * BLOCK_SCALE);
                if (_pos.x + PLAYER_SPEED <= SCREEN_WIDTH && map[block_posy_up][block_posx] == 'O' && map[block_posy_down][block_posx] == 'O') {
				    _pos.x += PLAYER_SPEED;
                    _realPos.x += PLAYER_SPEED;
                }
            }
        }

        bool isInside(float x, float y)
        {
            if (x > _pos.x && x < (_pos.x + (PLAYER_SIZE * PLAYER_SCALE)) && y > _pos.y && y < (_pos.y + (PLAYER_SIZE * PLAYER_SCALE)))
                return true;
            return false; 
        }

        uint64_t _clientId;
        pos_t _pos;
        pos_t _realPos;
        Direction _dir;
    };

};

#endif /* !PLAYER_HPP_ */
