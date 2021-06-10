 /*
** EPITECH PROJECT, 2019
** RType
** File description:
** Game object
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Projectile.hpp"

#ifndef DOUBLELASER_HPP_
#define DOUBLELASER_HPP_

class DoubleLaser : public Projectile {
    public:
        DoubleLaser();
        ~DoubleLaser();
        void launch(float angle, sf::Vector2f pos);
        void update(float delta);
    protected:
    private:
};

#endif /* !ENTITY_HPP_ */