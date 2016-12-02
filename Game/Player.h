#pragma once

#include "Entity.h"

class Player : public Entity {
public:
	Player(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager);

	void update(int frame_time);
};