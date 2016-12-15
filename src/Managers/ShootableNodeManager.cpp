#include "ShootableNodeManager.hpp"

//*****************************************************************************
// Take Damage
//*****************************************************************************
template <typename NodeType>
void ShootableNodeManager<NodeType>::TakeDamage( irr::IrrlichtDevice* device, float damage )
{
  //Take damage
  HP -= damage;
  //Check for node life
  if( HP <= 0 )
    {
    //Die
    Die( device );
    }
}

//*****************************************************************************
// Die : Behavior to adopt if HP < 0
//*****************************************************************************
template <typename NodeType>
void ShootableNodeManager<NodeType>::Die( irr::IrrlichtDevice* device )
{
  //Get information from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();

  //Delete node
  sceneManager->addToDeletionQueue( NodeManager<NodeType>::node );
  NodeManager<NodeType>::node->removeAnimators();
//  NodeManager<NodeType>::node->drop;

  //Set Flag to update collision setup in SceneManager
  requestUpdate = true;

  return;
}

template class ShootableNodeManager<irr::scene::IAnimatedMeshSceneNode>;

