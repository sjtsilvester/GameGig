#include "stdafx.h"
#include "TopLayerObj.h"

TopLayerObj::TopLayerObj(sf::RectangleShape shape, int duration) 
 : shape_(shape), duration_(duration), time_(0){}

void TopLayerObj::render(sf::RenderTarget* target) {
	target->draw(shape_);
}

bool TopLayerObj::toRemove() const {
	return (time_ >= duration_);
}	

void TopLayerObj::update(int frame_time) {
	time_ += frame_time;
}