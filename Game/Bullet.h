#pragma once

#include "Entity.h"

class Bullet : public Entity {
public:
	Bullet(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, std::string tex_name, sfld::Vector2f pos, sfld::Vector2f dir, float speed);
	void update(int frame_time);
	void collided(Entity* other);
private:
	float speed_;
	sfld::Vector2f direction_;
};