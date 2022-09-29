/*
** EPITECH PROJECT, 2022
** advencedCollision
** File description:
** Game
*/

#pragma once

#include "SFML.hpp"

class Game {
    public:
        Game();
        ~Game();

        static Game &getInstance() {
            static Game instance;
            return instance;
        }

        void run();

    protected:
    private:
        void update();
        void draw();

        sf::Font _font;

        sf::RenderWindow _window;
};
