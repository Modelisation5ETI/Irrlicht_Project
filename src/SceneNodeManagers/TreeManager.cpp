#include "TreeManager.hpp"

//*****************************************************************************
// Load
//*****************************************************************************
void TreeManager::Load( irr::IrrlichtDevice* device )
{
  //Get information from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();
  irr::video::IVideoDriver* driver = device->getVideoDriver();

  // Load textures
  for ( irr::s32 i = 0; i < NUM_TREE_DESIGNS; i++ )
    {
    treeDesigns[i].Generator = new irr::scene::CTreeGenerator( sceneManager );
    // Read xml design
    irr::io::IXMLReader* xml = device->getFileSystem()->createXMLReader(
      PathFinder::GetFullMediaPath(treeDesignFiles[i].DesignFile) );
    if (xml)
      {
      treeDesigns[i].Generator->loadFromXML( xml );
      xml->drop();
      }

    treeDesigns[i].TreeTexture = driver->getTexture( PathFinder::GetFullMediaPath(treeDesignFiles[i].TreeTextureFile) );
    treeDesigns[i].LeafTexture = driver->getTexture( PathFinder::GetFullMediaPath(treeDesignFiles[i].LeafTextureFile) );
    treeDesigns[i].BillTexture = driver->getTexture( PathFinder::GetFullMediaPath(treeDesignFiles[i].BillTextureFile) );
    }

  // Load leaf shader
  leafMaterialType = (irr::video::E_MATERIAL_TYPE) driver->getGPUProgrammingServices()->addHighLevelShaderMaterialFromFiles(
    PathFinder::GetFullShaderPath( "leaves.vert" ),
    "main",
    irr::video::EVST_VS_2_0,
    PathFinder::GetFullShaderPath( "leaves.frag" ),
    "main",
    irr::video::EPST_PS_2_0,
    0,
    irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL,
    0 );

  // Indicates that material data have been loaded
  loaded = true;
}

//*****************************************************************************
// Add multiple Trees
//*****************************************************************************
void TreeManager::AddNodeGroupToScene( irr::IrrlichtDevice* device, irr::s32 id,
  unsigned int nbNodes )
{
  //WARNING: Hard cast here because we know that terrain has id 1
  irr::scene::ITerrainSceneNode* terrain =
    (irr::scene::ITerrainSceneNode*)(device->getSceneManager()->getSceneNodeFromId(1));

  if( !terrain )
    return;

  for( unsigned int i = 0; i < nbNodes; i++ )
    {
    //Generate pseudo-random position
    float x =rand()%int(terrain->getBoundingBox().getExtent().X - 100) + 100;
    float z =rand()%int(terrain->getBoundingBox().getExtent().Z - 100) + 100;
    float y = terrain->getHeight( x, z ) - 30;

    //Add Tree
    TreeManager::AddNodeToScene( device, id + i, irr::core::vector3df( x, y, z ) );

    //Change seed
    seed++;
    }
}

//*****************************************************************************
// Add Tree
//*****************************************************************************
void TreeManager::AddNodeToScene( irr::IrrlichtDevice* device,
  irr::s32 id, irr::core::vector3df position )
{
  //Load data if necessary
  if( !loaded )
    Load( device );

  //Get information from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();

  //Scene Node
  irr::scene::CTreeSceneNode* tree =
    new irr::scene::CTreeSceneNode( sceneManager->getRootSceneNode(),
      sceneManager, id, position );
  tree->drop();
  tree->setMaterialFlag( irr::video::EMF_LIGHTING, false );

  //Set Name
  tree->setName( "Tree" );

  //Generate
  tree->setup( treeDesigns[currentTreeDesign].Generator, seed, treeDesigns[currentTreeDesign].BillTexture );

  //Set Material
  tree->getLeafNode()->getMaterial(0).TextureLayer[0].AnisotropicFilter = true;
  tree->getLeafNode()->getMaterial(0).TextureLayer[0].BilinearFilter = false;

  tree->getLeafNode()->setMaterialTexture( 0, treeDesigns[currentTreeDesign].LeafTexture );
  tree->getLeafNode()->setMaterialType( irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF );

  tree->setMaterialTexture( 0, treeDesigns[currentTreeDesign].TreeTexture );

  if ( lightsEnabled )
    tree->getLeafNode()->applyVertexShadows( lightDir, 1.0f, 0.30f );

  tree->getLeafNode()->setMaterialType( leafMaterialType );

  //Set Triangle Selector
  tree->setTriangleSelector( sceneManager->createTriangleSelectorFromBoundingBox(tree) );

  //Store Data
  NodeGroupManager::nodes.push_back( tree );
  treeNodesHealth.push_back( 100 );
}

//*****************************************************************************
// Take Damage
//*****************************************************************************
void TreeManager::TakeDamage( irr::IrrlichtDevice* device, irr::s32 id, float damage )
{

  for( unsigned int i = 0; i < NodeGroupManager::nodes.size(); i++ )
    {
    if( NodeGroupManager::nodes[i]->getID() == id )
      {
      treeNodesHealth[i] -= damage;
      if( treeNodesHealth[i] <= 0 )
        {
        requestUpdate = true;

        device->getSceneManager()->addToDeletionQueue(NodeGroupManager::nodes[i]);
        NodeGroupManager::nodes[i]->removeAnimators();
        NodeGroupManager::nodes.erase(NodeGroupManager::nodes.begin()+i);
        treeNodesHealth.erase(treeNodesHealth.begin()+i);
        }
      }
    }
}
