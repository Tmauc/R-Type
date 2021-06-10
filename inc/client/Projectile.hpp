 /*
** EPITECH PROJECT, 2019
** RType
** File description:
** Game object
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.hpp"

#ifndef PROJECTILE_HPP_
    #define PROJECTILE_HPP_

class Projectile : public Entity {
    public:
        Projectile(std::string path, sf::Vector2f pos, sf::IntRect rect, float sp,
        int damage, float range, bool bounce);
        ~Projectile();
        void launch(float angle, sf::Vector2f pos);
        void update();
    protected:
    int _damage;
    bool _alive = false;
    bool _bounce = false;
    float _range;
    float _rangeDone = 0;
};

#endif /* !ENTITY_HPP_ */
