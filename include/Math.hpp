#pragma once

#ifndef MATH_HPP
#define MATH_HPP

class Math
{
  public:
    //Clamp a value in range [lowValue,hightValue]
    static void Clamp( float* param, float lowValue, float hightValue );

    //Clamp an angle value in range [-180,180]
    static void ClampAsAngle( float* angle );

};

#endif // MATH_HPP
