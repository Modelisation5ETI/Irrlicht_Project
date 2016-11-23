#pragma once

#ifndef CAMERAMANAGER_HPP
#define CAMERAMANAGER_HPP

#include <irrlicht.h>
#include "PathFinder.hpp"
#include "EventReceiver.hpp"
#include "CharacterManager.hpp"
#include <iostream>

class CameraManager
{
  public:
    //! Constructor
    CameraManager()
      :FarValue( 42000.0f ), setCameraToMeshOrientation( true ),
       moveCameraCursor( false ), d_Interpolate( 1.0f ),
       x_Rotation( 0.0f ), y_Rotation( 0.0f )
    {}

    //Add 3er person camera
    void add3rdPersonCameraToScene( irr::scene::ISceneManager* sceneManager );

    //Add FPS camera
    void addFPSCameraToScene( irr::scene::ISceneManager* sceneManager );

    //Add Static camera
    void addStaticCameraToScene( irr::scene::ISceneManager* sceneManager );

    //Timer tick
    void timerTick( irr::IrrlichtDevice* device );

    //Add scene node collision
    void addSceneNodeCollision( irr::scene::ISceneManager* sceneManager, irr::scene::ISceneNode* sceneNode );

    // Update camera according to the 3rd person character
    void Update( irr::IrrlichtDevice* device,
      EventReceiver* eventReceiver, CharacterManager characterManager );

    //Set camera orientation to mesh orientation
    void replaceCameraToMesh( float y_MeshRotation );

    //Check orientation condition to replace camera to mesh orientation
    bool checkOrientation( irr::IrrlichtDevice* device,
      bool arrowDown, float dx, float dy, float y_MeshRotation );


    //Camera parameters
    irr::scene::ICameraSceneNode* cameraNode;
    float FarValue;

    //Collision handling
    irr::scene::IMetaTriangleSelector * metaTriangleSelector;

    //3rd Person Camera parameters
    // Replace camera to mesh direction parameters
    bool setCameraToMeshOrientation;
    bool moveCameraCursor;
    float d_Interpolate;
    // Rotation parameters
    float x_Rotation;
    float y_Rotation;

    //Time parameters
    float time;
    float timer;


};

#endif // CAMERAMANAGER_HPP
