#include "stdafx.h"
#include "EntityManager.h"
#include "Enemy.h"

Enemy::Enemy(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, sfld::Vector2f initial_pos, std::vector<Action> actions) {
    actions = actions;
    beat_count = 0;
    constructEntity(resourceManager, "enemy", entityManager,  initial_pos, Entity::SHAPE_SQUARE, Entity::DYNAMIC_MOVING, Entity::TYPE_DEFAULT);
}

void Enemy::update(int frame_time) {

}

void Enemy::shoot() {

}

void Enemy::onBeat() {
    if (beat_count >= actions.size()) {
        beat_count = 0;
    }
    Action action = actions[beat_count];
    if (action == ACTION_LEFT) {
        setPosition(getPosition() + sfld::Vector2f(-TILE_SIZE, 0));
    } else if (action == ACTION_LEFT) {
        setPosition(getPosition() + sfld::Vector2f(TILE_SIZE, 0));
    } else if (action == ACTION_RIGHT) {
        setPosition(getPosition() + sfld::Vector2f(0, -TILE_SIZE));
    } else if (action == ACTION_DOWN) {
        setPosition(getPosition() + sfld::Vector2f(0, TILE_SIZE));
    } else if (action == ACTION_SHOOT) {
        shoot();
    }
    beat_count++;
}
