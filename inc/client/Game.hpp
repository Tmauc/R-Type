 /*
** EPITECH PROJECT, 2019
** RType
** File description:
** Game object
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GObject.hpp"
#include "map.hpp"
#include "LivingEntity.hpp"
#include "Projectile.hpp"
#include "Laser.hpp"

namespace RType
{

    class Game {
        public:
            Game(int width = 1920, int height = 1080);

            void closeWindow();
            void draw();
            void update(Frame);
            void update_event(RType::Client &&client);

            sf::RenderWindow *getWindow() { return _window; };
            Map &getMap() { return _map; };

        private:
            Map _map;

            std::vector<LivingEntity> _players;
            std::vector<Projectile> _lasers;
            std::vector<LivingEntity> _ennemies;
            sf::RenderWindow *_window;
            sf::Event _event;

            void draw_map();
    };

};

#endif /* !GOBJECT_HPP_ */
