#include "GraphEdge.h"

using namespace Structures;

GraphEdge::GraphEdge(const GraphNodePtr &from, const GraphNodePtr &to, unsigned int cost)
  : from(from), to(to), cost(cost)
{
}

GraphEdge::~GraphEdge()
{
}
