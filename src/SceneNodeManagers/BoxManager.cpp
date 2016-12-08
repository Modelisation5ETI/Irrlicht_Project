#include "BoxManager.hpp"

//*****************************************************************************
// Add multiple Boxes
//*****************************************************************************
void BoxManager::AddNodeGroupToScene( irr::IrrlichtDevice* device, irr::s32 id,
  unsigned int nbNodes )
{
  for( unsigned int i = 0; i < nbNodes; i++ )
    {
    BoxManager::AddNodeToScene( device, id + i, irr::core::vector3df( 1050, 570 + 60*i, 1000 ) );
    }
}

//*****************************************************************************
// Add box
//*****************************************************************************
void BoxManager::AddNodeToScene( irr::IrrlichtDevice* device, irr::s32 id,
  irr::core::vector3df position )
{
  //Get information from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();
  irr::video::IVideoDriver* driver = device->getVideoDriver();

  //Add Box
  irr::f32 boxSize = 50;
  irr::scene::IMeshSceneNode* box =
    sceneManager->addCubeSceneNode( boxSize, 0, id, position );

  //Set Name
  box->setName("Box");

  //Material
  box->setMaterialTexture( 0, driver->getTexture( PathFinder::GetFullMediaPath("box.jpg") ) );
  box->setMaterialFlag( irr::video::EMF_LIGHTING, false );

  //Collision
  box->setTriangleSelector( sceneManager->createTriangleSelectorFromBoundingBox( box ) );

  //Save Data
  NodeGroupManager::nodes.push_back( box );
  nodesHP.push_back( 100 );
}

//*****************************************************************************
// CollisionCallback
//*****************************************************************************
bool BoxManager::onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse& animator)
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
// Take Damage
//*****************************************************************************
void BoxManager::TakeDamage( irr::IrrlichtDevice* device, irr::s32 id, float damage )
{
  //Find node
  for( unsigned int i = 0; i < NodeGroupManager::nodes.size(); i++ )
    {
    if( NodeGroupManager::nodes[i]->getID() == id )
      {
      //Take damage
      nodesHP[i] -= damage;
      //Check for node life
      if( nodesHP[i] <= 0 )
        {
        //Set Flag to update collision setup in SceneManager
        requestUpdate = true;

        //Delete node
        device->getSceneManager()->addToDeletionQueue(NodeGroupManager::nodes[i]);
        NodeGroupManager::nodes[i]->removeAnimators();
        NodeGroupManager::nodes.erase(NodeGroupManager::nodes.begin()+i);
        nodesHP.erase(nodesHP.begin()+i);
        }
      }
    }
}
