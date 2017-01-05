#include "SceneManager.hpp"

//*****************************************************************************
// Load scene
//*****************************************************************************
void SceneManager::LoadScene( irr::IrrlichtDevice* device )
{
  //Get information from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();

  //Add terrain
  terrainManager.AddNodeToScene( device, TERRAIN, irr::core::vector3df(0,0,0) );
  terrainManager.addSkyBox( device );

  //Add water terrain
  waterTerrainManager.AddNodeToScene(device, WATER, irr::core::vector3df(4000,-6,4000) );

  //Add character
  playerManager.AddNodeToScene( device, PLAYER, irr::core::vector3df(  5768, 700, 4844 ) );

  //Add camera
  cameraManager.add3rdPersonCameraToScene( sceneManager, CAMERA );
  cameraManager.addSceneNodeCollision( sceneManager, terrainManager.GetNode() );

  //Add Boxes
  boxManager.AddNodeGroupToScene( device, BOX, NB_BOXES );

  //Add Trees
  treeManager.AddNodeGroupToScene( device, TREE, NB_TREES );

  //Add Enemies
  enemyManager.AddNodeGroupToScene( device, ENEMY, NB_ENEMIES );


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

  //Enemies Collision
  std::vector<irr::scene::ISceneNode*> enemyCollisionNodes( treeManager.nodes.begin(), treeManager.nodes.end());
  enemyCollisionNodes.push_back( terrainManager.GetNode() );
  enemyManager.SetupCollision( device, enemyCollisionNodes,
    irr::core::vector3df(25,24.44,25), irr::core::vector3df(0,-10,0));
  enemyManager.SetupInterCollision( device,
    irr::core::vector3df(25,24.44,25), irr::core::vector3df(0,0,0) );

  //Set Bullet Manager information for shooting
  bulletManager.device = device;
  bulletManager.boxManager = &boxManager;
  bulletManager.treeManager = &treeManager;
  bulletManager.enemyManager = &enemyManager;

  //Load GUI font to display text
  font = device->getGUIEnvironment()->getFont( PathFinder::GetFullMediaPath( "bigfont.png" ) );

}

//*****************************************************************************
// Update scene
//*****************************************************************************
void SceneManager::UpdateScene( irr::IrrlichtDevice* device, EventReceiver* eventReceiver )
{
    //Handle GameOver
    if( playerManager.GameOver )
      {
      //Stop updating unless restart is requested
      while( !eventReceiver->IsKeyDown( irr::KEY_KEY_R ) )
        return;
      //Reload scene
      device->getSceneManager()->clear();
      playerManager = PlayerManager();//TODO: Implement Destructors for managers
      terrainManager = TerrainManager();
      cameraManager = CameraManager();
      waterTerrainManager = WaterTerrainManager();
      boxManager = BoxManager();
      bulletManager = BulletManager();
      enemyManager = EnemyManager();
      treeManager = TreeManager();
      LoadScene( device );
      return;
  }
  //Handle creation of bullets when shooting
  if( playerManager.requestShoot )
    {
    //Bullets Collision nodes
    std::vector<irr::scene::ISceneNode*> bulletCollisionNodes( treeManager.nodes.begin(), treeManager.nodes.end());
    bulletCollisionNodes.insert( bulletCollisionNodes.end(), boxManager.nodes.begin(), boxManager.nodes.end());
    bulletCollisionNodes.insert( bulletCollisionNodes.end(), enemyManager.nodes.begin(), enemyManager.nodes.end());

    //Create bullet
    bulletManager.Shoot( device, BULLET, bulletCollisionNodes, playerManager.GetNode()->getPosition(), playerManager.forward );
    playerManager.requestShoot = false;
    }

  //Update collision system when a node is deleted
  if( boxManager.requestUpdate || treeManager.requestUpdate || enemyManager.requestUpdate )
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

    //Enemies Collision
    for(unsigned int i =0; i<enemyManager.nodes.size(); i++)
      enemyManager.nodes[i]->removeAnimators();
    std::vector<irr::scene::ISceneNode*> enemyCollisionNodes( treeManager.nodes.begin(), treeManager.nodes.end());
    enemyCollisionNodes.push_back( terrainManager.GetNode() );
    enemyManager.SetupCollision( device, enemyCollisionNodes,
      irr::core::vector3df(25,24.44,25), irr::core::vector3df(0,-10,0));
    enemyManager.SetupInterCollision( device,
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
    treeManager.requestUpdate = false;
    enemyManager.requestUpdate = false;
    }

  //Update managers
  playerManager.Update( eventReceiver );
  cameraManager.Update( device, eventReceiver, playerManager );
  bulletManager.Update();
  enemyManager.Update( device, &playerManager );

}

//*****************************************************************************
// Draw All
//*****************************************************************************
void SceneManager::drawAll( irr::IrrlichtDevice* device )
{
  //Get information from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();

  sceneManager->drawAll();

  //Draw score
  int score = boxManager.scoreContribution +
    treeManager.scoreContribution +
    enemyManager.scoreContribution;
  irr::core::stringw text = "Score : ";
  text += score;
  font->draw( text.c_str(),
      irr::core::rect<irr::s32>( 10, 10, 400, 50 ),
      irr::video::SColor( 255, 255, 255, 0 ) );

  //GameOver
  if( playerManager.GameOver )
    font->draw( L"Game Over ! Restart -> r",
      irr::core::rect<irr::s32>( 150, 300, 400, 50 ),
      irr::video::SColor( 255, 255, 255, 0 ) );
}

