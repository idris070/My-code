#pragma once
#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"
#include "Explosion.h"

class Bullet :public Entity//класс пули
{
public:
	int damage;
	float rotation,c,d,timeS;
	sf::Clock Time;

	//Bullet(Image &image, float X, float Y, int W, int H, float Rotation, string Used);//всЄ так же, только вз€ли в конце состо€ние игрока (int dir)
	Bullet(BulletTank bullet, float X, float Y, float Rotation, std::string Used);//всЄ так же, только вз€ли в конце состо€ние игрока (int dir)
	sf::FloatRect getRect();
	void update(float time);
};
#endif /* BULLET_H */