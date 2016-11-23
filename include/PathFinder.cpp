# include "PathFinder.hpp"

//*****************************************************************************
// Return full path to the file stored in media file
//*****************************************************************************
irr::core::stringc PathFinder::GetFullMediaPath( const char* filename )
{
  irr::core::stringc media_DIR = MEDIA_DIR;
  return media_DIR + filename;
}
