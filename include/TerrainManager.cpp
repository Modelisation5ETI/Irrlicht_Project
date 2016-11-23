#include "TerrainManager.hpp"

//*****************************************************************************
// Add ITerrainSceneNode to scene manager
//*****************************************************************************
void TerrainManager::addTerrainToScene( irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver )
{
  //Create node
  terrainNode = sceneManager->addTerrainSceneNode(
    PathFinder::GetFullMediaPath( "terrain-heightmap.bmp" ),//HeightMap
    0,					                                   //Parent node
    -1,					                                   //Node id
    irr::core::vector3df( 0.f, 0.f, 0.f ),		           //Position
    irr::core::vector3df( 0.f, 0.f, 0.f ),		           //Rotation
    irr::core::vector3df( 40.f, 2.0f, 40.f ),	           //Scale
    irr::video::SColor( 255, 255, 255, 255 ),              //VertexColor
    5,					                                   //MaxLOD
    irr::scene::ETPS_17,	    		                   //PatchSize
    4 );				                                   //SmoothFactor

  //Set Material
  terrainNode->setMaterialFlag( irr::video::EMF_LIGHTING, false );
  terrainNode->setMaterialTexture( 0,
    driver->getTexture( PathFinder::GetFullMediaPath( "terrain-texture.jpg" ) ) );
  terrainNode->setMaterialTexture(1,
    driver->getTexture( PathFinder::GetFullMediaPath( "detailmap3.jpg" ) ) );
  terrainNode->setMaterialType( irr::video::EMT_DETAIL_MAP );
  terrainNode->scaleTexture( 1.0f, 20.0f );

  //Set triangle selector for collisions
  irr::scene::ITriangleSelector* selector =
    sceneManager->createTerrainTriangleSelector( terrainNode, 0 );
  terrainNode->setTriangleSelector( selector );
  selector->drop();

//  // DEBUG
//  terrainNode->setMaterialFlag( irr::video::EMF_WIREFRAME,
//    !terrainNode->getMaterial(0).Wireframe );
//  terrainNode->setMaterialFlag( irr::video::EMF_POINTCLOUD, false );
}

//*****************************************************************************
// Add Sky Dome
//*****************************************************************************
void addSkyDome( irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver )
{
  // Create skydome
  driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
  sceneManager->addSkyDomeSceneNode(
      driver->getTexture( PathFinder::GetFullMediaPath( "skydome.jpg" ) ),16,8,0.9f,2.0f);
  driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
}

//*****************************************************************************
// Add Sky Box
//*****************************************************************************
void TerrainManager::addSkyBox( irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver )
{
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
