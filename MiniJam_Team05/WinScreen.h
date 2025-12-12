
#pragma once
#include "Utilities.h"
#include "UIBtn.h"
#include "SoundManager.h"

class WinScreen
{
private:
    RectangleShape Background;

    sf::Texture RetryTexture;
    sf::Texture NextTexture;

    UIBtn RetryBtn;
    UIBtn NextBtn;


    void NextBtnClicked();
    void RestartBtnClicked();

public:
    WinScreen(sf::Window& window);
    void Update(sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
};
