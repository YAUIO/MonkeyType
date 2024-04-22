#pragma once
#include "const.h"
#include <thread>
#include <fstream>

std::pair<std::vector<sf::RectangleShape>, std::vector<sf::Text>> drawMenu(sf::RenderWindow &window, sf::Font &font);

std::vector<std::vector<sf::Text>>
drawLeaderboard(sf::RenderWindow &window, sf::Font &font, std::vector<leaderboardEntry> const &leaderboard);

std::pair<sf::Text, sf::Text> drawEnterUsername(sf::RenderWindow &window, sf::Font &font, std::string &username);

void drawPlayfield (sf::RenderWindow &window, std::vector<std::pair<std::string,sf::Text>> words, int const &speed);