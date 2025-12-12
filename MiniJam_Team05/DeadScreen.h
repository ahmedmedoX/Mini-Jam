#pragma once
#include "Utilities.h"
#include "UIBtn.h"
#include "SpriteLoader.h"
#include "FilePathes.h"

class DeadScreen {
    RectangleShape Background;

    UIBtn RestartBtn;
    UIBtn MenuBtn;

    void MenuBtnClicked();
    void RestartBtnClicked();

public:
    DeadScreen();
    void Update(RenderWindow& window);
    void Draw(RenderWindow& window);
};