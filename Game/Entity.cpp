#include "stdafx.h"
#include "Entity.h"
#include "Collision.h"
#include "EntityManager.h"

Entity::Entity() = default;
Entity::~Entity() = default;

void Entity::constructEntity(
	ResourceManager<sf::Texture, std::string>* resourceManager, std::string spriteName,
	EntityManager* entityManager, sfld::Vector2f position, ENTITY_SHAPE shape, ENTITY_DYNAMIC dynamic, ENTITY_TYPE type) {
	resourceManager_ = resourceManager;
	entityManager_ = entityManager;
	sprite_ = sf::Sprite(resourceManager_->get(spriteName));
	centreOrigin();
	setPosition(position);
	shape_ = shape;
	dynamic_ = dynamic;
	type_ = type;
	destroyed_ = false;
	rotating_ = false;
}

bool Entity::isDestroyed() const {
	return destroyed_;
}

Entity::ENTITY_DYNAMIC Entity::getDynamic() const{
	return dynamic_;
}

Entity::ENTITY_SHAPE Entity::getShape() const{
	return shape_;
}

Entity::ENTITY_TYPE Entity::getType() const {
	return type_;
}

void Entity::destroy() {
	destroyed_ = true;
}

void Entity::update(int frameTime) {
}

void Entity::render(sf::RenderTarget* target) {
	target->draw(sprite_);
}

sfld::Vector2f Entity::getPosition() const {
	return position_;
}

sf::Sprite Entity::getSprite() const {
	return sprite_;
}

void Entity::collided(Entity* other) {
}

float Entity::getRadius() const {
	//uh, assumes it's a circle!
	return getSprite().getLocalBounds().width;
}

void Entity::setPosition(sfld::Vector2f position) {
	position_ = position;
	sprite_.setPosition(position);
}

void Entity::doOffset(sfld::Vector2f offset) {
	sfld::Vector2f newpos = position_ + offset;
	setPosition(newpos);
}

void Entity::centreOrigin() {
	sfld::Vector2f local_centre(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
	sprite_.setOrigin(local_centre);
}

bool Entity::contains(sfld::Vector2f point) const {
	return getSprite().getGlobalBounds().contains(point);
}

void Entity::move(sfld::Vector2f direction, int frameTime, float magnitude) {
	EntityList* list = entityManager_->getEntities();
	for (auto& it : *list) {
		if (it.get() != this) {
			float dist = sfld::Vector2f(it->getPosition() - getPosition()).length();
			if (dist <= TILE_SIZE*1.5f) { //need accurate collisions here
				MTV mtv(Collision::getCollision(getSprite(), getShape(), it->getSprite(), it->getShape()));
				if (!(mtv.axis == MTV::NONE.axis && mtv.overlap == MTV::NONE.overlap)) {
					;
					//collided
					sfld::Vector2f n = mtv.axis;
					sfld::Vector2f comp_u(0, 0);

					if (direction.dot(n) < 0) {
						if (n != sfld::Vector2f(0, 0)) {
							comp_u = n * (direction.dot(n) / n.dot(n)); //component of hit axis in dir
						}
					}
					direction = direction - comp_u;
					collided(it.get());
					if (it->getDynamic() == DYNAMIC_STATIC) { //because then it won't resolve its own collisions
						it->collided(this);
					}
					}
			}
			else {//otherwise, it's a circle, and we are only concerned with checking if they touch, no more
				if (dist <= TILE_SIZE*1.5f) {
					MTV mtv(Collision::getCollision(getSprite(), getShape(), it->getSprite(), it->getShape()));
					if (!(mtv.axis == MTV::NONE.axis && mtv.overlap == MTV::NONE.overlap)) {
						collided(it.get());
						if (it->getDynamic() == DYNAMIC_STATIC) { //because then it won't resolve its own collisions
							it->collided(this);
						}
					}
				}
			}
		}
	}
	if (direction != sf::Vector2f(0, 0) && !rotating_) {
		sprite_.setRotation(maths::toDegrees(atan2(direction.y, direction.x)));
	}
	doOffset(direction*(float)frameTime*magnitude);
}