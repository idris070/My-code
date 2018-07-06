#include "Explosion.h"

Explosion::Explosion(float X, float Y, int W, int H, float Rotation){//всё так же, только взяли в конце состояние игрока (int dir)
	posMouse.x = 0; posMouse.y = 0; secondTimer = 0;
	x = X; y = Y; w = W; h = H; 
	life = true;
	sprite.setTexture(explos[0]);
	sprite.setOrigin(w/2, h/2);
	size = sqrt(w*w+h*h);
	sizeWidth = size;
	sizeHeight = size;

	rotation = Rotation;
	sprite.setRotation(rotation);
	sprite.setPosition(x, y);//задается позицию
}

void Explosion::update(float time)
{
	name = "Explosion";
	timeS = Time.getElapsedTime().asMilliseconds();
	num = timeS/30;
	sprite.setTexture(explos[num]);

	if(timeS >= 30*24)
	life = false;
}