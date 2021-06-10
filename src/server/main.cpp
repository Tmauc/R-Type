/*
** EPITECH PROJECT, 2019
** rtype server
** File description:
** main
*/

#include "rtype_server.hpp"

double wait(void)
{
    std::clock_t c_start = std::clock();
    static auto t_start = std::chrono::high_resolution_clock::now();
    auto t_end = std::chrono::high_resolution_clock::now();    
    double time = (1000.0 / NUMBER_FRAMES_PER_SEC) - std::chrono::duration<double, std::milli>(t_end - t_start).count();

    (void)c_start;
    if (time > 0)
        usleep(time * 1000);
    t_start = std::chrono::high_resolution_clock::now();
    return time;
}

void sendFrame(RType::Server &&s, const double delta)
{
    std::string player_string;
    std::string laser_string;
    std::string ennemy_string;

    for (auto p : s.players) {
        player_string += p.getPlayerString() + ";";
    }
    if (!player_string.empty()) {
        player_string.pop_back();
    }
    for (auto l : s.lasers) {
        laser_string += l.getLaserString() + ";";
    }
    if (!laser_string.empty()) {
        laser_string.pop_back();
    }
    for (auto &e : s.ennemies) {
        ennemy_string += e.getEnnemyString() + ";";
    }
    if (!ennemy_string.empty()) {
        ennemy_string.pop_back();
    }
    s.SendToAll(std::to_string(delta) + "|" + player_string + "|" + laser_string + "|" + ennemy_string + "|");
}

int main(int ac, char **av)
{
    RType::Server s(DEFAULT_PORT);
    double delta;

    while (s.players.size() < 2) {
        std::cout << s.players.size() << " waiting for other player" << std::endl;
        sleep(1);
    }
    while (true) {
        while (s.HasMessages()) {
            ClientMessage msg = s.PopMessage();
            if (msg.first == "RES") s.disconnect(msg.second);
            if (msg.first.substr(0, 4) == "MOVE") if (msg.first.size() > 5) s.movePlayer(msg.second, msg.first.substr(5));
            if (msg.first.substr(0, 4) == "SHOT") s.launchShot(msg.second);
        }
        s.update();
        delta = wait();
        sendFrame(std::move(s), delta);
    }
    return (0);
}