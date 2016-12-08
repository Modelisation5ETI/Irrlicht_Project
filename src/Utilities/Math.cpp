#include "Math.hpp"

//*****************************************************************************
// Clamp a value in range [lowValue,hightValue]
//*****************************************************************************
void Math::Clamp( float* param, float lowValue, float hightValue )
{
  if( *param > hightValue )
    {
    *param = hightValue;
    }
  if( *param < lowValue )
    {
    *param = lowValue;
    }
}

//*****************************************************************************
// Clamp an angle value in range [-180,180]
//*****************************************************************************
void Math::ClampAsAngle( float* angle )
{
if( *angle > 180.f )
  {
  *angle -= 360.0f;
  }
if( *angle <- 180.f )
  {
  *angle += 360.0f;
  }
}
