#include "LoadResources.h"

sf::Texture TextureTank1,TextureTank2,TextureTank3,
	TextureBullet1,TextureBullet2,TextureBullet3,
	TextureWeapon1,TextureWeapon2,TextureWeapon3,
	TexturePlayerTank,TexturePlayerWeapon,
	TextureEmpty;
sf::Texture explos[24];

SkinnedMesh m_mesh;
SkinnedMesh m_mesh2;
SkinnedMesh GroundMesh;
sf::Texture GroundTex;


bool initMesh() {

	GroundTex.loadFromFile("snow3.jpg");
	if (!m_mesh2.LoadMesh("gun.fbx")) {
		printf("Mesh load failed\n");
		return false;
	}
	if (!m_mesh.LoadMesh("tank.fbx")) {
		printf("Mesh load failed\n");
		return false;
	}
	if (!GroundMesh.LoadMesh("ground.fbx")) {
		printf("Mesh load failed\n");
		return false;
	}

	*GroundMesh.m_Textures[0] = GroundTex;
}

void initTexture()
{
	TextureTank1.loadFromFile("images/tank1_body.png");
	TextureTank2.loadFromFile("images/tank2_body.png");
	TextureTank3.loadFromFile("images/tank3_body.png");

	TextureBullet1.loadFromFile("images/bullet.png");
	TextureBullet2.loadFromFile("images/bullet2.png");
	TextureBullet3.loadFromFile("images/bullet3.png");

	TextureWeapon1.loadFromFile("images/tank1_gun.png");
	TextureWeapon2.loadFromFile("images/tank2_gun.png");
	TextureWeapon3.loadFromFile("images/tank3_gun.png");

	TexturePlayerTank.loadFromFile("images/t1.png");
	TexturePlayerWeapon.loadFromFile("images/t3.png");

	explos[0].loadFromFile("images/explosion/expl_01_0000.png");
	explos[1].loadFromFile("images/explosion/expl_01_0001.png");
	explos[2].loadFromFile("images/explosion/expl_01_0002.png");
	explos[3].loadFromFile("images/explosion/expl_01_0003.png");
	explos[4].loadFromFile("images/explosion/expl_01_0004.png");
	explos[5].loadFromFile("images/explosion/expl_01_0005.png");
	explos[6].loadFromFile("images/explosion/expl_01_0006.png");
	explos[7].loadFromFile("images/explosion/expl_01_0007.png");
	explos[8].loadFromFile("images/explosion/expl_01_0008.png");
	explos[9].loadFromFile("images/explosion/expl_01_0009.png");
	explos[10].loadFromFile("images/explosion/expl_01_0010.png");
	explos[11].loadFromFile("images/explosion/expl_01_0011.png");
	explos[12].loadFromFile("images/explosion/expl_01_0012.png");
	explos[13].loadFromFile("images/explosion/expl_01_0013.png");
	explos[14].loadFromFile("images/explosion/expl_01_0014.png");
	explos[15].loadFromFile("images/explosion/expl_01_0015.png");
	explos[16].loadFromFile("images/explosion/expl_01_0016.png");
	explos[17].loadFromFile("images/explosion/expl_01_0017.png");
	explos[18].loadFromFile("images/explosion/expl_01_0018.png");
	explos[19].loadFromFile("images/explosion/expl_01_0019.png");
	explos[20].loadFromFile("images/explosion/expl_01_0020.png");
	explos[21].loadFromFile("images/explosion/expl_01_0021.png");
	explos[22].loadFromFile("images/explosion/expl_01_0022.png");
	explos[23].loadFromFile("images/explosion/expl_01_0023.png");
}