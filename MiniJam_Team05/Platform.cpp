#include "Platform.h"
#include "Enums.h"	


Platform::Platform(b2World& world, float scale, int length, sf::Vector2f cellSize, b2Vec2 position)
{
    this->position = position;  
    this->length = length;
    this->scale = scale;
    this->cellSize = cellSize;

    filter.categoryBits = GROUND;
    filter.maskBits = PLAYER | BOX | KEY | DOOR;

    SetBody(world);
    SetFixture();
    SetCells();
}

void Platform::SetBody(b2World& world)
{
    float halfWidth = (length * cellSize.x) * 0.5f;
    float halfHeight = cellSize.y * 0.5f;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;

    bodyDef.position.Set(
        (position.x + halfWidth) / scale,
        (position.y + halfHeight) / scale
    );
    body = world.CreateBody(&bodyDef);
}

void Platform::SetFixture()
{
    float halfWidth = (length * cellSize.x * 0.5f) / scale;
    float halfHeight = (cellSize.y * 0.5f) / scale;

    b2PolygonShape boxShape;
    boxShape.SetAsBox(halfWidth, halfHeight);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter = filter;

    body->CreateFixture(&fixtureDef);
}
void Platform::SetCells()
{
    for (int i = 0; i < length; i++)
    {
        b2Vec2 cellPos;
        cellPos.x = position.x + i * cellSize.x;
        cellPos.y = position.y;
        Cell cell( cellSize, cellPos);
        cells.push_back(cell);
    }
}

void Platform::Update()
{
    float angle = body->GetAngle();
    b2Vec2 center = body->GetPosition();

    float cellWidthMeters = cellSize.x / scale;

    float centerOffset = (length * cellWidthMeters) * 0.5f;

    for (int i = 0; i < length; i++)
    {
        float localX = (i * cellWidthMeters) - centerOffset;

        float rotatedX = localX * cos(angle);
        float rotatedY = localX * sin(angle);

        b2Vec2 worldPos;
        worldPos.x = center.x + rotatedX;
        worldPos.y = center.y + rotatedY;

        cells[i].SetPosition(b2Vec2(worldPos.x * scale, worldPos.y * scale));
        cells[i].setRotation(angle * 180.f / 3.14159265f);
    }

    for (auto& cell : cells)
        cell.Update();
}

void Platform::setRotation(float angle)
{
    for (auto& cell : cells) 
        cell.setRotation(angle);
    float radians = angle * 3.14159265f / 180.f;
    body->SetTransform(body->GetPosition(), radians);
}

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& cell : cells)
        target.draw(cell, states);
}

Platform::~Platform() {}
