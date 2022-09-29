/*
** EPITECH PROJECT, 2022
** advencedCollision
** File description:
** Colission
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>

class CollisionPrivate {
    typedef struct {
        sf::Sprite *sprite;
        sf::Image *imageSprite;
        sf::Image *imageAll;
        sf::Vector2f pos;
    } CollisionPrivate_Sprite;

    typedef struct {
        sf::CircleShape *CircleShape;
        sf::Image *imageCircle;
        sf::Image *imageAll;
        sf::Vector2f pos;
    } CollisionPrivate_Circle;

    typedef struct {
        sf::RectangleShape *RectangleShape;
        sf::Image *imageRectangle;
        sf::Image *imageAll;
        sf::Vector2f pos;
    } CollisionPrivate_Rectangle;

    public:
        ~CollisionPrivate();

        static CollisionPrivate *getInstance(){ 
            static CollisionPrivate instance;
            return &instance;
        }; // Singleton

        sf::Image *getImageSprite(sf::Sprite &sprite);
        sf::Image *getImageCircle(sf::CircleShape &circle);
        sf::Image *getImageRectangle(sf::RectangleShape &rectangle);

        std::vector<CollisionPrivate_Sprite> _imagesSprite;
        std::vector<CollisionPrivate_Circle> _imagesCircle;
        std::vector<CollisionPrivate_Rectangle> _imagesRectangle;
};

namespace Collision {
    bool isColliding(sf::CircleShape &shape1, sf::CircleShape &shape2);             // circle vs circle
    bool isColliding(sf::CircleShape &shape1, sf::RectangleShape &shape2);          // circle vs rect
    bool isColliding(sf::RectangleShape &shape1, sf::CircleShape &shape2);          // rect vs circle
    bool isColliding(sf::RectangleShape &shape1, sf::RectangleShape &shape2);       // rect vs rect
    bool isColliding(sf::Sprite &sprite, sf::CircleShape &circle);                  // sprite vs circle
    bool isColliding(sf::CircleShape &circle, sf::Sprite &sprite);                  // circle vs sprite
    bool isColliding(sf::RectangleShape &rect, sf::Sprite &sprite);                 // rect vs sprite
    bool isColliding(sf::Sprite &sprite1, sf::Sprite &sprite2);                     // sprite vs sprite
} // namespace Collison

