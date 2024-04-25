#pragma once
#include "const.h"
#include <thread>
#include <deque>

template <typename T>
void deleteIndexDeque(std::deque<T> & gameWords, const int & i);

bool isCursorOnButton(sf::RenderWindow &window, sf::RectangleShape const &button1);

void setFillColorDraw(sf::RenderWindow &window, sf::Text &text, sf::Color const &color);

void setActiveTextColor(sf::RenderWindow &window, std::vector<sf::Text> &elements);

std::string
getMenuPress(sf::RenderWindow &window, std::vector<sf::Text> &elements);

void setActiveTextColorLb(sf::RenderWindow &window, std::vector<std::vector<sf::Text>> &elements);

bool checkEntered(std::string & wordTyp, std::deque<sf::Text> & gameWords);
