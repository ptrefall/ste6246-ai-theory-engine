#pragma once

#include <memory>
#include <vector>

namespace Structures
{
  class GraphEdge;
  typedef std::shared_ptr<GraphEdge> GraphEdgePtr;

  class GraphNode;
  typedef std::shared_ptr<GraphNode> GraphNodePtr;

  class GraphNode : public std::enable_shared_from_this<GraphNode>
  {
  public:
    GraphNode();
    virtual ~GraphNode();

    void clearAdjNodes();
    void clearVisited();

  public:
    enum VisitStatus {
      NOT_VISITED = 0,
      VISITED
    };

    VisitStatus getVisitStatus() const { return visit_status; }
    void setVisitStatus(VisitStatus visit_status) { this->visit_status = visit_status; }

  public:
    GraphEdgePtr addAdjNode(const GraphNodePtr &node, unsigned int cost);
    std::vector<GraphEdgePtr> &getAdjNodes() { return adj_nodes; }
    const std::vector<GraphEdgePtr> &getAdjNodes() const { return adj_nodes; }

  private:
    std::vector<GraphEdgePtr> adj_nodes;
    VisitStatus visit_status;
  };
}
