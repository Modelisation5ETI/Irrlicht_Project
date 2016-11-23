#pragma once

#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include "Project_Config.h"
#include "irrString.h"

class PathFinder
{
  public:

    // Return full path to the file stored in media file
    static irr::core::stringc GetFullMediaPath( const char* filename );

};

#endif // PATHFINDER_HPP

