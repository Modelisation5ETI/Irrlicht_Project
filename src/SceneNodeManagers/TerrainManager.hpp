#pragma once

#ifndef TERRAINMANAGER_HPP
#define TERRAINMANAGER_HPP

#include "NodeManager.hpp"

class TerrainManager : public NodeManager<irr::scene::ITerrainSceneNode>
{
  public:
    //! Constructor
    TerrainManager()
    {}

    // Add node to scene
    void AddNodeToScene( irr::IrrlichtDevice* device ,
      irr::s32 id, irr::core::vector3df position);

    // Add Sky Dome
    void addSkyDome( irr::IrrlichtDevice* device );

    // Add Sky Box
    void addSkyBox( irr::IrrlichtDevice* device );

};
#endif // TERRAINMANAGER_HPP
