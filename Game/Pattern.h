#pragma once

#include "stdafx.h"
#include "ResourceManager.h"
#include "PatternData.h"

class EntityManager;

class Pattern {
public:
	Pattern(EntityManager* entity_manager, ResourceManager<sf::Texture, std::string>* resource_manager);
	~Pattern();
	
	void runPattern();
	void addData(PatternData data);
	void loadFile(std::string filename);
private:
	std::vector<PatternData> pattern_data_;

	EntityManager* entity_manager_;
	ResourceManager<sf::Texture, std::string>* resource_manager_;
};
