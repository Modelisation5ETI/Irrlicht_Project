#include "CameraManager.hpp"

//*****************************************************************************
// Add 3er person camera
//*****************************************************************************
void CameraManager::add3rdPersonCameraToScene( irr::scene::ISceneManager* sceneManager, irr::s32 id )
{
  cameraNode = sceneManager->addCameraSceneNode( 0, //Parent Node
    irr::core::vector3df( 0.0f, 0.0f, 0.0f ),       //CamDOWNera position
    irr::core::vector3df( 0.0f, 0.0f, 0.0f ),       //Camera orientation
    id,                                         //Camera Id
    true );                                         //Set Active
  cameraNode->setFarValue( FarValue );

  // Handle Collision
  metaTriangleSelector = sceneManager->createMetaTriangleSelector();
}

//*****************************************************************************
// Add FPS camera
//*****************************************************************************
void CameraManager::addFPSCameraToScene( irr::scene::ISceneManager* sceneManager )
{
  cameraNode = sceneManager->addCameraSceneNodeFPS( 0, 100.0f, 1.2f );
  cameraNode->setPosition(irr::core::vector3df(2700*2,255*2,2600*2));
  cameraNode->setTarget(irr::core::vector3df(2397*2,343*2,2700*2));
  cameraNode->setFarValue( FarValue );
}

//*****************************************************************************
// Add Static camera
//*****************************************************************************
void CameraManager::addStaticCameraToScene( irr::scene::ISceneManager* sceneManager )
{
  cameraNode = sceneManager->addCameraSceneNode( 0, //Parent Node
    irr::core::vector3df( 40.0f, 10.0f, 15.0f ),    //Camera position
    irr::core::vector3df( 0.0f, 9.0f, 15.0f ) );    //Camera orientation
  cameraNode->setFarValue( FarValue );
}

//*****************************************************************************
// Timer tick
//*****************************************************************************
void CameraManager::timerTick( irr::IrrlichtDevice* device )
{
  float TIMER_SPEED = 5e-5f;
  float deltaTime = device->getTimer()->getTime() - time;
  timer += deltaTime * TIMER_SPEED;
}

//*****************************************************************************
// Add scene node collision
//*****************************************************************************
void CameraManager::addSceneNodeCollision( irr::scene::ISceneManager* sceneManager, irr::scene::ISceneNode* sceneNode )
{
  //Add triangle selector to the collection
  irr::scene::ITriangleSelector* selector = sceneNode->getTriangleSelector();
  if(!selector)
    {
    std::cout<<"No animator was found"<<std::endl;
    return;
    }

  // Handle collision with the scene node parameter
  metaTriangleSelector->addTriangleSelector(selector);
  // Create collision response animator and attach it to the scene node
  irr::scene::ISceneNodeAnimatorCollisionResponse* animator = sceneManager->createCollisionResponseAnimator(
    metaTriangleSelector, cameraNode,
    irr::core::vector3df( 10, 10, 10 ),//Ellipsoid Radius
    irr::core::vector3df( 0, 0, 0 ),//Gravity per second
    irr::core::vector3df( 0, 0, 0) );  //Ellipsoid Translation (Offset)
  selector->drop();
  cameraNode->addAnimator( animator );
  animator->drop();
}

//*****************************************************************************
// Update camera according to the 3rd person character
//*****************************************************************************
void CameraManager::Update( irr::IrrlichtDevice* device,
  EventReceiver* eventReceiver, PlayerManager playerManager )
{
  //Get cursor mouvement
  irr::core::position2d<irr::f32> cursorPos =
    device->getCursorControl()->getRelativePosition();

  float cursorSensibility = 256.0f;
  float dx = ( cursorPos.X - 0.5 ) * cursorSensibility;
  float dy = ( cursorPos.Y - 0.5 ) * cursorSensibility;

  //Update Rotation
  y_Rotation += dx;
  x_Rotation += dy;

  Math::Clamp( &x_Rotation, -90, 10 );
  Math::ClampAsAngle( &y_Rotation );

  //Reset Cursor position
  device->getCursorControl()->setPosition( 0.5f, 0.5f );

  //Set Camera orientation to the 3rd person orientation
  if( checkOrientation( device, eventReceiver->IsArrowDown(), dx, dy, playerManager.Get_Y_Rotation() ) )
    {
    replaceCameraToMesh( playerManager.Get_Y_Rotation() );
    }

  //3rd person position
  irr::scene::IAnimatedMeshSceneNode* playerNode = playerManager.GetNode();
  irr::core::vector3df playerPosition = playerNode->getPosition();
  //Camera Zoom
  float Zoom = 70.0f;

  //Camera Position and Orientation
  irr::core::vector3df cameraPos = playerPosition + irr::core::vector3df( Zoom, Zoom, 0 );
  cameraPos.rotateXYBy( x_Rotation, playerPosition );
  cameraPos.rotateXZBy( -y_Rotation, playerPosition );

  //Update
  cameraNode->setPosition( cameraPos );
  cameraNode->setTarget( playerPosition );
}

//*****************************************************************************
// Set camera orientation to mesh orientation
//*****************************************************************************
void CameraManager::replaceCameraToMesh( float y_MeshRotation )
{
  if( abs(y_MeshRotation-y_Rotation) >= 1.0f || abs( x_Rotation - 25.0f ) >= 1.0f )
    {
    //Determine delta rotation to perform
    //**WARNING: Could be improve by doing calculation only on first pass
    // No need to recalculate angle at every frame for interpolation**
    float yOmega = y_MeshRotation - y_Rotation;
    Math::ClampAsAngle( &yOmega );

    float xOmega = -25.0f - x_Rotation;
    Math::ClampAsAngle( &xOmega );

    //Interpolate rotation between mesh and camera
    irr::core::vector3df d_Rotation(xOmega,yOmega, 0);
    irr::core::vector3df currentRotation;
    currentRotation.interpolate(irr::core::vector3df(0.0f,0.0f,0.0f),d_Rotation,d_Interpolate);

    //Rotate camera to mesh
    x_Rotation += currentRotation.X;
    y_Rotation +=currentRotation.Y;

    //Update interpolation step
    d_Interpolate -= 0.5e-4f;
    }
  else
    {
    //Reset interpolation parameters
    d_Interpolate = 1.0f;
    setCameraToMeshOrientation = false;
    }
}

//*****************************************************************************
// Check orientation condition to replace camera to mesh orientation
//*****************************************************************************
bool CameraManager::checkOrientation( irr::IrrlichtDevice* device,
  bool arrowDown, float dx, float dy, float y_MeshRotation )
{
  // Check Mesh-Camera angle when Mesh is moving and camera is not moved
  // with cursor or already moving
  if( abs(y_MeshRotation-y_Rotation) >= 50.0f &&
      !setCameraToMeshOrientation &&
      arrowDown &&
      !moveCameraCursor )
    {
    setCameraToMeshOrientation = true;
    }

  // Check if cursor has moved
  if( dx > 0 || dy > 0 )
    {
    setCameraToMeshOrientation = false;
    moveCameraCursor = true;
    //Reset timer
    timer = 0.0f;
    time = device->getTimer()->getTime();
    }

  // Reset camera orientation after a certain time if it has been moved
  // with cursor
  if( moveCameraCursor )
    {
    timerTick( device );
    if( timer > 2.0f )
      {
      // The camera has to be replaced
      setCameraToMeshOrientation =true;
      moveCameraCursor = false;
      timer = 0.0f;
      }
    }

  return setCameraToMeshOrientation;
}
