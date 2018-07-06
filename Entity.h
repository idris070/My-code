#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include "HandyMathLib\hm.h"
#include <vector>
#include <list>
#include "Unit.h"

// Класс Entity //

enum KeyboardMove{ Up,Down,None };
extern sf::Texture explos[24];

class Entity {
public:
	float x, y, speed,moveTimer,size,reload,secondTimer;
	int w,h,health,sizeWidth,sizeHeight,side,num;
	bool life;
	sf::Vector2f posMouse;
	sf::Sprite sprite,sprite2;
	sf::String name, control, name_type, name_type2;
	KeyboardMove move;
	bool Left, Right, LeftClick;

	SkinnedMesh *mesh1, *mesh2;
	float mesh1_r, mesh2_r, trackTimer;
	sf::Vector3f m2loc;

	Entity();
	Entity(sf::Image &image, float X, float Y, int W, int H);
	Entity(sf::Texture &Texture, float X, float Y, int W, int H);
	Entity(Basis &basis, float X, float Y);
	sf::FloatRect getRect();
	vec2 rotate(vec2 point, float angle);
	int checkCollision(Entity* b);
	virtual void update(float time) = 0;

	// Новое под 3D
	Entity(Unit &unit, float X, float Y);
};

extern std::list<Entity*> entities;
extern std::list<Entity*> entenemy;
extern std::list<Entity*>::iterator it;
extern std::list<Entity*>::iterator it2;

// Класс Entity //

#endif /* ENTITY_H */