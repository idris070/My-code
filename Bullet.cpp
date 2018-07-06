#include "Bullet.h"


//Bullet::Bullet(Image &image, float X, float Y, int W, int H, float Rotation, string Used) :Entity(image,X,Y,W,H){//всё так же, только взяли в конце состояние игрока (int dir)
//	//obj = lvl.GetObjects("solid");//инициализируем .получаем нужные объекты для взаимодействия пули с картой
//	name = "Bullet";
//	control = Used;
//	rotation = Rotation;
//	speed = 0.6;
//	c = sin(rotation * 3.14 / 180);
//	d = cos(rotation * 3.14 / 180);
//	sprite.setRotation(Rotation);
//	w = 12;
//	h = 38;
//	damage = 5;
//}

Bullet::Bullet(BulletTank bullet, float X, float Y, float Rotation, std::string Used) :Entity(bullet,X,Y){//всё так же, только взяли в конце состояние игрока (int dir)
	//obj = lvl.GetObjects("solid");//инициализируем .получаем нужные объекты для взаимодействия пули с картой
	name = "Bullet";
	name_type = bullet.name;
	control = Used;
	rotation = Rotation;
	speed = bullet.speed;
	damage = bullet.damage;
	c = sin(rotation * 3.14 / 180);
	d = cos(rotation * 3.14 / 180);
	sprite.setRotation(Rotation);
	w = bullet.widthBullet;	h = bullet.heightBullet;
}

sf::FloatRect Bullet::getRect(){
	return sf::FloatRect(x-sizeWidth/2, y-sizeHeight/2, sizeWidth, sizeHeight);
}

void Bullet::update(float time){
	timeS = Time.getElapsedTime().asSeconds();
	x += c * time*speed;
	y -= d * time*speed;
	if(timeS >= 5)	life = false;
	for (it2 = entenemy.begin(); it2 != entenemy.end();)
	{
		Entity *enemy2 = *it2;
		if(enemy2->name != control)
		if(checkCollision(enemy2))
		{
			enemy2->health -= damage;
			if(enemy2->health <= 0)
			{
				enemy2->life = false;
			}
			life = false;
			entities.push_back(new Explosion(x, y, 64, 64, rotation));
			break;
		}
		it2++;
	}
	sprite.setPosition(x, y);//задается позицию пуле
}