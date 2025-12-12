#pragma once
#include "Utilities.h"
#include "UIBtn.h"
#include "SpriteLoader.h"
#include "FilePathes.h"
#include "Enums.h"

class MainMenu {
    RectangleShape Background;

    UIBtn StartBtn;
    UIBtn QuitBtn;

    float TotalTime = 0;
    GameState state;

    void StartBtnClicked();
    void QuitBtnClicked();
public:
    MainMenu();
    ~MainMenu();

    GameState GetState();
    void Reset();
    void Update(RenderWindow& window, const float deltaTime);
    void Draw(RenderWindow& window);
};