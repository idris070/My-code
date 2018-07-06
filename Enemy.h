#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"

extern int** Ground;
extern std::list <sf::Vector2i> search(sf::Vector2i s, sf::Vector2i finP);
extern int intersection(sf::Vector2i a1, sf::Vector2i a2, sf::Vector2i b);
extern sf::Vector2f playerPos;

class Enemy: public Entity {
public:
	sf::Clock resetMove,resetTrack;
	int randX, randY,targetX,targetY;
	float randB, moveTimer2, speed2, WayTimer,distControl;
	bool WayMove;
	sf::Vector2i weaponGun;
	std::list <sf::Vector2i> Act, Act2;
	std::list <sf::Vector2i>::iterator itAct,itAct2;
	BulletTank bullet;

	Enemy(Tank &tank, WeaponTank &weapon, float X, float Y);
	void TrackWay();
	void rotation(float time, sf::Vector2f pos);
	float degreesPoints(vec2 a, vec2 b);
	void update(float time);
	void reset();
};
#endif /* ENEMY_H */