#pragma once

#include "const.h"
#include <thread>

bool isCursorOnButton(sf::RenderWindow &window, sf::RectangleShape const &button1);

void setFillColorDraw(sf::RenderWindow &window, sf::Text &text, sf::Color const &color);

void setActiveTextColor(sf::RenderWindow &window,
                        std::pair<std::vector<sf::RectangleShape>, std::vector<sf::Text>> &elements);

std::string
getMenuPress(sf::RenderWindow &window, std::pair<std::vector<sf::RectangleShape>, std::vector<sf::Text>> &elements);

void setActiveTextColorLb(sf::RenderWindow &window, std::vector<std::vector<sf::Text>> &elements);
