#pragma once

#include "ISearch.h"

#include "../../Structures/Tree/Tree.h"
#include "../../Structures/Tree/TreeEdge.h"
#include "../../Structures/Tree/TreeNode.h"

#include "../../Structures/Graph/Graph.h"
#include "../../Structures/Graph/GraphEdge.h"
#include "../../Structures/Graph/GraphNode.h"

#include <memory>
#include <vector>

namespace Algorithms { namespace Search
{
  class DepthFirst;
  typedef std::shared_ptr<DepthFirst> DepthFirstPtr;

  class DepthFirst : public ISearch
  {
  public:
    DepthFirst();
    ~DepthFirst();

    std::vector<Structures::TreeEdgePtr> search(const Structures::TreePtr &tree, const Structures::TreeNodePtr &start, const Structures::TreeNodePtr &goal) override;
    std::vector<Structures::GraphEdgePtr> search(const Structures::GraphPtr &graph, const Structures::GraphNodePtr &start, const Structures::GraphNodePtr &goal) override;
    
  private:
    bool visit(std::list<Structures::TreeNodePtr> &queue, const Structures::TreeNodePtr &node, const Structures::TreeNodePtr &goal, std::vector<Structures::TreeEdgePtr> &path);
    bool visit(std::list<Structures::GraphNodePtr> &queue, const Structures::GraphNodePtr &node, const Structures::GraphNodePtr &goal, std::vector<Structures::GraphEdgePtr> &path);

	void constructPath(const Structures::GraphNodePtr &node, std::vector<Structures::GraphEdgePtr> &path);
  };
}}

