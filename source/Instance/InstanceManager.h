// ******************************************************************************
// Filename:    InstanceManager.h
// Project:     Game
// Author:      Steven Ball
//
// Purpose:
//
// Revision History:
//   Initial Revision - 11/06/12
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include "../Maths/3dmaths.h"

class Chunk;
class QubicleBinary;
class Renderer;

class InstanceObject
{
public:
	bool m_erase;
	bool m_render;
	Matrix4x4 m_worldMatrix;

	Chunk* m_pOwningChunk;
	int m_voxelX;
	int m_voxelY;
	int m_voxelZ;

	void UpdateMatrix(vec3 position, vec3 rotation, float scale)
	{
		m_worldMatrix.SetRotation(rotation.x, rotation.y, rotation.z);
		m_worldMatrix.SetTranslation(position);

		Matrix4x4 scaleMat;
		scaleMat.SetScale(vec3(scale, scale, scale));
		m_worldMatrix = scaleMat * m_worldMatrix;
	}
};

typedef vector<InstanceObject*> InstanceObjectList;

class InstanceParent
{
public:
	unsigned int m_vertexArray;
	unsigned int m_positionBuffer;
	unsigned int m_normalBuffer;
	unsigned int m_colourBuffer;
	unsigned int m_matrixBuffer;

	InstanceObjectList m_vpInstanceObjectList;

	string m_modelName;
	QubicleBinary* m_pQubicleBinary;
};

typedef vector<InstanceParent*> InstanceParentList;


class InstanceManager
{
public:
	/* Public methods */
	InstanceManager(Renderer* pRenderer);
	~InstanceManager();

	void ClearInstanceObjects();

	int GetNumInstanceParents();
	int GetNumInstanceObjectsForParent(int parentId);
	int GetNumInstanceRenderObjectsForParent(int parentId);
	int GetTotalNumInstanceObjects();
	int GetTotalNumInstanceRenderObjects();

	void SetupGLBuffers(InstanceParent *pInstanceParent);

	InstanceParent* GetInstanceParent(string modelName);
	InstanceObject* AddInstanceObject(string modelName, vec3 position, vec3 rotation, float instanceScale, Chunk* pOwningChunk, int voxelX, int voxelY, int voxelZ);

	// Update
	void Update(float dt);

	// Rendering
	void Render();

protected:
	/* Protected methods */

private:
	/* Private methods */

public:
	/* Public members */

protected:
	/* Protected members */

private:
	/* Private members */
	Renderer* m_pRenderer;

	unsigned int m_instanceShader;

	InstanceParentList m_vpInstanceParentList;

	float m_checkChunkInstanceTimer;
};
