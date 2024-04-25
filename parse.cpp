#include "parse.h"

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

std::string generateWord (){
    int length = maxLength;

    if(maxLength>4){
        length -= rand()%4;
    }

    int i = 0;
    auto word = std::string();
    while(i<length){
        word += alphabet[rand()%26];
        i++;
    }
    return word;
}

void interpWord (std::string const& word, sf::Font const& font, std::deque<sf::Text> &vec){
    auto graphWord = sf::Text(word,font);
    float ry;
    int i = 0;
    bool nUniq = false;
    graphWord.setFillColor(idleColor);
    graphWord.setCharacterSize(characterSize/2);
    if(!vec.empty()) {
        while (!nUniq) {
            ry = rand() % static_cast<int>(wy-(240+graphWord.getGlobalBounds().height));
            i = 0;
            while (i < vec.size()) {
                if ( vec[i].getPosition().y + graphWord.getLocalBounds().height + 20 < ry) {
                    i++;
                } else if (vec[i].getPosition().y > ry + graphWord.getLocalBounds().height + 20.f){
                    i++;
                } else if (vec[i].getPosition().x > graphWord.getLocalBounds().width) {
                    i++;
                } else {
                    break;
                }
            }
            if (i == vec.size()){
                break;
            }else{
                nUniq = false;
            }
        }
    }else{
        ry = rand() % wy;
    }
    graphWord.setPosition(-graphWord.getLocalBounds().width,ry);
    vec.push_back(graphWord);
}