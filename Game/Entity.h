#pragma once

#include "stdafx.h"
#include "ResourceManager.h"

class EntityManager;

class Entity : public sf::NonCopyable {
public:
	Entity();
	~Entity();

	virtual void sfmlEvent(sf::Event evt);

	enum ENTITY_DYNAMIC {
		DYNAMIC_MOVING,
		DYNAMIC_STATIC
	};

	enum ENTITY_SHAPE {
		SHAPE_CIRCLE,
		SHAPE_SQUARE
	};

	enum ENTITY_TYPE {
		TYPE_DEFAULT
	};

	virtual void constructEntity(ResourceManager<sf::Texture, std::string>* resourceManager, std::string spriteName, EntityManager* entityManager, sfld::Vector2f position,
		ENTITY_SHAPE shape, ENTITY_DYNAMIC dynamic, ENTITY_TYPE type);

	ENTITY_SHAPE getShape() const;
	ENTITY_DYNAMIC getDynamic() const;
	ENTITY_TYPE getType() const;
	
	virtual void update(int frameTime);
	virtual void render(sf::RenderTarget* target);

	sfld::Vector2f getPosition() const;
	sf::Sprite getSprite() const;
	void setSprite(std::string tex_name);

	bool contains(sfld::Vector2f point) const;

	virtual void collided(Entity* other);
	float getRadius() const;


	bool isDestroyed() const;
	void setPosition(sfld::Vector2f position);

	virtual void takeDamage(int amount);
protected:
	int health;

	bool rotating_;
	void destroy();

	void centreOrigin();
	void move(sfld::Vector2f direction, int frameTime, float magnitude); //moves entity, including collisions with walls

	void doOffset(sfld::Vector2f offset);

	ResourceManager<sf::Texture, std::string>* resourceManager_;
	EntityManager* entityManager_;
	sf::Sprite sprite_;
private:
	ENTITY_SHAPE shape_;
	ENTITY_DYNAMIC dynamic_;
	ENTITY_TYPE type_;
	bool destroyed_;

	sfld::Vector2f position_; //centre position

};
