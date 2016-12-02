#include "stdafx.h"
#include <fstream>
#include <sstream>
#include "Pattern.h"
#include "EntityManager.h"
#include "StaticObj.h"
#include "Enemy.h"
#include <fstream>

Pattern::Pattern(EntityManager* entity_manager, ResourceManager<sf::Texture, std::string>* resource_manager)
	: entity_manager_(entity_manager), resource_manager_(resource_manager){
}

Pattern::~Pattern() = default;

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    // thanks StackOverflow
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

void Pattern::loadFile(std::string filename) {
	std::ifstream file("Patterns/" + filename);
	std::string str;
	std::vector<std::string> parts;

	while (std::getline(file, str)) {
		std::vector<std::string> parts;
		split(str, ' ', parts);
		std::string enemy_id = parts[0];
		sfld::Vector2f position = Vector2f(std::stoi(parts[1])*TILE_SIZE + TILE_SIZE/2, std::stoi(parts[2])*TILE_SIZE + TILE_SIZE/2);
		std::vector<Enemy::Action> actions;
		for (int i = 2; i < parts.size(); i++) {
			std::string w = parts[i];
			if (w == "up") {
				actions.push_back(Enemy::ACTION_UP);
			} else if (w == "down") {
				actions.push_back(Enemy::ACTION_DOWN);
			} else if (w == "left") {
				actions.push_back(Enemy::ACTION_LEFT);
			} else if (w == "right") {
				actions.push_back(Enemy::ACTION_RIGHT);
			} else if (w == "shoot") {
				actions.push_back(Enemy::ACTION_SHOOT);
			}
			else if (w == "none") {
				actions.push_back(Enemy::ACTION_NONE);
			}
		}
		addData(PatternData(actions, position, enemy_id));
	}
}

void Pattern::addData(PatternData data) {
	pattern_data_.push_back(data);
}

void Pattern::runPattern() {
	for (auto& it : pattern_data_) {
		if (it.id == "e") {
			entity_manager_->addEnemy(new Enemy(resource_manager_, entity_manager_, it.initial_position, it.actions));
		} //else if...
	}
}
