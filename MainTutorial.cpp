#include <gl\glew.h>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\Window.hpp>
#include "Util.h"
#include "Pipeline.h"
#include "Camera.h"
#include "Skinning_technique.h"
#include "Skinned_mesh.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define COLOR_TEXTURE_UNIT              GL_TEXTURE0
#define COLOR_TEXTURE_UNIT_INDEX        0

long long m_frameTime;
long long m_startTime;

float GetRunningTime()
{
	float RunningTime = (float)((double)GetCurrentTimeMillis() - (double)m_startTime) / 1000.0f;
	return RunningTime;
}

SkinningTechnique* m_pEffect;
Camera* m_pGameCamera;
DirectionalLight m_directionalLight;
SkinnedMesh m_mesh;
SkinnedMesh m_mesh2;
math3d::Vector3f m_position;
PersProjInfo m_persProjInfo;
float m_scale;

bool Init()
{
	m_frameTime = 0;
	m_frameTime = m_startTime = GetCurrentTimeMillis(); // Стараная хрень FrameTime убираешь ее, начинает зависать, нужно определить что это!

	math3d::Vector3f Pos(0.0f, 0.0f, 25.0f);
	math3d::Vector3f Target(0.0f, .25f, -1.0f);
	math3d::Vector3f Up(0.0f, 1.0f, 0.0f); // это вращение смотреть в точку Target, с позиции при этом вращая камеру

	m_pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, Pos, Target, Up);

	m_pEffect = new SkinningTechnique();

	if (!m_pEffect->Init()) {
		printf("Error initializing the lighting technique\n");
		return false;
	}

	m_pEffect->Enable();

	m_pEffect->SetColorTextureUnit(COLOR_TEXTURE_UNIT_INDEX);
	m_pEffect->SetDirectionalLight(m_directionalLight);
	m_pEffect->SetMatSpecularIntensity(0.0f);
	m_pEffect->SetMatSpecularPower(0);

	if (!m_mesh2.LoadMesh("gun.fbx")) {
		printf("Mesh load failed\n");
		return false;
	}
	if (!m_mesh.LoadMesh("tank.fbx")) {
		printf("Mesh load failed\n");
		return false;
	}
}

static void RenderScene()
{
	m_scale += 0.057f;

	m_pGameCamera->OnRender();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_pEffect->Enable();

	std::vector<Matrix4f> Transforms;

	float RunningTime = GetRunningTime();

	m_mesh.BoneTransform(RunningTime, Transforms);

	for (uint i = 0; i < Transforms.size(); i++) {
		m_pEffect->SetBoneTransform(i, Transforms[i]);
	}

	m_pEffect->SetEyeWorldPos(m_pGameCamera->GetPos());

	Pipeline p;
	p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
	p.SetPerspectiveProj(m_persProjInfo);
	p.Scale(1.f, 1.f, 1.f);

	math3d::Vector3f Pos(m_position);
	p.WorldPos(Pos);
	p.Rotate(0.0f, 0.0f, 0.0f);
	m_pEffect->SetWVP(p.GetWVPTrans());
	m_pEffect->SetWorldMatrix(p.GetWorldTrans());

	m_mesh.Render(*m_pEffect);

	m_mesh2.BoneTransform(0, RunningTime, Transforms);

	for (uint i = 0; i < Transforms.size(); i++) {
		m_pEffect->SetBoneTransform(i, Transforms[i]);
	}
	p.WorldPos(math3d::Vector3f(.0f, -0.19f, 2.87));
	p.Rotate(0.0f, 0.0f, m_scale);
	m_pEffect->SetWVP(p.GetWVPTrans());
	m_pEffect->SetWorldMatrix(p.GetWorldTrans());
	m_mesh2.Render(*m_pEffect);
}

static void SpecialKeyboardCB(int Key)
{
	if (Key == sf::Keyboard::A) {
		m_directionalLight.AmbientIntensity += 0.05f;
		return;
	}
	if (Key == sf::Keyboard::S) {
		m_directionalLight.AmbientIntensity -= 0.05f;
		return;
	}
	if (Key == sf::Keyboard::Z) {
		m_directionalLight.DiffuseIntensity += 0.05f;
		return;
	}
	if (Key == sf::Keyboard::X) {
		m_directionalLight.DiffuseIntensity -= 0.05f;
		return;
	}
	//if (Key == sf::Keyboard::Right) {
	//	//m_startTime = GetCurrentTimeMillis();
	//	//m_mesh.SetAnimation(aiString("die"));
	//	if (m_mesh.iAnim < 14) {
	//		m_mesh.iAnim++;
	//	}
	//}
	//if (Key == sf::Keyboard::Left) {
	//	//m_startTime = GetCurrentTimeMillis();
	//	//m_mesh.SetAnimation(aiString("Attack"));
	//	if (m_mesh.iAnim != 0) {
	//		m_mesh.iAnim--;
	//	}
	//}
m_pGameCamera->OnKeyboard(Key);
}
static void PassiveMouseCB(int x, int y)
{
	m_pGameCamera->OnMouse(x, y);
}
int main()
{
	sf::ContextSettings settings;
	settings.depthBits = 32;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;


	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML OpenGL", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	m_pGameCamera = NULL;
	m_pEffect = NULL;
	m_directionalLight.Color = math3d::Vector3f(1.0f, 1.0f, 1.0f);
	m_directionalLight.AmbientIntensity = 0.55f;
	m_directionalLight.DiffuseIntensity = 0.9f;
	m_directionalLight.Direction = math3d::Vector3f(0.0f, 0.0, -1.0);

	m_persProjInfo.FOV = 60.0f;
	m_persProjInfo.Height = WINDOW_HEIGHT;
	m_persProjInfo.Width = WINDOW_WIDTH;
	m_persProjInfo.zNear = 1.0f;
	m_persProjInfo.zFar = 1000.0f; // дальность видимости (или туман так скажем!)

	m_position = math3d::Vector3f(0.0f, 0.0f, 0.0f);

	Init();

	printf("GL version: %s\n", glGetString(GL_VERSION)); // Вывод версии GL

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.8f);

	while (window.isOpen())
	{
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			if (Event.type == sf::Event::KeyPressed)
			{
				//m_pGameCamera->OnKeyboard(Event.key.code);
				SpecialKeyboardCB(Event.key.code);
			}
			if (Event.type == sf::Event::MouseWheelScrolled)
			{
				if ((Event.mouseWheelScroll.delta) > 0){
					m_pGameCamera->SetPos(1);
				}else {
					m_pGameCamera->SetPos(-1);
				}
			}
			if (Event.type == sf::Event::MouseMoved)
			{
				//PassiveMouseCB(Event.mouseMove.x, Event.mouseMove.y);
			}
			if (Event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (Event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, Event.size.width, Event.size.height);
			}
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();
		}
		
		RenderScene();

		window.display();
	}
	return 0;
}