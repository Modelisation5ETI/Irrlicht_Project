#include "CollisionNodeManager.hpp"

//*****************************************************************************
// Setup Collision with an ISceneNode
//*****************************************************************************
template <typename NodeType>
void CollisionNodeManager<NodeType>::SetupCollision( irr::IrrlichtDevice* device,
  irr::scene::ISceneNode* collidableNode,
  const irr::core::vector3df& ellipsoidRadius,
  const irr::core::vector3df& gravity )
{
  //Get SceneManager from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();

  //Create collision response animator and attach it to the scene node
  irr::scene::ISceneNodeAnimatorCollisionResponse* animator =
    sceneManager->createCollisionResponseAnimator(
      collidableNode->getTriangleSelector(), NodeManager<NodeType>::node,
      ellipsoidRadius,                      //Ellipsoid Radius
      gravity,                              //Gravity per second
      irr::core::vector3df( 0, 0, 0) );     //Ellipsoid Translation (Offset)
  animator->setCollisionCallback( this );
  NodeManager<NodeType>::node->addAnimator( animator );

  //Cleaning
  animator->drop();
}

//*****************************************************************************
// Setup Collision with a vector of ISceneNode
//*****************************************************************************
template <typename NodeType>
void CollisionNodeManager<NodeType>::SetupCollision( irr::IrrlichtDevice* device,
  std::vector<irr::scene::ISceneNode*> collidableNodes,
  const irr::core::vector3df& ellipsoidRadius,
  const irr::core::vector3df& gravity )
{
  //Get SceneManager from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();

  //Create MetaTriangleSelector
  irr::scene::IMetaTriangleSelector* metaTriangleSelector =
    sceneManager->createMetaTriangleSelector();

  for( unsigned int i = 0; i < collidableNodes.size(); i++ )
    {
    metaTriangleSelector->addTriangleSelector(
      collidableNodes[i]->getTriangleSelector() );
    }

  //Create collision response animator and attach it to the scene node
  irr::scene::ISceneNodeAnimatorCollisionResponse* animator =
    sceneManager->createCollisionResponseAnimator(
      metaTriangleSelector, NodeManager<NodeType>::node,
      ellipsoidRadius,                      //Ellipsoid Radius
      gravity,                              //Gravity per second
      irr::core::vector3df( 0, 0, 0) );     //Ellipsoid Translation (Offset)
  animator->setCollisionCallback( this );
  NodeManager<NodeType>::node->addAnimator( animator );

  //Cleaning
  animator->drop();
  metaTriangleSelector->drop();
}

template class CollisionNodeManager<irr::scene::IAnimatedMeshSceneNode>;
