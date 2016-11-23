#pragma once

#ifndef CHARACTERMANAGER_HPP
#define CHARACTERMANAGER_HPP

#include <irrlicht.h>
#include "PathFinder.hpp"
#include "EventReceiver.hpp"
#include "AnimationEndCallBack.hpp"
#include "Math.hpp"
#include <iostream>

class CharacterManager
{
  public:
    //! Constructor
    CharacterManager()
      :y_MeshRotation( 0.0f ),
       animationType( irr::scene::EMAT_STAND ), animationSwitch( false )
    {}


    //Add IAnimatedMeshSceneNode to scene manager
    void addCharacterToScene( irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver );

    // Update Character
    void Update( EventReceiver* eventReceiver, irr::scene::ITerrainSceneNode* terrainNode );

    //Update 3rd person position and orientation
    void updateTransform( EventReceiver* eventReceiver, irr::scene::ITerrainSceneNode* terrainNode );

    //Update 3rd person animation
    void updateAnimation( EventReceiver* eventReceiver );


    //Animated Mesh scene node
    irr::scene::IAnimatedMeshSceneNode* characterNode;

    //Collision handling
    irr::scene::ISceneNodeAnimatorCollisionResponse* animator;
    irr::scene::IMetaTriangleSelector * metaTriangleSelector;

    //3rd Person parameters
    // Rotation parameter
    float y_MeshRotation;
    // Animation
    irr::scene::EMD2_ANIMATION_TYPE animationType;
    AnimationEndCallBack attackEndReceiver;
    AnimationEndCallBack jumpEndReceiver;
    bool animationSwitch;

};

#endif // CHARACTERMANAGER_HPP
