#pragma once
#include "GameObject.h"
#include "Key.h"
#include "Door.h"
#include "Spike.h"
#include <vector>
using namespace std;

class Rotator {
	const b2Vec2 center = b2Vec2_zero;
	void rotateBodyAround(b2Body* body, const b2Vec2& center, float angle);
public:
	void RotateLevel(vector<unique_ptr<GameObject>>& objects, const float angle);
	void RotateKey(unique_ptr<Key>& Level_Key, const float angle);
	void RotateDoor(unique_ptr<Door>& Level_Door, const float angle);
	void RotateSpike(vector<unique_ptr<Spike>>& Level_Spike, const float angle);
};