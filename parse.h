#pragma once

#include "const.h"
#include <fstream>
#include <filesystem>

std::vector<leaderboardEntry> parseLeaderboard();

std::string generateWord ();

std::pair<std::string,sf::Text> interpWord (std::string const& word, sf::Font const& font, std::vector<std::pair<std::string,sf::Text>> &vec);