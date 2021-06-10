/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** rtype
*/

#include "rtype_client.hpp"
#include "Game.hpp"

void waitForNextFrame(RType::Client &&c)
{
    while (!c.HasMessages());
}

std::vector<std::pair<RType::pos_t, RType::Direction>> parseEntity(std::string parent)
{
    std::vector<std::pair<RType::pos_t, RType::Direction>> returnv;
    std::stringstream stream(parent);
    std::string token;

    while (std::getline(stream, token, ';')) {
        std::pair<RType::pos_t, RType::Direction> temp;
        std::stringstream child_stream(token);
        std::string child_token;
        for (size_t i = 0; std::getline(child_stream, child_token, ',') && i < ENTITY_FRAME_SIZE; i++) {
            switch (i) {
            case 0:
                temp.first.x = std::stof(child_token);
                break;
            case 1:
                temp.first.y = std::stof(child_token);
                break;
            case 2:
                temp.second = static_cast<RType::Direction>(std::stoi(child_token));
                break;
            }
        }
        returnv.push_back(temp);
    }
    return returnv;
}

RType::Frame parseFrame(std::string frame)
{
    RType::Frame f;
    std::stringstream stream(frame);
    std::string token;

    for (int i = 0; std::getline(stream, token, '|') && i < FRAME_SIZE; i++) {
        switch (i) {
        case 0: // DELTA TIME
            f.delta = std::stod(token);
            break;
        case 1: // players
            f.players = parseEntity(token);
            break;
        case 2: // projectiles
            f.lasers = parseEntity(token);
            break;
        case 3: // ennemies
            f.ennemies = parseEntity(token);
            break;
        }
    }
    return f;
}

int main(int ac, char **av)
{
    RType::Game game;
    RType::Client c(DEFAULT_HOST, std::to_string(DEFAULT_PORT));

    try {
        game.getMap().recieve(std::move(c));
        while (game.getWindow()->isOpen()) {
            game.update_event(std::move(c));
            waitForNextFrame(std::move(c));
            RType::Frame curFrame = parseFrame(c.PopMessage());
            game.update(curFrame);
            game.draw();
        }
        c.disconnect();
        game.closeWindow();
    }
    catch (...) {
        c.disconnect();
    }
    return (0);
}
