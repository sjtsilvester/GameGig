#pragma once

#include "Entity.h"

class StaticObj : public Entity {
public:
	StaticObj(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, std::string tex_name, sfld::Vector2f position, Entity::ENTITY_SHAPE shape, Entity::ENTITY_TYPE type);
};