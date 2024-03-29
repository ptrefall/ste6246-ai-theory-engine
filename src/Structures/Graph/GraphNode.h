#pragma once

#include <Totem\PropertyContainer.h>

#include <memory>
#include <vector>

namespace Structures
{
  class GraphEdge;
  typedef std::shared_ptr<GraphEdge> GraphEdgePtr;

  class GraphNode;
  typedef std::shared_ptr<GraphNode> GraphNodePtr;

  class GraphNode : public Totem::PropertyContainer<>, public std::enable_shared_from_this<GraphNode>
  {
  public:
    GraphNode();
    virtual ~GraphNode();

    void setUID(unsigned int uid) { this->uid = uid; }
    unsigned int getUID() const { return uid; }

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
    GraphEdgePtr addAdjNode(const GraphNodePtr &node, float cost);
    std::vector<GraphEdgePtr> &getAdjNodes() { return adj_nodes; }
    const std::vector<GraphEdgePtr> &getAdjNodes() const { return adj_nodes; }

	GraphEdgePtr getAdjNode(const GraphNodePtr &node);

  public:
	  void setParent(const GraphNodePtr &parent) { this->parent = parent; }
	  const GraphNodePtr &getParent() const { return parent; }

  private:
    unsigned int uid;
    std::vector<GraphEdgePtr> adj_nodes;
	GraphNodePtr parent;
    VisitStatus visit_status;
  };
}
