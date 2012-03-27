#pragma once

#include "ISearch.h"

#include <memory>
#include <vector>

namespace Algorithms { namespace Search
{
  class AStar;
  typedef std::shared_ptr<AStar> AStarPtr;

  class AStar //: public ISearch
  {
  public:
    AStar();
    ~AStar();
  };
}}

