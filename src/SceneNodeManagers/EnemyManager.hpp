#pragma once

#ifndef ENEMYMANAGER_HPP
#define ENEMYMANAGER_HPP

#include "CollisionNodeGroupManager.hpp"
#include "PlayerManager.hpp"

typedef typename irr::scene::IAnimatedMeshSceneNode EnemyNodeType;
class EnemyManager : public CollisionNodeGroupManager<EnemyNodeType>
{
  public:
    //Add multiple Boxes
    void AddNodeGroupToScene( irr::IrrlichtDevice* device, irr::s32 id,
      unsigned int nbNodes );

    //Add Box
    void AddNodeToScene( irr::IrrlichtDevice* device, irr::s32 id,
      irr::core::vector3df position  );

    //Update
    void Update( irr::IrrlichtDevice* device, PlayerManager playerManager );

  private:
    // Collision Callback
    bool onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse& animator);

    // Animation
    irr::scene::EMD2_ANIMATION_TYPE animationType;
};

#endif // ENEMYMANAGER_HPP
