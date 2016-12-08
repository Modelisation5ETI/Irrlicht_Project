#pragma once

#ifndef EVENTRECEIVER_H
#define EVENTRECEIVER_H

#include <irrlicht.h>

// Define controls
#define KEY_UP irr::KEY_KEY_Z
#define KEY_DOWN irr::KEY_KEY_S
#define KEY_LEFT irr::KEY_KEY_Q
#define KEY_RIGHT irr::KEY_KEY_D
#define KEY_JUMP irr::KEY_KEY_K
#define KEY_ATTACK irr::KEY_SPACE

class EventReceiver : public irr::IEventReceiver
{
  public:
    EventReceiver()
    {
      for ( irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i )
        {
        KeyIsDown[i] = false;
        KeyIsPressed[i] = false;
        }
    }

    // OnEvent
    virtual bool OnEvent(const irr::SEvent& event);

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown( irr::EKEY_CODE keyCode ) const;

    // Indicates if any arrow key is down
    bool IsArrowDown();

    // Return number of key down
    int numberOfKeysDown();

  private:
    // We use this array to store the current state of each key
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    // Check if keys are pressed
    bool KeyIsPressed[irr::KEY_KEY_CODES_COUNT];

};

#endif // EVENTRECEIVER_H
