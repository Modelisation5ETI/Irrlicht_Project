#include <irrlicht.h>

#include "Project_Config.h"
#include "../include/EventReceiver.hpp"
#include "../include/SceneManager.hpp"

int main(void)
{
  //Event Receiver
  EventReceiver eventReceiver;

  // Device creation
  irr::IrrlichtDevice* device = irr::createDevice(
    irr::video::EDT_OPENGL, // API = OpenGL
    irr::core::dimension2d<irr::u32>( 800, 600 ), // Window Size 640x480p
    32, false, false, false, &eventReceiver ); // 32 bits/pixel, FullScreen, StencilBuffer, Vsync, Receiver

  // Create Video Driver
  irr::video::IVideoDriver* driver = device->getVideoDriver();

  // Set cursor position
  device->getCursorControl()->setPosition( 0.5f, 0.5f );
  //Set Cursor visibility
  device->getCursorControl()->setVisible( false );

  //Set font color ( A (transparency), R, G, B )
  irr::video::SColor color( 255, 255, 255, 255);

  // Scene Manager
  SceneManager sceneManager( driver, device->getSceneManager() );
  sceneManager.LoadScene();

  int lastFPS = -1;// FPS

  //Rendering loop
  while (device->run())
  {
    // Close window if the Escape key is pressed
    if(eventReceiver.IsKeyDown( irr::KEY_ESCAPE ))
    {
      device->closeDevice();
    }

    // Update scene
    sceneManager.UpdateScene( device, &eventReceiver );

    // Draw scene
    driver->beginScene( true, true, color );
    sceneManager.drawAll();
    driver->endScene ();

    // FPS
    int fps = driver->getFPS();
    if( lastFPS != fps )
      {
      irr::core::stringw str = L"Boom - Irrlicht Engine [";
      str += driver->getName();
      str += "] FPS:";
      str += fps;

      device->setWindowCaption(str.c_str());
      lastFPS = fps;
      }
  }
  device->drop (); //Free memory

  return EXIT_SUCCESS;
}
