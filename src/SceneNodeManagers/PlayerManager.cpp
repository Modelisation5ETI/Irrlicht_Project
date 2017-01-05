#include "PlayerManager.hpp"

//*****************************************************************************
// Add node to scene
//*****************************************************************************
void PlayerManager::AddNodeToScene( irr::IrrlichtDevice* device,
  irr::s32 id, irr::core::vector3df position )
{
  // Get information from device
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();
  irr::video::IVideoDriver* driver = device->getVideoDriver();

  //Add mesh
  irr::scene::IAnimatedMesh* mesh = sceneManager->getMesh(
    PathFinder::GetFullMediaPath( "Marvin.md2" ) );
  NodeManager::node = sceneManager->addAnimatedMeshSceneNode( mesh, 0, id );

  //Set Name
  NodeManager::node->setName("Player");

  //Material
  NodeManager::node->setMaterialFlag( irr::video::EMF_LIGHTING, false );
  NodeManager::node->setMaterialTexture( 0,
    driver->getTexture( PathFinder::GetFullMediaPath( "Marvin.jpg" ) ) );

  //Animation and transform
  NodeManager::node->setMD2Animation( irr::scene::EMAT_STAND );
  NodeManager::node->setPosition( position );

  //Set Triangle Selector
  NodeManager::node->setTriangleSelector( sceneManager->createTriangleSelector( NodeManager::node ) );

  // DEBUG
//  NodeManager::node ->setDebugDataVisible(irr::scene::EDS_BBOX );
}

//*****************************************************************************
// Collision Callback
//*****************************************************************************
bool PlayerManager::onCollision( const irr::scene::ISceneNodeAnimatorCollisionResponse& animator )
{
  irr::scene::ISceneNode* collisionNode = animator.getCollisionNode();
  irr::core::string<irr::c8> nodeName = collisionNode->getName();

  // Collision with a box
  if( nodeName == irr::core::string<irr::c8>("Box") )
    {
    std::cout<<NodeManager::node->getName()<<" collision with Box "
      <<collisionNode->getID()<<std::endl;

    irr::core::vector3df direction = collisionNode->getPosition() - NodeManager::node->getPosition();
    collisionNode->setPosition( collisionNode->getPosition() + direction.normalize() );
    }

    return false;
}

//*****************************************************************************
// Update
//*****************************************************************************
void PlayerManager::Update( EventReceiver* eventReceiver )
{
  updateTransform( eventReceiver );
  updateAnimation( eventReceiver );
}

//*****************************************************************************
// Die : Behavior to adopt if HP < 0
//*****************************************************************************
void PlayerManager::Die( irr::IrrlichtDevice* device )
{
  //Die Animation
  NodeManager::node->setLoopMode( false );
  NodeManager::node->setMD2Animation(irr::scene::EMAT_DEATH_FALLBACK);

  //GAME OVER
  GameOver = true;
}

//*****************************************************************************
// Update Transform
//*****************************************************************************
void PlayerManager::updateTransform( EventReceiver* eventReceiver )
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
    y_Rotation += rotation_dt;
    speed = turnSpeed;
    }
  if( eventReceiver->IsKeyDown( KEY_LEFT ) )  // Turn left
    {
    y_Rotation -= rotation_dt;
    speed = turnSpeed;
    }
  if( animationType == irr::scene::EMAT_ATTACK  ) // Attack
    {
    speed = 0.0f;
    }

  Math::ClampAsAngle( &y_Rotation );

  //Calculates mesh position
  forward = irr::core::vector3df(
    sin( ( NodeManager::node->getRotation().Y + 90.0f ) * irr::core::PI/180.0f ),
    0,
    cos( ( NodeManager::node->getRotation().Y + 90.0f ) * irr::core::PI/180.0f ) );

  irr::core::vector3df newPos = forward.normalize() * speed + NodeManager::node->getPosition();

//  // Apply gravity manually
//  newPos.Y -= 5;

//  // Handle collision with terrain manually
//  float terrainHeight = terrainNode->getHeight(newPos.X,newPos.Z);
//  if( newPos.Y < terrainHeight + 24.44)
//    {
//    newPos.Y=terrainHeight + 24.44 ;
//    }

  //Update Mesh
  NodeManager::node->setPosition( newPos );
  NodeManager::node->setRotation( irr::core::vector3df( 0, y_Rotation + 180.0f, 0 ) );
}

//*****************************************************************************
// Update animation
//*****************************************************************************
void PlayerManager::updateAnimation( EventReceiver* eventReceiver )
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
    if( eventReceiver->IsKeyDown( KEY_JUMP ) /*&& !eventReceiver->IsKeyDown( KEY_ATTACK )*/ )
      {
      // WARNING : Hard cast because we know the first animator is a Collision animator
      irr::scene::ISceneNodeAnimatorCollisionResponse* animator =
        (irr::scene::ISceneNodeAnimatorCollisionResponse*) *(node->getAnimators().begin());
      if( !animator->isFalling() )
        {
        NodeManager::node->setLoopMode( false );
        animationType = irr::scene::EMAT_JUMP ;
        animationSwitch = true;
        NodeManager::node->setAnimationEndCallback( &jumpEndReceiver );
        animator->jump(4);
        }
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
    if(eventReceiver->IsKeyDown( KEY_ATTACK) /*&& !eventReceiver->IsKeyDown( KEY_JUMP )*/)
      {
      NodeManager::node->setLoopMode( false );
      animationType = irr::scene::EMAT_ATTACK ;
      animationSwitch = true;
      NodeManager::node->setAnimationEndCallback( &attackEndReceiver );

      requestShoot = true;
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
    NodeManager::node->setMD2Animation(animationType);
    animationSwitch =false;
    }
}

//*****************************************************************************
// Return rotation value around Y axis
//*****************************************************************************
float PlayerManager::Get_Y_Rotation()
{
  return y_Rotation;
}
