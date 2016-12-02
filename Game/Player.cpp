#include "stdafx.h"
#include "Player.h"

Player::Player(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager) {
	constructEntity(resourceManager, "test1", entityManager, sfld::Vector2f(50, 50), Entity::SHAPE_SQUARE, Entity::DYNAMIC_MOVING, Entity::TYPE_DEFAULT);
}

void Player::update(int frame_time) {
	using namespace sf;
	sfld::Vector2f dir(0, 0);
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		dir.y--;
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		dir.x--;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		dir.y++;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		dir.x++;
	}

	move(dir.normalise(), frame_time, 0.5f);
}