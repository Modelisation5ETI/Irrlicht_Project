#include "ShootableNodeGroupManager.hpp"
#include "CTreeSceneNode.h"

//*****************************************************************************
// Take Damage
//*****************************************************************************
template <typename NodeType>
void ShootableNodeGroupManager<NodeType>::TakeDamage( irr::IrrlichtDevice* device, irr::s32 id, float damage )
{
  //Find node
  for( unsigned int i = 0; i < NodeGroupManager<NodeType>::nodes.size(); i++ )
    {
    if( NodeGroupManager<NodeType>::nodes[i]->getID() == id )
      {
       DammageParticles( device, i );

      //Take damage
      nodesHP[i] -= damage;
      //Check for node life
      if( nodesHP[i] <= 0 )
        {
        //Set Flag to update collision setup in SceneManager
        requestUpdate = true;
        //Die
        Die( device, i );
        nodesHP.erase( nodesHP.begin() + i );
        }
      }

    }
}

//*****************************************************************************
// Die : Behavior to adopt if HP < 0
//*****************************************************************************
template <typename NodeType>
void ShootableNodeGroupManager<NodeType>::Die( irr::IrrlichtDevice* device, unsigned int i )
{
  //Get information from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();

  //Compute billboard position
  irr::scene::ISceneNode* node = NodeGroupManager<NodeType>::nodes[i];
  irr::core::vector3df position( node->getPosition() +
    irr::core::vector3df( 0, (node->getBoundingBox().getExtent().Y)/2.0f, 0 ) );

  //Draw score using BillboardTextNode
  irr::core::stringw text = irr::core::stringw( score );
  irr::video::SColor colorTop( 255, 255, 255, 0 );//Yellow
  irr::video::SColor colorBottom( 255, 255, 0, 0 );//Red
  irr::gui::IGUIFont* font = device->getGUIEnvironment()->getFont(
    PathFinder::GetFullMediaPath( "bigfont.png" ) );
  irr::scene::IBillboardTextSceneNode* scoreBillboard =
    sceneManager->addBillboardTextSceneNode(
      font, text.c_str(), 0, irr::core::dimension2df(30,20), position, -1,
      colorTop, colorBottom );
  scoreContribution += score;

  //Fly Animator
  irr::scene::ISceneNodeAnimator* flyAnimator = sceneManager->createFlyStraightAnimator(
    position, position + irr::core::vector3df(0,60,0), 750 );
  scoreBillboard->addAnimator( flyAnimator );
  flyAnimator->drop();

  //Delete Animator
  irr::scene::ISceneNodeAnimator* deleteAnimator = sceneManager->createDeleteAnimator( 1000 );
  scoreBillboard->addAnimator( deleteAnimator );
  deleteAnimator->drop();

  //Delete node
  sceneManager->addToDeletionQueue( NodeGroupManager<NodeType>::nodes[i] );
  NodeGroupManager<NodeType>::nodes[i]->removeAnimators();
  NodeGroupManager<NodeType>::nodes.erase( NodeGroupManager<NodeType>::nodes.begin() + i );

  return;
}

template <typename NodeType>
void ShootableNodeGroupManager<NodeType>::DammageParticles( irr::IrrlichtDevice* device, unsigned int i )
{

  //Get information from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();
  irr::video::IVideoDriver* driver = device->getVideoDriver();

  irr::scene::IParticleSystemSceneNode* ps =
      sceneManager->addParticleSystemSceneNode(false);

  //Compute particles position
  irr::scene::ISceneNode* node = NodeGroupManager<NodeType>::nodes[i];
  irr::core::vector3df position( node->getPosition() +
    irr::core::vector3df( 0, (node->getBoundingBox().getExtent().Y)/2.0f, 0 ) );

  //Compute particles position
 // TO DO : en fonction des ID (box, tree, etc)
  irr::scene::IParticleEmitter* em = ps->createBoxEmitter(
      irr::core::aabbox3d<irr::f32>(-3,0,-3,3,1,3), // emitter size
      irr::core::vector3df(0.0f,0.06f,0.0f),   // initial direction
      80,1000,                             // emit rate
      irr::video::SColor(0,255,255,255),       // darkest color
      irr::video::SColor(0,255,255,255),       // brightest color=
      600,3000,0,                         // min and max age, angle //heigh
      irr::core::dimension2df(10.f,10.f),         // min size
      irr::core::dimension2df(20.f,20.f));        // max size

  irr::scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();
  ps->addAffector(paf); // same goes for the affector
  paf->drop();

        ps->setPosition(irr::core::vector3df(position));
        ps->setScale(irr::core::vector3df(2,2,2));
        ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
        ps->setMaterialTexture(0, driver->getTexture(PathFinder::GetFullMediaPath("fire.bmp")));
        ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
        ps->setEmitter(em); // this grabs the emitter

        em->setMaxAngleDegrees(100-nodesHP[i]);
        em->drop(); // so we can drop it here without deleting it

  if( nodesHP[i] < 60 )
  {
        //TO DO : delete particles when node kill

//      //Delete Animator
//      irr::scene::ISceneNodeAnimator* deleteAnimator = sceneManager->createDeleteAnimator( 100 );
//      ps->addAnimator( deleteAnimator );
//      deleteAnimator->drop();

//      ps->clearParticles();
//      ps->setEmitter(0);
  }
  return;
}


template class ShootableNodeGroupManager<irr::scene::IMeshSceneNode>;
template class ShootableNodeGroupManager<irr::scene::IBillboardSceneNode>;
template class ShootableNodeGroupManager<irr::scene::ISceneNode>;
template class ShootableNodeGroupManager<irr::scene::CTreeSceneNode>;
