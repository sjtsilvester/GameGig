#pragma once

#include "stdafx.h"

class TopLayerObj {
public:
	TopLayerObj(sf::RectangleShape shape, int duration);
	virtual void update(int frame_time);
	virtual void render(sf::RenderTarget* target);
	bool toRemove() const;
private:
	int time_;
	int duration_;
	sf::RectangleShape shape_;
};