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

Color Utilities::HSV_to_RGB(const float H) {
    float HuePrimeColor = fmod(H / 60.0, 6);
    float fX = 1.0f - fabs(fmod(HuePrimeColor, 2.0f) - 1.0f);

    if (0 <= HuePrimeColor && HuePrimeColor < 1) {
        return Color(255, fX * 255, 0);
    }
    else if (1 <= HuePrimeColor && HuePrimeColor < 2) {
        return Color(fX * 255, 255, 0);
    }
    else if (2 <= HuePrimeColor && HuePrimeColor < 3) {
        return Color(0, 255, fX * 255);
    }
    else if (3 <= HuePrimeColor && HuePrimeColor < 4) {
        return Color(0, fX * 255, 255);
    }
    else if (4 <= HuePrimeColor && HuePrimeColor < 5) {
        return Color(fX * 255, 0, 255);
    }
    else if (5 <= HuePrimeColor && HuePrimeColor < 6) {
        return Color(255, 0, fX * 255);
    }
    else {
        return Color(0, 0, 0);
    }
}