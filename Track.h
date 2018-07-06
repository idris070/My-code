#pragma once
#ifndef TRACK_H
#define TRACK_H
#include "Entity.h"

class Track :public Entity//класс пули
{
public:
	float rotation;
	sf::Clock Time;
	float timeS;

	Track(sf::Image &image, float X, float Y, int W, int H, float Rotation);
	void update(float time);
};
#endif /* TRACK_H */