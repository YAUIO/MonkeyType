#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <filesystem>
#include <string>
#include <cmath>
#include <deque>
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
    std::string pauseState = "no";
    std::string username = "Guest";
    std::string wordTyp;
    bool menu = true;
    bool isLbParsed = true;
    bool isGuest = true;
    bool timerStarted = false;
    long long timeElapsed = 0;
    long long lastWordSpawned = 0;
    long long timeNow = 0;
    int wordsLost = 0;
    auto pos = std::vector<sf::Vector2f>();
    auto csv = std::vector<std::string>();
    auto lb = parseLeaderboard();
    auto start = std::chrono::steady_clock::now();
    auto gameWords = std::deque<sf::Text>();

    while (window.isOpen()) {
        window.clear(bgColor);

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
                wordsLost = 0;
                timeElapsed = 0;
                csv = parseCSV();
                pos.clear();
                gameWords.clear();
                gameState = "username";
                wordTyp = "";
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
            } else if (gameState == "game") {
                if (!timerStarted) {
                    start = std::chrono::steady_clock::now();
                    timerStarted = true;
                }

                if (wordsLost >= 10) {
                    gameState = "failed";
                    //td parsetolb
                }

                timeNow = std::chrono::steady_clock::now().time_since_epoch().count();

                timeElapsed = timeNow - start.time_since_epoch().count(); //time since start
                timeElapsed = timeElapsed / convToSec; //conversion to seconds

                if ((timeNow - lastWordSpawned) / convToSec > 4) {
                    interpWord(generateWord(csv), font, gameWords);
                    lastWordSpawned = std::chrono::steady_clock::now().time_since_epoch().count();
                    pos.push_back(gameWords[gameWords.size() - 1].getPosition());
                }

                auto speed = std::pow(2, timeElapsed / 10000) * speedMultiplier;
                wordsLost += drawPlayfield(window, gameWords, speed);
                drawGameUI(window, font, wordTyp, timeElapsed, wordsLost);
            } else if (gameState == "pause") {
                if (pauseState == "no") {
                    auto posElements = drawPauseMenu(window,font);
                    setActiveTextColor(window,posElements);
                    if (event.type == sf::Event::MouseButtonPressed) {
                        pauseState = getMenuPress(window,posElements);
                    }

                } else if (pauseState == "Continue") {
                    pauseState = "no";
                    gameState = "game";
                }else if (pauseState == "Save") {
                    saveGame(wordsLost,timeElapsed,pos,gameWords,wordTyp,username);
                    gameState = "no";
                    menu = true;
                    menuState = "no";
                    pauseState = "no";
                }else if (pauseState == "Exit") {
                    gameState = "no";
                    menu = true;
                    menuState = "no";
                    pauseState = "no";
                }
            }

        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    if (gameState == "game") {
                        gameState = "pause";
                    }else{
                        menu = true;
                        menuState = "no";
                        gameState = "no";
                    }
                }
            }

            if (gameState != "no") {
                if (gameState == "username") {
                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Enter) {
                            gameState = "game";
                            if (username.empty()) {
                                username = "Guest";
                            }
                        }

                        if (event.key.code == sf::Keyboard::BackSpace) {
                            username = username.substr(0, username.size() - 1);
                        }
                        if (username.length() < 10) {
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
                } else if (gameState == "game") {
                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Enter) {
                            checkEntered(wordTyp, gameWords);
                        }

                        if (event.key.code == sf::Keyboard::BackSpace) {
                            wordTyp = wordTyp.substr(0, wordTyp.size() - 1);
                        }


                        if (event.key.code >= sf::Keyboard::Key::A && event.key.code <= sf::Keyboard::Key::Z) {
                            wordTyp += (char) alphabet[event.key.code];
                        }

                    }
                }
            }
        }

        window.display();
    }
}
