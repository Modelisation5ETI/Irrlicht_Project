#include "EventReceiver.hpp"

//*****************************************************************************
// OnEvent()
//*****************************************************************************
bool EventReceiver::OnEvent( const irr::SEvent& event )
{
  // Remember whether each key is down or up
  if ( event.EventType == irr::EET_KEY_INPUT_EVENT )
    {
    KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }

  return false;
}

//*****************************************************************************
// This is used to check whether a key is being held down
//*****************************************************************************
bool EventReceiver::IsKeyDown( irr::EKEY_CODE keyCode ) const
{
  return KeyIsDown[keyCode];
}

//*****************************************************************************
// Indicates if any arrow key is down
//*****************************************************************************
bool EventReceiver::IsArrowDown()
{
  return( KeyIsDown[irr::KEY_KEY_Z] ||
    KeyIsDown[irr::KEY_KEY_S] ||
    KeyIsDown[irr::KEY_KEY_Q] ||
    KeyIsDown[irr::KEY_KEY_D] );
}

//*****************************************************************************
// Return number of key down
//*****************************************************************************
int EventReceiver::numberOfKeysDown()
{
  int count = 0;
  for ( irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i )
    {
    if( KeyIsDown[i] )
      {
      ++count;
      }
    }
  return( count );
}
