#include "stdafx.h"
#include "Player.h"
#include "EntityManager.h"

Player::Player(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager) {
	constructEntity(resourceManager, "test1", entityManager, sfld::Vector2f(40, 700), Entity::SHAPE_SQUARE, Entity::DYNAMIC_MOVING, Entity::TYPE_DEFAULT);
}

void Player::update(int frame_time) {
	using namespace sf;
	
}

void Player::takeDamage(int amount) {
	std::cout << "PLAYER WAS HIT!" << std::endl;
}

void Player::switchColumn(bool left) {
	if (left && getPosition().x >= TILE_SIZE) {
		setPosition(getPosition() - sfld::Vector2f(TILE_SIZE, 0));
	}
	else if (!left && getPosition().x <= 2014 - TILE_SIZE) {
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
	}
}