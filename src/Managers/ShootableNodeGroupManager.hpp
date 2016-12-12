#pragma once

#ifndef SHOOTABLENODEGROUP_HPP
#define SHOOTABLENODEGROUP_HPP

#include "NodeGroupManager.hpp"

template <typename NodeType>
class ShootableNodeGroupManager : public NodeGroupManager<NodeType>
{
public:
  //Take Damage
  void TakeDamage( irr::IrrlichtDevice* device, irr::s32 id, float damage );
  
  //Die : Behavior to adopt if HP < 0
  virtual void Die( irr::IrrlichtDevice* device, unsigned int i );

  //Request update if a node is deleted
  bool requestUpdate = false;

protected:
  //Nodes' Health Points
  std::vector<int> nodesHP;

  //Score Billboard Texture
  irr::video::ITexture* scoreBillboard = 0;

};

#endif // SHOOTABLENODEGROUP_HPP