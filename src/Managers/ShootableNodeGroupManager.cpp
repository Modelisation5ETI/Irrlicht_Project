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
        //Die
        Die( device, i );
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

  //Draw score using BillboardTextNode
  irr::core::stringw text = irr::core::stringw( score );
  irr::video::SColor colorTop( 255, 255, 255, 0 );//Yellow
  irr::video::SColor colorBottom( 255, 255, 0, 0 );//Red
  irr::gui::IGUIFont* font = device->getGUIEnvironment()->getFont(
    PathFinder::GetFullMediaPath( "bigfont.png" ) );
  irr::scene::IBillboardTextSceneNode* scoreBillboard =
    sceneManager->addBillboardTextSceneNode(
      font, text.c_str(), 0, irr::core::dimension2df(30,20), position, -1,
      colorTop, colorBottom );
  scoreContribution += score;

  //Fly Animator
  irr::scene::ISceneNodeAnimator* flyAnimator = sceneManager->createFlyStraightAnimator(
    position, position + irr::core::vector3df(0,60,0), 750 );
  scoreBillboard->addAnimator( flyAnimator );
  flyAnimator->drop();

  //Delete Animator
  irr::scene::ISceneNodeAnimator* deleteAnimator = sceneManager->createDeleteAnimator( 1000 );
  scoreBillboard->addAnimator( deleteAnimator );
  deleteAnimator->drop();

  //Delete node
  sceneManager->addToDeletionQueue( NodeGroupManager<NodeType>::nodes[i] );
  NodeGroupManager<NodeType>::nodes[i]->removeAnimators();
  NodeGroupManager<NodeType>::nodes.erase( NodeGroupManager<NodeType>::nodes.begin() + i );

  //Set Flag to update collision setup in SceneManager
  requestUpdate = true;
  //Clean HP vector
  nodesHP.erase( nodesHP.begin() + i );

  return;
}


template class ShootableNodeGroupManager<irr::scene::IMeshSceneNode>;
template class ShootableNodeGroupManager<irr::scene::IAnimatedMeshSceneNode>;
template class ShootableNodeGroupManager<irr::scene::ISceneNode>;
template class ShootableNodeGroupManager<irr::scene::CTreeSceneNode>;
