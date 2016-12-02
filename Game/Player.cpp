#include "stdafx.h"
#include "Player.h"
#include "EntityManager.h"
#include "Bullet.h"
#include "ParticleEngine.h"

Player::Player(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager) {
	constructEntity(resourceManager, "player", entityManager, sfld::Vector2f(TILE_SIZE * 7 + TILE_SIZE/2, SCREEN_HEIGHT - 2*TILE_SIZE), Entity::SHAPE_SQUARE, Entity::DYNAMIC_MOVING, Entity::TYPE_DEFAULT);
	health = 10;
	reload_ = (EntityManager::bpm / 60) * 1000 / 2;
	timer_ = reload_;
}

void Player::update(int frame_time) {
	using namespace sf;
	timer_ += frame_time;
}

int Player::getHealth() const {
	return health;
}

void Player::takeDamage(int amount) {
	health -= 1;
	entityManager_->clearEnemies();
	entityManager_->screenShake(10.0f, 500);
	entityManager_->getParticleEngine()->generateExplosionEffect(getPosition());
	//TODO: repeat last pattern
}

void Player::switchColumn(bool left) {
	if (left && getPosition().x >= TILE_SIZE) {
		setPosition(getPosition() - sfld::Vector2f(TILE_SIZE, 0));
	}
	else if (!left && getPosition().x <= SCREEN_WIDTH - TILE_SIZE) {
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
			if (timer_ >= reload_) {
				timer_ = 0;
				entityManager_->addEntity(new Bullet(resourceManager_, entityManager_,
					"bullet", getPosition() + sfld::Vector2f(0, -TILE_SIZE), sfld::Vector2f(0, -1),
					1.0f));
			}
		}
	}
}