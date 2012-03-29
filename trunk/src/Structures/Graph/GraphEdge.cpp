#include "GraphEdge.h"

using namespace Structures;

GraphEdge::GraphEdge(const GraphNodePtr &from, const GraphNodePtr &to, float cost)
  : from(from), to(to), cost(cost)
{
}

GraphEdge::~GraphEdge()
{
}
