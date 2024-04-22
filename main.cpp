#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include <thread>
#include <fstream>
#include "draw.h"
#include "parse.h"
#include "setget.h"

auto main() -> int {

    //SFML
    auto window = sf::RenderWindow(sf::VideoMode(wx, wy), "MonkeyTyper");
    window.setFramerateLimit(240);
    auto font = sf::Font();
    font.loadFromFile("reqfiles/font.otf");
    auto event = sf::Event();
    auto words = std::vector<sf::Text>();

    //vars
    std::string menuState = "no";
    std::string gameState = "no";
    std::string username = "Guest";
    bool menu = true;
    bool isLbParsed = true;
    bool isGuest = true;
    bool timerStarted = false;
    long long timeElapsed = 0;
    long long lastWordSpawned = 0;
    long long timeNow = 0;
    auto pos = std::vector<sf::Vector2f>();
    auto lb = parseLeaderboard();
    auto start = std::chrono::steady_clock::now();
    auto gameWords = std::vector<std::pair<std::string,sf::Text>>();

    while (window.isOpen()) {
        window.clear(sf::Color::Black);

        if (menu) {
            if (menuState == "no") {
                auto elements = drawMenu(window, font);
                setActiveTextColor(window, elements);
                if (event.type == sf::Event::MouseButtonPressed) {
                    menuState = getMenuPress(window, elements);
                }
            } else if (menuState == "New game") {
                menu = false;
                isLbParsed = false;
                isGuest = true;
                timerStarted = false;
                timeElapsed = 0;
                pos.clear();
                gameWords.clear();
                gameState = "username";
            } else if (menuState == "Settings") {

            } else if (menuState == "Leaderboard") {
                if (!isLbParsed) {
                    lb = parseLeaderboard();
                    isLbParsed = true;
                }
                auto leaderboardText = drawLeaderboard(window, font, lb);
                setActiveTextColorLb(window, leaderboardText);
            } else if (menuState == "Exit") {
                window.close();
            }
        }

        if (gameState != "no") {

            if (gameState == "username") {
                auto usernameGraphic = drawEnterUsername(window, font, username);
            }else if (gameState == "game"){
                if (!timerStarted){
                    start = std::chrono::steady_clock::now();
                    timerStarted = true;
                }

                timeNow = std::chrono::steady_clock::now().time_since_epoch().count();

                timeElapsed = timeNow - start.time_since_epoch().count(); //time since start
                timeElapsed = timeElapsed / convToSec; //conversion to seconds

                if((timeNow - lastWordSpawned) / convToSec > 6){
                    gameWords.push_back(interpWord(generateWord(), font, gameWords));
                    lastWordSpawned = std::chrono::steady_clock::now().time_since_epoch().count();
                    pos.push_back(gameWords[gameWords.size()-1].second.getPosition());
                }
                drawPlayfield(window,gameWords, timeElapsed*4);
            }

        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    menu = true;
                    menuState = "no";
                    gameState = "no";
                }
            }

            if (gameState != "no") {
                if (gameState == "username") {
                    if(event.type == sf::Event::KeyPressed){
                        if (event.key.code == sf::Keyboard::Enter) {
                            gameState = "game";
                            if (username.empty()){
                                username = "Guest";
                            }
                        }

                        if (event.key.code == sf::Keyboard::BackSpace) {
                            username = username.substr(0, username.size() - 1);
                        }
                        if (username.length()<10) {
                            if (event.key.code >= sf::Keyboard::Key::A && event.key.code <= sf::Keyboard::Key::Z) {
                                if (isGuest) {
                                    username = "";
                                    isGuest = false;
                                }
                                username += (char) alphabet[event.key.code];
                            }

                            if (event.key.code == sf::Keyboard::Space) {
                                username += ' ';
                            }
                        }
                    }
                }else if (gameState == "game") {

                }
            }
        }

        window.display();
    }
}
