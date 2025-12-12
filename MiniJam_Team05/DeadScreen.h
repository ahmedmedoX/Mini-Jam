#pragma once
#include "Utilities.h"
#include "UIBtn.h"
#include "SoundManager.h"

class DeadScreen
{
private:
    RectangleShape Background;

    sf::Texture RetryTexture;
    sf::Texture MenuTexture;

    UIBtn RetryBtn;
    UIBtn MenuBtn;


    void MenuBtnClicked();
    void RestartBtnClicked();

public:
    DeadScreen(sf::Window& window);
    void Update(sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
};
