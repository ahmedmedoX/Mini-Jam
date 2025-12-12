#include "UIBtn.h"

UIBtn::UIBtn(sf::Texture* normalTex, sf::Vector2f position, sf::Vector2f size) {
    BtnTexture = normalTex;

    btnRect.setSize(size);
    btnRect.setOrigin(size / 2.f);
    btnRect.setPosition(position);
    btnRect.setTexture(normalTex);

    hoverRect.setSize(size + sf::Vector2f(10, 10));
    hoverRect.setOrigin((size + sf::Vector2f(10, 10)) / 2.f);
    hoverRect.setPosition(position);
    hoverRect.setFillColor(sf::Color(255, 255, 0, 100));

    SoundManager::Instance().LoadSound("hoversound", "assets/Audio/hover-sound.mp3");
}

void UIBtn::SetOnClick(std::function<void()> func) {
    onClickCallback = func;
}

void UIBtn::OnClick(sf::Vector2f mousePosition) {
    bool over = btnRect.getGlobalBounds().contains(mousePosition);
    bool pressing = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (over && pressing && !isClicked) {
        isClicked = true;
        if (onClickCallback)
            onClickCallback();
    }
    if (!pressing)
        isClicked = false;
}

void UIBtn::Update(sf::Vector2f mousePosition) {
    bool over = btnRect.getGlobalBounds().contains(mousePosition);

    if (over && !isHovered) {
        isHovered = true;
        SoundManager::Instance().Play("hoversound");
    }
    else if (!over && isHovered) {
        isHovered = false;
        btnRect.setTexture(BtnTexture);
    }
}

void UIBtn::Draw(sf::RenderWindow& window) {
    if (isHovered)
        window.draw(hoverRect);
    window.draw(btnRect);
}

void UIBtn::SetTexture(sf::Texture* texture) {
    BtnTexture = texture;
	btnRect.setTexture(texture);
}