#pragma once

#ifndef TREEMANAGER_HPP
#define TREEMANAGER_HPP

#include "NodeGroupManager.hpp"
#include "CTreeSceneNode.h"

// Tree design filenames
struct STreeDesignFiles
{
    const irr::c8* DesignFile;
    const irr::c8* TreeTextureFile;
    const irr::c8* LeafTextureFile;
    const irr::c8* BillTextureFile;
};

// Tree design : Composed of a tree generator and textures for Tree, Leaf and
//               Billboard.
struct STreeDesign
{
    irr::scene::CTreeGenerator* Generator;
    irr::video::ITexture* TreeTexture;
    irr::video::ITexture* LeafTexture;
    irr::video::ITexture* BillTexture;
};

// Number of different designs
const irr::s32 NUM_TREE_DESIGNS = 4;

class TreeManager : public NodeGroupManager<irr::scene::CTreeSceneNode>
{
  public:
    // Load data
    void Load( irr::IrrlichtDevice* device );

    // Add multiple Trees
    void AddNodeGroupToScene( irr::IrrlichtDevice* device, irr::s32 id,
      unsigned int nbNodes );

    // Add Tree
    void AddNodeToScene( irr::IrrlichtDevice* device, irr::s32 id,
      irr::core::vector3df position  );

    // Take Damage
    void TakeDamage( irr::IrrlichtDevice* device, irr::s32 id, float damage );
    //Nodes' Health Points
    std::vector<int> nodesHP;
    //Request update if a node is deleted
    bool requestUpdate = false;

  private:
    //Tree design files
    const STreeDesignFiles treeDesignFiles[NUM_TREE_DESIGNS] = {
      { "./trees/Oak.xml", "./textures/OakBark.png", "./textures/OakLeaf.png", "./textures/OakBillboard.png" },
      { "./trees/Aspen.xml", "./textures/AspenBark.png", "./textures/AspenLeaf.png", "./textures/AspenBillboard.png" },
      { "./trees/Pine.xml", "./textures/PineBark.png", "./textures/PineLeaf.png", "./textures/PineBillboard.png" },
      { "./trees/Willow.xml", "./textures/WillowBark.png", "./textures/WillowLeaf.png", "./textures/WillowBillboard.png" }
    };

    //Tree designs
    STreeDesign treeDesigns [NUM_TREE_DESIGNS];

    //Current design for tree creation
    irr::s32 currentTreeDesign = 0;
    //Seed for tree generation
    irr::s32 seed = 0;

    // Leaf Material Type. Loaded from Asger Feldthaus' custom shader in Load()
    irr::video::E_MATERIAL_TYPE leafMaterialType = irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL;
    //Light direction for shadowing
    irr::core::vector3df lightDir;
    //Enable shadowing
    bool lightsEnabled = true;


    // Indicates that data have been loaded
    bool loaded = false;

};

#endif // TREEMANAGER_HPP
