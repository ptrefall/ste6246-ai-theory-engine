#pragma once

#include <memory>
#include <vector>

namespace Structures
{
  class GraphNode;
  typedef std::shared_ptr<GraphNode> GraphNodePtr;

  class Graph;
  typedef std::shared_ptr<Graph> GraphPtr;

  class Graph
  {
  public:
    Graph();
    ~Graph();

  public:
    void clearVisited();

  public:
    const GraphNodePtr &addNode(const GraphNodePtr &node);
    std::vector<GraphNodePtr> &getNodes() { return nodes; }
    const std::vector<GraphNodePtr> &getNodes() const { return nodes; }

  private:
    std::vector<GraphNodePtr> nodes;
  };
}
