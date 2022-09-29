/*
** EPITECH PROJECT, 2022
** advencedCollision
** File description:
** CollsionPrivate
*/

#include "Collision.hpp"
#include <iostream>

CollisionPrivate::~CollisionPrivate()
{
    for (auto &it : _imagesSprite) {
        delete it.imageSprite;
        delete it.imageAll;
    }
    for (auto &it : _imagesCircle) {
        delete it.imageCircle;
        delete it.imageAll;
    }
}

/**
 * @brief Get the Image Sprite object
 * @deprecated not optimized, using sf::Image
 * @param sprite 
 * @return sf::Image* 
 */
sf::Image *CollisionPrivate::getImageSprite(sf::Sprite &sprite)
{
    for (auto &it : _imagesSprite) {
        if (it.sprite == &sprite){
            if (it.pos != sprite.getPosition()) {
                it.pos = sprite.getPosition();
                it.imageAll->copy(
                    sprite.getTexture()->copyToImage(),
                    (it.pos.x >= 0) ? it.pos.x : 0,
                    (it.pos.y >= 0) ? it.pos.y : 0,
                    sf::IntRect(0, 0, 1920, 1080)
                );
            }
            return it.imageAll;
        }
    }
    CollisionPrivate_Sprite newImage;

    // local variable
    newImage.sprite = &sprite;
    newImage.pos = sprite.getPosition();
    // create a local image of the sprite
    newImage.imageSprite = new sf::Image();
    newImage.imageSprite->copy(sprite.getTexture()->copyToImage(), 0, 0);

    // create a total image
    newImage.imageAll = new sf::Image();
    newImage.imageAll->create(1920, 1080, sf::Color::Transparent);
    newImage.imageAll->copy(sprite.getTexture()->copyToImage(), newImage.pos.x, newImage.pos.y, sf::IntRect(0, 0, 1920, 1080));
    _imagesSprite.push_back(newImage);
    return newImage.imageAll;
}

static void createCircleImage(sf::Image *image, sf::CircleShape &circle)
{
    sf::Vector2f pos = circle.getPosition();
    sf::Vector2f size = circle.getScale();
    sf::Color color = circle.getFillColor();
    float radius = circle.getRadius();

    for (int i = 0; i < radius * 2; i++) {
        for (int j = 0; j < radius * 2; j++) {
            if (sqrt(pow(i - radius, 2) + pow(j - radius, 2)) <= radius) {
                if (pos.x + i >= 0 && pos.y + j >= 0)
                    image->setPixel(pos.x + i, pos.y + j, color);
            }
        }
    }
}

static void createRectangleImage(sf::Image *image, sf::RectangleShape &rect)
{
    sf::Vector2f pos = rect.getPosition();
    sf::Vector2f size = {rect.getGlobalBounds().width, rect.getGlobalBounds().height};
    sf::Color color = rect.getFillColor();

    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            if (pos.x + i >= 0 && pos.y + j >= 0){
                image->setPixel(i, j, color);
            }
        }
    }
}

/**
 * @brief Get the Image Circle object
 * @deprecated not optimized, using sf::Image
 * @param Circle 
 * @return sf::Image* 
 */
sf::Image *CollisionPrivate::getImageCircle(sf::CircleShape &Circle)
{
    for (auto &it : _imagesCircle) {
        if (it.CircleShape == &Circle){
            if (it.pos != Circle.getPosition()) {
                it.pos = Circle.getPosition();
                it.imageAll->copy(
                    *(it.imageCircle),
                    (it.pos.x >= 0) ? it.pos.x : 0,
                    (it.pos.y >= 0) ? it.pos.y : 0,
                    sf::IntRect(0, 0, 1920, 1080)
                );
            }
            return it.imageAll;
        }
    }
    CollisionPrivate_Circle newImage;

    // local variable
    newImage.CircleShape = &Circle;
    newImage.pos = Circle.getPosition();
    // create a local image of the Circle
    newImage.imageCircle = new sf::Image();
    newImage.imageCircle->create(1920, 1080, sf::Color::Transparent);
    createCircleImage(newImage.imageCircle, Circle);

    // create a total image
    newImage.imageAll = new sf::Image();
    newImage.imageAll->create(1920, 1080, sf::Color::Transparent);
    newImage.imageAll->copy(*(newImage.imageCircle), newImage.pos.x, newImage.pos.y, sf::IntRect(0, 0, 1920, 1080));
    _imagesCircle.push_back(newImage);
    return newImage.imageAll;
}

sf::Image *CollisionPrivate::getImageRectangle(sf::RectangleShape &rect)
{
    for (auto &it : _imagesRectangle) {
        if (it.RectangleShape == &rect){
            if (it.pos != rect.getPosition()) {
                it.pos = rect.getPosition();
                it.imageAll->copy(
                    *(it.imageRectangle),
                    (it.pos.x >= 0) ? it.pos.x : 0,
                    (it.pos.y >= 0) ? it.pos.y : 0,
                    sf::IntRect(0, 0, 1920, 1080)
                );
            }
            return it.imageAll;
        }
    }
    CollisionPrivate_Rectangle newImage;

    // local variable
    newImage.RectangleShape = &rect;
    newImage.pos = rect.getPosition();
    // create a local image of the Circle
    newImage.imageRectangle = new sf::Image();
    newImage.imageRectangle->create(1920, 1080, sf::Color::Transparent);
    createRectangleImage(newImage.imageRectangle, rect);

    // create a total image
    newImage.imageAll = new sf::Image();
    newImage.imageAll->create(1920, 1080, sf::Color::Transparent);
    newImage.imageAll->copy(*(newImage.imageRectangle), newImage.pos.x, newImage.pos.y, sf::IntRect(0, 0, 1920, 1080));
    _imagesRectangle.push_back(newImage);

    return newImage.imageAll;
}
