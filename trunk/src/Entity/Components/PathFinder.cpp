#include "PathFinder.h"

using namespace Component;

PathFinder::PathFinder(const EntityPtr &owner, const std::string &name, irr::scene::ISceneManager *smgr, Structures::GraphPtr graph)
	: Totem::Component<PathFinder>(name), owner(owner), smgr(smgr)
{
  this->graph = owner->add<Structures::GraphPtr>("NavGraph", graph);
  position = owner->add<irr::core::vector3df>("Position", irr::core::vector3df());
  goal = owner->add<EntityPtr>("Goal", nullptr);
  searchAlg = owner->add<Algorithms::Search::ISearchPtr>("SearchAlg", nullptr);
  path_gizmos = owner->addList<irr::scene::ISceneNode*>("PathGizmos");
}

PathFinder::~PathFinder()
{
}

void PathFinder::initialize(const EntityPtr &target, const Algorithms::Search::ISearchPtr &search)
{
  this->goal = target;
  this->searchAlg = search;
  findPath();

  path_lines = std::make_shared<Scene::LineStripNode>(smgr->getRootSceneNode(), smgr);
  
  int color1d = 0;
  int stepsize = (255*3) / path.size();
  if(stepsize < 1)
    stepsize = 1;

  irr::video::SColor color(255,0,0,0);
  for(auto i = 0; i < path.size(); i++)
  {
    irr::core::vector3df pos = path[i]->getFrom()->get<irr::core::vector3df>("Position").get();
    irr::core::vector3df to_pos = path[i]->getTo()->get<irr::core::vector3df>("Position").get();

    if(i != 0 && i != path.size()-1)
    {
      irr::scene::IMeshSceneNode *gizmo = smgr->addSphereSceneNode(5.0f, 16, 0, -1, pos);

      if(color1d - 255 > 0)
      {
        color.setRed(255);

        if(color1d - 510 > 0)
        {
          color.setGreen(255);

          if(color1d - 765 > 0)
            color.setBlue(255);
          else
            color.setBlue(color1d-510);
        }
        else
          color.setGreen(color1d-255);
      }
      else
        color.setRed(color1d);
    
      color1d += stepsize;

      gizmo->getMaterial(0).AmbientColor = color;
      gizmo->getMaterial(0).DiffuseColor = color;
      gizmo->getMaterial(0).EmissiveColor = color;
      gizmo->getMaterial(0).SpecularColor = color;
      smgr->getMeshManipulator()->setVertexColors(gizmo->getMesh(), color);
      gizmo->setMaterialType(irr::video::EMT_SOLID);
      gizmo->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      path_gizmos.push_back(gizmo);
    }
    else if(i == 0)
    {
      color.set(255,0,255,0);
      irr::scene::IMeshSceneNode *gizmo = smgr->addCubeSceneNode(20.0f, 0, -1, pos);
      gizmo->getMaterial(0).AmbientColor = color;
      gizmo->getMaterial(0).DiffuseColor = color;
      gizmo->getMaterial(0).EmissiveColor = color;
      gizmo->getMaterial(0).SpecularColor = color;
      smgr->getMeshManipulator()->setVertexColors(gizmo->getMesh(), color);
      gizmo->setMaterialType(irr::video::EMT_SOLID);
      gizmo->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      path_gizmos.push_back(gizmo);
    }
    else
    {
      color.set(255,255,0,0);
      irr::scene::IMeshSceneNode *gizmo = smgr->addCubeSceneNode(20.0f, 0, -1, pos);
      gizmo->getMaterial(0).AmbientColor = color;
      gizmo->getMaterial(0).DiffuseColor = color;
      gizmo->getMaterial(0).EmissiveColor = color;
      gizmo->getMaterial(0).SpecularColor = color;
      smgr->getMeshManipulator()->setVertexColors(gizmo->getMesh(), color);
      gizmo->setMaterialType(irr::video::EMT_SOLID);
      gizmo->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      path_gizmos.push_back(gizmo);
    }

    path_lines->addPoint(pos, to_pos, color);
    //if(i == path.size()-1)
      //path_lines->addPoint(pos, pos, color);

    color.set(255,0,0,0);
  }
}

void PathFinder::findPath()
{
  auto start_node = getNodeFromPos(position.get());
  auto goal_node = getNodeFromPos(goal.get()->get<irr::core::vector3df>("Position").get());
  if(start_node == nullptr || goal_node == nullptr || searchAlg.get() == nullptr || graph.get() == nullptr)
    return;

  path = searchAlg.get()->search(graph.get(), start_node, goal_node);
}

Structures::GraphNodePtr PathFinder::getNodeFromPos(const irr::core::vector3df &posit)
{
  for(auto i = 0; i < graph.get()->getNodes().size(); i++)
  {
    auto &node = graph.get()->getNodes()[i];
    const irr::core::vector3df &pos = node->get<irr::core::vector3df>("Position").get();
    if(abs(pos.X - posit.X) < 65.0f &&
       abs(pos.Z - posit.Z) < 65.0f)
    {
      return node;
    }
  }
  return nullptr;
}
