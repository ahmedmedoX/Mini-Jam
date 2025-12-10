#pragma once
#include "GameObject.h"
#include "Key.h"
#include <vector>
using namespace std;

class Rotator {
	void rotateBodyAround(b2Body* body, const b2Vec2& center, float angle);
public:
	void RotateLevel(vector<unique_ptr<GameObject>>& objects, b2World& world,
		const b2Vec2& center, const float angle);
	void RotateKey(unique_ptr<Key>& Level_Key, b2World& world,
		const b2Vec2& center, const float angle);
};