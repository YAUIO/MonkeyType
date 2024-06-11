#pragma once
#include "const.h"
#include <thread>
#include <deque>
#include <regex>


template <typename T>
void deleteIndexDeque(std::deque<T> & gameWords, const int & i);

std::vector<int> getDefaultCfg();

std::vector<sf::Text> highlight(std::string &wordTyp, std::deque<sf::Text> &gameWords, sf::Font const& font);

bool isCursorOnButton(sf::RenderWindow &window, sf::RectangleShape const &button1);

void setFillColorDraw(sf::RenderWindow &window, sf::Text &text, sf::Color const &color);

void setActiveTextColor(sf::RenderWindow &window, std::vector<sf::Text> &elements);

std::string
getMenuPress(sf::RenderWindow &window, std::vector<sf::Text> &elements);

int
getMenuPressI(sf::RenderWindow &window, std::vector<sf::Text> &elements);

void setActiveTextColorLb(sf::RenderWindow &window, std::vector<std::vector<sf::Text>> &elements);

bool checkEntered(std::string & wordTyp, std::deque<sf::Text> & gameWords);

void saveGame(Save & data);

void writeToCfg();

void toLeaderboard(leaderboardEntry const& l,std::vector<leaderboardEntry> const & lbv);

int getFirstDigit(std::string & s);

std::string getSavePath(std::string state, std::vector<sf::Text> buttons);