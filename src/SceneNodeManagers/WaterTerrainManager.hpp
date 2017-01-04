#ifndef WATERTERRAINMANAGER_HPP
#define WATERTERRAINMANAGER_HPP


#include "NodeManager.hpp"

class WaterTerrainManager : public NodeManager<irr::scene::ISceneNode>
{
  public:
    //! Constructor
    WaterTerrainManager()
    {}

    // Add node to scene
    void AddNodeToScene( irr::IrrlichtDevice* device ,
      irr::s32 id, irr::core::vector3df position);

};

#endif // WATERTERRAINMANAGER_HPP
