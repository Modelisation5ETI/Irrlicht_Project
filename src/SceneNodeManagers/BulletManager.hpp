#pragma once

#ifndef BULLETMANAGER_HPP
#define BULLETMANAGER_HPP

#include "CollisionNodeGroupManager.hpp"

#include "BoxManager.hpp"
#include "TreeManager.hpp"
#include "EnemyManager.hpp"


class BulletManager : public CollisionNodeGroupManager<irr::scene::ISceneNode>
{
public:
  //Add multiple Boxes
  void AddNodeGroupToScene( irr::IrrlichtDevice* device, irr::s32 id,
    unsigned int nbNodes );

  //Add Box
  void AddNodeToScene( irr::IrrlichtDevice* device, irr::s32 id,
    irr::core::vector3df position  );

  //Shoot one bullet
  void Shoot( irr::IrrlichtDevice* device,
    irr::s32 id,
    std::vector<irr::scene::ISceneNode*> collidableNode,
    irr::core::vector3df startPoint, irr::core::vector3df direction );

  // Update bullets
  void Update();

  // Update Lifetime
  void updateLifetime();


  irr::IrrlichtDevice* device;
  BoxManager* boxManager;
  TreeManager* treeManager;
  EnemyManager* enemyManager;

  //Lifetime
  std::vector<float> time;


private:
  //Collision Callback
  bool onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse& animator);


};

#endif // BULLETMANAGER_HPP
