#pragma once

#include "../../Structures/Tree/Tree.h"
#include "../../Structures/Tree/TreeEdge.h"
#include "../../Structures/Tree/TreeNode.h"

#include "../../Structures/Graph/Graph.h"
#include "../../Structures/Graph/GraphEdge.h"
#include "../../Structures/Graph/GraphNode.h"

#include <memory>
#include <vector>
#include <list>

namespace Algorithms { namespace Search
{
  class ISearch;
  typedef std::shared_ptr<ISearch> ISearchPtr;

  class ISearch
  {
  public:
    virtual std::vector<Structures::TreeEdgePtr> search(const Structures::TreePtr &tree, const Structures::TreeNodePtr &start, const Structures::TreeNodePtr &goal) = 0;
    virtual std::vector<Structures::GraphEdgePtr> search(const Structures::GraphPtr &graph, const Structures::GraphNodePtr &start, const Structures::GraphNodePtr &goal) = 0;
  };
}}
