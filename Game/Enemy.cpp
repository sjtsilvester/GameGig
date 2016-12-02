#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, int initial_x, int initial_y) {
    constructEntity(resourceManager, "enemy", entityManager, sfld::Vector2f(initial_x, initial_y), Entity::SHAPE_SQUARE, Entity::DYNAMIC_MOVING, Entity::TYPE_DEFAULT);
}

void Enemy::update(int frame_time) {

}
