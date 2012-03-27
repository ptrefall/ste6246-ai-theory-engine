#pragma once

#include "ISearch.h"

#include <memory>
#include <vector>

namespace Algorithms { namespace Search
{
  class Dijkstras;
  typedef std::shared_ptr<Dijkstras> DijkstrasPtr;

  class Dijkstras //: public ISearch
  {
  public:
    Dijkstras();
    ~Dijkstras();
  };
}}

