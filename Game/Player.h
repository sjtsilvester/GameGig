#pragma once

#include "Entity.h"

class Player : public Entity {
public:
	Player(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager);

	void update(int frame_time);
	void sfmlEvent(sf::Event evt);
	void takeDamage(int amount);
private:
	int timer_;
	int reload_;

	void switchColumn(bool left);
};