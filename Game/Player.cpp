#include "stdafx.h"
#include "Player.h"
#include "EntityManager.h"
#include "Bullet.h"

Player::Player(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager) {
	constructEntity(resourceManager, "player", entityManager, sfld::Vector2f(5*TILE_SIZE, 700), Entity::SHAPE_SQUARE, Entity::DYNAMIC_MOVING, Entity::TYPE_DEFAULT);
	health = 10;
}

void Player::update(int frame_time) {
	using namespace sf;
}

void Player::takeDamage(int amount) {
	health -= 1;
	entityManager_->clearEnemies();
	entityManager_->screenShake(10.0f, 500);
	//TODO: repeat last pattern
}

void Player::switchColumn(bool left) {
	if (left && getPosition().x >= TILE_SIZE) {
		setPosition(getPosition() - sfld::Vector2f(TILE_SIZE, 0));
	}
	else if (!left && getPosition().x <= 1024 - TILE_SIZE) {
		setPosition(getPosition() + sfld::Vector2f(TILE_SIZE, 0));
	}
}

void Player::sfmlEvent(sf::Event evt) {
	if (evt.type == evt.KeyPressed) {
		if (evt.key.code == sf::Keyboard::A) {
			switchColumn(true);
		}
		else if (evt.key.code == sf::Keyboard::D) {
			switchColumn(false);
		}
		else if (evt.key.code == sf::Keyboard::Space) {
			entityManager_->addEntity(new Bullet(resourceManager_, entityManager_,
				"bullet", getPosition() + sfld::Vector2f(0, -TILE_SIZE), sfld::Vector2f(0, -1),
				1.0f));
		}
	}
}