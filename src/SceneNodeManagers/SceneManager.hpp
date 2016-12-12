#pragma once

#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <irrlicht.h>
#include "PathFinder.hpp"

#include "PlayerManager.hpp"

#include "TerrainManager.hpp"
#include "CameraManager.hpp"
#include "BoxManager.hpp"
#include "TreeManager.hpp"
#include "BulletManager.hpp"

#include "CTreeSceneNode.h"

#include <vector>

// Number of  objects
const unsigned int NB_BOXES = 15;
const unsigned int NB_TREES = 15;
// Node IDs
enum NodeID { PLAYER, TERRAIN, CAMERA, BOX, TREE = BOX + NB_BOXES, BULLET = TREE + NB_TREES };


class SceneManager
{
  public:
    //! Constructor
    SceneManager( irr::video::IVideoDriver* iVideoDriver,
      irr::scene::ISceneManager* iSceneManager ) :
      videoDriver(iVideoDriver), sceneManager(iSceneManager)
    {}

  // Load scene
  void LoadScene( irr::IrrlichtDevice* device );

  // Update scene
  void UpdateScene( irr::IrrlichtDevice* device,
                    EventReceiver* eventReceiver );

  // Draw All
  void drawAll();


  private:
    // Scene nodes
    PlayerManager playerManager;
    TerrainManager terrainManager;
    CameraManager cameraManager;
    BoxManager boxManager;
    TreeManager treeManager;
    BulletManager bulletManager;

    // Irrlicht Video Driver
    irr::video::IVideoDriver* videoDriver;

    // Irrlicht SceneManager
    irr::scene::ISceneManager* sceneManager;

    // Score font
    irr::gui::IGUIFont* font;

};
#endif // SCENEMANAGER_HPP
