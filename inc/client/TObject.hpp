/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** Text Object
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifndef TOBJECT_HPP_
    #define TOBJECT_HPP_

class TObject {
    public:
        TObject(std::string &str, std::string &fontpath, sf::Vector2f pos, unsigned int size = 30);
        ~TObject();

        sf::Vector2f getPos() { return _pos; }
        void setPos(sf::Vector2f pos);
        sf::Text *getText() { return _text; }
        void setText(sf::Text &text) { _text = &text; }
        sf::Font *getFont() { return _font; }
        void setFont(sf::Font &font);
        std::string getString() { return _str; }
        void setString(std::string str);
        int getSize() { return _size; }
        void setSize(int size);
        sf::Color *getColor() { return _color; }
        void setColor(sf::Color &color);
        void draw(sf::RenderWindow *window) { window->draw(*_text); }

    protected:
    private:
        sf::Color *_color;
        std::string _str;
        sf::Text *_text;
        sf::Font *_font;
        sf::Vector2f _pos;
        int _size = 30;
};

#endif /* !TOBJECT_HPP_ */
