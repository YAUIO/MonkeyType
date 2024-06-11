#include "setget.h"
#include "fmt/core.h"
#include "fmt/ranges.h"

template <typename T>
void deleteIndexDeque(std::deque<T> & gameWords, const int & i){
    if (i == gameWords.size()-1){
        gameWords.pop_back();
    }
    else if (i == 0){
        gameWords.pop_front();
    }
    else if (i <= gameWords.size() / 2) {
        auto s = std::deque(gameWords.begin(), gameWords.begin() + i);
        int x = 0;
        while (x <= i) {
            gameWords.pop_front();
            x++;
        }
        s.insert(s.end(), gameWords.begin(), gameWords.end());
        gameWords = s;
    } else if (i > gameWords.size() / 2) {
        auto s = std::deque(gameWords.begin() + i, gameWords.end());
        int x = 0;
        while (x >= i) {
            gameWords.pop_back();
            x++;
        }
        s.insert(s.end(), gameWords.begin(), gameWords.end());
        gameWords = s;
    }
}

bool isCursorOnButton(sf::RenderWindow &window, sf::RectangleShape const &button1) {
    return (sf::Mouse::getPosition(window).x - (button1.getPosition().x) <=
            button1.getSize().x) &&
           (sf::Mouse::getPosition(window).x - (button1.getPosition().x + button1.getSize().x) >=
            button1.getSize().x * -1) &&
           (sf::Mouse::getPosition(window).y - (button1.getPosition().y) <=
            button1.getSize().y) &&
           (sf::Mouse::getPosition(window).y - (button1.getPosition().y + button1.getSize().y) >=
            button1.getSize().y * -1);
}

bool isCursorOnButton(sf::RenderWindow &window, sf::Text const &button1) {
    return (sf::Mouse::getPosition(window).x - (button1.getPosition().x) <=
            button1.getGlobalBounds().width) &&
           (sf::Mouse::getPosition(window).x - (button1.getPosition().x + button1.getGlobalBounds().width) >=
            button1.getGlobalBounds().width * -1) &&
           (sf::Mouse::getPosition(window).y - (button1.getPosition().y) <=
            button1.getGlobalBounds().height) &&
           (sf::Mouse::getPosition(window).y - (button1.getPosition().y + button1.getGlobalBounds().height) >=
            button1.getGlobalBounds().height * -1);
}

void setFillColorDraw(sf::RenderWindow &window, sf::Text &text, sf::Color const &color) {
    text.setFillColor(color);
    window.draw(text);
}

void setActiveTextColor(sf::RenderWindow &window, std::vector<sf::Text> &elements) {
    int i = 0;
    while (i < elements.size()) {
        if (isCursorOnButton(window, elements[i])) {
            setFillColorDraw(window, elements[i], selectColor);
        } else {
            setFillColorDraw(window, elements[i], idleColor);
        }
        i++;
    }
}

std::string
getMenuPress(sf::RenderWindow &window, std::vector<sf::Text> &elements) {
    using namespace std::chrono_literals;
    std::string returnStr = "no";
    int i = 0;
    while (i < elements.size()) {
        if (isCursorOnButton(window, elements[i])) {
            returnStr = elements[i].getString();
            break;
        } else {
            setFillColorDraw(window, elements[i], idleColor);
        }
        i++;
    }

    if (returnStr != "no") {
        auto animationR = 0;
        while (animationR < 6) {
            setFillColorDraw(window, elements[i], selectColor);
            window.display();
            std::this_thread::sleep_for(40ms);
            setFillColorDraw(window, elements[i], animColor);
            window.display();
            std::this_thread::sleep_for(40ms);
            animationR++;
        }
    }

    return returnStr;
}

int
getMenuPressI(sf::RenderWindow &window, std::vector<sf::Text> &elements) {
    using namespace std::chrono_literals;
    int returnStr = -1;
    int i = 0;
    while (i < elements.size()) {
        if (isCursorOnButton(window, elements[i])) {
            returnStr = i;
            break;
        } else {
            setFillColorDraw(window, elements[i], idleColor);
        }
        i++;
    }
    return returnStr;
}

void setActiveTextColorLb(sf::RenderWindow &window, std::vector<std::vector<sf::Text>> &elements) {
    int i = 1;
    int lineC;
    while (i < elements.size()) {
        auto line = sf::RectangleShape(sf::Vector2f(wx, 100));
        line.setPosition(elements[i][0].getPosition().x, elements[i][0].getPosition().y + 22);
        lineC = 0;
        if (isCursorOnButton(window, line)) {
            while (lineC < 4) {
                setFillColorDraw(window, elements[i][lineC], selectColor);
                lineC++;
            }
        } else {
            while (lineC < 4) {
                setFillColorDraw(window, elements[i][lineC], idleColor);
                lineC++;
            }
        }
        i++;
    }
}

int getFirstDigit(std::string & s) {
    int index = 0;

    while(index<s.size()) {
        if(std::regex_match(s.substr(0,index),std::regex(".*[0-9]"))) {
            //fmt::println("{} {}",index,s.substr(0,index));
            return index-1;
        }
        index++;
    }

    return 0;
}

bool checkEntered(std::string &wordTyp, std::deque<sf::Text> &gameWords) {
    int i = 0;
    bool isEntered = false;
    while (i < gameWords.size()) {
        if (wordTyp == gameWords[i].getString()) {
            wordTyp = "";
            isEntered = true;
            break;
        }
        i++;
    }
    if (isEntered){
        deleteIndexDeque(gameWords,i);
    }

    return isEntered;
}

std::vector<std::string> toFMT(std::vector<sf::Vector2f> const& v){
    auto sv = std::vector<std::string>();
    for(sf::Vector2f tf : v){
        sv.push_back(std::to_string(tf.x).append(" ").append(std::to_string(tf.y)));
    }
    return sv;
}

std::vector<std::string> toFMTD(std::deque<sf::Text> const& v){
    auto vs = std::vector<std::string>();

    for(sf::Text t : v){
        vs.push_back(fmt::format("x:{} y:{} string:{}",t.getPosition().x,t.getPosition().y,(std::string)t.getString()));
    }

    return vs;
}

void saveGame(Save & data){
    std::fstream save;
    std::string dir = "reqfiles/saves/";
    std::string saveName = data.username;
    saveName.append(std::to_string(static_cast<long long>(std::chrono::system_clock::now().time_since_epoch().count()))).append(".txt");
    save.open(dir.append(saveName),std::ios::out);

    save << fmt::format("{}\n{}\n{}\n{}\n{}\n{}\n{}\n",data.wordsLost,data.timeElapsed,toFMT(data.pos),toFMTD(data.gameWords),data.wordTyp,data.username,data.wordsTyped);
}

void toLeaderboard(leaderboardEntry const& l, std::vector<leaderboardEntry> const & lbv){
    std::fstream lb;
    std::string dir = "reqfiles/Leaderboard.txt";
    lb.open(dir,std::ios::out | std::fstream::app);
    if(!lbv.empty()){
        lb << '\n';
    }
    lb << fmt::format("{},{},{}",l.username,l.wordsTyped,l.time);
}

std::string getSavePath(std::string state, std::vector<sf::Text> buttons) {
    int i = 0;
    while (i<buttons.size()) {
        if(buttons[i].getString()==state) {
            break;
        }
        i++;
    }
    std::vector<std::string> paths;
    for(const auto& entry : std::filesystem::directory_iterator("reqfiles/saves/")) {
        paths.push_back(entry.path().filename().generic_string());
    }
    return "reqfiles/saves/" + paths[i];
}