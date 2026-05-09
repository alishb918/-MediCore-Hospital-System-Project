#pragma once
#pragma once
#ifndef GUI_H
#define GUI_H
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

// Simple button class
class Button {
public:
    sf::RectangleShape box;
    sf::Text label;
    sf::Color normalColor;
    sf::Color hoverColor;

    Button() {}

    void setup(float x, float y, float w, float h,
        const string& text, sf::Font& font,
        sf::Color normal, sf::Color hover) {
        box.setPosition(x, y);
        box.setSize(sf::Vector2f(w, h));
        normalColor = normal;
        hoverColor = hover;
        box.setFillColor(normal);
        box.setOutlineThickness(2);
        box.setOutlineColor(sf::Color::White);

        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(20);
        label.setFillColor(sf::Color::White);

        // Center text in button
        sf::FloatRect textBounds = label.getLocalBounds();
        label.setPosition(
            x + (w - textBounds.width) / 2,
            y + (h - textBounds.height) / 2 - 5
        );
    }

    bool isHovered(sf::RenderWindow& window) {
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        return box.getGlobalBounds().contains(
            (float)mouse.x, (float)mouse.y);
    }

    void update(sf::RenderWindow& window) {
        if (isHovered(window))
            box.setFillColor(hoverColor);
        else
            box.setFillColor(normalColor);
    }

    bool isClicked(sf::RenderWindow& window, sf::Event& event) {
        return event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left &&
            isHovered(window);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(box);
        window.draw(label);
    }
};

// Simple input box class
class InputBox {
public:
    sf::RectangleShape box;
    sf::Text text;
    sf::Text placeholder;
    string input;
    bool active;
    bool isPassword;

    InputBox() : active(false), isPassword(false) {}

    void setup(float x, float y, float w, float h,
        const string& hint, sf::Font& font,
        bool password = false) {
        box.setPosition(x, y);
        box.setSize(sf::Vector2f(w, h));
        box.setFillColor(sf::Color(50, 50, 50));
        box.setOutlineThickness(2);
        box.setOutlineColor(sf::Color(150, 150, 150));
        isPassword = password;

        text.setFont(font);
        text.setCharacterSize(18);
        text.setFillColor(sf::Color::White);
        text.setPosition(x + 10, y + 10);

        placeholder.setFont(font);
        placeholder.setString(hint);
        placeholder.setCharacterSize(18);
        placeholder.setFillColor(sf::Color(150, 150, 150));
        placeholder.setPosition(x + 10, y + 10);
    }

    void handleEvent(sf::Event& event,
        sf::RenderWindow& window) {
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mouse =
                sf::Mouse::getPosition(window);
            active = box.getGlobalBounds().contains(
                (float)mouse.x, (float)mouse.y);
            box.setOutlineColor(active ?
                sf::Color::Cyan : sf::Color(150, 150, 150));
        }

        if (active && event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8 && !input.empty())
                input.pop_back(); // backspace
            else if (event.text.unicode >= 32 &&
                event.text.unicode < 128)
                input += (char)event.text.unicode;

            string display = isPassword ?
                string(input.size(), '*') : input;
            text.setString(display);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(box);
        if (input.empty())
            window.draw(placeholder);
        else
            window.draw(text);
    }

    string getValue() { return input; }
    void clear() {
        input = "";
        text.setString("");
    }
};
#endif
