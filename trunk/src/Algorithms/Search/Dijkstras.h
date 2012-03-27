#pragma once

#include <memory>
#include <vector>

namespace Algorithms { namespace Search
{
  class Dijkstras;
  typedef std::shared_ptr<Dijkstras> DijkstrasPtr;

  class Dijkstras
  {
  public:
    Dijkstras();
    ~Dijkstras();
  };
}}

