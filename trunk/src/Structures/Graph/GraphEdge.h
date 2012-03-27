#pragma once

#include <Totem\PropertyContainer.h>

#include <memory>

namespace Structures
{
  class GraphNode;
  typedef std::shared_ptr<GraphNode> GraphNodePtr;

  class GraphEdge;
  typedef std::shared_ptr<GraphEdge> GraphEdgePtr;

  class GraphEdge : public Totem::PropertyContainer<>
  {
  public:
    GraphEdge(const GraphNodePtr &from, const GraphNodePtr &to, unsigned int cost = 0);
    ~GraphEdge();

    const GraphNodePtr &getFrom() const { return from; }
    const GraphNodePtr &getTo() const { return to; }
    unsigned int getCost() const { return cost; }

  public:
    GraphNodePtr from;
    GraphNodePtr to;
    unsigned int cost;
  };
}
