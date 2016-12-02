#include "stdafx.h"
#include "Pattern.h"
#include "EntityManager.h"
#include "StaticObj.h"

Pattern::Pattern(EntityManager* entity_manager, ResourceManager<sf::Texture, std::string>* resource_manager)
	: entity_manager_(entity_manager), resource_manager_(resource_manager){
}

Pattern::~Pattern() = default;

void Pattern::add(sfld::Vector2f position, std::string id) {
	contents_.push_back(std::make_pair(position, id));
}

void Pattern::runPattern() {
	for (auto& it : contents_) {
		if (it.second == "test") {
			entity_manager_->addEntity(new StaticObj(resource_manager_, entity_manager_,
				"test2", it.first, Entity::SHAPE_SQUARE, Entity::TYPE_DEFAULT));
		}//else if...
	}
}