/*****************************************************************//**
 * \file   MeshManager.cpp
 * \brief  
 * 
 * \author Luke Tseng
 *         Benedict Yau
 * \date   September 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/

#define _USE_MATH_DEFINES
#include <cmath>
#include "rapidjson/document.h"
#include "readFile.h"
#include "MeshManager.h"
#include "Trace.h"

using rapidjson::Document;

MeshManager* MeshManager::instance = nullptr;

/**
* This function accesses the singleton instance of the MeshManager system, creating it if needed.
*
* \return Singleton instance of the MeshManager system
*/
MeshManager* MeshManager::getInstance() {
    if (instance == nullptr) {
        instance = new MeshManager();
    }
    return instance;
}

/**
* This function closes and deletes the singleton instance of the MeshManager system
*
*/
void MeshManager::closeInstance() {
    delete instance;
    instance = nullptr;
}

/**
* Constructor for meshmanager
*
*/
MeshManager::MeshManager() : ISystem(sMeshMan) {
}

#define meshCircleX(i) (cos(i) / 2) + 0.5f
#define meshCircleY(i) (sin(i) / 2) + 0.5f

/**
* Initializes sound system
*
*/
void MeshManager::initialize() {
    if (isActive()) {
        return;
    }
    ISystem::initialize();

#define JSONMeshX
#ifdef JSONMesh
    // Read the game JSON file.
    const char* jsonData = readWholeFile("Data/Json/graphics.json");

    Document jsonDoc;
    jsonDoc.Parse(jsonData);

    if (!jsonDoc.IsObject() || !jsonDoc.HasMember("meshes")) {
        return;
    }

    if (jsonDoc.HasMember("meshes") && jsonDoc["meshes"].IsArray()) {
        for (auto& element : jsonDoc["meshes"].GetArray()) {
            if (element.IsObject()) {
                rapidjson::GenericObject<false, rapidjson::Value> mesh = element.GetObject();
                if (mesh.HasMember("name") && mesh.HasMember("vertices")) {
                    const char* name = mesh["name"].GetString();
                    if (mesh["vertices"].IsArray()) {
                        std::vector<Vertex> vertices;
                        for (auto& vertex : mesh["vertices"].GetArray()) {
                            if (vertex.IsObject() &&
                                vertex["position"].IsArray() &&
                                vertex["textureCoord"].IsArray() &&
                                vertex["color"].IsArray()
                               ) {
                                rapidjson::GenericArray<false, rapidjson::Value> positionArray = vertex["position"].GetArray();
                                glm::vec2 position = glm::vec2(positionArray[0].GetFloat(), 
                                                              positionArray[1].GetFloat());

                                rapidjson::GenericArray<false, rapidjson::Value> textureCoordArray = vertex["textureCoord"].GetArray();
                                glm::vec2 textureCoord = glm::vec2(textureCoordArray[0].GetFloat(), 
                                                                  textureCoordArray[1].GetFloat());

                                rapidjson::GenericArray<false, rapidjson::Value> colorArray = vertex["color"].GetArray();
                                glm::vec4 color = glm::vec4(colorArray[0].GetFloat(),
                                                            colorArray[1].GetFloat(),
                                                            colorArray[2].GetFloat(),
                                                            colorArray[3].GetFloat());

                                vertices.push_back(Vertex(position, textureCoord, color));
                            }
                        }

                        Mesh* mesh = new Mesh(vertices);
                        if (mesh) {
                            meshesMap[name] = mesh;
                        }
                    }
                }
            }
        }
    }
#endif
#ifndef JSONMesh

	//	Variable: list of vertices for each mesh
	std::vector<Vertex> vertices;

	//	Add vertices for single frame mesh
	vertices.emplace_back(glm::vec2(0.5f, 0.5f), glm::vec2(1, 0), glm::vec4(1, 1, 1, 1));
	vertices.emplace_back(glm::vec2(0.5f, -0.5f), glm::vec2(1, 1), glm::vec4(1, 1, 1, 1));
	vertices.emplace_back(glm::vec2(-0.5f, -0.5f), glm::vec2(0, 1), glm::vec4(1, 1, 1, 1));
	vertices.emplace_back(glm::vec2(0.5f, 0.5f), glm::vec2(1, 0), glm::vec4(1, 1, 1, 1));
	vertices.emplace_back(glm::vec2(-0.5f, -0.5f), glm::vec2(0, 1), glm::vec4(1, 1, 1, 1));
	vertices.emplace_back(glm::vec2(-0.5f, 0.5f), glm::vec2(0, 0), glm::vec4(1, 1, 1, 1));

	//	Create mesh
	meshesMap[single] = new Mesh(vertices);

	//	Add vertices
	vertices.clear();
	vertices.emplace_back(glm::vec2(0.5f, 1), glm::vec2(1, 0), glm::vec4(1, 1, 1, 1));
	vertices.emplace_back(glm::vec2(0.5f, 0), glm::vec2(1, 1), glm::vec4(1, 1, 1, 1));
	vertices.emplace_back(glm::vec2(-0.5f, 0), glm::vec2(0, 1), glm::vec4(1, 1, 1, 1));
	vertices.emplace_back(glm::vec2(0.5f, 1), glm::vec2(1, 0), glm::vec4(1, 1, 1, 1));
	vertices.emplace_back(glm::vec2(-0.5f, 0), glm::vec2(0, 1), glm::vec4(1, 1, 1, 1));
	vertices.emplace_back(glm::vec2(-0.5f, 1), glm::vec2(0, 0), glm::vec4(1, 1, 1, 1));

	//	Create mesh
	meshesMap[line] = new Mesh(vertices);

	//	Add vertices
	vertices.clear();
	vertices.emplace_back(glm::vec2(0.25f, 0.5f), glm::vec2(1.0f / 96, 0), glm::vec4(1, 1, 1, 1));
	vertices.emplace_back(glm::vec2(0.25f, -0.5f), glm::vec2(1.0f / 96, 1), glm::vec4(1, 1, 1, 1));
	vertices.emplace_back(glm::vec2(-0.25f, -0.5f), glm::vec2(0, 1), glm::vec4(1, 1, 1, 1));
	vertices.emplace_back(glm::vec2(0.25f, 0.5f), glm::vec2(1.0f / 96, 0), glm::vec4(1, 1, 1, 1));
	vertices.emplace_back(glm::vec2(-0.25f, -0.5f), glm::vec2(0, 1), glm::vec4(1, 1, 1, 1));
	vertices.emplace_back(glm::vec2(-0.25f, 0.5f), glm::vec2(0, 0), glm::vec4(1, 1, 1, 1));

	//	Create mesh
	meshesMap[text] = new Mesh(vertices);

	/*	Variables:
	ratio: Pi divided by 180
	head: "Base of the fan" for the circle mesh
	prev: Previous vertex for the circle mesh
	*/
	float ratio = (float) (M_PI / 180);
	glm::vec2 head1(1, 0.5f), head2(0.5f, 0), prev(meshCircleX(ratio), meshCircleY(ratio));
	
	//	Add vertices
	vertices.clear();
	for(float i = 2 * ratio; i < (float) (2 * M_PI); i += ratio){

		//	Push `head` and `prev`
		vertices.emplace_back(head2, head1, glm::vec4(1, 1, 1, 1));
		vertices.emplace_back(glm::vec2(prev.x - 0.5f, 0.5f - prev.y), prev, glm::vec4(1, 1, 1, 1));

		//	Variable: New vertex for the circle mesh
		glm::vec2 cur(meshCircleX(i), meshCircleY(i));

		//	Push `cur`
		vertices.emplace_back(glm::vec2(cur.x - 0.5f, 0.5f - cur.y), cur, glm::vec4(1, 1, 1, 1));

		//	Update `prev`
		prev = cur;

	}

	//	Create mesh
	meshesMap[circle] = new Mesh(vertices);

	//	Add red to yellow vertices
	vertices.clear();
	vertices.emplace_back(glm::vec2(-1.0f / 3, 0.5f), glm::vec2(1, 0), glm::vec4(1, 1, 0, 1));
	vertices.emplace_back(glm::vec2(-1.0f / 3, -0.5f), glm::vec2(1, 1), glm::vec4(1, 1, 0, 1));
	vertices.emplace_back(glm::vec2(-0.5f, -0.5f), glm::vec2(0, 1), glm::vec4(1, 0, 0, 1));
	vertices.emplace_back(glm::vec2(-1.0f / 3, 0.5f), glm::vec2(1, 0), glm::vec4(1, 1, 0, 1));
	vertices.emplace_back(glm::vec2(-0.5f, -0.5f), glm::vec2(0, 1), glm::vec4(1, 0, 0, 1));
	vertices.emplace_back(glm::vec2(-0.5f, 0.5f), glm::vec2(0, 0), glm::vec4(1, 0, 0, 1));

	//	Add yellow to green vertices
	vertices.emplace_back(glm::vec2(-1.0f / 6, 0.5f), glm::vec2(1, 0), glm::vec4(0, 1, 0, 1));
	vertices.emplace_back(glm::vec2(-1.0f / 6, -0.5f), glm::vec2(1, 1), glm::vec4(0, 1, 0, 1));
	vertices.emplace_back(glm::vec2(-1.0f / 3, -0.5f), glm::vec2(0, 1), glm::vec4(1, 1, 0, 1));
	vertices.emplace_back(glm::vec2(-1.0f / 6, 0.5f), glm::vec2(1, 0), glm::vec4(0, 1, 0, 1));
	vertices.emplace_back(glm::vec2(-1.0f / 3, -0.5f), glm::vec2(0, 1), glm::vec4(1, 1, 0, 1));
	vertices.emplace_back(glm::vec2(-1.0f / 3, 0.5f), glm::vec2(0, 0), glm::vec4(1, 1, 0, 1));

	//	Add green to cyan vertices
	vertices.emplace_back(glm::vec2(0.0f, 0.5f), glm::vec2(1, 0), glm::vec4(0, 1, 1, 1));
	vertices.emplace_back(glm::vec2(0.0f, -0.5f), glm::vec2(1, 1), glm::vec4(0, 1, 1, 1));
	vertices.emplace_back(glm::vec2(-1.0f / 6, -0.5f), glm::vec2(0, 1), glm::vec4(0, 1, 0, 1));
	vertices.emplace_back(glm::vec2(0.0f, 0.5f), glm::vec2(1, 0), glm::vec4(0, 1, 1, 1));
	vertices.emplace_back(glm::vec2(-1.0f / 6, -0.5f), glm::vec2(0, 1), glm::vec4(0, 1, 0, 1));
	vertices.emplace_back(glm::vec2(-1.0f / 6, 0.5f), glm::vec2(0, 0), glm::vec4(0, 1, 0, 1));

	//	Add cyan to blue vertices
	vertices.emplace_back(glm::vec2(1.0f / 6, 0.5f), glm::vec2(1, 0), glm::vec4(0, 0, 1, 1));
	vertices.emplace_back(glm::vec2(1.0f / 6, -0.5f), glm::vec2(1, 1), glm::vec4(0, 0, 1, 1));
	vertices.emplace_back(glm::vec2(0.0f, -0.5f), glm::vec2(0, 1), glm::vec4(0, 1, 1, 1));
	vertices.emplace_back(glm::vec2(1.0f / 6, 0.5f), glm::vec2(1, 0), glm::vec4(0, 0, 1, 1));
	vertices.emplace_back(glm::vec2(0.0f, -0.5f), glm::vec2(0, 1), glm::vec4(0, 1, 1, 1));
	vertices.emplace_back(glm::vec2(0.0f, 0.5f), glm::vec2(0, 0), glm::vec4(0, 1, 1, 1));
	
	//	Add blue to magenta vertices
	vertices.emplace_back(glm::vec2(1.0f / 3, 0.5f), glm::vec2(1, 0), glm::vec4(1, 0, 1, 1));
	vertices.emplace_back(glm::vec2(1.0f / 3, -0.5f), glm::vec2(1, 1), glm::vec4(1, 0, 1, 1));
	vertices.emplace_back(glm::vec2(1.0f / 6, -0.5f), glm::vec2(0, 1), glm::vec4(0, 0, 1, 1));
	vertices.emplace_back(glm::vec2(1.0f / 3, 0.5f), glm::vec2(1, 0), glm::vec4(1, 0, 1, 1));
	vertices.emplace_back(glm::vec2(1.0f / 6, -0.5f), glm::vec2(0, 1), glm::vec4(0, 0, 1, 1));
	vertices.emplace_back(glm::vec2(1.0f / 6, 0.5f), glm::vec2(0, 0), glm::vec4(0, 0, 1, 1));
	
	//	Add magenta to red vertices
	vertices.emplace_back(glm::vec2(0.5f, 0.5f), glm::vec2(1, 0), glm::vec4(1, 0, 0, 1));
	vertices.emplace_back(glm::vec2(0.5f, -0.5f), glm::vec2(1, 1), glm::vec4(1, 0, 0, 1));
	vertices.emplace_back(glm::vec2(1.0f / 3, -0.5f), glm::vec2(0, 1), glm::vec4(1, 0, 1, 1));
	vertices.emplace_back(glm::vec2(0.5f, 0.5f), glm::vec2(1, 0), glm::vec4(1, 0, 0, 1));
	vertices.emplace_back(glm::vec2(1.0f / 3, -0.5f), glm::vec2(0, 1), glm::vec4(1, 0, 1, 1));
	vertices.emplace_back(glm::vec2(1.0f / 3, 0.5f), glm::vec2(0, 0), glm::vec4(1, 0, 1, 1));

	//	Create mesh
	meshesMap[rainbow] = new Mesh(vertices);

#endif
}

//|LUKE|
bool MeshManager::getMesh(MeshType name, Mesh *&ans) const {

	//	Variable: iterator to find the right mesh
    std::map<MeshType, Mesh*>::const_iterator iter = meshesMap.find(name);

	//	Check if the mesh exists
	if(iter == meshesMap.end()) return false;

	//	Return
	ans = iter -> second;
	return true;
}

/**
* Shuts down system
*
*/
void MeshManager::shutdown() {
    if (isActive()) {
        ISystem::shutdown();
        for (auto iter : meshesMap) {
            delete iter.second;
        }

        meshesMap.clear();
    }
}


//Luke's Depricated Code
/*

Mesh* MeshManager::instanceBuild()
{
	Mesh* newMesh = new Mesh();
	newMesh->createMesh();
	add(newMesh);
	if (newMesh)
	{
		return newMesh;
	}
	return NULL;
}

void MeshManager::instanceAdd(Mesh* mesh)
{
	list.push_back(mesh);
	++count;
	return;
}

int MeshManager::instanceGetCount()
{
	return count;
}

void MeshManager::instanceRemove(Mesh* mesh)
{
	list.erase(std::remove(list.begin(), list.end(), mesh), list.end());
}

Mesh* MeshManager::build()
{
	if (instance == nullptr)
	{
        Trace::message("MeshManager instance is NULL");
		return nullptr;
	}
	return instance->instanceBuild();
}

void MeshManager::add(Mesh* mesh)
{
	if (instance == nullptr)
	{
        Trace::message("MeshManager instance is NULL");
		return;
	}
	instance->instanceAdd(mesh);
}

int MeshManager::getCount()
{
	if (instance == nullptr)
	{
        Trace::message("MeshManager instance is NULL");
		return -1;
	}
	return instance->instanceGetCount();
}

void MeshManager::remove(Mesh* mesh)
{
	if (instance == nullptr)
	{
        Trace::message("MeshManager instance is NULL");
		return;
	}
	instance->instanceRemove(mesh);
}
*/

