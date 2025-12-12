#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "SoundManager.h"

class UIBtn {
    sf::RectangleShape btnRect;
    sf::RectangleShape hoverRect;

    sf::Texture* BtnTexture;

    std::function<void()> onClickCallback;

    bool isHovered = false;
    bool isClicked = false;
public:
    UIBtn() {}  // DEFAULT CONSTRUCTOR (empty)
    UIBtn(sf::Texture* normalTex, sf::Vector2f pos, sf::Vector2f size);

    void SetOnClick(std::function<void()> func);
    void OnClick(sf::Vector2f mousePosition);
    void Update(sf::Vector2f mousePosition);
    void SetTexture(sf::Texture* texture);
    void Draw(sf::RenderWindow& window);
};