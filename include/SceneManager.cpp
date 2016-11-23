#include "SceneManager.hpp"

//*****************************************************************************
// Load scene
//*****************************************************************************
void SceneManager::LoadScene()
{
  //Add terrain
  terrainManager.addTerrainToScene( sceneManager, videoDriver );
  terrainManager.addSkyBox( sceneManager, videoDriver );

  //Add character
  characterManager.addCharacterToScene( sceneManager, videoDriver );

  //Add camera
  cameraManager.add3rdPersonCameraToScene( sceneManager );
  cameraManager.addSceneNodeCollision( sceneManager, terrainManager.terrainNode );

}

//*****************************************************************************
// Update scene
//*****************************************************************************
void SceneManager::UpdateScene( irr::IrrlichtDevice* device,
                                EventReceiver* eventReceiver )
{
  characterManager.Update( eventReceiver, terrainManager.terrainNode );
  cameraManager.Update( device, eventReceiver, characterManager );
}

//*****************************************************************************
// Draw All
//*****************************************************************************
void SceneManager::drawAll()
{
  sceneManager->drawAll();
}
