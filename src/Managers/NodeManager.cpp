#include "NodeManager.hpp"

//*****************************************************************************
// GetNode
//*****************************************************************************
template <typename NodeType>
NodeType* NodeManager<NodeType>::GetNode()
{
  return node;
}

template class NodeManager<irr::scene::IAnimatedMeshSceneNode>;
template class NodeManager<irr::scene::ITerrainSceneNode>;
