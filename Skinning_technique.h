#pragma once
/*
Copyright 2011 Etay Meiri

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SKINNING_TECHNIQUE_H
#define	SKINNING_TECHNIQUE_H

#include "Technique.h"
#include "Math_3d.h"

struct BaseLight
{
	math3d::Vector3f Color;
	float AmbientIntensity;
	float DiffuseIntensity;

	BaseLight()
	{
		Color = math3d::Vector3f(0.0f, 0.0f, 0.0f);
		AmbientIntensity = 0.0f;
		DiffuseIntensity = 0.0f;
	}
};

struct DirectionalLight : public BaseLight
{
	math3d::Vector3f Direction;

	DirectionalLight()
	{
		Direction = math3d::Vector3f(0.0f, 0.0f, 0.0f);
	}
};

struct PointLight : public BaseLight
{
	math3d::Vector3f Position;

	struct
	{
		float Constant;
		float Linear;
		float Exp;
	} Attenuation;

	PointLight()
	{
		Position = math3d::Vector3f(0.0f, 0.0f, 0.0f);
		Attenuation.Constant = 1.0f;
		Attenuation.Linear = 0.0f;
		Attenuation.Exp = 0.0f;
	}
};

struct SpotLight : public PointLight
{
	math3d::Vector3f Direction;
	float Cutoff;

	SpotLight()
	{
		Direction = math3d::Vector3f(0.0f, 0.0f, 0.0f);
		Cutoff = 0.0f;
	}
};

class SkinningTechnique : public Technique {
public:

	static const uint MAX_POINT_LIGHTS = 2;
	static const uint MAX_SPOT_LIGHTS = 2;
	static const uint MAX_BONES = 300;

	SkinningTechnique();

	virtual bool Init();

	void SetWVP(const Matrix4f& WVP);
	void SetWorldMatrix(const Matrix4f& WVP);
	void SetColorTextureUnit(uint TextureUnit);
	void SetDirectionalLight(const DirectionalLight& Light);
	void SetPointLights(uint NumLights, const PointLight* pLights);
	void SetSpotLights(uint NumLights, const SpotLight* pLights);
	void SetEyeWorldPos(const math3d::Vector3f& EyeWorldPos);
	void SetMatSpecularIntensity(float Intensity);
	void SetMatSpecularPower(float Power);
	void SetBoneTransform(uint Index, const Matrix4f& Transform);
	void SetColorMesh(float Red, float Green, float Blue, float Alpha);

private:

	/*GLuint m_WVPLocation;
	GLuint m_WorldMatrixLocation;
	GLuint m_colorTextureLocation;
	GLuint m_eyeWorldPosLocation;
	GLuint m_matSpecularIntensityLocation;
	GLuint m_matSpecularPowerLocation;
	GLuint m_numPointLightsLocation;
	GLuint m_numSpotLightsLocation;
	GLuint m_colorMesh;*/
	std::string m_WVPLocation;
	std::string m_WorldMatrixLocation;
	std::string m_colorTextureLocation;
	std::string m_eyeWorldPosLocation;
	std::string m_matSpecularIntensityLocation;
	std::string m_matSpecularPowerLocation;
	std::string m_numPointLightsLocation;
	std::string m_numSpotLightsLocation;
	std::string m_colorMesh;

	struct {
		std::string Color;
		std::string AmbientIntensity;
		std::string DiffuseIntensity;
		std::string Direction;
	} m_dirLightLocation;

	struct {
		GLuint Color;
		GLuint AmbientIntensity;
		GLuint DiffuseIntensity;
		GLuint Position;
		struct {
			GLuint Constant;
			GLuint Linear;
			GLuint Exp;
		} Atten;
	} m_pointLightsLocation[MAX_POINT_LIGHTS];

	struct {
		GLuint Color;
		GLuint AmbientIntensity;
		GLuint DiffuseIntensity;
		GLuint Position;
		GLuint Direction;
		GLuint Cutoff;
		struct {
			GLuint Constant;
			GLuint Linear;
			GLuint Exp;
		} Atten;
	} m_spotLightsLocation[MAX_SPOT_LIGHTS];

	std::string m_boneLocation[MAX_BONES];
};


#endif	/* SKINNING_TECHNIQUE_H */
