# include "PathFinder.hpp"

//*****************************************************************************
// Return full path to a file stored in the media folder
//*****************************************************************************
irr::core::stringc PathFinder::GetFullMediaPath( const char* filename )
{
  irr::core::stringc media_DIR = MEDIA_DIR;
  return media_DIR + filename;
}

//*****************************************************************************
// Return full path to a file stored in the shader folder
//*****************************************************************************
irr::core::stringc PathFinder::GetFullShaderPath( const char* filename )
{
  irr::core::stringc shader_DIR = SHADER_DIR;
  return shader_DIR + filename;
}

