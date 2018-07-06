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

#include <limits.h>
#include <string>


#include "skinning_technique.h"
#include "Util.h"

SkinningTechnique::SkinningTechnique()
{
}


bool SkinningTechnique::Init()
{
	if (!Technique::Init()) {
		return false;
	}

	if (!shader.loadFromFile("skinning.vs", "skinning.fs"))
	{
		printf("error#5");
		// error...
	}

	/*if (!AddShader(GL_VERTEX_SHADER, "skinning.vs")) {
		return false;
	}

	if (!AddShader(GL_FRAGMENT_SHADER, "skinning.fs")) {
		return false;
	}

	if (!Finalize()) {
		return false;
	}*/

	m_WVPLocation = "gWVP";
	m_WorldMatrixLocation = "gWorld";
	m_colorTextureLocation = "gColorMap";
	m_eyeWorldPosLocation = "gEyeWorldPos";
	m_dirLightLocation.Color = "gDirectionalLight.Base.Color";
	m_dirLightLocation.AmbientIntensity = "gDirectionalLight.Base.AmbientIntensity";
	m_dirLightLocation.Direction = "gDirectionalLight.Direction";
	m_dirLightLocation.DiffuseIntensity = "gDirectionalLight.Base.DiffuseIntensity";
	m_matSpecularIntensityLocation = "gMatSpecularIntensity";
	m_matSpecularPowerLocation = "gSpecularPower";
	m_numPointLightsLocation = "gNumPointLights";
	m_numSpotLightsLocation = "gNumSpotLights";
	m_colorMesh = "gColor";

	/*m_WVPLocation = GetUniformLocation("gWVP");
	m_WorldMatrixLocation = GetUniformLocation("gWorld");
	m_colorTextureLocation = GetUniformLocation("gColorMap");
	m_eyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");
	m_dirLightLocation.Color = GetUniformLocation("gDirectionalLight.Base.Color");
	m_dirLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.Base.AmbientIntensity");
	m_dirLightLocation.Direction = GetUniformLocation("gDirectionalLight.Direction");
	m_dirLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.Base.DiffuseIntensity");
	m_matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
	m_matSpecularPowerLocation = GetUniformLocation("gSpecularPower");
	m_numPointLightsLocation = GetUniformLocation("gNumPointLights");
	m_numSpotLightsLocation = GetUniformLocation("gNumSpotLights");
	m_colorMesh = GetUniformLocation("gColor");*/

	/*if (m_dirLightLocation.AmbientIntensity == INVALID_UNIFORM_LOCATION ||
		m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
		m_colorTextureLocation == INVALID_UNIFORM_LOCATION ||
		m_eyeWorldPosLocation == INVALID_UNIFORM_LOCATION ||
		m_dirLightLocation.Color == INVALID_UNIFORM_LOCATION ||
		m_dirLightLocation.DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
		m_dirLightLocation.Direction == INVALID_UNIFORM_LOCATION ||
		m_matSpecularIntensityLocation == INVALID_UNIFORM_LOCATION ||
		m_matSpecularPowerLocation == INVALID_UNIFORM_LOCATION ||
		m_numPointLightsLocation == INVALID_UNIFORM_LOCATION ||
		m_numSpotLightsLocation == INVALID_UNIFORM_LOCATION) {
		return false;
	}*/

	/*for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_pointLightsLocation); i++) {
		char Name[128];
		memset(Name, 0, sizeof(Name));
		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.Color", i);
		m_pointLightsLocation[i].Color = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.AmbientIntensity", i);
		m_pointLightsLocation[i].AmbientIntensity = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Position", i);
		m_pointLightsLocation[i].Position = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.DiffuseIntensity", i);
		m_pointLightsLocation[i].DiffuseIntensity = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Constant", i);
		m_pointLightsLocation[i].Atten.Constant = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Linear", i);
		m_pointLightsLocation[i].Atten.Linear = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Exp", i);
		m_pointLightsLocation[i].Atten.Exp = GetUniformLocation(Name);

		if (m_pointLightsLocation[i].Color == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].AmbientIntensity == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].Position == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].Atten.Constant == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].Atten.Linear == INVALID_UNIFORM_LOCATION ||
			m_pointLightsLocation[i].Atten.Exp == INVALID_UNIFORM_LOCATION) {
			return false;
		}
	}*/

	/*for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_spotLightsLocation); i++) {
		char Name[128];
		memset(Name, 0, sizeof(Name));
		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.Color", i);
		m_spotLightsLocation[i].Color = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.AmbientIntensity", i);
		m_spotLightsLocation[i].AmbientIntensity = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Position", i);
		m_spotLightsLocation[i].Position = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Direction", i);
		m_spotLightsLocation[i].Direction = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Cutoff", i);
		m_spotLightsLocation[i].Cutoff = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.DiffuseIntensity", i);
		m_spotLightsLocation[i].DiffuseIntensity = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Constant", i);
		m_spotLightsLocation[i].Atten.Constant = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Linear", i);
		m_spotLightsLocation[i].Atten.Linear = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Exp", i);
		m_spotLightsLocation[i].Atten.Exp = GetUniformLocation(Name);

		if (m_spotLightsLocation[i].Color == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].AmbientIntensity == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Position == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Direction == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Cutoff == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Atten.Constant == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Atten.Linear == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Atten.Exp == INVALID_UNIFORM_LOCATION) {
			return false;
		}
	}*/

	for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_boneLocation); i++) {
		char Name[128];
		memset(Name, 0, sizeof(Name));
		SNPRINTF(Name, sizeof(Name), "gBones[%d]", i);
		//m_boneLocation[i] = GetUniformLocation(Name);
		m_boneLocation[i] = Name;
	}

	return true;
}

void SkinningTechnique::SetWVP(const Matrix4f& WVP)
{
	//glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP);
	//shader.setUniform(m_WVPLocation, sf::Glsl::Mat4((const GLfloat*)WVP));
	float array[16] =
	{
		WVP.m[0][0], WVP.m[1][0], WVP.m[2][0], WVP.m[3][0],
		WVP.m[0][1], WVP.m[1][1], WVP.m[2][1], WVP.m[3][1],
		WVP.m[0][2], WVP.m[1][2], WVP.m[2][2], WVP.m[3][2],
		WVP.m[0][3], WVP.m[1][3], WVP.m[2][3], WVP.m[3][3]
	};
	shader.setUniform(m_WVPLocation, sf::Glsl::Mat4(array));
}


void SkinningTechnique::SetWorldMatrix(const Matrix4f& World)
{
	//glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, (const GLfloat*)World);
	
	//shader.setUniform(m_WorldMatrixLocation, sf::Glsl::Mat4(World));
	float array[16] =
	{
		World.m[0][0], World.m[1][0], World.m[2][0], World.m[3][0],
		World.m[0][1], World.m[1][1], World.m[2][1], World.m[3][1],
		World.m[0][2], World.m[1][2], World.m[2][2], World.m[3][2],
		World.m[0][3], World.m[1][3], World.m[2][3], World.m[3][3]
	};
	shader.setUniform(m_WorldMatrixLocation, sf::Glsl::Mat4(array));
}


void SkinningTechnique::SetColorTextureUnit(unsigned int TextureUnit)
{
	//glUniform1i(m_colorTextureLocation, TextureUnit);
	shader.setUniform(m_colorTextureLocation, (int) TextureUnit);
}


void SkinningTechnique::SetDirectionalLight(const DirectionalLight& Light)
{
	//glUniform3f(m_dirLightLocation.Color, Light.Color.x, Light.Color.y, Light.Color.z);
	//glUniform1f(m_dirLightLocation.AmbientIntensity, Light.AmbientIntensity);
	shader.setUniform(m_dirLightLocation.Color, sf::Vector3f(Light.Color.x, Light.Color.y, Light.Color.z));
	shader.setUniform(m_dirLightLocation.AmbientIntensity, Light.AmbientIntensity);
	math3d::Vector3f Direction = Light.Direction;
	Direction.Normalize();
	//glUniform3f(m_dirLightLocation.Direction, Direction.x, Direction.y, Direction.z);
	//glUniform1f(m_dirLightLocation.DiffuseIntensity, Light.DiffuseIntensity);
	shader.setUniform(m_dirLightLocation.Direction, sf::Vector3f(Direction.x, Direction.y, Direction.z));
	shader.setUniform(m_dirLightLocation.DiffuseIntensity, Light.DiffuseIntensity);
}


void SkinningTechnique::SetEyeWorldPos(const math3d::Vector3f& EyeWorldPos)
{
	//glUniform3f(m_eyeWorldPosLocation, EyeWorldPos.x, EyeWorldPos.y, EyeWorldPos.z);
	shader.setUniform(m_eyeWorldPosLocation, sf::Vector3f(EyeWorldPos.x, EyeWorldPos.y, EyeWorldPos.z));
}


void SkinningTechnique::SetMatSpecularIntensity(float Intensity)
{
	//glUniform1f(m_matSpecularIntensityLocation, Intensity);
	shader.setUniform(m_matSpecularIntensityLocation, Intensity);
}


void SkinningTechnique::SetMatSpecularPower(float Power)
{
	//glUniform1f(m_matSpecularPowerLocation, Power);
	shader.setUniform(m_matSpecularPowerLocation, Power);
}


void SkinningTechnique::SetPointLights(unsigned int NumLights, const PointLight* pLights)
{
	/*glUniform1i(m_numPointLightsLocation, NumLights);

	for (unsigned int i = 0; i < NumLights; i++) {
		glUniform3f(m_pointLightsLocation[i].Color, pLights[i].Color.x, pLights[i].Color.y, pLights[i].Color.z);
		glUniform1f(m_pointLightsLocation[i].AmbientIntensity, pLights[i].AmbientIntensity);
		glUniform1f(m_pointLightsLocation[i].DiffuseIntensity, pLights[i].DiffuseIntensity);
		glUniform3f(m_pointLightsLocation[i].Position, pLights[i].Position.x, pLights[i].Position.y, pLights[i].Position.z);
		glUniform1f(m_pointLightsLocation[i].Atten.Constant, pLights[i].Attenuation.Constant);
		glUniform1f(m_pointLightsLocation[i].Atten.Linear, pLights[i].Attenuation.Linear);
		glUniform1f(m_pointLightsLocation[i].Atten.Exp, pLights[i].Attenuation.Exp);
	}*/
}

void SkinningTechnique::SetSpotLights(unsigned int NumLights, const SpotLight* pLights)
{
	/*glUniform1i(m_numSpotLightsLocation, NumLights);

	for (unsigned int i = 0; i < NumLights; i++) {
		glUniform3f(m_spotLightsLocation[i].Color, pLights[i].Color.x, pLights[i].Color.y, pLights[i].Color.z);
		glUniform1f(m_spotLightsLocation[i].AmbientIntensity, pLights[i].AmbientIntensity);
		glUniform1f(m_spotLightsLocation[i].DiffuseIntensity, pLights[i].DiffuseIntensity);
		glUniform3f(m_spotLightsLocation[i].Position, pLights[i].Position.x, pLights[i].Position.y, pLights[i].Position.z);
		math3d::Vector3f Direction = pLights[i].Direction;
		Direction.Normalize();
		glUniform3f(m_spotLightsLocation[i].Direction, Direction.x, Direction.y, Direction.z);
		glUniform1f(m_spotLightsLocation[i].Cutoff, cosf(ToRadian(pLights[i].Cutoff)));
		glUniform1f(m_spotLightsLocation[i].Atten.Constant, pLights[i].Attenuation.Constant);
		glUniform1f(m_spotLightsLocation[i].Atten.Linear, pLights[i].Attenuation.Linear);
		glUniform1f(m_spotLightsLocation[i].Atten.Exp, pLights[i].Attenuation.Exp);
	}*/
}


void SkinningTechnique::SetBoneTransform(uint Index, const Matrix4f& Transform)
{
	assert(Index < MAX_BONES);
	//Transform.Print();
	//glUniformMatrix4fv(m_boneLocation[Index], 1, GL_TRUE, (const GLfloat*)Transform);
	//shader.setUniform(m_boneLocation[Index], (const GLfloat*)Transform);
	float array[16] =
	{
		Transform.m[0][0], Transform.m[1][0], Transform.m[2][0], Transform.m[3][0],
		Transform.m[0][1], Transform.m[1][1], Transform.m[2][1], Transform.m[3][1],
		Transform.m[0][2], Transform.m[1][2], Transform.m[2][2], Transform.m[3][2],
		Transform.m[0][3], Transform.m[1][3], Transform.m[2][3], Transform.m[3][3]
	};

	shader.setUniform(m_boneLocation[Index], sf::Glsl::Mat4(array));
}

void SkinningTechnique::SetColorMesh(float Red, float Green, float Blue, float Alpha)
{
	//glUniform4f(m_colorMesh, Red, Green, Blue, Alpha);
	shader.setUniform(m_colorMesh, sf::Glsl::Vec4(Red, Green, Blue, Alpha));
}
