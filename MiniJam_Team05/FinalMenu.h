#pragma once
#include "Utilities.h"
#include "UIBtn.h"
#include "SpriteLoader.h"
#include "FilePathes.h"
#include "Animation.h"
#include "Enums.h"

class FinalMenu
{
    RectangleShape Background;
    RectangleShape Text;
    Sprite Key;
    Animation key_Anim;
    Texture* texture = new Texture();

    UIBtn MenuBtn;
    UIBtn QuitBtn;
    bool Play_Music = true;
    GameState state;

    void MenuBtnClicked();
    void QuitBtnClicked();
public:
    FinalMenu();
    ~FinalMenu();

    GameState GetState();
    void Reset();
    void Update(RenderWindow& window, const float deltaTime);
    void Draw(RenderWindow& window);
};