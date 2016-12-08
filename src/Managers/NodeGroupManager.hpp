#pragma once

#ifndef NODEGROUPMANAGER_HPP
#define NODEGROUPMANAGER_HPP

#include <irrlicht.h>
#include "PathFinder.hpp"

#include <vector>
#include <iostream>

template <typename NodeType>
class NodeGroupManager
{
  public:
  // Add multiple node to scene
  virtual void AddNodeGroupToScene( irr::IrrlichtDevice* device,
    irr::s32 id, unsigned int nbNodes ) = 0;

  // Add node to scene
  virtual void AddNodeToScene( irr::IrrlichtDevice* device,
    irr::s32 id, irr::core::vector3df position ) = 0;


  // SceneNode
  std::vector<NodeType*> nodes;
};

#endif // NODEGROUPMANAGER_HPP
