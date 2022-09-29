/*
** EPITECH PROJECT, 2022
** advencedCollision
** File description:
** Game
*/

#include "Game.hpp"

Game::Game()
{
    _window.create(sf::VideoMode(1920, 1080), "SPRITE CREATOR!");
    _window.setFramerateLimit(144);

    _font.loadFromFile("assets/font.ttf");

}

Game::~Game()
{
}

void Game::run()
{
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                _window.close();
        }
        update();
        draw();
    }
}

void Game::update()
{
}

void Game::draw()
{
    _window.clear();
    _window.display();
}
