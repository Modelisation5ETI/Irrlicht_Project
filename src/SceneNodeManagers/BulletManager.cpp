#include "BulletManager.hpp"

//*****************************************************************************
// Add multiple Bullets
//*****************************************************************************
void BulletManager::AddNodeGroupToScene( irr::IrrlichtDevice* device, irr::s32 id,
  unsigned int nbNodes )
{
  for( unsigned int i = 0; i < nbNodes; i++ )
    {
    BulletManager::AddNodeToScene( device, id + i, irr::core::vector3df( 0,0,0 ) );
    }
}

//*****************************************************************************
// Add bullet
//*****************************************************************************
void BulletManager::AddNodeToScene( irr::IrrlichtDevice* device, irr::s32 id,
  irr::core::vector3df position )
{
  //Get information from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();
  irr::video::IVideoDriver* driver = device->getVideoDriver();

  //Add bullet
  irr::scene::IBillboardSceneNode* bullet = sceneManager->addBillboardSceneNode(
    0, irr::core::dimension2df(15,15), position, id );

  //Material
  bullet->setMaterialTexture( 0, driver->getTexture(
    PathFinder::GetFullMediaPath("particlegreen.jpg") ) );
  bullet->setMaterialType( irr::video::EMT_TRANSPARENT_ADD_COLOR );
  bullet->setMaterialFlag( irr::video::EMF_LIGHTING, false );
  bullet->setMaterialFlag( irr::video::EMF_ZWRITE_ENABLE, false );

  //Store datas
  NodeGroupManager::nodes.push_back( bullet );
  time.push_back(0);
}

//*****************************************************************************
// Shoot
//*****************************************************************************
void BulletManager::Shoot( irr::IrrlichtDevice* device,
  irr::s32 id,
  std::vector<irr::scene::ISceneNode*> collidableNode,
  irr::core::vector3df startPoint, irr::core::vector3df direction )
{

  BulletManager::AddNodeToScene( device, id + NodeGroupManager::nodes.size(), startPoint);

  //Get information from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();

  //Get last bullet
  irr::scene::ISceneNode* bullet = NodeGroupManager::nodes[NodeGroupManager::nodes.size()-1];

  //Add Fly Animator
  irr::core::vector3df endPoint = startPoint + 2500 * direction;
  irr::scene::ISceneNodeAnimator* flyAnimator =
    device->getSceneManager()->createFlyStraightAnimator( startPoint, endPoint, 650 );
  bullet->addAnimator( flyAnimator );

  //Add Collision Animator
  irr::scene::IMetaTriangleSelector* metaTriangleSelector = device->getSceneManager()->createMetaTriangleSelector();
  for( unsigned int i = 0; i < collidableNode.size(); i++ )
    {
    metaTriangleSelector->addTriangleSelector( collidableNode[i]->getTriangleSelector() );
    }

  irr::scene::ISceneNodeAnimatorCollisionResponse* animator = sceneManager->createCollisionResponseAnimator(
    metaTriangleSelector, bullet,
    irr::core::vector3df( 3, 3, 3 ),       //Ellipsoid Radius
    irr::core::vector3df( 0, 0, 0 ),       //Gravity per second
    irr::core::vector3df( 0, 0, 0 ) );     //Ellipsoid Translation (Offset)
  animator->setCollisionCallback( this );
  bullet->addAnimator( animator );

  // Cleaning
  metaTriangleSelector->drop();
  animator->drop();
  flyAnimator->drop();

}

//*****************************************************************************
// CollisionCallback
//*****************************************************************************
bool BulletManager::onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse& animator)
{
  irr::scene::ISceneNode* collisionNode = animator.getCollisionNode();
  irr::core::string<irr::c8> nodeName = collisionNode->getName();

  // Collision with a box
  if( nodeName == irr::core::string<irr::c8>("Box") )
    {
    std::cout<<"COLLISION BULLET - BOX"<<std::endl;
    boxManager->TakeDamage( device, collisionNode->getID(), 20 );
    }

  // Collision with a tree
  if( nodeName == irr::core::string<irr::c8>("Tree") )
    {
    std::cout<<"COLLISION BULLET - TREE"<<std::endl;
    treeManager->TakeDamage( device, collisionNode->getID(), 20 );
    }

  // Collision with a tree
  if( nodeName == irr::core::string<irr::c8>("Enemy") )
    {
    std::cout<<"COLLISION BULLET - ENEMY"<<std::endl;
    enemyManager->TakeDamage( device, collisionNode->getID(), 20 );
    }

  // Delete bullet
  irr::s32 id = animator.getTargetNode()->getID();
  for( unsigned int i = 0; i < NodeGroupManager::nodes.size(); i++ )
    {
    if( NodeGroupManager::nodes[i]->getID() == id )
      {
      device->getSceneManager()->addToDeletionQueue(NodeGroupManager::nodes[i]);
      NodeGroupManager::nodes[i]->removeAnimators();
      NodeGroupManager::nodes.erase(NodeGroupManager::nodes.begin()+i);
      time.erase(time.begin()+i);
      }
    }

  return true;
}

//*****************************************************************************
//  Update
//*****************************************************************************
void BulletManager::Update()
{
  updateLifetime();
}

//*****************************************************************************
// Update Lifetime
//*****************************************************************************
void BulletManager::updateLifetime()
{
  float Lifetime = 50.0f;
  for(unsigned int i = 0; i < NodeGroupManager::nodes.size(); i++)
    {
    if( time[i] > Lifetime )
      {
      // Delete bullet
      device->getSceneManager()->addToDeletionQueue( NodeGroupManager::nodes[i] );
      NodeGroupManager::nodes[i]->removeAnimators();
      NodeGroupManager::nodes.erase( NodeGroupManager::nodes.begin()+ i);
      time.erase( time.begin()+ i );
      }
    else
      {
      time[i] +=1;
      }
    }
}
