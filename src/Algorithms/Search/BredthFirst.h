#pragma once

#include "ISearch.h"

namespace Algorithms { namespace Search
{
  class BredthFirst;
  typedef std::shared_ptr<BredthFirst> BredthFirstPtr;

  class BredthFirst : public ISearch
  {
  public:
    BredthFirst();
    ~BredthFirst();

    std::vector<Structures::TreeEdgePtr> search(const Structures::TreePtr &tree, const Structures::TreeNodePtr &start, const Structures::TreeNodePtr &goal) override;
    std::vector<Structures::GraphEdgePtr> search(const Structures::GraphPtr &graph, const Structures::GraphNodePtr &start, const Structures::GraphNodePtr &goal) override;
    
  private:
    bool visit(std::list<Structures::TreeNodePtr> &queue, const Structures::TreeNodePtr &node, const Structures::TreeNodePtr &goal, std::vector<Structures::TreeEdgePtr> &path);
    bool visit(std::list<Structures::GraphNodePtr> &queue, const Structures::GraphNodePtr &node, const Structures::GraphNodePtr &goal, std::vector<Structures::GraphEdgePtr> &path);
  };
}}

