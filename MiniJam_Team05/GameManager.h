#pragma once
#include "Level_Rock.h"
#include "Level_Forest.h"
#include "Level_Lava.h"
#include "LevelData.h"
#include "FilePathes.h"
#include "Player.h"
#include "MainMenu.h"
#include "DeadScreen.h"
#include "WinScreen.h"
#include "FinalMenu.h"

class GameManager {
    RenderWindow m_window;
    Clock m_deltaClock;
    Clock m_rotationClock;
    float m_deltaTime;

    GameState state;

    unique_ptr<b2World> m_world;
    const float timeStep = 1.0f / (float)Utilities::FPS;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;

    int m_currentIndex = 0;
    vector<LevelData> m_levelData;
    unique_ptr<Level> m_currentLevel;

    unique_ptr<Player> player;
    Direction dir;
    Control control;

    MainMenu* MenuUI;
    DeadScreen* DeathUI;
    WinScreen* WinUI;
    FinalMenu* FinalUI;

    bool restart = true;

    void HandleInput();
    void Update();
    void Draw();
    void SwitchLevel(const int index);
    void RestartLevel();
    void CheckLevelWin();
    void CheckLevelLose();

public:
    GameManager();
    ~GameManager();
    void Run();
};