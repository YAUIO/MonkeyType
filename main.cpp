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
    switch (fontI) {
        case 0:{
            font.loadFromFile("reqfiles/font.otf");
            break;
        }
        case 1:{
            font.loadFromFile("reqfiles/font1.otf");
            break;
        }
        case 2:{
            font.loadFromFile("reqfiles/font2.otf");
            break;
        }
        default:{
            throw std::runtime_error("font value outside of range");
        }
    }

    auto event = sf::Event();
    auto words = std::vector<sf::Text>();

    //vars
    std::string menuState = "no";
    std::string loadState = "no";
    std::string gameState = "no";
    std::string pauseState = "no";
    std::string username = "Guest";
    std::string setting = "no";
    std::string wordTyp;
    bool menu = true;
    bool isLbParsed = true;
    bool isGuest = true;
    bool timerStarted = false;
    bool errorTyp = false;
    bool rPress = false;
    bool lPress = false;
    bool cfgWritten = true;
    long long timeElapsed = 0;
    long long lastWordSpawned = 0;
    long long timeNow = 0;
    int wordsLost = 0;
    int wordsTyped = 0;
    int indSetting = 0;
    Save loadGame;
    auto posSet = getDefaultCfg();
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
                wordsTyped = 0;
                timeElapsed = 0;
                csv = parseCSV();
                pos.clear();
                gameWords.clear();
                gameState = "username";
                wordTyp = "";
            } else if (menuState == "Load game") {
                auto loadGameText = drawLoadGame(window, font);
                setActiveTextColor(window, loadGameText);
                if (event.type == sf::Event::MouseButtonPressed) {
                    loadState = getMenuPress(window, loadGameText);
                }

                if (loadState != "no") {
                    menu = false;
                    isLbParsed = false;
                    timerStarted = false;
                    csv = parseCSV();
                    gameState = "game";
                    loadGame = parseSave(getSavePath(loadState, loadGameText), font);
                }
            } else if (menuState == "Settings") {
                auto set = drawSettings(window, font, posSet);
                setActiveTextColor(window, set);
                if (event.type == sf::Event::MouseButtonPressed) {
                    setting = getMenuPress(window, set);
                    if (!setting.empty() && setting != "Exit" && setting != "no") {
                        cfgWritten = false;
                        indSetting = getMenuPressI(window, set);
                        if (posSet[indSetting] + 1 < cfgVal[indSetting].size()) {
                            posSet[indSetting]++;
                        } else {
                            posSet[indSetting] = 0;
                        }
                    }
                } else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Key::Right && !rPress) {
                        cfgWritten = false;
                        indSetting = getMenuPressI(window, set);
                        rPress = true;
                        if (posSet[indSetting] + 1 < cfgVal[indSetting].size()) {
                            posSet[indSetting]++;
                        } else {
                            posSet[indSetting] = 0;
                        }
                    } else if (event.key.code == sf::Keyboard::Key::Left && !lPress) {
                        cfgWritten = false;
                        indSetting = getMenuPressI(window, set);
                        lPress = true;
                        if (posSet[indSetting] - 1 >= 0) {
                            posSet[indSetting]--;
                        } else {
                            posSet[indSetting] = cfgVal[indSetting].size() - 1;
                        }
                    }
                } else if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Key::Right && rPress) {
                        rPress = false;
                    } else if (event.key.code == sf::Keyboard::Key::Left && lPress) {
                        lPress = false;
                    }
                }
                if (setting == "Exit") {
                    menuState = "no";
                    setting = "no";
                    indSetting = 0;
                }
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

            if (!cfgWritten) {
                if(cfgVal[0][posSet[0]] != fontI){
                    fontI = cfgVal[0][posSet[0]];
                    switch (fontI) {
                        case 0:{
                            font.loadFromFile("reqfiles/font.otf");
                            break;
                        }
                        case 1:{
                            font.loadFromFile("reqfiles/font1.otf");
                            break;
                        }case 2:{
                            font.loadFromFile("reqfiles/font2.otf");
                            break;
                        }
                        default:{
                            throw std::runtime_error("font value outside of range");
                        }
                    }
                }
                characterSize = cfgVal[1][posSet[1]];
                speedMultiplier = cfgVal[2][posSet[2]];
                if (cfgVal[3][posSet[3]] != wx) {
                    wx = cfgVal[3][posSet[3]];
                    wy = cfgVal[4][posSet[3]];
                    window.create(sf::VideoMode(wx, wy), "MonkeyType");
                }
                writeToCfg();
                cfgWritten = true;
            }
        }

        if (gameState != "no") {
            if (gameState == "username") {
                auto usernameGraphic = drawEnterUsername(window, font, username);
            } else if (gameState == "game") {
                if (!timerStarted) {
                    start = std::chrono::steady_clock::now();
                    if (!loadGame.username.empty()) {
                        wordsTyped = loadGame.wordsTyped;
                        wordsLost = loadGame.wordsLost;
                        gameWords = loadGame.gameWords;
                        pos = loadGame.pos;
                        wordTyp = loadGame.wordTyp;
                        username = loadGame.username;
                        timeElapsed += loadGame.timeElapsed;
                    }
                    timerStarted = true;
                }

                if (wordsLost >= 10) {
                    gameState = "failed";
                    toLeaderboard(leaderboardEntry(username, wordsTyped, timeElapsed), lb);
                }

                timeNow = std::chrono::steady_clock::now().time_since_epoch().count();

                timeElapsed = timeNow - start.time_since_epoch().count(); //time since start
                timeElapsed = timeElapsed / convToSec; //conversion to seconds
                if ((timeNow - lastWordSpawned) / convToSec > 1) {
                    interpWord(generateWord(csv), font, gameWords);
                    lastWordSpawned = std::chrono::steady_clock::now().time_since_epoch().count();
                    pos.push_back(gameWords[gameWords.size() - 1].getPosition());
                }
                auto speed = std::pow(2, timeElapsed / (1000/speedMultiplier));
                wordsLost += drawPlayfield(window, gameWords, speed, font, wordTyp);
                drawGameUI(window, font, wordTyp, timeElapsed, wordsLost, wordsTyped, errorTyp);
            } else if (gameState == "pause") {
                if (pauseState == "no") {
                    auto posElements = drawPauseMenu(window, font);
                    setActiveTextColor(window, posElements);
                    if (event.type == sf::Event::MouseButtonPressed) {
                        pauseState = getMenuPress(window, posElements);
                    }
                } else if (pauseState == "Continue") {
                    pauseState = "no";
                    gameState = "game";
                } else if (pauseState == "Save") {
                    auto save = Save(wordsLost, timeElapsed, pos, gameWords, wordTyp, username, wordsTyped);
                    saveGame(save);
                    gameWords.clear();
                    timerStarted = false;
                    pos.clear();
                    gameState = "no";
                    menu = true;
                    menuState = "no";
                    pauseState = "no";
                    loadState = "no";
                } else if (pauseState == "Exit") {
                    gameWords.clear();
                    wordsTyped = 0;
                    wordTyp.clear();
                    wordsLost = 0;
                    timerStarted = false;
                    pos.clear();
                    gameState = "no";
                    menu = true;
                    menuState = "no";
                    pauseState = "no";
                    loadState = "no";
                }
            } else if (gameState == "failed") {
                auto failed = drawFailed(window, font);
                setActiveTextColor(window, failed);
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (getMenuPress(window, failed) == "Exit") {
                        gameWords.clear();
                        wordsTyped = 0;
                        wordTyp.clear();
                        wordsLost = 0;
                        timerStarted = false;
                        pos.clear();
                        gameState = "no";
                        menu = true;
                        menuState = "no";
                        pauseState = "no";
                        loadState = "no";
                    }
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
                    } else {
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
                            if (checkEntered(wordTyp, gameWords)) {
                                wordsTyped++;
                                errorTyp = false;
                            } else {
                                errorTyp = true;
                                wordTyp = "";
                            }
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
