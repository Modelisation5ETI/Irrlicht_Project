#pragma once

#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include "Project_Config.h"
#include "irrString.h"


// Path Finder
class PathFinder
{
  public:

    // Return full path to a file stored in the media folder
    static irr::core::stringc GetFullMediaPath( const char* filename );

    // Return full path to a file stored in the shader folder
    static irr::core::stringc GetFullShaderPath( const char* filename );

};

#endif // PATHFINDER_HPP

