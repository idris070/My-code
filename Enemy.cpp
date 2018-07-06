#include "Enemy.h"
#include "Bullet.h"

Enemy::Enemy(Tank &tank, WeaponTank &weapon, float X, float Y) :Entity(tank,X,Y){
	moveTimer2 = 0; moveTimer = 0; WayTimer = 0;
	name = "Enemy";
	name_type = tank.name;
	name_type2 = weapon.name;
	weaponGun = weapon.GunOrigin;
	bullet = weapon.bullet;
	randB = 1 + rand() % 3;
	speed = 0; speed2 = tank.speed; health = tank.health;
	//texture2.loadFromImage(weapon.image);
	sprite2.setTexture(*weapon.texture);
	sprite2.setOrigin(weapon.width/2, weapon.height/2);
}

void Enemy::TrackWay()
{
	using namespace sf;
	using namespace std;
	Act2.clear();
target:
	targetX = rand() % 50;
	targetY = rand() % 24;
	if(Ground[targetX][targetY]==1)
	goto target;
	Act = search(sf::Vector2i(x, y), sf::Vector2i(targetX,targetY));
	for (itAct = Act.begin(); itAct != Act.end();)
	{
		sf::Vector2i b = *itAct;
		int CorrectX = 16;
		int CorrectY = 16;
		if(Ground[b.x-1][b.y-1]==1 || Ground[b.x-1][b.y]==1 || Ground[b.x-1][b.y+1]==1)
			CorrectX += 16;
		if(Ground[b.x+1][b.y-1]==1 || Ground[b.x+1][b.y]==1 || Ground[b.x+1][b.y+1]==1)
			CorrectX -= 16;
		if(Ground[b.x-1][b.y-1]==1 || Ground[b.x][b.y-1]==1 || Ground[b.x+1][b.y-1]==1)
			CorrectY += 16;
		if(Ground[b.x-1][b.y+1]==1 || Ground[b.x][b.y+1]==1 || Ground[b.x+1][b.y+1]==1)
			CorrectY -= 16;
		itAct->x = b.x*32+CorrectX;
		itAct->y = b.y*32+CorrectY;
		itAct++;
	}
	if(!Act.empty())
	{
		itAct = Act.begin();
		Vector2i start(itAct->x, itAct->y);
		Act2.push_front(start);
		bool check = true;
		Vector2i last;
		for (itAct = Act.begin(); itAct != Act.end();)
		{

			if(itAct == Act.begin()) {
				itAct++; 
				continue;
			}
			Vector2i b = *itAct;
			Vector2i finish(itAct->x,itAct->y);

			float x,y;
			x = finish.x - start.x;
			y = finish.y - start.y;
			float theta_rad = atan2(x,-y);
			float theta_deg = (theta_rad/3.1417*180) + (theta_rad > 0 ? 0 : 360);
			float angl = theta_deg *3.1417/180;
			vec2 vecX = rotate(vec2(0,1),angl);
			vec2 vecY = rotate(vec2(1,0),angl);
			Vector2i s1((0*vecX.x + -w/2*vecY.x) + start.x, (0*vecX.y + -w/2*vecY.y) + start.y);
			Vector2i s2((0*vecX.x + w/2*vecY.x) + start.x, (0*vecX.y + w/2*vecY.y) + start.y);
			Vector2i f1((0*vecX.x + -w/2*vecY.x) + finish.x, (0*vecX.y + -w/2*vecY.y) + finish.y);
			Vector2i f2((0*vecX.x + w/2*vecY.x) + finish.x, (0*vecX.y + w/2*vecY.y) + finish.y);
			for (int x = 0; x < 51; x++)
			for (int y = 0; y < 25; y++)
			if(Ground[x][y]==1)
			if(intersection(s1,f1,Vector2i(x*32, y*32)) || intersection(s2,f2,Vector2i(x*32, y*32)))
			{
				start = finish;
				itAct--;
				Act2.push_front(*itAct);
				itAct++;
				goto reset;
			}
			reset:
			itAct++;
		}
	}
}

void Enemy::rotation(float time, sf::Vector2f pos){
	float dX = pos.x - x; // вектор колинеарный прямой, которая пересекает спрайт и курсор
	float dY = pos.y - y; // вектор колинеарный прямой, которая пересекает спрайт и курсор
	float rotP = sprite2.getRotation();
	float rotation = (atan2(dY,dX)) * 180 / 3.14159265 + 90; // получаем угол в радианах и переводим его в градусы
	if(rotation<0)rotation +=360;
	if(rotP+180>360){
		if(rotation>rotP || rotation < rotP-180) sprite2.rotate(0.5*time*0.1);
		else sprite2.rotate(-0.5*time*0.1);
	}else{
		if(rotP<rotation && rotation<rotP+180) sprite2.rotate(0.5*time*0.1);
		else sprite2.rotate(-0.5*time*0.1);
	}
}

float Enemy::degreesPoints(vec2 a, vec2 b)
{
	float a1,a2,a3,b1,b2,b3;

	a1 = sqrt(pow(a.x,2)+pow(a.y,2));
	a2 = a.x/a1;
	a3 = a.y/a1;

	b1 = sqrt(pow(b.x,2)+pow(b.y,2));
	b2 = b.x/b1;
	b3 = b.y/b1;

	return acos(a2*b2 + a3*b3)*180/3.14;
}

void Enemy::update(float time)
{
	moveTimer = resetMove.getElapsedTime().asSeconds();
	trackTimer = resetTrack.getElapsedTime().asMilliseconds();

	float SinSprite = sin(sprite.getRotation() * 3.14 / 180);
	float CosSprite = cos(sprite.getRotation() * 3.14 / 180);

	if(Act2.empty())
	{
		TrackWay();
		distControl = 100000;
	}
	if(!Act2.empty()){

		// тогда даем точку для движения!
		itAct = Act2.begin();
		sf::Vector2i c = *itAct;
		randX = c.x - x;
		randY = c.y - y;
		// если точка движения есть
		vec2 a1(SinSprite,-CosSprite);
		vec2 a2(randX,randY);
		float grad = degreesPoints(a1,a2);
		if(grad<30)
		{
			x = x + SinSprite * time*speed;
			y = y - CosSprite * time*speed;
		}
			
		float rotP = sprite.getRotation();
		float rot = (atan2(randY,randX)) * 180 / 3.14159265 + 90;
		if(rot<0)rot +=360;
		if(rotP+180>360){
			if(rot>rotP || rot < rotP-180) sprite.rotate(0.5*time*0.1), sprite2.rotate(0.5*time*0.1);
			else sprite.rotate(-0.5*time*0.1), sprite2.rotate(-0.5*time*0.1);
		}else{
			if(rotP<rot && rot<rotP+180) sprite.rotate(0.5*time*0.1),sprite2.rotate(0.5*time*0.1);
			else sprite.rotate(-0.5*time*0.1), sprite2.rotate(-0.5*time*0.1);
		}
		//если дошли до точки то удаляем точку
		int distance = sqrt(randX*randX + randY*randY);
		if(distance<30){
			Act2.erase(itAct);
			distControl = 100000;
		}
		//
		if(secondTimer>WayTimer)
		{
			WayTimer = secondTimer + 1;
			if(distControl<distance)
			{
				TrackWay();
				distControl = 100000;
			}else{
				distControl = distance;
			}
		}
	}

	if(moveTimer > randB) {
		randB = 10 + rand() % 30;
		randB /= 10;
		float angl = sprite2.getRotation() *3.14/180;
		vec2 vecX = rotate(vec2(0,1),angl);
		vec2 vecY = rotate(vec2(1,0),angl);
		sf::Vector2f c1((weaponGun.y*vecX.x + weaponGun.x*vecY.x) + x, (weaponGun.y*vecX.y + weaponGun.x*vecY.y) + y);
		entities.push_back(new Bullet(bullet, c1.x, c1.y, sprite2.getRotation(), "Enemy"));
		resetMove.restart();
	}
		
	if(trackTimer>150) resetTrack.restart();

	for (it2 = entenemy.begin(); it2 != entenemy.end();)
	{
		Entity *b = *it2;//для удобства, чтобы не писать (*it)->
		if(checkCollision(b)){
			float dX = x - b->x;
			float dY = y - b->y;
			float rotation1 = (atan2(dY,dX)) * 180 / 3.14159265 + 90;
			if(rotation1<0)rotation1 +=360;
			float sinMove = sin(rotation1*3.14/180);
			float cosMove = cos(rotation1*3.14/180);

			if(sinMove*b->h*sinMove*b->h>cosMove*b->w*cosMove*b->w)
				x += sinMove,
				x = x - SinSprite * time*speed;
			else
				y -= cosMove,
				y = y + CosSprite * time*speed;
			if(side==0) sprite.rotate(time*0.1);
			if(side==3) sprite.rotate(-time*0.1);
			if(b->name == "Enemy")
			{
				b->x -= sinMove;
				b->y += cosMove;
			}
		}
		it2++;
	}
	if(secondTimer>moveTimer2)
	{
		moveTimer2 = secondTimer + 0.1;
		speed = speed2;
		//if(speed<0.01 && speed>-0.01) speed = 0;
	}

	sprite.setPosition(x, y);
	sprite2.setPosition(x, y);

	rotation(time, playerPos);
}

void Enemy::reset(){
	resetTrack.restart();
}