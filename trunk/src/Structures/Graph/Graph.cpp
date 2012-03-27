#include "Graph.h"
#include "GraphNode.h"
#include <algorithm>

using namespace Structures;

Graph::Graph()
{
}

Graph::~Graph()
{
  std::for_each(begin(nodes), end(nodes), [](const GraphNodePtr &node)
  {
    node->clearAdjNodes();
  });
}

void Graph::clearVisited()
{
  std::for_each(begin(nodes), end(nodes), [](const GraphNodePtr &node)
  {
    node->clearVisited();
  });
}

const GraphNodePtr &Graph::addNode(const GraphNodePtr &node)
{
  nodes.push_back(node);
  return node;
}

