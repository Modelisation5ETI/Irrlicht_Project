#pragma once

#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <irrlicht.h>
#include "PathFinder.hpp"

#include "TerrainManager.hpp"
#include "CharacterManager.hpp"
#include "CameraManager.hpp"

class SceneManager
{
  public:
    //! Constructor
    SceneManager( irr::video::IVideoDriver* iVideoDriver,
      irr::scene::ISceneManager* iSceneManager ) :
      videoDriver(iVideoDriver), sceneManager(iSceneManager)
    {}

  // Load scene
  void LoadScene();

  // Update scene
  void UpdateScene( irr::IrrlichtDevice* device,
                    EventReceiver* eventReceiver );

  // Draw All
  void drawAll();


  private:
    // Scene nodes
    TerrainManager terrainManager;
    CharacterManager characterManager;
    CameraManager cameraManager;

    // Irrlicht Video Driver
    irr::video::IVideoDriver* videoDriver;

    // Irrlicht SceneManager
    irr::scene::ISceneManager* sceneManager;

};
#endif // SCENEMANAGER_HPP
