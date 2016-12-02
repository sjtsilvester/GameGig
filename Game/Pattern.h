#pragma once

#include "stdafx.h"
#include "ResourceManager.h"

class EntityManager;

class Pattern {
public:
	Pattern(EntityManager* entity_manager, ResourceManager<sf::Texture, std::string>* resource_manager);
	~Pattern();
	
	void runPattern();
	void add(sfld::Vector2f position, std::string id);
private:
	std::vector<std::pair<sfld::Vector2f, std::string>>	contents_;

	EntityManager* entity_manager_;
	ResourceManager<sf::Texture, std::string>* resource_manager_;
};
