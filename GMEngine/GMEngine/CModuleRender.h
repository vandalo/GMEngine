#pragma once

#include "IModule.h"
#include "MathGeoLib/src/Math/float4x4.h"

#include <map>

struct SDL_Renderer;

struct renderData
{
	float4x4 id;
	float4x4 normalId;
	int idVertVBO;
	unsigned int sizeVertVBO;
	int idNormalVBO;
	int idIdxVAO;
	unsigned int sizeNormalVBO;
	unsigned int sizeIdxVAO;
	unsigned int textureID;	//This has to be a vector later, and meshComponent needs a map: for each mesh added to the verticesVBO, a reference to the textureID that needs
	unsigned int normalMapID;
	unsigned int textureCoordsID;
	unsigned int colorID;
	bool hasMaterial;
	bool hasNormalMap;
	bool hasTexture;
	unsigned int mode;
};

class CModuleRender : public IModule
{
public:

	CModuleRender();
	~CModuleRender();

	bool Init();
	bool PreUpdate(float deltaTime);
	bool PostUpdate(float deltaTime);

private:

	void renderObjects();

private:
	std::multimap<unsigned int, renderData> renderQueue;
};