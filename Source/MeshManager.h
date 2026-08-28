/*****************************************************************//**
 * \file   MeshManager.h
 * \brief  
 * 
 * \author Luke Tseng
 *         Benedict Yau
 * \date   September 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
#pragma once

#include <vector>
#include <map>
#include "Mesh.h"
#include "ISystem.h"


class MeshManager : public ISystem
{
public:
	//|LUKE|
	enum MeshType{single = 's', line = 'l', text = 't', circle = 'c', rainbow = 'r'};
	/**
	 * Initializes sound system
	 *
	 */
	void initialize() override;
	/**
	 * Shuts down system
	 *
	 */
	void shutdown() override;
	/**
	 * Creates mesh and adds it to list
	 * 
	 * \return 
	 */
	//static Mesh* build();
	/**
	 * Adds mesh to list
	 *
	 * \param mesh Mesh to add to list
	 */
	//static void add(Mesh* mesh);
	/**
	 * Gets count of meshes in list
	 *
	 */
	//static int getCount();
	/**
	 * Removes specific mesh from list
	 *
	 */
	//static void remove(Mesh* mesh);
	/**
	 * This function accesses the singleton instance of the MeshManager system, creating it if needed.
	 *
	 * \return Singleton instance of the MeshManager system
	 */
	static MeshManager* getInstance();
	/**
	 * This function closes and deletes the singleton instance of the MeshManager system
	 *
	 */
	static void closeInstance();

    bool getMesh(MeshType, Mesh *&) const;

private:
	// number of meshes
	//int count;
	//list of meshes
	//std::vector<Mesh*>list;

    /**
     * Constructor for meshmanager
     *
     */
    MeshManager();
	/**
	 * Creates mesh and adds it to list
	 *
	 * \return
	 */
	//Mesh* instanceBuild();
	/**
	 * Adds mesh to list
	 *
	 * \param mesh Mesh to add to list
	 */
	//void instanceAdd(Mesh* mesh);
	/**
	 * Gets count of meshes in list
	 *
	 */
	//int instanceGetCount();
	/**
	 * Removes specific mesh from list
	 *
	 */
	//void instanceRemove(Mesh* mesh);

    // The instance of mesh manager
    static MeshManager* instance;

    //list of meshes
    std::map<MeshType, Mesh*> meshesMap;
};
