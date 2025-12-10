#include "Utilities.h"

Vector2f Utilities::Convert_Box2D_SFML_Space(const b2Vec2 position) {
    Vector2f newPosition;
    newPosition.x = position.x * PIXELS_PER_UNIT;
    newPosition.y = position.y * PIXELS_PER_UNIT;
    newPosition.x += WINDOW_WIDTH / 2.0f;
    newPosition.y = (WINDOW_HEIGHT / 2.0f) - newPosition.y;
    return newPosition;
}

b2Vec2 Utilities::Convert_SFML_Box2D_Space(const Vector2f position) {
    b2Vec2 newPosition(0, 0);
    newPosition.x = (position.x - (WINDOW_WIDTH / 2.0f)) / PIXELS_PER_UNIT;
    newPosition.y = ((WINDOW_HEIGHT / 2.0f) - position.y) / PIXELS_PER_UNIT;
    return newPosition;
}

float Utilities::Degree_to_Radian(float angle) {
    return angle * PI / 180.f;
}

float Utilities::Radian_to_Degree(float angle) {
    return angle * 180.0f / (float)PI;
}