#pragma once
#ifndef RECEIVEENTITY_H
#define RECEIVEENTITY_H
#include "Entity.h"

class ReceiveEntity {
public:
	float x,y,rotation;
	int health;
	sf::String name, control;
	sf::Sprite sprite,sprite2;
	sf::Texture *texture, *texture2;

	ReceiveEntity(void);
	ReceiveEntity(float X, float Y, sf::String Name, float Rot);
	ReceiveEntity(float X, float Y, sf::String NameType1, sf::String NameType2, float Rot1, float Rot2);
	ReceiveEntity(float X, float Y, int NUM);
	~ReceiveEntity(void);
	void update(float time);
};

extern std::list<ReceiveEntity*> entities2;
extern std::list<ReceiveEntity*> entities3;
extern std::list<ReceiveEntity*>::iterator it3;

#endif /* RECEIVEENTITY_H */