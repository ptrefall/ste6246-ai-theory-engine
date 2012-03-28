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
#include <list>

namespace Algorithms { namespace Search
{
  class AStar;
  typedef std::shared_ptr<AStar> AStarPtr;

  class AStar : public ISearch
  {
  public:
    AStar();
    ~AStar();

    std::vector<Structures::TreeEdgePtr> search(const Structures::TreePtr &tree, const Structures::TreeNodePtr &start, const Structures::TreeNodePtr &goal) override;
    std::vector<Structures::GraphEdgePtr> search(const Structures::GraphPtr &graph, const Structures::GraphNodePtr &start, const Structures::GraphNodePtr &goal) override;

  private:
    void initialize(const Structures::GraphPtr &graph, const Structures::GraphNodePtr &start, const Structures::GraphNodePtr &goal);
    bool step(const Structures::GraphPtr &graph, const Structures::GraphNodePtr &start, const Structures::GraphNodePtr &goal, std::vector<Structures::GraphEdgePtr> &path);

  private:
    float goalDistanceEstimate(const Structures::GraphPtr &graph, const Structures::GraphNodePtr &start, const Structures::GraphNodePtr &goal);
    void constructPath(std::vector<Structures::GraphEdgePtr> &path);
    static bool sort(const Structures::GraphNodePtr &x, const Structures::GraphNodePtr &y);

  private:
    unsigned int steps;
    
    class AStarNode;
    typedef std::shared_ptr<AStarNode> AStarNodePtr;

    class AStarNode
    {
    public:
      Structures::GraphNodePtr node;
      AStarNodePtr parent;
      float G;
      float H;
      float F;
    };
    

    std::list<AStarNodePtr> open;
    std::list<AStarNodePtr> closed;

    AStarNodePtr start_node;
    AStarNodePtr goal_node;
  };
}}

