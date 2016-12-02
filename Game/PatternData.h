#pragma once

#include "Enemy.h"

struct PatternData {
	PatternData(std::vector<Enemy::Action> a, sfld::Vector2f p, std::string i)
		:actions(a), initial_position(p), id(i) {}
	std::vector<Enemy::Action> actions;
	sfld::Vector2f initial_position;
	std::string id;
};