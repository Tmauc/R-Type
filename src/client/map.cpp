/*
** EPITECH PROJECT, 2019
** map.cpp
** File description:
** rtype
*/

#include "Game.hpp"
#include "map.hpp"

namespace RType
{

  Map::Map() : _background("../res/map/background2.png", sf::Vector2f(0, 0), sf::IntRect(0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT), 5.0) {};

  void Map::choose_entity(char c, int i, int j)
  {
    std::string spritePath;

    switch (c) {
      case '-':
        spritePath = "../res/map/wall.gif";
        break;
      case 'x':
        spritePath = "../res/map/wall.gif";
        break;
      default:
        break;
    }
    if (spritePath != "") {
      Entity tmpEntity(spritePath, sf::Vector2f(i, j), sf::IntRect(0, 0, BLOCK_SIZE, BLOCK_SIZE), MAP_SPEED);
      tmpEntity.scaleWithWindow(_scale);
      _map.push_back(tmpEntity);
    }
  }


  std::vector<std::string> Map::parsMap(std::string strMap)
  {
    std::vector<std::string> tmpMap;
    char tmpC;
    sf::Vector2f tmpPos;
    char *test = strdup(strMap.data());

    char *tab = strtok(test, ";");
    while (tab != NULL) {
      tmpMap.push_back(tab);
      tab = strtok(NULL, ";");
    }
    for (int i = 0; i < tmpMap.size(); i++) {
      std::string tmpString;
      for (int j = 0, k = 0; j < tmpMap[i].size(); j++) {
        if (tmpMap[i][j] == ',' || j + 1 >= tmpMap[i].size()) {
          if (k == 0) {
            tmpPos.x = std::stoi(tmpString);
          } else if (k == 1) {
            tmpPos.y = std::stoi(tmpString);
          } else {
            tmpC = tmpMap[i][j];
          }
          k++;
          tmpString = "";
        } else {
          tmpString += tmpMap[i][j];
        }
      }
      choose_entity(tmpC, tmpPos.x, tmpPos.y);
    }
    return tmpMap;
  }

  void Map::recieve(RType::Client &&c)
  {
    while (!c.HasMessages());
    std::string msg = c.PopMessage();
    if (msg.find("MAP|") != std::string::npos) {
      msg = msg.substr(4);
    }
    parsMap(msg);
  }

  void Map::parallax()
  {
    if (_clock.getElapsedTime().asMilliseconds() > 1.0f) {
      for (int i = 0; _moveMap == true && i < _map.size(); i++) {
          sf::Vector2f posBlock = _map[i].getPos();
          if (i + 1 >= _map.size() && _map[i].getPos().x <= (SCREEN_WIDTH - BLOCK_SIZE * _scale)) {
            _moveMap = false;
          }
          _map[i].setPos(sf::Vector2f(posBlock.x - _map[i].getSpeed(), posBlock.y));
      }
      sf::Vector2f pos = _background.getPos();
      if (pos.x < -1900) {
        _background.setPos(sf::Vector2f(pos.x = 0, pos.y));
      } else if (_moveMap == false) {
        _background.setPos(sf::Vector2f(pos.x - 1, pos.y));
      } else {
        _background.setPos(sf::Vector2f(pos.x - 5, pos.y));
      }
      _clock.restart();
    }
  }

}; // namespace