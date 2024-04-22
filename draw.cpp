#include "draw.h"

std::pair<std::vector<sf::RectangleShape>, std::vector<sf::Text>> drawMenu(sf::RenderWindow &window, sf::Font &font) {

    int xpos = wx/2;

    auto button1Text = sf::Text{"New game", font};
    button1Text.setCharacterSize(characterSize);
    button1Text.setPosition(xpos - 727 / 2, 20);
    button1Text.setFillColor(idleColor);
    auto button2Text = sf::Text{"Settings", font};
    button2Text.setCharacterSize(characterSize);
    button2Text.setPosition(xpos - 628 / 2, 140);
    button2Text.setFillColor(idleColor);
    auto button3Text = sf::Text{"Leaderboard", font};
    button3Text.setCharacterSize(characterSize);
    button3Text.setPosition(xpos - 984 / 2, 260);
    button3Text.setFillColor(idleColor);
    auto button4Text = sf::Text{"Exit", font};
    button4Text.setCharacterSize(characterSize);
    button4Text.setPosition(xpos - 282 / 2, 380);
    button4Text.setFillColor(idleColor);
    auto text = std::vector<sf::Text>{button1Text, button2Text, button3Text, button4Text};

    auto button1 = sf::RectangleShape(sf::Vector2f(727, 100));
    button1.setPosition(xpos - 718 / 2, 42);
    button1.setFillColor(sf::Color::Cyan);
    auto button2 = sf::RectangleShape(sf::Vector2f(628, 100));
    button2.setPosition(xpos - 628 / 2, 162);
    button2.setFillColor(sf::Color::Cyan);
    auto button3 = sf::RectangleShape(sf::Vector2f(984, 100));
    button3.setPosition(xpos - 984 / 2, 282);
    button3.setFillColor(sf::Color::Cyan);
    auto button4 = sf::RectangleShape(sf::Vector2f(282, 100));
    button4.setPosition(xpos - 284 / 2, 402);
    button4.setFillColor(sf::Color::Cyan);
    auto hitboxes = std::vector<sf::RectangleShape>{button1, button2, button3, button4};

    /* window.draw(button1);
     window.draw(button2);
     window.draw(button3);
     window.draw(button4);*/
    window.draw(button1Text);
    window.draw(button2Text);
    window.draw(button3Text);
    window.draw(button4Text);

    return std::pair{hitboxes, text};
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
    usernameGraphic.setPosition(wx/2 - 0.04*wx - 28 * username.size(), wy/2);

    auto staticText = sf::Text("Enter username", font);
    staticText.setCharacterSize(characterSize);
    staticText.setFillColor(idleColor);
    staticText.setPosition(wx/4 - 0.04*wx, 20);

    window.draw(usernameGraphic);
    window.draw(staticText);

    return std::pair{staticText, usernameGraphic};
}

void drawPlayfield (sf::RenderWindow &window, std::vector<std::pair<std::string,sf::Text>> words, int const &speed){
    int i = 0;

    //move and draw
    while (i<words.size()){
        if (words[i].second.getPosition().x!=0) {
            words[i].second.move(speed, 0);
        }else{
            words[i].second.setPosition(speed, 0);
        }
        window.draw(words[i].second);
        i++;
    }

}