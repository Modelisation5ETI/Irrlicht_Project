#pragma once

#ifndef TERRAINMANAGER_HPP
#define TERRAINMANAGER_HPP

#include <irrlicht.h>
#include "PathFinder.hpp"

class TerrainManager
{
  public:
    //! Constructor
    TerrainManager()
    {}

    //Add ITerrainSceneNode to scene manager
    void addTerrainToScene( irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver );

    // Add Sky Dome
    void addSkyDome( irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver );

    // Add Sky Box
    void addSkyBox( irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver );

    //Terrain scene node
    irr::scene::ITerrainSceneNode* terrainNode;

};
#endif // TERRAINMANAGER_HPP
