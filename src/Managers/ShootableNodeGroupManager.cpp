#include "ShootableNodeGroupManager.hpp"
#include "CTreeSceneNode.h"

//*****************************************************************************
// Take Damage
//*****************************************************************************
template <typename NodeType>
void ShootableNodeGroupManager<NodeType>::TakeDamage( irr::IrrlichtDevice* device, irr::s32 id, float damage )
{
  //Find node
  for( unsigned int i = 0; i < NodeGroupManager<NodeType>::nodes.size(); i++ )
    {
    if( NodeGroupManager<NodeType>::nodes[i]->getID() == id )
      {
      //Take damage
      nodesHP[i] -= damage;
      //Check for node life
      if( nodesHP[i] <= 0 )
        {
        //Set Flag to update collision setup in SceneManager
        requestUpdate = true;
        //Die
        Die( device, i );
        nodesHP.erase( nodesHP.begin() + i );
        }
      }
    }
}

//*****************************************************************************
// Die : Behavior to adopt if HP < 0
//*****************************************************************************
template <typename NodeType>
void ShootableNodeGroupManager<NodeType>::Die( irr::IrrlichtDevice* device, unsigned int i )
{

  //Get information from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();

  //Compute billboard position
  irr::scene::ISceneNode* node = NodeGroupManager<NodeType>::nodes[i];
  irr::core::vector3df position( node->getPosition() +
    irr::core::vector3df( 0, (node->getBoundingBox().getExtent().Y)/2.0f, 0 ) );

  //Draw billbord points
  irr::scene::IBillboardSceneNode* points = sceneManager->addBillboardSceneNode(
    0, irr::core::dimension2df(15,15), position, -1 );

  //Material
  points->setMaterialTexture( 0, scoreBillboard );
  points->setMaterialType( irr::video::EMT_TRANSPARENT_ADD_COLOR );
  points->setMaterialFlag( irr::video::EMF_LIGHTING, false );
  points->setMaterialFlag( irr::video::EMF_ZWRITE_ENABLE, false );

  //Fly Animator
  irr::scene::ISceneNodeAnimator* flyAnimator = sceneManager->createFlyStraightAnimator(
    position, position + irr::core::vector3df(0,60,0), 750 );
  points->addAnimator( flyAnimator );
  flyAnimator->drop();

  //Delete Animator
  irr::scene::ISceneNodeAnimator* deleteAnimator = sceneManager->createDeleteAnimator( 1000 );
  points->addAnimator( deleteAnimator );
  deleteAnimator->drop();

  //Delete node
  device->getSceneManager()->addToDeletionQueue( NodeGroupManager<NodeType>::nodes[i] );
  NodeGroupManager<NodeType>::nodes[i]->removeAnimators();
  NodeGroupManager<NodeType>::nodes.erase( NodeGroupManager<NodeType>::nodes.begin() + i );

  return;
}


template class ShootableNodeGroupManager<irr::scene::IMeshSceneNode>;
template class ShootableNodeGroupManager<irr::scene::IBillboardSceneNode>;
template class ShootableNodeGroupManager<irr::scene::ISceneNode>;
template class ShootableNodeGroupManager<irr::scene::CTreeSceneNode>;
