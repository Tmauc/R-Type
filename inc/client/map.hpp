/*
** EPITECH PROJECT, 2019
** map.hpp
** File description:
** rtype
*/

#pragma once

#include "rtype.hpp"
#include "rtype_client.hpp"
#include "Entity.hpp"
#include "Game.hpp"

namespace RType
{

  class Map
  {
  private:
    std::vector<std::string> _strmap;
    std::vector<int> _players;
    std::vector<int> _ennemies;
    sf::Clock _clock;
    bool _moveMap = true;
    int _sizeMap;
    float _scale = BLOCK_SCALE;
  public:
    Map();

    void parallax();

    size_t size() const { return _map.size(); };
    float getScale() const { return _scale; };
    
    void choose_entity(char, int, int);
    std::vector<std::string> parsMap(std::string strMap);
    void recieve(RType::Client &&);

    Entity _background;
    std::vector<Entity> _map;

    Entity &operator[](const size_t &i) { return this->_map[i]; };
  };

}; // namespace RType