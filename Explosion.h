#pragma once
#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "Entity.h"
class Explosion :public Entity//класс пули
{
public:
	float rotation;
	sf::Clock Time;
	float timeS;

	Explosion(float X, float Y, int W, int H, float Rotation);
	void update(float time);
};
#endif /* EXPLOSION_H */