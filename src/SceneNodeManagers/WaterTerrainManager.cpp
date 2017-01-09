#include "WaterTerrainManager.hpp"
#include <iostream>

//*****************************************************************************
// Add ISceneNode to scene manager
//*****************************************************************************
void WaterTerrainManager::AddNodeToScene( irr::IrrlichtDevice* device,
  irr::s32 id, irr::core::vector3df position )
{
  // Get information from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();
  irr::video::IVideoDriver* driver = device->getVideoDriver();

  irr::scene::IAnimatedMesh* mesh = sceneManager->addHillPlaneMesh( "myHill", //name
     irr::core::dimension2d<irr::f32>(30,30), //tile size
     irr::core::dimension2d<irr::u32>(30,30), 0, 0.1, // tile count, material, hillheight
     irr::core::dimension2d<irr::f32>(0,0), // count hills
     irr::core::dimension2d<irr::f32>(10,10)); // texture repeat

    node = sceneManager->addWaterSurfaceSceneNode(mesh->getMesh(0), //mesh
     4.0f, 300.0f, 10.0f, //wave height, wave speed, wave lenght
     0, id,position,
     irr::core::vector3df( 0.f, 0.0f, 0.f ), //rotation
     irr::core::vector3df( 15.0f, 1.0f, 15.0f )); //scale

    node->setMaterialFlag( irr::video::EMF_LIGHTING, false );
    node->setMaterialTexture(0, driver->getTexture(PathFinder::GetFullMediaPath( "stones.jpg" )));
    node->setMaterialTexture(1, driver->getTexture(PathFinder::GetFullMediaPath( "water.jpg" )));

    node->setMaterialType(irr::video::EMT_REFLECTION_2_LAYER);
}

