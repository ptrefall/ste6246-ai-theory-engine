#include "TreeEdge.h"

using namespace Structures;

TreeEdge::TreeEdge(const TreeNodePtr &parent, const TreeNodePtr &child, unsigned int cost)
  : parent(parent), child(child), cost(cost)
{
}

TreeEdge::~TreeEdge()
{
}
