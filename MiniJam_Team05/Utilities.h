#pragma once
#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>

using namespace sf;

#define PI 3.14f

class Utilities {
public:
	const static unsigned int PIXELS_PER_UNIT = 32;
	const static unsigned int WINDOW_WIDTH = 800;
	const static unsigned int WINDOW_HEIGHT = 800;
	const static unsigned int FPS = 120;
	const static bool DEBUG = false;

	static Vector2f Convert_Box2D_SFML_Space(const b2Vec2 position);
	static b2Vec2 Convert_SFML_Box2D_Space(const Vector2f position);
	static float Degree_to_Radian(float angle);
	static float Radian_to_Degree(float angle);
	static Color HSV_to_RGB(const float H);
};