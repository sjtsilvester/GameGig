#include "stdafx.h"
#include "Pattern.h"
#include "EntityManager.h"
#include "StaticObj.h"
#include "Enemy.h"

Pattern::Pattern(EntityManager* entity_manager, ResourceManager<sf::Texture, std::string>* resource_manager)
	: entity_manager_(entity_manager), resource_manager_(resource_manager){
}

Pattern::~Pattern() = default;

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