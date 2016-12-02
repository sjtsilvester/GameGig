#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, 
	std::string tex_name, sfld::Vector2f pos, sfld::Vector2f dir, float speed):direction_(dir),speed_(speed) {
	constructEntity(resourceManager, tex_name, entityManager, pos, Entity::SHAPE_CIRCLE, Entity::DYNAMIC_MOVING, Entity::TYPE_BULLET);
}

void Bullet::update(int frame_time) {
	move(direction_, frame_time, speed_);
	if (getPosition().y < 0){
		destroy();
	}
}

void Bullet::collided(Entity* other) {
	destroy();
}