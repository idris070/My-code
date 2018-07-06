#include "ReceiveEntity.h"
#include "LoadResources.h"
#include "Unit.h"

ReceiveEntity::ReceiveEntity(void)
{
}

ReceiveEntity::ReceiveEntity(float X, float Y, sf::String Name, float Rot)
{
	BulletTank bullet(Name);
	texture = bullet.texture;
	x = X; y = Y; rotation = Rot; name = Name;

	sprite.setTexture(*texture);
	sprite.setOrigin(texture->getSize().x/2,texture->getSize().y/2);
	sprite.setRotation(Rot);
	sprite.setPosition(x,y);
}

ReceiveEntity::ReceiveEntity(float X, float Y, sf::String NameType1, sf::String NameType2, float Rot1, float Rot2)
{
	Tank tank(NameType1);
	WeaponTank weapon(NameType2);
	texture = tank.texture;
	texture2 = weapon.texture;
	if(NameType1 == "player")	texture = &TexturePlayerTank;
	if(NameType2 == "player")	texture2 = &TexturePlayerWeapon;

	sprite.setTexture(*texture);
	sprite2.setTexture(*texture2);
	sprite.setOrigin(texture->getSize().x/2,texture->getSize().y/2);
	sprite2.setOrigin(texture2->getSize().x/2,texture2->getSize().y/2);
	sprite.setRotation(Rot1);
	sprite2.setRotation(Rot2);
	sprite.setPosition(X,Y);
	sprite2.setPosition(X,Y);
}

ReceiveEntity::ReceiveEntity(float X, float Y, int NUM)
{
	texture = &explos[NUM];
	if(texture)
	{
		sprite.setTexture(*texture);
		sprite.setPosition(X,Y);
	}
}


ReceiveEntity::~ReceiveEntity(void)
{
}

void ReceiveEntity::update(float time)
{
}

std::list<ReceiveEntity*> entities2;
std::list<ReceiveEntity*> entities3;
std::list<ReceiveEntity*>::iterator it3;
