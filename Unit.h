#pragma once
#ifndef UNIT_H
#define UNIT_H
#include <SFML/Graphics.hpp>
#include "3D\Skinned_mesh.h"

struct Basis
{
	int width;
	int height;
	sf::Texture *texture;
	sf::String name;
	Basis();
};
struct Tank : Basis
{
	int health;
	float speed;
	Tank();
	Tank(sf::String Name);
};
struct BulletTank : Basis
{
	int damage;
	float speed;
	int widthBullet;
	int heightBullet;
	BulletTank();
	BulletTank(sf::String Name);
};
struct WeaponTank : Basis
{
	BulletTank bullet;
	sf::Vector2i GunOrigin;
	WeaponTank();
	WeaponTank(sf::String Name);
};
struct Unit {
	SkinnedMesh *Body;
	SkinnedMesh *Gun;
};


extern Unit *Tank1;
//extern Tank tank1,tank2,tank3;
//extern WeaponTank weapon1,weapon2,weapon3;
//extern BulletTank bullet1,bullet2,bullet3;
void initUnit();

#endif /* UNIT_H */