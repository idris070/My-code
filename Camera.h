#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "Math_3d.h"

class Camera
{
public:

	Camera(int WindowWidth, int WindowHeight);
	Camera(int WindowWidth, int WindowHeight, const math3d::Vector3f& Pos, const math3d::Vector3f& Target, const math3d::Vector3f& Up);
	
	bool OnKeyboard(int Key);
	void OnMouse(int x, int y);
	void OnRender();

	const math3d::Vector3f& GetPos() const
	{
		return m_pos;
	}

	const math3d::Vector3f& GetTarget() const
	{
		return m_target;
	}

	const math3d::Vector3f& GetUp() const
	{
		return m_up;
	}

	void SetPos(float zoom)
	{
		m_pos.z -= zoom;
	}

private:

	void Init();
	void Update();

	math3d::Vector3f m_pos;
	math3d::Vector3f m_target;
	math3d::Vector3f m_up;

	int m_windowWidth;
	int m_windowHeight;

	float m_AngleH;
	float m_AngleV;

	bool m_OnUpperEdge;
	bool m_OnLowerEdge;
	bool m_OnLeftEdge;
	bool m_OnRightEdge;

	math3d::Vector2i m_mousePos;
};

#endif // !CAMERA_H
