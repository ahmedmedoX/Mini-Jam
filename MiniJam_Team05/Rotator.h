#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "GameObject.h"
#include <vector>
using namespace std;

class Rotator
{
public:
	void RotatLevel(vector<GameObject*>& objects, b2World& world,b2Vec2& center, float angleRad);
private:

	void rotateBodyAround(b2Body* body, const b2Vec2& center, float angleRad);

};