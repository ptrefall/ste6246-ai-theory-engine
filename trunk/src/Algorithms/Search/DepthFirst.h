#pragma once

#include "../../Structures/Tree/Tree.h"
#include "../../Structures/Tree/TreeEdge.h"
#include "../../Structures/Tree/TreeNode.h"

#include <memory>
#include <vector>

namespace Algorithms { namespace Search
{
  class DepthFirst;
  typedef std::shared_ptr<DepthFirst> DepthFirstPtr;

  class DepthFirst
  {
  public:
    DepthFirst();
    ~DepthFirst();

    std::vector<Structures::TreeEdgePtr> search(const Structures::TreePtr &tree, const Structures::TreeNodePtr &start, const Structures::TreeNodePtr &goal);
    
  private:
    bool visit(std::list<Structures::TreeNodePtr> &queue, const Structures::TreeNodePtr &node, const Structures::TreeNodePtr &goal, std::vector<Structures::TreeEdgePtr> &path);
  };
}}

