#pragma once

#ifndef BOXMANAGER_HPP
#define BOXMANAGER_HPP

#include "CollisionNodeGroupManager.hpp"

class BoxManager : public CollisionNodeGroupManager<irr::scene::IMeshSceneNode>
{
  public:
    // Add multiple Boxes
    void AddNodeGroupToScene( irr::IrrlichtDevice* device, irr::s32 id,
      unsigned int nbNodes );

    // Add Box
    void AddNodeToScene( irr::IrrlichtDevice* device, irr::s32 id,
      irr::core::vector3df position  );

    // Take Damage
    void TakeDamage( irr::IrrlichtDevice* device, irr::s32 id, float damage );


    // Box nodes' health
    std::vector<int> boxNodesHealth;
    bool requestUpdate = false;

  private:
    // Collision Callback
    bool onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse& animator);



};

#endif // BOXMANAGER_HPP
