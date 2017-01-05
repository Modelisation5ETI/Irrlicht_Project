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
#include "WaterTerrainManager.hpp"

#include "EnemyManager.hpp"

#include "CTreeSceneNode.h"

#include <vector>

// Number of  objects
const unsigned int NB_BOXES = 15;
const unsigned int NB_TREES = 15;
const unsigned int NB_ENEMIES = 1;
// Node IDs
enum NodeID { PLAYER, TERRAIN, CAMERA, WATER, BOX, TREE = BOX + NB_BOXES, ENEMY = TREE + NB_TREES, BULLET = ENEMY + NB_ENEMIES };

class SceneManager
{
  public:
    //! Constructor
    SceneManager()
    {}

  // Load scene
  void LoadScene( irr::IrrlichtDevice* device );

  // Update scene
  void UpdateScene( irr::IrrlichtDevice* device,
                    EventReceiver* eventReceiver );

  // Draw All
  void drawAll( irr::IrrlichtDevice* device );


  private:
    // Scene nodes
    PlayerManager playerManager;
    TerrainManager terrainManager;
    CameraManager cameraManager;
    BoxManager boxManager;
    TreeManager treeManager;
    BulletManager bulletManager;
    WaterTerrainManager waterTerrainManager;
    EnemyManager enemyManager;

    // Text font
    irr::gui::IGUIFont* font;
};
#endif // SCENEMANAGER_HPP
