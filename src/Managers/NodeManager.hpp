#pragma once

#ifndef NODEMANAGER_HPP
#define NODEMANAGER_HPP

#include <irrlicht.h>
#include "PathFinder.hpp"

#include <iostream>

template <typename NodeType>
class NodeManager
{
  public:

  // Add node to scene
  virtual void AddNodeToScene( irr::IrrlichtDevice* device,
    irr::s32 id, irr::core::vector3df position ) = 0;

  // GetNode
  NodeType* GetNode();


  protected:

  // SceneNode
  NodeType* node;
};

#endif // NODEMANAGER_HPP
