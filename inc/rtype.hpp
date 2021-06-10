/*
** EPITECH PROJECT, 2019
** rtype client
** File description:
** hpp
*/

#ifndef RTYPE_HPP_
#define RTYPE_HPP_

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/bimap.hpp>

#include <iostream>
#include <memory>
#include <array>
#include <string>
#include <queue>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <thread>
#include <future>
#include <utility>
#include <cmath>
#include <stdio.h>

#define DEFAULT_HOST "localhost"
#define DEFAULT_PORT 5124
#define BUFFER_SIZE 8192

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define NUMBER_FRAMES_PER_SEC 60

#define PLAYER_SPRITE "../res/ship/r-typesheet27.gif"
#define PLAYER_SPEED 5
#define PLAYER_SIZE 34
#define PLAYER_SCALE 3
#define DEFAULT_PLAYER_POSITION {PLAYER_SIZE * 3, SCREEN_HEIGHT / 2 - ((PLAYER_SIZE * PLAYER_SCALE) / 2)}

#define LASER_SIZEX 512
#define LASER_SIZEY 95
#define LASER_SCALE 0.2

#define ENTITY_FRAME_SIZE 3
#define FRAME_SIZE 4

#define ENNEMY_SIN 300
#define ENNEMY_CHANCE 600
#define ENNEMY_SPRITE "../res/ship/r-typesheet26.gif"
#define ENNEMY_SPEED 2
#define ENNEMY_SIZE 50
#define ENNEMY_SCALE 1.5

#define MAP_SPEED 2
#define BLOCK_SIZE 39
#define BLOCK_SCALE 3.5

namespace RType
{

	struct pos_t
	{
		float x; float y;

		pos_t& operator=(const pos_t& other) { this->x = other.x; this->y = other.y; return *this; };
		pos_t& operator=(const float *other) { this->x = other[0]; this->y = other[1]; return *this; };
	};

	enum class Direction
	{
		Left,
		Right,
		Up,
		Down
	};

	struct Frame
	{
		double delta;
		std::vector<std::pair<pos_t, Direction>> players;
		std::vector<std::pair<pos_t, Direction>> ennemies;
		std::vector<std::pair<pos_t, Direction>> lasers;
		Frame &operator=(const Frame& other) { this->delta = other.delta; this->players = other.players; this->ennemies = other.ennemies; this->lasers = other.lasers; return *this; };
	};

    template<typename T> class RTypeQueue
    {
    private:
    	std::mutex mutex;
    	std::queue<T> queue;
    public:
    	void push(T value)
    	{
    		std::unique_lock<std::mutex> lock(mutex);
    		queue.push(value);
    	};

    	T pop()
    	{
    		std::unique_lock<std::mutex> lock(mutex);
    		T value;
    		std::swap(value, queue.front());
    		queue.pop();
    		return value;
    	};

    	bool empty() {
    		std::unique_lock<std::mutex> lock(mutex);
    		return queue.empty();
    	}
    };

} // namespace RType

#endif /* !RTYPE_HPP_ */
