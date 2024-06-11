#include "parse.h"

#include <variant>

#include "fmt/ranges.h"

std::vector<leaderboardEntry> parseLeaderboard() {
    namespace fs = std::filesystem;
    auto lbpath = fs::path("reqfiles/Leaderboard.txt");
    auto lbstream = std::fstream(lbpath);
    auto line = std::string();
    auto arg = std::string();
    auto leaderboard = std::vector<leaderboardEntry>();
    int i;
    int lineC = 0;
    long long startPos;
    long long endPos;

    while (std::getline(lbstream, line, '\n')) {
        i = 0;

        if (line == "") {
            break;
        }

        leaderboard.push_back(leaderboardEntry());
        while (i < 3) {
            if (i != 0) {
                startPos = endPos + 1;
            } else {
                startPos = 0;
            }

            if (i != 2) {
                endPos = line.find(',', startPos + 1);
            } else {
                endPos = line.size();
            }

            arg = line.substr(startPos, endPos - startPos);

            if (i == 0) {
                leaderboard[lineC].username = arg;
            } else if (i == 1) {
                leaderboard[lineC].wordsTyped = std::stol(arg);
            } else if (i == 2) {
                leaderboard[lineC].time = std::stol(arg);
            }
            i++;
        }

        lineC++;
    }

    return leaderboard;
}

std::vector<std::string> parseCSV() {
    namespace fs = std::filesystem;
    auto csvpath = fs::path("reqfiles/lib.csv");
    auto csvstream = std::fstream(csvpath);
    auto line = std::string();
    auto arg = std::string();
    auto csv = std::vector<std::string>();
    int lineC = 0;

    while (std::getline(csvstream, line, '\n')) {
        if (line == "") {
            break;
        }

        if (line.size() <= maxLength && !line.empty()) {
            csv.push_back(line.substr(0, line.size() - 1));
        }

        lineC++;
    }

    return csv;
}

std::vector<sf::Vector2f> fromFMT(std::string const &v) {
    auto r = std::vector<sf::Vector2f>();
    int i = 0;
    std::vector<int> space;
    std::vector<int> com;
    while (i < v.size()) {
        if (v[i] == ',') {
            com.push_back(i);
        } else if (v[i] == ' ' && v[i - 1] != ',') {
            space.push_back(i);
        }
        i++;
    }

    i = 0;
    int a = 0;
    while (a < com.size() + 1) {
        if (i != 0) {
            i = com[a - 1] + 1;
        }

        i += 2;

        try {
            r.push_back(sf::Vector2f(std::stof(v.substr(i, space[a] - i)),
                                     std::stof(v.substr(space[a], com[a] - space[a] - 1))));
        } catch (std::invalid_argument const &e) {
        }
        a++;
    }
    //sv.push_back(std::to_string(tf.x).append(" ").append(std::to_string(tf.y)));

    return r;
}

std::deque<sf::Text> fromFMTD(std::string const &v,sf::Font const &font) {
    auto vs = std::deque<sf::Text>();
    //vs.push_back(fmt::format("x:{} y:{} string:{}",t.getPosition().x,t.getPosition().y,(std::string)t.getString()));
    int i = 0;
    std::vector<int> x;
    std::vector<int> y;
    std::vector<int> wrd;
    std::vector<int> com;
    std::vector<int> sp;
    while (i < v.size()) {
        if (v[i] == ':') {
            if (v[i - 1] == 'x') {
                x.push_back(i);
            } else if (v[i - 1] == 'y') {
                y.push_back(i);
            } else if (v[i - 1] == 'g') {
                wrd.push_back(i);
            }
        } else if (v[i] == ',') {
            com.push_back(i);
        } else if (v[i] == ' ') {
            sp.push_back(i);
        }
        i++;
    }

    int a = 0;
    sf::Text b;
    while (a < com.size() + 1) {
        b.setPosition(std::stoi(v.substr(x[a] + 1, sp[a * 3] - x[a])),
                      std::stoi(v.substr(y[a] + 1, sp[a * 3 + 1] - y[a])));

        if (a == com.size()) {
            b.setString(v.substr(wrd[a] + 1, v.size() - 3 - wrd[a]));
        } else {
            b.setString(v.substr(wrd[a] + 1, sp[a * 3 + 2] - wrd[a] - 4));
        }

        b.setFont(font);
        b.setFillColor(idleColor);
        b.setCharacterSize(characterSize / 2);

        vs.push_back(b);
        a++;
    }

    return vs;
}


Save parseSave(std::string const &path, sf::Font const &font) {
    auto save = Save();

    std::fstream saveF;
    std::string line;
    saveF.open(path, std::ios::in);

    std::getline(saveF, line);
    save.wordsLost = std::stoi(line);
    std::getline(saveF, line);
    save.timeElapsed = std::stol(line);
    std::getline(saveF, line);
    save.pos = fromFMT(line);
    std::getline(saveF, line);
    save.gameWords = fromFMTD(line,font);
    std::getline(saveF, line);
    std::getline(saveF, line);
    save.username = line;
    return save;
}

std::string generateWord(std::vector<std::string> const &csv) {
    int length = maxLength;

    if (maxLength >= 6) {
        length -= rand() % 4;
    }

    auto word = std::string();

    word = csv[rand() % csv.size()].substr(0, word.size() - 1);

    return word;
}

void interpWord(std::string const &word, sf::Font const &font, std::deque<sf::Text> &vec) {
    auto graphWord = sf::Text(word, font);
    float ry;
    int i = 0;
    bool nUniq = false;
    graphWord.setFillColor(idleColor);
    graphWord.setCharacterSize(characterSize / 2);
    if (!vec.empty()) {
        while (!nUniq) {
            ry = rand() % static_cast<int>(wy - (240 + graphWord.getGlobalBounds().height));
            i = 0;
            while (i < vec.size()) {
                if (ry > wy - 240) {
                    break;
                }
                if (vec[i].getPosition().y + graphWord.getLocalBounds().height + 20 < ry) {
                    i++;
                } else if (vec[i].getPosition().y > ry + graphWord.getLocalBounds().height + 20.f) {
                    i++;
                } else if (vec[i].getPosition().x > graphWord.getLocalBounds().width) {
                    i++;
                } else {
                    break;
                }
            }
            if (i == vec.size()) {
                break;
            } else {
                nUniq = false;
            }
        }
    } else {
        ry = rand() % static_cast<int>(wy - (240 + graphWord.getGlobalBounds().height));
    }
    graphWord.setPosition(-graphWord.getLocalBounds().width, ry);
    vec.push_back(graphWord);
}
