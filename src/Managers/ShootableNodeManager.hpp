#pragma once

#ifndef SHOOTABLENODEMANAGER_HPP
#define SHOOTABLENODEMANAGER_HPP

#include "NodeManager.hpp"

template <typename NodeType>
class ShootableNodeManager : public NodeManager<NodeType>
{
public:
  //Take Damage
  void TakeDamage( irr::IrrlichtDevice* device, float damage );
  
  //Die : Behavior to adopt if HP < 0
  virtual void Die( irr::IrrlichtDevice* device );

  //Request update if a node is deleted
  bool requestUpdate = false;

protected:
  //Node's Health Points
  int HP = 100;

  //Score contribution
  int score = 100;

};

#endif // SHOOTABLENODEMANAGER_HPP
