 /*
** EPITECH PROJECT, 2019
** RType
** File description:
** Game object
*/

#ifndef LASER_HPP_
#define LASER_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Projectile.hpp"
#include "rtype.hpp"

class Laser : public Projectile {
    public:
        Laser(RType::pos_t pos);
        ~Laser();
        void launch(float angle, sf::Vector2f pos);
        void update(float delta);
    protected:
    private:
};

#endif /* !ENTITY_HPP_ */