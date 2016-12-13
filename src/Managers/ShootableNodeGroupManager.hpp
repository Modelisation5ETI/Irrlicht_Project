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

  // Particles when dammage
  virtual void DammageParticles( irr::IrrlichtDevice* device, unsigned int i );


  //Request update if a node is deleted
  bool requestUpdate = false;

  //Total score contribution accumulated
  int scoreContribution = 0;

protected:
  //Nodes' Health Points
  std::vector<int> nodesHP;

  //Score contribution
  int score = 100;

};

#endif // SHOOTABLENODEGROUP_HPP
