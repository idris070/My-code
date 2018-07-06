#include "Entity.h"

Entity::Entity(){

}

Entity::Entity(sf::Image &image, float X, float Y, int W, int H){
	posMouse.x = 0; posMouse.y = 0; secondTimer = 0;
	x = X; y = Y; w = W; h = H; 
	life = true;
	//sprite.setTexture(texture);
	//sprite.setOrigin(w/2, h/2);
	size = sqrt(w*w+h*h);
	sizeWidth = size;
	sizeHeight = size;
}

Entity::Entity(sf::Texture &Texture, float X, float Y, int W, int H){
	posMouse.x = 0; posMouse.y = 0; secondTimer = 0;
	x = X; y = Y; w = W; h = H; 
	life = true;
	sprite.setTexture(Texture);
	sprite.setOrigin(w/2, h/2);
	size = sqrt(w*w+h*h);
	sizeWidth = size;
	sizeHeight = size;
}

Entity::Entity(Basis &basis, float X, float Y){
	posMouse.x = 0; posMouse.y = 0; secondTimer = 0;
	x = X; y = Y; w = basis.width; h = basis.height; 
	life = true;
	sprite.setTexture(*basis.texture);
	sprite.setOrigin(w/2, h/2);
	size = sqrt(w*w+h*h);
	sizeWidth = size;
	sizeHeight = size;
}

sf::FloatRect Entity::getRect(){
	return sf::FloatRect(x-sizeWidth/2, y-sizeHeight/2, sizeWidth, sizeHeight);
}

vec2 Entity::rotate(vec2 point, float angle){
	vec2 rotated_point;
	rotated_point.x = point.x * cos(angle) - point.y * sin(angle);
	rotated_point.y = point.x * sin(angle) + point.y * cos(angle);
	return rotated_point;
}

int Entity::checkCollision(Entity* b)
{
	if (b != this && getRect().intersects(b->getRect()))
	{
		float angl = sprite.getRotation() *3.14/180;
		vec2 vecX = rotate(vec2(0,1),angl);
		vec2 vecY = rotate(vec2(1,0),angl);
		sf::Vector2f c1((-h/2*vecX.x + -w/2*vecY.x) + x, (-h/2*vecX.y + -w/2*vecY.y) + y);
		sf::Vector2f c2((h/2*vecX.x + -w/2*vecY.x) + x, (h/2*vecX.y + -w/2*vecY.y) + y);
		sf::Vector2f c3((h/2*vecX.x + w/2*vecX.y) + x, (h/2*vecY.x + w/2*vecY.y) + y);
		sf::Vector2f c4((-h/2*vecX.x + w/2*vecX.y) + x,(-h/2*vecY.x + w/2*vecY.y) + y);

		angl = b->sprite.getRotation() *3.14/180;
		vecX = rotate(vec2(0,1),angl);
		vecY = rotate(vec2(1,0),angl);
		sf::Vector2f v1((-b->h/2*vecX.x + -b->w/2*vecY.x) + b->x, (-b->h/2*vecX.y + -b->w/2*vecY.y) + b->y);
		sf::Vector2f v2((b->h/2*vecX.x + -b->w/2*vecY.x) + b->x, (b->h/2*vecX.y + -b->w/2*vecY.y) + b->y);
		sf::Vector2f v3((b->h/2*vecX.x + b->w/2*vecX.y) + b->x, (b->h/2*vecY.x + b->w/2*vecY.y) + b->y);
		sf::Vector2f v4((-b->h/2*vecX.x + b->w/2*vecX.y) + b->x, (-b->h/2*vecY.x + b->w/2*vecY.y) + b->y);

		sf::Vector2f v5,c5;
		for (int i = 0; i < 4; i++)
		{
			if(i==0) { c5=v1; v5=c1; }
			if(i==1) { c5=v2; v5=c2; }
			if(i==2) { c5=v3; v5=c3; }
			if(i==3) { c5=v4; v5=c4; }

			float d1 = (c1.x-c5.x)*(c2.y-c1.y)-(c2.x-c1.x)*(c1.y-c5.y);
			float d2 = (c2.x-c5.x)*(c3.y-c2.y)-(c3.x-c2.x)*(c2.y-c5.y);
			float d3 = (c3.x-c5.x)*(c4.y-c3.y)-(c4.x-c3.x)*(c3.y-c5.y);
			float d4 = (c4.x-c5.x)*(c1.y-c4.y)-(c1.x-c4.x)*(c4.y-c5.y);

			float f1 = (v1.x-v5.x)*(v2.y-v1.y)-(v2.x-v1.x)*(v1.y-v5.y);
			float f2 = (v2.x-v5.x)*(v3.y-v2.y)-(v3.x-v2.x)*(v2.y-v5.y);
			float f3 = (v3.x-v5.x)*(v4.y-v3.y)-(v4.x-v3.x)*(v3.y-v5.y);
			float f4 = (v4.x-v5.x)*(v1.y-v4.y)-(v1.x-v4.x)*(v4.y-v5.y);

			if(d1<0 && d2<0 && d3<0 && d4<0 || f1<0 && f2<0 && f3<0 && f4<0){
				side = i;
				return 1;
			}
		}
	}
	return 0;
}

Entity::Entity(Unit & unit, float X, float Y)
{
	trackTimer = 10;
	mesh1_r = 0;
	mesh2_r = 0;
	life = true;
	x = X;
	y = Y;
	mesh1 = unit.Body;
	mesh2 = unit.Gun;
}

std::list<Entity*> entities;
std::list<Entity*> entenemy;
std::list<Entity*>::iterator it;
std::list<Entity*>::iterator it2;

// Класс Entity //