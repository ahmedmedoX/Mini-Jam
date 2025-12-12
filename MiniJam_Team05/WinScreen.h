
#pragma once
#include "Utilities.h"
#include "UIBtn.h"
#include "SpriteLoader.h"
#include "FilePathes.h"
#include "Enums.h"

class WinScreen {
    RectangleShape Background;
    RectangleShape WinText;

    UIBtn RestartBtn;
    UIBtn NextBtn;

    GameState state;
    bool play = true;

    void NextBtnClicked();
    void RestartBtnClicked();
public:
    WinScreen();
    ~WinScreen();

    void Play();
    void Reset();
    void Update(RenderWindow& window);
    void Draw(RenderWindow& window);
    GameState GetState();
};
