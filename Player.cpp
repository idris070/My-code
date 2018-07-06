#include "Player.h"
#include "Bullet.h"

Player::Player(Tank &tank, WeaponTank &weapon, float X, float Y) :Entity(tank,X,Y){
	speed = 0; health = 1111111; moveTimer = 0;
	Left = false, Right = false; LeftClick = false;
	name = "Player"; 
	name_type = tank.name; 
	name_type2 = weapon.name;
	weaponGun = weapon.GunOrigin;
	bullet = weapon.bullet;
	reload = 0;
	sprite2.setTexture(*weapon.texture);
	sprite2.setOrigin(weapon.width/2, weapon.height/2);
	CurrentFrame = 0;
}

void Player::rotation(float time, sf::Vector2f pos){
	float dX = pos.x - x;
	float dY = pos.y - y;
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

void Player::update(float time)
{
	while (mesh1_r > 360 || mesh1_r < 0)
	{
		if (mesh1_r > 360)		mesh1_r -= 360;
		else if (mesh1_r < 0)	mesh1_r += 360;
	}
	while (mesh1_r > 360 || mesh1_r < 0)
	{
		if (mesh1_r > 360)		mesh1_r -= 360;
		else if (mesh1_r < 0)	mesh1_r += 360;
	}
	//trackTimer = resetTrack.getElapsedTime().asMilliseconds();
	//if(trackTimer>150) resetTrack.restart();
	//if(trackTimer>35){
	//	if(CurrentFrame==0)
	//	{
	//		//sprite.setTexture(texture3);
	//		CurrentFrame++;
	//	}
	//	else if(CurrentFrame==1)
	//	{
	//		//sprite.setTexture(texture);
	//		CurrentFrame=0;
	//	}
	//	resetTrack.restart();
	//}
	//rotation(time, posMouse);
	//playerPos.x = x;
	//playerPos.y = y;

	float c = sin(mesh1_r * 3.14 / 180);
	float d = cos(mesh1_r * 3.14 / 180);

	x = x - c * time*speed;
	y = y + d * time*speed;
	//for (it2 = entenemy.begin(); it2 != entenemy.end();)
	//{
	//	Entity *b = *it2;//для удобства, чтобы не писать (*it)->
	//	if(checkCollision(b)){
	//		float dX = x - b->x; 
	//		float dY = y - b->y; 
	//		float rotation1 = (atan2(dY,dX)) * 180 / 3.14159265 + 90; // получаем угол в радианах и переводим его в градусы
	//		if(rotation1<0)rotation1 +=360;
	//		float sinMove = sin(rotation1*3.14/180);
	//		float cosMove = cos(rotation1*3.14/180);
	//		if(sinMove*b->h*sinMove*b->h>cosMove*b->w*cosMove*b->w)
	//			x += sinMove*time*0.1,
	//			x = x - c * time*speed;
	//		else
	//			y -= cosMove*time*0.1,
	//			y = y + d * time*speed;
	//		if(speed>0) speed -= 0.007;//останавливаем
	//		else if(speed<0) speed += 0.007;//останавливаем
	//		if(side==0) sprite.rotate(time*0.1);
	//		if(side==3) sprite.rotate(-time*0.1);
	//		if(b->name == "Enemy")
	//		{
	//			b->x -= sinMove;
	//			b->y += cosMove;
	//		}
	//	}
	//	it2++;
	//}
	if(Left){
		mesh1_r += ((-speed*6)*time);
		mesh2_r += ((-speed*6)*time);
	}
	if(Right){
		mesh1_r += ((speed*6)*time);
		mesh2_r += ((speed*6)*time);
	}
	/*if(LeftClick)
	if(reload<secondTimer){
		reload = secondTimer + 0.5;
		float angl = sprite2.getRotation() *3.14/180;
		vec2 vecX = rotate(vec2(0,1),angl);
		vec2 vecY = rotate(vec2(1,0),angl);
		sf::Vector2f c1((weaponGun.y*vecX.x + weaponGun.x*vecY.x) + x, (weaponGun.y*vecX.y + weaponGun.x*vecY.y) + y);
		entities.push_back(new Bullet(bullet, c1.x, c1.y, sprite2.getRotation(), "Player"));
	}*/

	if(move==Up)  speed = 0.01;
	else if(move==Down)  speed = -0.008;
	else if(move==None)  speed = 0;
	trackTimer += speed * time*0.1;

	if (trackTimer < 0) {
		trackTimer = 100000;
	}
	/*if(PassedTime>moveTimer)
	{
		moveTimer = PassedTime + 0.1;
	}*/
//sprite.setPosition(x, y);
//sprite2.setPosition(x, y);
}

Player::Player(Unit & unit, float X, float Y): Entity(unit, X, Y)
{
	move = KeyboardMove::None;
	speed = 0; health = 1111111; moveTimer = 0;
	Left = false, Right = false; LeftClick = false;
	name = "Player";
	reload = 0;
	m2loc = mesh2->GetPosition();
}
