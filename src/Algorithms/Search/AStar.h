#pragma once

#include <memory>
#include <vector>

namespace Algorithms { namespace Search
{
  class AStar;
  typedef std::shared_ptr<AStar> AStarPtr;

  class AStar
  {
  public:
    AStar();
    ~AStar();
  };
}}

