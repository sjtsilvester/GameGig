#pragma once

#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy(ResourceManager<sf::Texture, std::string>* resourceManager, EntityManager* entityManager);

    void update(int frame_time);
};
