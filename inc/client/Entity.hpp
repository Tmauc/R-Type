 /*
** EPITECH PROJECT, 2019
** RType
** File description:
** Game object
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GObject.hpp"

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_

class Entity : public GObject {
    public:
        Entity(std::string path, sf::Vector2f pos, sf::IntRect rect, float sp);
        Entity(const Entity& other);
        ~Entity();
        void move(float x, float y);
        int load();
        int spawn();
        int destroy();

        Entity& operator=(const Entity& other);
};

#endif /* !ENTITY_HPP_ */
