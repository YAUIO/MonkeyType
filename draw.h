#pragma once
#include "const.h"
#include "setget.h"
#include <thread>
#include <fstream>
#include <fmt/core.h>
#include <thread>
#include <deque>
#include <fmt/ranges.h>
#include <regex>
#include "setget.h"

std::vector<sf::Text> drawLoadGame(sf::RenderWindow &window, sf::Font &font);

std::vector<sf::Text> drawMenu(sf::RenderWindow &window, sf::Font &font);

std::vector<sf::Text> drawPauseMenu(sf::RenderWindow &window, sf::Font &font);

std::vector<sf::Text> drawSettings(sf::RenderWindow &window, sf::Font &font, std::vector<int> const& pos);

std::vector<sf::Text> drawFailed(sf::RenderWindow &window, sf::Font &font);

std::vector<std::vector<sf::Text>>
drawLeaderboard(sf::RenderWindow &window, sf::Font &font, std::vector<leaderboardEntry> const &leaderboard);

std::pair<sf::Text, sf::Text> drawEnterUsername(sf::RenderWindow &window, sf::Font &font, std::string &username);

int drawPlayfield(sf::RenderWindow &window, std::deque<sf::Text> & words, int const &speed);

void drawGameUI(sf::RenderWindow &window, sf::Font &font, std::string &wordTyp, long long & timeElapsed, int & wordsLost, int & wordsTyped, bool const& error);