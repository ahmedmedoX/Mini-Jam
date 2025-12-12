#pragma once
#include "Utilities.h"
#include "UIBtn.h"
#include "Enums.h"
#include "SpriteLoader.h"
#include "FilePathes.h"

class DeadScreen {
    RectangleShape Background;

    UIBtn RestartBtn;
    UIBtn MenuBtn;
    RenderTexture MaskTexture;
    CircleShape Mask;
    Sprite DeathUI;

    GameState state;
    bool play = true;
    float TotalTime;

    void MenuBtnClicked();
    void RestartBtnClicked();

public:
    DeadScreen();
    ~DeadScreen();
    void Play();
    void Reset();
    void Death(RenderWindow& window, const float deltaTime,
        const Vector2f Position);
    void Update(RenderWindow& window);
    GameState GetState();
};