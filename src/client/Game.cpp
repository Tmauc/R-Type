#include "Game.hpp"

namespace RType
{

    Game::Game(int width, int height)
    {
        _window = new sf::RenderWindow(sf::VideoMode(width, height), "RTYPE", sf::Style::Close);
        _window->setVerticalSyncEnabled(true);
        _window->setActive(true);
    }

    void Game::closeWindow()
    {
        delete _window;
    }

    void Game::update(Frame frame)
    {
        while (_players.size() > frame.players.size())
            _players.erase(_players.begin());
        for (size_t i = 0; i < frame.players.size(); i++) {
            if (_players.size() <= i) {
                LivingEntity newPlayer(PLAYER_SPRITE, {frame.players[i].first.x, frame.players[i].first.y}, {PLAYER_SIZE, 0, PLAYER_SIZE, PLAYER_SIZE});
                newPlayer.scaleWithWindow(PLAYER_SCALE);
                _players.push_back(newPlayer);
            } else {
                _players[i].setPos({frame.players[i].first.x, frame.players[i].first.y});
            }
        }
        while (_lasers.size() > frame.lasers.size())
            _lasers.erase(_lasers.begin());
        for (size_t i = 0; i < frame.lasers.size(); i++) {
            if (_lasers.size() <= i) {
                Laser newLaser({frame.lasers[i].first.x, frame.lasers[i].first.y});
                newLaser.scaleWithWindow(LASER_SCALE);
                _lasers.push_back(newLaser);
            } else {
                _lasers[i].setPos({frame.lasers[i].first.x, frame.lasers[i].first.y});
            }
        }
        while (_ennemies.size() > frame.ennemies.size())
            _ennemies.erase(_ennemies.begin());
        for (size_t i = 0; i < frame.ennemies.size(); i++) {
            if (_ennemies.size() <= i) {
                LivingEntity newEnnemy(ENNEMY_SPRITE, {frame.ennemies[i].first.x, frame.ennemies[i].first.y}, {0, 0, ENNEMY_SIZE, ENNEMY_SIZE});
                newEnnemy.scaleWithWindow(ENNEMY_SCALE);
                _ennemies.push_back(newEnnemy);
            } else {
                _ennemies[i].setPos({frame.ennemies[i].first.x, frame.ennemies[i].first.y});
            }
        }
    }

    void Game::update_event(RType::Client &&client)
    {
        while (_window->pollEvent(this->_event)) {
            if (_event.type == sf::Event::Closed) {
                _window->close();
            }
            if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Space) {
                client.Send("SHOT");
            }
        }
        std::string event = "MOVE|";
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            event += "UP;";
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            event += "DOWN;";
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            event += "LEFT;";
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            event += "RIGHT;";
        }
        if (event.find(";") != std::string::npos)
            client.Send(event);
    }

    void Game::draw_map()
    {
        _map.parallax();
        _window->draw(_map._background.getSprite());
        for (int i = 0; i < _map._map.size(); i++) {
            if (_map[i].getPos().x >= (-BLOCK_SIZE * _map.getScale()) &&  _map[i].getPos().x <= (2000 - BLOCK_SIZE * _map.getScale())) {
                _window->draw(_map[i].getSprite());
            }
        }
    }

    void Game::draw()
    {
        _window->clear();
        this->draw_map();
        for (auto e : _ennemies) {
            _window->draw(e.getSprite());
        }
        for (auto l : _lasers) {
            _window->draw(l.getSprite());
        }
        for (auto p : _players) {
            _window->draw(p.getSprite());
        }
        _window->display();
    }

};