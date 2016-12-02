#include "stdafx.h"
#include "Enemy.h"

Player::Player(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager) {
    constructEntity(resourceManager, "test1", entityManager, sfld::Vector2f(50, 50), Entity::SHAPE_SQUARE, Entity::DYNAMIC_MOVING, Entity::TYPE_DEFAULT);
}

void Player::update(int frame_time) {

}
