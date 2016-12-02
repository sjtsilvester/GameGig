#include "stdafx.h"
#include "EntityManager.h"
#include "Enemy.h"

Enemy::Enemy(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager, int initial_x, int initial_y, vector<Action> actions) {
    actions = actions;
    beat_count = 0;
    constructEntity(resourceManager, "enemy", entityManager, sfld::Vector2f(initial_x, initial_y), Entity::SHAPE_SQUARE, Entity::DYNAMIC_MOVING, Entity::TYPE_DEFAULT);
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
    if (action == Action.Left) {
        setPosition(getPosition() + new Vector2f(-TILE_SIZE, 0));
    } else if (action == Action.Right) {
        setPosition(getPosition() + new Vector2f(TILE_SIZE, 0));
    } else if (action == Action.Up) {
        setPosition(getPosition() + new Vector2f(0, -TILE_SIZE));
    } else if (action == Action.Down) {
        setPosition(getPosition() + new Vector2f(0, TILE_SIZE));
    } else if (action == Action.Shoot) {
        shoot();
    }
    beat_count++;
}
