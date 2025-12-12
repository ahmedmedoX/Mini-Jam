#pragma once
#include "Utilities.h"
#include "UIBtn.h"
#include "SpriteLoader.h"
#include "FilePathes.h"

class MainMenu {
    RectangleShape Background;

    UIBtn StartBtn;
    UIBtn QuitBtn;

    RenderWindow* window;

    bool GameStarted = false;

    void StartBtnClicked();
    void QuitBtnClicked();

public:
    MainMenu(RenderWindow& m_window);
    ~MainMenu();

    bool StartGame();
    void Update(RenderWindow& window);
    void Draw(RenderWindow& window);
};
