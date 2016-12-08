#include "TerrainManager.hpp"
#include <iostream>
//*****************************************************************************
// Add ITerrainSceneNode to scene manager
//*****************************************************************************
void TerrainManager::AddNodeToScene( irr::IrrlichtDevice* device,
  irr::s32 id, irr::core::vector3df position )
{
  // Get information from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();
  irr::video::IVideoDriver* driver = device->getVideoDriver();

  //Create node
  node = sceneManager->addTerrainSceneNode(
    PathFinder::GetFullMediaPath( "terrain-heightmap.bmp" ),//HeightMap
    0,					                                   //Parent node
    id,					                                   //Node id
    position,		                                       //Position
    irr::core::vector3df( 0.f, 0.f, 0.f ),		           //Rotation
    irr::core::vector3df( 40.f, 2.0f, 40.f ),	           //Scale
    irr::video::SColor( 255, 255, 255, 255 ),              //VertexColor
    5,					                                   //MaxLOD
    irr::scene::ETPS_17,	    		                   //PatchSize
    4 );				                                   //SmoothFactor

  node->setName("Terrain");

  //Set Material
  node->setMaterialFlag( irr::video::EMF_LIGHTING, false );
  node->setMaterialTexture( 0,
    driver->getTexture( PathFinder::GetFullMediaPath( "terrain-texture.jpg" ) ) );
  node->setMaterialTexture(1,
    driver->getTexture( PathFinder::GetFullMediaPath( "detailmap3.jpg" ) ) );
  node->setMaterialType( irr::video::EMT_DETAIL_MAP );
  node->scaleTexture( 1.0f, 20.0f );

  //Set triangle selector for collisions
  irr::scene::ITriangleSelector* selector =
    sceneManager->createTerrainTriangleSelector( node, 0 );
  node->setTriangleSelector( selector );
  selector->drop();

//  // DEBUG
//  node->setMaterialFlag( irr::video::EMF_WIREFRAME,
//    !node->getMaterial(0).Wireframe );
//  node->setMaterialFlag( irr::video::EMF_POINTCLOUD, false );
}

//*****************************************************************************
// Add Sky Dome
//*****************************************************************************
void TerrainManager::addSkyDome( irr::IrrlichtDevice* device )
{
  // Get information from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();
  irr::video::IVideoDriver* driver = device->getVideoDriver();

  // Create skydome
  driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
  sceneManager->addSkyDomeSceneNode(
      driver->getTexture( PathFinder::GetFullMediaPath( "skydome.jpg" ) ),16,8,0.9f,2.0f);
  driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
}

//*****************************************************************************
// Add Sky Box
//*****************************************************************************
void TerrainManager::addSkyBox( irr::IrrlichtDevice* device )
{
  // Get information from device
    irr::scene::ISceneManager* sceneManager = device->getSceneManager();
    irr::video::IVideoDriver* driver = device->getVideoDriver();

  // Create skybox
  driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);

  sceneManager->addSkyBoxSceneNode(
    driver->getTexture( PathFinder::GetFullMediaPath( "irrlicht2_up.jpg" ) ),
    driver->getTexture( PathFinder::GetFullMediaPath( "irrlicht2_dn.jpg" ) ),
    driver->getTexture( PathFinder::GetFullMediaPath( "irrlicht2_lf.jpg" ) ),
    driver->getTexture( PathFinder::GetFullMediaPath( "irrlicht2_rt.jpg" ) ),
    driver->getTexture( PathFinder::GetFullMediaPath( "irrlicht2_ft.jpg" ) ),
    driver->getTexture( PathFinder::GetFullMediaPath( "irrlicht2_bk.jpg" ) ) );

  driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
}
