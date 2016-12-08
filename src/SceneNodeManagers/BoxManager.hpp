#pragma once

#ifndef BOXMANAGER_HPP
#define BOXMANAGER_HPP

#include "CollisionNodeGroupManager.hpp"

typedef typename irr::scene::IMeshSceneNode NodeType;
class BoxManager : public CollisionNodeGroupManager<NodeType>
{
  public:
    //Add multiple Boxes
    void AddNodeGroupToScene( irr::IrrlichtDevice* device, irr::s32 id,
      unsigned int nbNodes );

    //Add Box
    void AddNodeToScene( irr::IrrlichtDevice* device, irr::s32 id,
      irr::core::vector3df position  );

    //Take Damage
    void TakeDamage( irr::IrrlichtDevice* device, irr::s32 id, float damage );
    //Nodes' Health Points
    std::vector<int> nodesHP;
    //Request update if a node is deleted
    bool requestUpdate = false;

  private:
    // Collision Callback
    bool onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse& animator);



};

#endif // BOXMANAGER_HPP
