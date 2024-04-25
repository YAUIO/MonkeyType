#pragma once

#include "const.h"
#include <fstream>
#include <filesystem>
#include <deque>

std::vector<leaderboardEntry> parseLeaderboard();

std::string generateWord ();

void interpWord (std::string const& word, sf::Font const& font, std::deque<sf::Text> &vec);