#include "CollisionNodeGroupManager.hpp"

//*****************************************************************************
// Setup Collision with an ISceneNode
//*****************************************************************************
template <typename NodeType>
void CollisionNodeGroupManager<NodeType>::SetupCollision( irr::IrrlichtDevice* device,
  irr::scene::ISceneNode* collidableNode,
  const irr::core::vector3df& ellipsoidRadius,
  const irr::core::vector3df& gravity )
{
  //Get SceneManager from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();

  for( unsigned int i = 0; i < NodeGroupManager<NodeType>::nodes.size(); i++ )
    {
    //Create collision response animator and attach it to the scene node
    irr::scene::ISceneNodeAnimatorCollisionResponse* animator =
      sceneManager->createCollisionResponseAnimator(
        collidableNode->getTriangleSelector(), NodeGroupManager<NodeType>::nodes[i],
        ellipsoidRadius,                      //Ellipsoid Radius
        gravity,                              //Gravity per second
        irr::core::vector3df( 0, 0, 0) );     //Ellipsoid Translation (Offset)
    animator->setCollisionCallback( this );
    NodeGroupManager<NodeType>::nodes[i]->addAnimator( animator );

    //Cleaning
    animator->drop();
    }
}

//*****************************************************************************
// Setup Collision with a vector of ISceneNode
//*****************************************************************************
template <typename NodeType>
void CollisionNodeGroupManager<NodeType>::SetupCollision( irr::IrrlichtDevice* device,
  std::vector<irr::scene::ISceneNode*> collidableNodes,
  const irr::core::vector3df& ellipsoidRadius,
  const irr::core::vector3df& gravity )
{
  //Get SceneManager from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();

  for( unsigned int i = 0; i < NodeGroupManager<NodeType>::nodes.size(); i++ )
    {
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
        metaTriangleSelector, NodeGroupManager<NodeType>::nodes[i],
        ellipsoidRadius,                      //Ellipsoid Radius
        gravity,                              //Gravity per second
        irr::core::vector3df( 0, 0, 0) );     //Ellipsoid Translation (Offset)
    animator->setCollisionCallback( this );
    NodeGroupManager<NodeType>::nodes[i]->addAnimator( animator );

    //Cleaning
    animator->drop();
    metaTriangleSelector->drop();
    }
}

//*****************************************************************************
// Setup collision between all the nodes from the group
//*****************************************************************************
template <typename NodeType>
void CollisionNodeGroupManager<NodeType>::SetupInterCollision( irr::IrrlichtDevice* device,
  const irr::core::vector3df& ellipsoidRadius,
  const irr::core::vector3df& gravity )
{
  //Get SceneManager from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();

  for( unsigned int i = 0; i < NodeGroupManager<NodeType>::nodes.size(); i++ )
    {
    //Define collidable nodes
    std::vector<irr::scene::ISceneNode*> collidableNodes;
    for( unsigned int j = 0; j < NodeGroupManager<NodeType>::nodes.size(); j++ )
      {
      if( i != j )
        collidableNodes.push_back(NodeGroupManager<NodeType>::nodes[j]);
      }

    //Create MetaTriangleSelector
    irr::scene::IMetaTriangleSelector* metaTriangleSelector = sceneManager->createMetaTriangleSelector();
    for( unsigned int i = 0; i < collidableNodes.size(); i++ )
      {
      metaTriangleSelector->addTriangleSelector( collidableNodes[i]->getTriangleSelector() );
      }

    // Create collision response animator and attach it to the scene node
    irr::scene::ISceneNodeAnimatorCollisionResponse* animator = sceneManager->createCollisionResponseAnimator(
      metaTriangleSelector, NodeGroupManager<NodeType>::nodes[i],
      ellipsoidRadius,                      //Ellipsoid Radius
      gravity,                              //Gravity per second
      irr::core::vector3df( 0, 0, 0) );     //Ellipsoid Translation (Offset)
    animator->setCollisionCallback( this );
    NodeGroupManager<NodeType>::nodes[i]->addAnimator( animator );
    metaTriangleSelector->drop();
    animator->drop();
    }

}

template class CollisionNodeGroupManager<irr::scene::ISceneNode>;
template class CollisionNodeGroupManager<irr::scene::IMeshSceneNode>;
