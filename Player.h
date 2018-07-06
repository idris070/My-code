#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

extern sf::Vector2f playerPos;
extern float PassedTime;

class Player: public Entity {
public:
	sf::Clock resetTrack;
	int CurrentFrame;
	sf::Vector2i weaponGun;
	BulletTank bullet;

	Player(Tank &tank, WeaponTank &weapon, float X, float Y);
	void rotation(float time, sf::Vector2f pos);
	void update(float time);

	// Новое на 3D

	Player(Unit & unit, float X, float Y);
};

#endif /* PLAYER_H */