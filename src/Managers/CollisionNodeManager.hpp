#pragma once

#ifndef COLLISIONNODEMANAGER_HPP
#define COLLISIONNODEMANAGER_HPP

#include "ShootableNodeManager.hpp"

#include <vector>

template <typename NodeType>
class CollisionNodeManager : public ShootableNodeManager<NodeType>, irr::scene::ICollisionCallback
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

  private:
  // Collision Callback
  virtual bool onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse& animator) = 0;


};

#endif // COLLISIONNODEMANAGER_HPP
