#ifndef OBJECTS_H
#define OBJECTS_H

#include "Unit.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Track.h"
#include "Wall.h"

extern sf::View view;
extern sf::Vector2f playerPos;
extern float PassedTime;
extern int** Ground;

extern int width, height;

void setArray(int*** arr);
int intersection(sf::Vector2i a1, sf::Vector2i a2, sf::Vector2i b);
std::list <sf::Vector2i> search(sf::Vector2i s, sf::Vector2i finP);


#endif /* OBJECTS_H */