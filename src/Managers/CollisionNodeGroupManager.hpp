#pragma once

#ifndef COLLISIONNODEGROUPMANAGER_HPP
#define COLLISIONNODEGROUPMANAGER_HPP

#include "ShootableNodeGroupManager.hpp"

template <typename NodeType>
class CollisionNodeGroupManager : public ShootableNodeGroupManager<NodeType>, public irr::scene::ICollisionCallback
{
  public:
  // Setup Collision with an ISceneNode
  void SetupCollision( irr::IrrlichtDevice* device,
    irr::scene::ISceneNode* collidableNode,
    const irr::core::vector3df& ellipsoidRadius,
    const irr::core::vector3df& gravity );

  // Setup Collision with a vector of ISceneNode
  void SetupCollision( irr::IrrlichtDevice* device,
    std::vector<irr::scene::ISceneNode*> collidableNodes,
    const irr::core::vector3df& ellipsoidRadius,
    const irr::core::vector3df& gravity );

  // Setup Collision between nodes of the group
  void SetupInterCollision( irr::IrrlichtDevice* device,
    const irr::core::vector3df& ellipsoidRadius,
    const irr::core::vector3df& gravity );

  private:
  // Collision Callback
  virtual bool onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse& animator) = 0;

};

#endif // COLLISIONNODEGROUPMANAGER_HPP
