#pragma once
#include <deque>
#include <SFML/Graphics.hpp>
#include <vector>
#include <filesystem>
#include <fstream>
#include <string>


inline std::vector<int> readConfig() {
    namespace fs = std::filesystem;
    auto cfgpath = fs::path("reqfiles/Config.txt");
    auto cfgstream = std::fstream(cfgpath);
    auto line = std::string();
    auto cfg = std::vector<int>();

    while (std::getline(cfgstream, line, '\n')) {
        if (line.empty()) {
            break;
        }

        cfg.push_back(std::stoi(line.substr(line.find_last_of(' '))));
    }

    return cfg;
}

inline const std::vector<int> cfg = readConfig();

inline const std::vector<char> alphabet = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
    'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};


const int wx = cfg[0];
const int wy = cfg[1];

//const int colors = cfg[2];
inline const sf::Color &selectColor = sf::Color::Green;
inline const sf::Color &idleColor = sf::Color::White;
inline const sf::Color &bgColor = sf::Color::Black;
inline const sf::Color &animColor = sf::Color::Yellow;

const int maxLength = cfg[3];
const int speedMultiplier = cfg[4];
const int characterSize = cfg[5];
const int convToSec = 1000000000;

class leaderboardEntry {
public:
    std::string username;
    long wordsTyped;
    long time;
};

class Save {
public:
    int wordsLost;
    long long timeElapsed;
    std::vector<sf::Vector2f> pos;
    std::deque<sf::Text> gameWords;
    std::string wordTyp;
    std::string username;
};
