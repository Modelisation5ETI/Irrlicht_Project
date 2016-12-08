#include "SceneManager.hpp"

//*****************************************************************************
// Load scene
//*****************************************************************************
void SceneManager::LoadScene( irr::IrrlichtDevice* device )
{
  //Add terrain
  terrainManager.AddNodeToScene( device, TERRAIN, irr::core::vector3df(0,0,0) );
  terrainManager.addSkyBox( device);

  //Add character
  playerManager.AddNodeToScene( device, PLAYER, irr::core::vector3df( 1000, 570, 1000 ) );

  //Add camera
  cameraManager.add3rdPersonCameraToScene( sceneManager, CAMERA );
  cameraManager.addSceneNodeCollision( sceneManager, terrainManager.GetNode() );

  //Add Boxes
  boxManager.AddNodeGroupToScene( device, BOX, NB_BOXES );

  //Add Trees
  treeManager.AddNodeGroupToScene( device, TREE, NB_TREES );


  //Player Collision
  std::vector<irr::scene::ISceneNode*> playerCollisionNodes( boxManager.nodes.begin(),boxManager.nodes.end());
  playerCollisionNodes.insert( playerCollisionNodes.end(), treeManager.nodes.begin(), treeManager.nodes.end());
  playerManager.SetupCollision( device, terrainManager.GetNode(), irr::core::vector3df(25,24.44,25), irr::core::vector3df(0,-10,0) );
  playerManager.SetupCollision( device, playerCollisionNodes, irr::core::vector3df(25,24.44,25), irr::core::vector3df(0,0,0) );

  //Boxes Collision
  std::vector<irr::scene::ISceneNode*> boxCollisionNodes( treeManager.nodes.begin(), treeManager.nodes.end());
  boxCollisionNodes.push_back( terrainManager.GetNode() );
  boxManager.SetupCollision( device, boxCollisionNodes,
    irr::core::vector3df(25,24.44,25), irr::core::vector3df(0,-10,0));
  boxManager.SetupInterCollision( device,
    irr::core::vector3df(25,24.44,25), irr::core::vector3df(0,0,0) );

  //Set Bullet Manager information for shooting
  bulletManager.device = device;
  bulletManager.boxManager = &boxManager;
  bulletManager.treeManager = &treeManager;

}

//*****************************************************************************
// Update scene
//*****************************************************************************
void SceneManager::UpdateScene( irr::IrrlichtDevice* device, EventReceiver* eventReceiver )
{
  //Handle creation of bullets when shooting
  if( playerManager.requestShoot )
    {
    //Bullets Collision nodes
    std::vector<irr::scene::ISceneNode*> bulletCollisionNodes( treeManager.nodes.begin(), treeManager.nodes.end());
    bulletCollisionNodes.insert( bulletCollisionNodes.end(), boxManager.nodes.begin(), boxManager.nodes.end());

    //Create bullet
    bulletManager.Shoot( device, BULLET, bulletCollisionNodes, playerManager.GetNode()->getPosition(), playerManager.forward );
    playerManager.requestShoot = false;
    }

  //Update collision system when a node is deleted
  if( boxManager.requestUpdate || treeManager.requestUpdate )
  {
      //Player Collision
      playerManager.GetNode()->removeAnimators();
      std::vector<irr::scene::ISceneNode*> playerCollisionNodes( boxManager.nodes.begin(),boxManager.nodes.end());
      playerCollisionNodes.insert( playerCollisionNodes.end(), treeManager.nodes.begin(), treeManager.nodes.end());
      playerManager.SetupCollision( device, terrainManager.GetNode(), irr::core::vector3df(25,24.44,25), irr::core::vector3df(0,-10,0) );
      playerManager.SetupCollision( device, playerCollisionNodes, irr::core::vector3df(25,24.44,25), irr::core::vector3df(0,0,0) );

      //Boxes Collision
      for(unsigned int i =0; i<boxManager.nodes.size(); i++)
        boxManager.nodes[i]->removeAnimators();
      std::vector<irr::scene::ISceneNode*> boxCollisionNodes( treeManager.nodes.begin(), treeManager.nodes.end());
      boxCollisionNodes.push_back( terrainManager.GetNode() );
      boxManager.SetupCollision( device, boxCollisionNodes,
        irr::core::vector3df(25,24.44,25), irr::core::vector3df(0,-10,0));
      boxManager.SetupInterCollision( device,
        irr::core::vector3df(25,24.44,25), irr::core::vector3df(0,0,0) );

      //Delete bullets
      for(unsigned int i = 0; i < bulletManager.nodes.size(); i++)
        {
        device->getSceneManager()->addToDeletionQueue(bulletManager.nodes[i]);
        bulletManager.nodes[i]->removeAnimators();
        }
      bulletManager.nodes.clear();
      bulletManager.time.clear();

      //Reset flags
      boxManager.requestUpdate = false;
      treeManager.requestUpdate =false;
  }

  //Update managers
  playerManager.Update( eventReceiver );
  cameraManager.Update( device, eventReceiver, playerManager );
  bulletManager.Update();
}

//*****************************************************************************
// Draw All
//*****************************************************************************
void SceneManager::drawAll()
{
  sceneManager->drawAll();
}

