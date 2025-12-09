#pragma once
#include "Level_Rock.h"
#include "Level_Forest.h"
#include "LevelData.h"

class GameManager {
public:
    GameManager();
    ~GameManager();
    void Run();

private:
    RenderWindow m_window;
    Clock m_deltaClock;
    Clock m_rotationClock;
    float m_deltaTime;

    unique_ptr<b2World> m_world;
    const float timeStep = 1.0f / (float)Utilities::FPS;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;

    unique_ptr<GameObject> m_box;

    std::vector<LevelData> m_levelData;
    std::unique_ptr<Level> m_currentLevel;
    int m_currentIndex = 0;

    void HandleInput();
    void Update();
    void Draw();
    void SwitchLevel(int index);
    void RestartLevel();
    bool CheckWin();
};