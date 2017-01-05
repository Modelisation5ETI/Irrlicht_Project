#pragma once

#ifndef BOXMANAGER_HPP
#define BOXMANAGER_HPP

#include "CollisionNodeGroupManager.hpp"

typedef typename irr::scene::IMeshSceneNode BoxNodeType;
class BoxManager : public CollisionNodeGroupManager<BoxNodeType>
{
  public:
    //Add multiple Boxes
    void AddNodeGroupToScene( irr::IrrlichtDevice* device, irr::s32 id,
      unsigned int nbNodes );

    //Add Box
    void AddNodeToScene( irr::IrrlichtDevice* device, irr::s32 id,
      irr::core::vector3df position  );

  private:
    // Collision Callback
    bool onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse& animator);

};

#endif // BOXMANAGER_HPP
