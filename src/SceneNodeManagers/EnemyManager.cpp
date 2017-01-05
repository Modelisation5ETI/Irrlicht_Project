#include "EnemyManager.hpp"

//*****************************************************************************
// Add multiple Boxes
//*****************************************************************************
void EnemyManager::AddNodeGroupToScene( irr::IrrlichtDevice* device, irr::s32 id,
  unsigned int nbNodes )
{
  //WARNING: Hard cast here because we know that terrain has id 1
  irr::scene::ITerrainSceneNode* terrain =
    (irr::scene::ITerrainSceneNode*)(device->getSceneManager()->getSceneNodeFromId(1));

  if( !terrain )
    return;

  for( unsigned int i = 0; i < nbNodes; i++ )
    {
    //Generate pseudo-random position
    float x =rand()%int(terrain->getBoundingBox().getExtent().X - 100) + 100;
    float z =rand()%int(terrain->getBoundingBox().getExtent().Z - 100) + 100;
    float y = terrain->getHeight( x, z ) + 100;

    //Add Box
    EnemyManager::AddNodeToScene( device, id + i, irr::core::vector3df( x, y, z ) );
    }
}

//*****************************************************************************
// Add box
//*****************************************************************************
void EnemyManager::AddNodeToScene( irr::IrrlichtDevice* device, irr::s32 id,
  irr::core::vector3df position )
{
    // Get information from device
    irr::scene::ISceneManager* sceneManager = device->getSceneManager();
    irr::video::IVideoDriver* driver = device->getVideoDriver();

    //Add mesh
    irr::scene::IAnimatedMesh* mesh = sceneManager->getMesh(
      PathFinder::GetFullMediaPath( "Enemy/Droid.md2" ) );
    irr::scene::IAnimatedMeshSceneNode* node = sceneManager->addAnimatedMeshSceneNode( mesh, 0, id, position );

    //Add particles system and emitter
    irr::scene::IParticleSystemSceneNode* ps =
      sceneManager->addParticleSystemSceneNode(false);
     nodesPS.push_back(ps);
  
    //Set Name
    node->setName("Enemy");

    //Material
    node->setMaterialFlag( irr::video::EMF_LIGHTING, false );
    node->setMaterialTexture( 0,
      driver->getTexture( PathFinder::GetFullMediaPath( "Enemy/Droid.jpg" ) ) );

    //MD2 Animation
    node->setMD2Animation( irr::scene::EMAT_STAND );

    node->setPosition(  irr::core::vector3df( 1500, 570, 1000 ) );

    //Set Triangle Selector
    node->setTriangleSelector( sceneManager->createTriangleSelector( node ) );

    //Save Data
    NodeGroupManager::nodes.push_back( node );
    nodesHP.push_back( 100 );
}

//*****************************************************************************
// CollisionCallback
//*****************************************************************************
bool EnemyManager::onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse& animator)
{
     irr::scene::ISceneNode* collisionNode = animator.getCollisionNode();
     irr::core::string<irr::c8> nodeName = collisionNode->getName();

     // Collision with a box
     if( nodeName == irr::core::string<irr::c8>("Box") )
       {
       std::cout<<animator.getTargetNode()->getID()<<" collision with "<<collisionNode->getID()<<std::endl;
       }
  return false;
}

//*****************************************************************************
// Update
//*****************************************************************************
void EnemyManager::Update( irr::IrrlichtDevice* device, PlayerManager* playerManager )
{
  for( unsigned int i = 0; i < NodeGroupManager::nodes.size(); i++ )
    {
    //Minimum distance to player
    float enemySize = 60;
    float minRadius = 300;
    //Enemy Speed
    float speed = 2.0f;
    //Enemy Node
    irr::scene::IAnimatedMeshSceneNode* enemyNode = NodeGroupManager::nodes[i];
    //Direction to player
    irr::core::vector3df direction = ( playerManager->GetNode()->getPosition() - enemyNode->getPosition() );
    float distToPlayerSQ = direction.getLengthSQ();
    direction.normalize();

    //Run toward player
    if( distToPlayerSQ < minRadius * minRadius )
      {
      enemyNode->setPosition( enemyNode->getPosition() + speed * direction );
      enemyNode->setMD2Animation( irr::scene::EMAT_RUN );
      animationType = irr::scene::EMAT_RUN;
      }
    else
      {
      if( animationType != irr::scene::EMAT_STAND  )
        {
        enemyNode->setMD2Animation( irr::scene::EMAT_STAND );
        animationType = irr::scene::EMAT_STAND;
        }
      }

    //Kamikaze
    if( distToPlayerSQ <  0.25 * enemySize * enemySize )
      {
      //Enemy explosion
      Die( device, i );
      //Hurt player
      playerManager->TakeDamage( device, 100 );
      }

    }
}
