#include "setget.h"

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

void setFillColorDraw(sf::RenderWindow &window, sf::Text &text, sf::Color const &color) {
    text.setFillColor(color);
    window.draw(text);
}

void setActiveTextColor(sf::RenderWindow &window,
                        std::pair<std::vector<sf::RectangleShape>, std::vector<sf::Text>> &elements) {
    int i = 0;
    while (i < elements.second.size()) {
        if (isCursorOnButton(window, elements.first[i])) {
            setFillColorDraw(window, elements.second[i], selectColor);
        } else {
            setFillColorDraw(window, elements.second[i], idleColor);
        }
        i++;
    }
}

std::string
getMenuPress(sf::RenderWindow &window, std::pair<std::vector<sf::RectangleShape>, std::vector<sf::Text>> &elements) {
    using namespace std::chrono_literals;
    std::string returnStr = "no";
    int i = 0;
    while (i < elements.second.size()) {
        if (isCursorOnButton(window, elements.first[i])) {
            returnStr = elements.second[i].getString();
            break;
        } else {
            setFillColorDraw(window, elements.second[i], idleColor);
        }
        i++;
    }

    if (returnStr != "no") {
        auto animationR = 0;
        while (animationR < 6) {
            setFillColorDraw(window, elements.second[i], selectColor);
            window.display();
            std::this_thread::sleep_for(40ms);
            setFillColorDraw(window, elements.second[i], sf::Color::Yellow);
            window.display();
            std::this_thread::sleep_for(40ms);
            animationR++;
        }
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