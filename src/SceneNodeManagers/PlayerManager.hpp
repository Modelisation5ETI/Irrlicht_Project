#pragma once

#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP

#include "CollisionNodeManager.hpp"
#include "AnimationEndCallBack.hpp"
#include "EventReceiver.hpp"
#include "Math.hpp"

class PlayerManager : public CollisionNodeManager<irr::scene::IAnimatedMeshSceneNode>
{
public:
  // Constructor
  PlayerManager()
    :y_Rotation( 0.0f ),
     animationType( irr::scene::EMAT_STAND ), animationSwitch( false )
  {}

  // Add node to scene
  void AddNodeToScene( irr::IrrlichtDevice* device,
    irr::s32 id, irr::core::vector3df position );
  
  // Collision Callback
  bool onCollision( const irr::scene::ISceneNodeAnimatorCollisionResponse& animator );

  // Update Character
  void Update( EventReceiver* eventReceiver, irr::IrrlichtDevice* device );

  //Return Rotation value around Y axis
  float Get_Y_Rotation();


  //Mesh Forward
  irr::core::vector3df forward;

  // Request Shooting
  bool requestShoot = false;

  //Game Over
  bool GameOver = false;

private:
  //Override Die()
  virtual void Die( irr::IrrlichtDevice* device );

  //Update 3rd person position and orientation
  void updateTransform( EventReceiver* eventReceiver, irr::IrrlichtDevice* device );

  //Update 3rd person animation
  void updateAnimation( EventReceiver* eventReceiver );

  //Rotation around Y
  float y_Rotation;
  // Animation
  irr::scene::EMD2_ANIMATION_TYPE animationType;
  bool animationSwitch;
  AnimationEndCallBack attackEndReceiver;
  AnimationEndCallBack jumpEndReceiver;

};

#endif // PLAYERMANAGER_HPP
