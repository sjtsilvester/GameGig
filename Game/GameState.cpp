#include "stdafx.h"
#include "GameState.h"
#include "EntityManager.h"
#include "Player.h"
#include "StaticObj.h"
#include "ParticleEngine.h"

GameState::GameState() = default;
GameState::~GameState() = default;

void GameState::sfmlEvent(sf::Event evt) {
	//...
}

void GameState::start() {
	resourceManager_.setDirectory("media/images/");
	resourceManager_.load("test1", "test1.png");
	resourceManager_.load("test2", "test2.png");

	particleEngine_ = std::unique_ptr<ParticleEngine>(new ParticleEngine());

	entityManager_ = std::unique_ptr<EntityManager>(new EntityManager(&resourceManager_, particleEngine_.get()));
	entityManager_->addEntity(new Player(&resourceManager_, entityManager_.get()));
	entityManager_->addEntity(new StaticObj(&resourceManager_, entityManager_.get(), "test2", sfld::Vector2f(200, 200), Entity::SHAPE_SQUARE, Entity::TYPE_DEFAULT));

	

}

void GameState::pause() {

}

void GameState::resume() {

}

void GameState::exit() {

}

void GameState::update(int frame_time) {
	entityManager_->update(frame_time);
}

void GameState::render(sf::RenderTarget* target) {
	entityManager_->render(target);
}

