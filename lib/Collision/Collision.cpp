/*
** EPITECH PROJECT, 2022
** advencedCollision
** File description:
** Collision
*/

#include "Collision.hpp"
#include <iostream>

/**
 * @brief check if two circle are colliding
 * 
 * @param shape1
 * @param shape2
 * @return true
 * @return false
 */
bool Collision::isColliding(sf::CircleShape &shape1, sf::CircleShape &shape2)
{
    sf::Vector2f pos1 = shape1.getPosition();
    sf::Vector2f pos2 = shape2.getPosition();
    float radius1 = shape1.getRadius();
    float radius2 = shape2.getRadius();

    if (sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2)) <= radius1 + radius2)
        return true;
    return false;
}

/**
 * @brief Check collision between a circle and a rectangle
 * 
 * @param circle CircleShape
 * @param rect RectangleShape
 * @return true 
 * @return false 
 */
bool Collision::isColliding(sf::CircleShape &circle, sf::RectangleShape &rect)
{
    sf::Vector2f circlePos = circle.getPosition();
    sf::Vector2f rectPos = {rect.getPosition().x - rect.getSize().x / 2, rect.getPosition().y - rect.getSize().y / 2};
    float testX = circlePos.x;
    float testY = circlePos.y;

    if (circlePos.x < rectPos.x)
        testX = rectPos.x;
    else if (circlePos.x > rectPos.x + rect.getSize().x)
        testX = rectPos.x + rect.getSize().x;
    if (circlePos.y < rectPos.y)
        testY = rectPos.y;
    else if (circlePos.y > rectPos.y + rect.getSize().y)
        testY = rectPos.y + rect.getSize().y;
    
    if (sqrt(pow(circlePos.x - testX, 2) + pow(circlePos.y - testY, 2)) <= circle.getRadius())
        return true;
    return false;
}

/**
 * @brief check if Rectangles are colliding with circle
 * 
 * @param rect
 * @param circle
 * @return true
 * @return false
 */
bool Collision::isColliding(sf::RectangleShape &rect, sf::CircleShape &circle)
{
    return isColliding(circle, rect);
}

/**
 * @brief Check if two rectangles are colliding
 * 
 * @param rect1
 * @param rect2
 * @return true
 * @return false
 */
bool Collision::isColliding(sf::RectangleShape &shape1, sf::RectangleShape &shape2)
{
    if (shape1.getGlobalBounds().intersects(shape2.getGlobalBounds()))
        return true;
    return false;
}

static sf::FloatRect intersects(sf::FloatRect rectangle, sf::FloatRect intersection)
{
    sf::FloatRect result;
    result.left = static_cast<float>(std::max(rectangle.left, intersection.left));
    result.top = static_cast<float>(std::max(rectangle.top, intersection.top));
    result.width = static_cast<float>(std::min(rectangle.left + rectangle.width, intersection.left + intersection.width) - result.left);
    result.height = static_cast<float>(std::min(rectangle.top + rectangle.height, intersection.top + intersection.height) - result.top);
    return result;

}

static bool pixelExist(sf::Color color)
{
    if (color.a != 0 && color.r != 0 && color.g != 0 && color.b != 0)
        return true;
    return false;
}

/**
 * @brief Check if a sprite is colliding with a circle
 * @deprecated This function use sf::image a lot, it's not optimized
 * @param sprite
 * @param Circle 
 * @return true / false
 */
bool Collision::isColliding(sf::Sprite &sprite, sf::CircleShape &circle)
{
    CollisionPrivate *instance = CollisionPrivate::getInstance();
    std::cout << circle.getGlobalBounds().intersects(sprite.getGlobalBounds()) << std::endl;
    if (intersects(sprite.getGlobalBounds(), circle.getGlobalBounds()).width == 0)
        return false;
    sf::Image *image_sprite = instance->getImageSprite(sprite);
    sf::Image *image_circle = instance->getImageCircle(circle);
    sf::FloatRect rect = intersects(sprite.getGlobalBounds(), circle.getGlobalBounds());
    sf::Image image;
    sf::Image image2;
    image.create(circle.getGlobalBounds().width, circle.getGlobalBounds().height, sf::Color::Transparent);
    image2.create(circle.getGlobalBounds().width, circle.getGlobalBounds().height, sf::Color::Transparent);
    image.copy(*image_circle, 0, 0, sf::IntRect(rect.left, rect.top, rect.width, rect.height), true);
    image2.copy(*image_sprite, 0, 0, sf::IntRect(rect.left, rect.top, rect.width, rect.height), true);
    for ( int i = 0; i < image.getSize().x; i++){
        for ( int j = 0; j < image.getSize().y; j++){
            if (image.getPixel(i, j) != sf::Color::Transparent && pixelExist(image2.getPixel(i, j))){
                return true;
            }
        }
    }
    return false;
}

bool Collision::isColliding(sf::RectangleShape &rect, sf::Sprite &sprite)
{
    CollisionPrivate *instance = CollisionPrivate::getInstance();
    // if (sprite.getGlobalBounds().intersects(rect.getGlobalBounds()) == false)
    //     return false;
    sf::Image *image_sprite = instance->getImageSprite(sprite);
    sf::Image *image_rect = instance->getImageRectangle(rect);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
        image_rect->saveToFile("rect.png");
        image_sprite->saveToFile("sprite.png");
    }
    sf::FloatRect rect2 = intersects(sprite.getGlobalBounds(), rect.getGlobalBounds());
    sf::Image image;
    sf::Image image2;
    image.create(rect.getGlobalBounds().width, rect.getGlobalBounds().height, sf::Color::Transparent);
    image2.create(rect.getGlobalBounds().width, rect.getGlobalBounds().height, sf::Color::Transparent);
    image.copy(*image_sprite, 0, 0, sf::IntRect(rect2.left, rect2.top, rect2.width, rect2.height), true);
    image2.copy(*image_rect, 0, 0, sf::IntRect(rect2.left, rect2.top, rect2.width, rect2.height), true);
    image.saveToFile("image.png");
    image2.saveToFile("image2.png");
    for ( int i = 0; i < image2.getSize().x; i++){
        for ( int j = 0; j < image2.getSize().y; j++){
            if (pixelExist(image.getPixel(i, j))){
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Check if a circle is colliding with a sprite (reverse function) 
 * @deprecated This function use sf::image a lot, it's not optimized
 * @param sprite
 * @param rect
 * @return true / false
 */
bool Collision::isColliding(sf::CircleShape &circle, sf::Sprite &sprite)
{
    return isColliding(sprite, circle);
}

/**
 * @brief Check if two sprites are colliding
 * @deprecated This function use sf::image a lot, it's not optimized
 * @param sprite1
 * @param sprite2
 * @return true / false
 */
bool Collision::isColliding(sf::Sprite &sprite1, sf::Sprite &sprite2)
{
    CollisionPrivate *instance = CollisionPrivate::getInstance();
    if (intersects(sprite1.getGlobalBounds(), sprite2.getGlobalBounds()).width == 0)
        return false;
    sf::Image *image_sprite1 = instance->getImageSprite(sprite1);
    sf::Image *image_sprite2 = instance->getImageSprite(sprite2);
    sf::FloatRect rect = intersects(sprite1.getGlobalBounds(), sprite2.getGlobalBounds());
    sf::Image image;
    sf::Image image2;
    image.create(sprite1.getGlobalBounds().width, sprite1.getGlobalBounds().height, sf::Color::Transparent);
    image2.create(sprite1.getGlobalBounds().width, sprite1.getGlobalBounds().height, sf::Color::Transparent);
    image.copy(*image_sprite1, 0, 0, sf::IntRect(rect.left, rect.top, rect.width, rect.height), true);
    image2.copy(*image_sprite2, 0, 0, sf::IntRect(rect.left, rect.top, rect.width, rect.height), true);
    for ( int i = 0; i < image.getSize().x; i++){
        for ( int j = 0; j < image.getSize().y; j++){
            if (image.getPixel(i, j) != sf::Color::Transparent && pixelExist(image2.getPixel(i, j))){
                return true;
            }
        }
    }
    return false;
}
