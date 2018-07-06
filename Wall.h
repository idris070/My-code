#pragma once
#ifndef WALL_H
#define WALL_H
#include "Entity.h"

class Wall: public Entity {
public:
	sf::Clock resetMove,resetTrack;
	int randX, randY;
	float randB;

	Wall(sf::Image &image, float X, float Y, int W, int H);
	void update(float time);
};
#endif /* WALL_H */