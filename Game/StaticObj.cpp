#include "stdafx.h"
#include "StaticObj.h"

StaticObj::StaticObj(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, std::string tex_name,
	sfld::Vector2f position, Entity::ENTITY_SHAPE shape, Entity::ENTITY_TYPE type) {
	constructEntity(resourceManager, tex_name, entityManager, position, shape, Entity::DYNAMIC_STATIC, type);

}