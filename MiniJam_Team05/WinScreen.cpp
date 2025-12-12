#include "WinScreen.h"


WinScreen::WinScreen(sf::Window& window)
{
    RetryTexture.loadFromFile("assets/ui/RestartBotton.png");
    NextTexture.loadFromFile("assets/ui/NextLevelBUtton.png");

    SoundManager::Instance().LoadSound("win", "assets/Audio/you-win.mp3");
    SoundManager::Instance().Play("win");

    RetryBtn = UIBtn(&RetryTexture,
        { Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2 + 100 },
        { 550 * 0.75f, 165 * 0.75f });

    NextBtn = UIBtn(&NextTexture,
        { Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2 - 100 },
        { 550 * 0.75f, 165 * 0.75f });

    RetryBtn.SetOnClick(std::bind(&WinScreen::RestartBtnClicked, this));
    NextBtn.SetOnClick(std::bind(&WinScreen::NextBtnClicked, this));
}




void WinScreen::Update(sf::RenderWindow& window)
{
    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));


    NextBtn.Update(mouse);
    NextBtn.OnClick(mouse);

    RetryBtn.Update(mouse);
    RetryBtn.OnClick(mouse);

}

void WinScreen::Draw(sf::RenderWindow& window) {
    sf::RectangleShape background(sf::Vector2f(Utilities::WINDOW_WIDTH, Utilities::WINDOW_HEIGHT));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color(0, 0, 0, 100));

    window.draw(background);
    RetryBtn.Draw(window);
    NextBtn.Draw(window);
}

void WinScreen::NextBtnClicked()
{
    std::cout << "next!\n";
}
void WinScreen::RestartBtnClicked()
{
    std::cout << "restated!\n";
}