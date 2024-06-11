#include "draw.h"


std::vector<sf::Text> drawLoadGame(sf::RenderWindow& window, sf::Font &font) {

    std::vector<std::string>saveNames;
    std::vector<sf::Text> buttons;

    for(const auto&entry : std::filesystem::directory_iterator("reqfiles/saves")) {
        saveNames.push_back(entry.path().filename().generic_string());
    }

    int i = 0;
    int size = 0;
    int xpos = wx/2;
    std::string butName;

    while(i<saveNames.size()) {
        size = static_cast<int>(saveNames[i].size());
        butName = saveNames[i].substr(0,size-(size-getFirstDigit(saveNames[i])));
        butName.append(" " + std::to_string(i));
        buttons.push_back(sf::Text(butName,font));
        buttons[i].setCharacterSize(characterSize);
        buttons[i].setPosition(xpos - buttons[i].getGlobalBounds().width/2,(i*120)+20);
        buttons[i].setFillColor(idleColor);
        i++;
    }

    return buttons;
}

std::vector<sf::Text> drawMenu(sf::RenderWindow &window, sf::Font &font) {

    int xpos = wx / 2;

    auto button1Text = sf::Text{"New game", font};
    button1Text.setCharacterSize(characterSize);
    button1Text.setPosition(xpos - button1Text.getLocalBounds().width/2, 20);
    button1Text.setFillColor(idleColor);
    auto button2Text = sf::Text{"Load game", font};
    button2Text.setCharacterSize(characterSize);
    button2Text.setPosition(xpos - button2Text.getLocalBounds().width/2, 140);
    button2Text.setFillColor(idleColor);
    auto button3Text = sf::Text{"Settings", font};
    button3Text.setCharacterSize(characterSize);
    button3Text.setPosition(xpos - button3Text.getLocalBounds().width/2, 260);
    button3Text.setFillColor(idleColor);
    auto button4Text = sf::Text{"Leaderboard", font};
    button4Text.setCharacterSize(characterSize);
    button4Text.setPosition(xpos - button4Text.getLocalBounds().width/2, 380);
    button4Text.setFillColor(idleColor);
    auto button5Text = sf::Text{"Exit", font};
    button5Text.setCharacterSize(characterSize);
    button5Text.setPosition(xpos - button5Text.getLocalBounds().width/2, 500);
    button5Text.setFillColor(idleColor);
    auto text = std::vector<sf::Text>{button1Text, button2Text, button3Text, button4Text,button5Text};

    window.draw(button1Text);
    window.draw(button2Text);
    window.draw(button3Text);
    window.draw(button4Text);
    window.draw(button5Text);

    return text;
}

std::vector<sf::Text> drawPauseMenu(sf::RenderWindow &window, sf::Font &font) {

    int xpos = wx / 2;

    auto button1Text = sf::Text{"Continue", font};
    button1Text.setCharacterSize(characterSize);
    button1Text.setPosition(xpos - button1Text.getLocalBounds().width/2, 20);
    button1Text.setFillColor(idleColor);
    auto button2Text = sf::Text{"Save", font};
    button2Text.setCharacterSize(characterSize);
    button2Text.setPosition(xpos - button2Text.getLocalBounds().width/2, 140);
    button2Text.setFillColor(idleColor);
    auto button3Text = sf::Text{"Exit", font};
    button3Text.setCharacterSize(characterSize);
    button3Text.setPosition(xpos - button3Text.getLocalBounds().width/2, 260);
    button3Text.setFillColor(idleColor);
    auto text = std::vector<sf::Text>{button1Text,button2Text,button3Text};

    window.draw(button1Text);
    window.draw(button2Text);
    window.draw(button3Text);

    return text;
}

std::vector<sf::Text> drawFailed(sf::RenderWindow &window, sf::Font &font) {

    int xpos = wx / 2;

    auto button1Text = sf::Text{"You failed!", font};
    button1Text.setCharacterSize(characterSize);
    button1Text.setPosition(xpos - button1Text.getLocalBounds().width/2, 20);
    button1Text.setFillColor(sf::Color::Red);
    auto button3Text = sf::Text{"Exit", font};
    button3Text.setCharacterSize(characterSize);
    button3Text.setPosition(xpos - button3Text.getLocalBounds().width/2, 260);
    button3Text.setFillColor(idleColor);
    auto text = std::vector<sf::Text>{button3Text};

    window.draw(button1Text);
    window.draw(button3Text);

    return text;
}

std::vector<sf::Text> drawSettings(sf::RenderWindow &window, sf::Font &font, std::vector<int> const& pos) {

    int xpos = wx / 2;

    auto button1Text = sf::Text{"Font < " + std::to_string(pos[0]) + " >", font};
    button1Text.setCharacterSize(characterSize);
    button1Text.setPosition(xpos - button1Text.getLocalBounds().width/2, 20);
    button1Text.setFillColor(idleColor);
    auto button2Text = sf::Text{"Speed < " + std::to_string(pos[1]) + " >", font};
    button2Text.setCharacterSize(characterSize);
    button2Text.setPosition(xpos - button2Text.getLocalBounds().width/2, 140);
    button2Text.setFillColor(idleColor);
    auto button3Text = sf::Text{"Resolution < " + std::to_string(pos[2]) + " >", font};
    button3Text.setCharacterSize(characterSize);
    button3Text.setPosition(xpos - button3Text.getLocalBounds().width/2, 260);
    button3Text.setFillColor(idleColor);
    auto button4Text = sf::Text{"Exit", font};
    button4Text.setCharacterSize(characterSize);
    button4Text.setPosition(xpos - button4Text.getLocalBounds().width/2, 380);
    button4Text.setFillColor(idleColor);
    auto text = std::vector<sf::Text>{button1Text,button2Text,button3Text,button4Text};

    window.draw(button1Text);
    window.draw(button2Text);
    window.draw(button3Text);
    window.draw(button4Text);

    return text;
}

std::vector<std::vector<sf::Text>>
drawLeaderboard(sf::RenderWindow &window, sf::Font &font, std::vector<leaderboardEntry> const &leaderboard) {
    int yOffset = 120;
    auto leaderboardGraphics = std::vector<std::vector<sf::Text>>();
    int i = 0;
    int element;
    while (i < leaderboard.size() + 1) {
        if (i != 0) {
            leaderboardGraphics.push_back(std::vector<sf::Text>{sf::Text(std::to_string(i), font),
                                                                sf::Text(leaderboard[i - 1].username, font),
                                                                sf::Text(std::to_string(leaderboard[i - 1].wordsTyped),
                                                                         font), sf::Text(
                            std::to_string(leaderboard[i - 1].time).append(" s"), font)});
        } else {
            leaderboardGraphics.push_back(std::vector<sf::Text>{sf::Text("Pos", font), sf::Text("Username", font),
                                                                sf::Text("Amount of words", font),
                                                                sf::Text("Time elapsed", font)});
        }

        element = 0;
        while (element < 4) {
            leaderboardGraphics[i][element].setFillColor(idleColor);

            if (i != 0) {
                leaderboardGraphics[i][element].setCharacterSize(characterSize);
            } else {
                leaderboardGraphics[i][element].setCharacterSize(characterSize / 3);
            }

            if (element == 0) {
                leaderboardGraphics[i][element].setPosition(20, yOffset * (i));
            } else if (element == 1) {
                leaderboardGraphics[i][element].setPosition(240, yOffset * (i));
            } else if (element == 2) {
                leaderboardGraphics[i][element].setPosition(800, yOffset * (i));
            } else if (element == 3) {
                leaderboardGraphics[i][element].setPosition(1400, yOffset * (i));
            }
            window.draw(leaderboardGraphics[i][element]);
            element++;
        }
        i++;
    }

    return leaderboardGraphics;
}

std::pair<sf::Text, sf::Text> drawEnterUsername(sf::RenderWindow &window, sf::Font &font, std::string &username) {
    auto usernameGraphic = sf::Text(username, font);
    usernameGraphic.setCharacterSize(characterSize);
    usernameGraphic.setFillColor(idleColor);
    usernameGraphic.setPosition(wx / 2 - usernameGraphic.getLocalBounds().width/2, wy / 2);

    auto staticText = sf::Text("Enter username", font);
    staticText.setCharacterSize(characterSize);
    staticText.setFillColor(idleColor);
    staticText.setPosition(wx / 2 - staticText.getLocalBounds().width/2, 20);

    window.draw(usernameGraphic);
    window.draw(staticText);

    return std::pair{staticText, usernameGraphic};
}

int drawPlayfield(sf::RenderWindow &window, std::deque<sf::Text> & words, int const &speed) {
    int i = 0;
    int lostWords = 0;

    //move and draw
    while (i < words.size()) {
        if(speed+words[i].getPosition().x+words[i].getGlobalBounds().width>wx){
            deleteIndexDeque(words,i);
            lostWords++;
        }
        if(words.size()!=0){
            words[i].move( speed, 0);
            window.draw(words[i]);
        }
        i++;
    }
    return lostWords;
}

void drawGameUI(sf::RenderWindow &window, sf::Font &font, std::string &wordTyp, long long & timeElapsed, int & wordsLost, int & wordsTyped, bool const& error){
    auto uiBase = sf::RectangleShape(sf::Vector2f(wx,240));
    uiBase.setPosition(0,wy-240);
    uiBase.setFillColor(selectColor);

    auto wordTypGraphic = sf::Text(wordTyp,font,characterSize/2);
    wordTypGraphic.setPosition(20,uiBase.getPosition().y+20);
    wordTypGraphic.setFillColor(idleColor);

    auto underscore = sf::Text("_",font,characterSize/2);
    if(error){
        underscore.setFillColor(sf::Color::Red);
    }else{
        underscore.setFillColor(idleColor);
    }
    underscore.setPosition(wordTypGraphic.getPosition().x+wordTypGraphic.getGlobalBounds().width+wordTypGraphic.getLetterSpacing(),wordTypGraphic.getPosition().y);

    auto wordsLostGraph = sf::Text("Fails: " + std::to_string(wordsLost).append("/10"),font,characterSize/2);
    wordsLostGraph.setFillColor(idleColor);
    wordsLostGraph.setPosition(20,wy-20-wordsLostGraph.getGlobalBounds().height);

    auto wordsTypedG = sf::Text("Words typed: " + std::to_string(wordsTyped),font,characterSize/2);
    wordsTypedG.setFillColor(idleColor);
    wordsTypedG.setPosition(20,wy-40-wordsLostGraph.getGlobalBounds().height-wordsTypedG.getGlobalBounds().height);

    window.draw(uiBase);
    if(timeElapsed%2>=1){
        window.draw(underscore);
    }
    window.draw(wordsLostGraph);
    window.draw(wordTypGraphic);
    window.draw(wordsTypedG);
}