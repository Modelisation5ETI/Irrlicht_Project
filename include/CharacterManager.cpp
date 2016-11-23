#include "CharacterManager.hpp"

//*****************************************************************************
// Add Character To Scene
//*****************************************************************************
void CharacterManager::addCharacterToScene( irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver )
{
  //Add mesh
  irr::scene::IAnimatedMesh* meshCharacter = sceneManager->getMesh(
    PathFinder::GetFullMediaPath( "Marvin.md2" ) );
  characterNode = sceneManager->addAnimatedMeshSceneNode( meshCharacter );

  characterNode->setMaterialFlag( irr::video::EMF_LIGHTING, false );
  characterNode->setMaterialTexture( 0,
    driver->getTexture( PathFinder::GetFullMediaPath( "Marvin.jpg" ) ) );
  characterNode->setMD2Animation( irr::scene::EMAT_STAND );
  characterNode->setPosition( irr::core::vector3df( 1000, 570, 1000 ) );

  metaTriangleSelector = sceneManager->createMetaTriangleSelector();
  characterNode->setTriangleSelector( sceneManager->createTriangleSelector( characterNode ) );


//  // DEBUG
//  characterNode ->setDebugDataVisible(irr::scene::EDS_BBOX );
}

//*****************************************************************************
// Update character
//*****************************************************************************
void CharacterManager::Update(EventReceiver *eventReceiver, irr::scene::ITerrainSceneNode *terrainNode)
{
  updateTransform( eventReceiver,terrainNode );
  updateAnimation( eventReceiver );
}

//*****************************************************************************
// Update Transform
//*****************************************************************************
void CharacterManager::updateTransform( EventReceiver* eventReceiver, irr::scene::ITerrainSceneNode* terrainNode )
{
  //Mesh Speed
  float speed = 0.0f;
  float forwardSpeed = 4.0f;
  float turnSpeed = 3.0f;
  float rotation_dt = 3.0f;

  //KeyBoard Mesh action
  if( eventReceiver->IsKeyDown( KEY_DOWN) ) // Run backward
    {
    speed = -forwardSpeed;
    }
  if( eventReceiver->IsKeyDown( KEY_UP ) ) // Run forward
    {
    speed = forwardSpeed;
    }
  if( eventReceiver->IsKeyDown( KEY_RIGHT ) ) //Turn right
    {
    y_MeshRotation += rotation_dt;
    speed = turnSpeed;
    }
  if( eventReceiver->IsKeyDown( KEY_LEFT ) )  // Turn left
    {
    y_MeshRotation -= rotation_dt;
    speed = turnSpeed;
    }
  if( animationType == irr::scene::EMAT_ATTACK  ) // Attack
    {
    speed = 0.0f;
    }

  Math::ClampAsAngle( &y_MeshRotation );

  //Calculates mesh position
  irr::core::vector3df meshForward(
    sin( ( characterNode->getRotation().Y + 90.0f ) * irr::core::PI/180.0f ),
    0,
    cos( ( characterNode->getRotation().Y + 90.0f ) * irr::core::PI/180.0f ) );

  irr::core::vector3df newPos = meshForward.normalize() * speed + characterNode->getPosition();

  // Apply gravity manually
  newPos.Y -= 5;

  // Handle collision with terrain manually
  float terrainHeight = terrainNode->getHeight(newPos.X,newPos.Z);
  if( newPos.Y < terrainHeight + 24.44)
    {
    newPos.Y=terrainHeight + 24.44 ;
    }

  //Update Mesh
  characterNode->setPosition( newPos );
  characterNode->setRotation( irr::core::vector3df( 0, y_MeshRotation + 180.0f, 0 ) );
}

//*****************************************************************************
// Update 3rd person animation
//*****************************************************************************
void CharacterManager::updateAnimation( EventReceiver* eventReceiver )
{
  //Set standing or running
  if( animationType != irr::scene::EMAT_ATTACK && //Prevent from running if animation is not over
      animationType != irr::scene::EMAT_JUMP  )
    {
    if( eventReceiver->IsKeyDown( KEY_UP ) ||     //Run
        eventReceiver->IsKeyDown( KEY_DOWN ) ||
        eventReceiver->IsKeyDown( KEY_LEFT ) ||
        eventReceiver->IsKeyDown( KEY_RIGHT ) )
      {
      if( animationType != irr::scene::EMAT_RUN )
       {
       animationType = irr::scene::EMAT_RUN;
       animationSwitch = true;
       }
     else
       {
       animationSwitch = false;
       }
     }
   else                                           //Stand
     {
     if(animationType != irr::scene::EMAT_STAND)
       {
       animationType = irr::scene::EMAT_STAND;
       animationSwitch = true;
       }
     else
       {
       animationSwitch = false;
       }
     }
   }

  // Handle Jump
  if( animationType != irr::scene::EMAT_JUMP )
    {
    if( eventReceiver->IsKeyDown( KEY_JUMP) )
      {
      characterNode->setLoopMode( false );
      animationType = irr::scene::EMAT_JUMP ;
      animationSwitch = true;characterNode->setAnimationEndCallback( &jumpEndReceiver );
      }
    }
  else
    {
    if( jumpEndReceiver.animationEnd )
      {
      animationSwitch = true;
      animationType = irr::scene::EMAT_STAND;
      jumpEndReceiver.animationEnd = false;
      }
    else
      {
      animationSwitch = false;
      }
    }

  // Handle attack
  if( animationType != irr::scene::EMAT_ATTACK )
    {
    if(eventReceiver->IsKeyDown( KEY_ATTACK))
      {
      characterNode->setLoopMode( false );
      animationType = irr::scene::EMAT_ATTACK ;
      animationSwitch = true;characterNode->setAnimationEndCallback( &attackEndReceiver );
      }
    }
  else
    {
    if( attackEndReceiver.animationEnd )
      {
      animationSwitch =true;
      animationType = irr::scene::EMAT_STAND;
      attackEndReceiver.animationEnd=false;
      }
    else
      {
      animationSwitch = false;
      }
    }

  //Switch animation
  if(animationSwitch)
    {
    characterNode->setMD2Animation(animationType);
    animationSwitch =false;
    }
}
