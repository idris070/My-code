#include "Camera.h"

const static float STEP_SCALE = 1.0f;
const static float EDGE_STEP = 0.5f;
const static int MARGIN = 100;


Camera::Camera(int WindowWidth, int WindowHeight)
{
	m_windowWidth = WindowWidth;
	m_windowHeight = WindowHeight;
	m_pos		= math3d::Vector3f(0.0f, 0.0f, 0.0f);
	m_target	= math3d::Vector3f(0.0f, 0.0f, -1.0f);
	m_target.Normalize();
	m_up		= math3d::Vector3f(0.0f, 1.0f, 0.0f);

	Init();
}

Camera::Camera(int WindowWidth, int WindowHeight, const math3d::Vector3f & Pos, const math3d::Vector3f & Target, const math3d::Vector3f & Up)
{
	m_windowWidth = WindowWidth;
	m_windowHeight = WindowHeight;
	m_pos = Pos;

	m_target = Target;
	m_target.Normalize();

	m_up = Up;
	m_up.Normalize();

	Init();
}

void Camera::Init()
{
	math3d::Vector3f HTarget(m_target.x, 0.0, m_target.z);
	HTarget.Normalize();

	if (HTarget.z >= 0.0f) {
		if (HTarget.x >= 0.0f) {
			m_AngleH = 360.0f - ToDegree(asin(HTarget.z));
		}
		else {
			m_AngleH = 180.0f + ToDegree(asin(HTarget.z));
		}
	}
	else {
		if (HTarget.x >= 0.0f) {
			m_AngleH = ToDegree(asin(-HTarget.z));
		}
		else {
			m_AngleH = 90.0f + ToDegree(asin(-HTarget.z));
		}
	}

	m_AngleV = -ToDegree(asin(m_target.y));

	m_OnUpperEdge = false;
	m_OnLowerEdge = false;
	m_OnLeftEdge = false;
	m_OnRightEdge = false;
	m_mousePos.x = m_windowWidth / 2;
	m_mousePos.y = m_windowHeight / 2;

	//glutWarpPointer(m_mousePos.x, m_mousePos.y); // Перемещает курсор в центр экрана
}
bool Camera::OnKeyboard(int Key) {
	bool Ret = false;
	switch (Key)
	{
		case sf::Keyboard::Up: {
			//m_pos += (m_target * STEP_SCALE);
			m_pos.y += 1.0;
			Ret = true;
		} break;
		case sf::Keyboard::Down: {
			//m_pos -= (m_target * STEP_SCALE);
			m_pos.y -= 1.0;
			Ret = true;
		} break;
		case sf::Keyboard::Left: {
			//Vector3f Left = m_target.Cross(m_up);
			//Left.Normalize();
			//Left *= STEP_SCALE;
			//m_pos += Left;
			m_pos.x += 1.0;
			Ret = true;
		} break;
		case sf::Keyboard::Right: {
			//Vector3f Right = m_up.Cross(m_target);
			//Right.Normalize();
			//Right *= STEP_SCALE;
			//m_pos += Right;
			m_pos.x -= 1.0;
			Ret = true;
		} break;
	}
	return Ret;
}
void Camera::OnMouse(int x, int y)
{
	const int DeltaX = x - m_mousePos.x;
	const int DeltaY = y - m_mousePos.y;

	m_mousePos.x = x;
	m_mousePos.y = y;

	m_AngleH += (float)DeltaX / 20.0f;
	m_AngleV += (float)DeltaY / 20.0f;

	if (DeltaX == 0) {
		if (x <= MARGIN) {
			m_OnLeftEdge = true;
		}
		else if (x >= (m_windowWidth - MARGIN)) {
			m_OnRightEdge = true;
		}
	}
	else {
		m_OnLeftEdge = false;
		m_OnRightEdge = false;
	}

	if (DeltaY == 0) {
		if (y <= MARGIN) {
			m_OnUpperEdge = true;
		}
		else if (y >= (m_windowHeight - MARGIN)) {
			m_OnLowerEdge = true;
		}
	}
	else {
		m_OnUpperEdge = false;
		m_OnLowerEdge = false;
	}

	Update();
}
void Camera::OnRender()
{
	bool ShouldUpdate = false;

	if (m_OnLeftEdge) {
		m_AngleH -= 0.1f;
		ShouldUpdate = true;
	}
	else if (m_OnRightEdge) {
		m_AngleH += 0.1f;
		ShouldUpdate = true;
	}

	if (m_OnUpperEdge) {
		if (m_AngleV > -90.0f) {
			m_AngleV -= 0.1f;
			ShouldUpdate = true;
		}
	}
	else if (m_OnLowerEdge) {
		if (m_AngleV < 90.0f) {
			m_AngleV += 0.1f;
			ShouldUpdate = true;
		}
	}

	if (ShouldUpdate) {
		Update();
	}
}
void Camera::Update()
{
	const math3d::Vector3f Vaxis(0.0f, 1.0f, 0.0f);

	//	Rotate the view vector by the horizontal angle around the vertical axis
	math3d::Vector3f View(1.0f, 0.0f, 0.0f);
	View.Rotate(m_AngleH, Vaxis);
	View.Normalize();

	//	Rotate the view vector by the vertical angle around the horizontal axis
	math3d::Vector3f Haxis = Vaxis.Cross(View);
	Haxis.Normalize();
	View.Rotate(m_AngleV, Haxis);
	View.Normalize();

	m_target = View;
	m_target.Normalize();

	m_up = m_target.Cross(Haxis);
	m_up.Normalize();
}


