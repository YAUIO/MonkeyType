#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

inline const std::vector<char> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
                                    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
inline const sf::Color &selectColor = sf::Color::Green;
inline const sf::Color &idleColor = sf::Color::White;
const int characterSize = 120;
const int maxLength = 8;
const int wx = 1880;
const int wy = 1000;
const int convToSec = 1000000000;

class leaderboardEntry {
public:
    std::string username;
    long wordsTyped;
    long time;
};