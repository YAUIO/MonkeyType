#pragma once
#include "const.h"
#include <fstream>
#include <filesystem>
#include <deque>

std::vector<leaderboardEntry> parseLeaderboard();

std::vector<std::string> parseCSV();

std::string generateWord (std::vector<std::string> const& csv);

void interpWord (std::string const& word, sf::Font const& font, std::deque<sf::Text> &vec);