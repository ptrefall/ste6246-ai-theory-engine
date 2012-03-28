#include "TerrainNavGraph.h"

using namespace Component;

TerrainNavGraph::TerrainNavGraph(const EntityPtr &owner, const std::string &name, irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver)
	: Totem::Component<TerrainNavGraph>(name), owner(owner), smgr(smgr), driver(driver)
{
  heightmap = owner->add<std::string>("Heightmap", std::string());
  terrain = owner->add<irr::scene::ITerrainSceneNode*>("Terrain", nullptr);
  scale = owner->add<irr::core::vector3df>("Scale", irr::core::vector3df(1.0f));
  graph = owner->add<Structures::GraphPtr>("NavGraph", nullptr);
}

TerrainNavGraph::~TerrainNavGraph()
{
}

void TerrainNavGraph::initialize()
{
  genGraph();
}

void TerrainNavGraph::genGraph()
{
  unsigned int inv_resolution = 8;

  graph = std::make_shared<Structures::Graph>();

  irr::video::ITexture *h = driver->getTexture(heightmap.get().c_str());
  graph.get()->getNodes().reserve((h->getSize().Width/inv_resolution)*(h->getSize().Height/inv_resolution));
  for(auto x_i = 0; x_i < h->getSize().Width/inv_resolution; x_i++)
  {
    for(auto z_i = 0; z_i < h->getSize().Height/inv_resolution; z_i++)
    {
      float x = x_i * scale.get().X * inv_resolution - (inv_resolution*scale.get().X);
      float z = z_i * scale.get().Z * inv_resolution - (inv_resolution*scale.get().X);
      float y = terrain.get()->getHeight(x,z);

      auto node = std::make_shared<Structures::GraphNode>();
      node->add<irr::core::vector3df>("Position", irr::core::vector3df(x,y,z));
      graph.get()->addNode(node);
    }
  }

  /*******

  00 04 08 12
  01 05 09 13
  02 06 10 14
  03 07 11 15

  x + z * h = n
 ---------------
  0 + 0 * 4 = 0
  1 + 0 * 4 = 1
  2 + 0 * 4 = 2

  *******/

  auto &nodes = graph.get()->getNodes();
  for(auto x_i = 0; x_i < h->getSize().Width/inv_resolution; x_i++)
  {
    for(auto z_i = 0; z_i < h->getSize().Height/inv_resolution; z_i++)
    {
      auto &node = nodes[x_i + z_i * (h->getSize().Width/inv_resolution)];

      //Neighbours
      Structures::GraphNodePtr node_west, node_north, node_east, node_south;
      if(x_i != 0)
      {
        node_west = nodes[x_i-1 + z_i * (h->getSize().Width/inv_resolution)];
        float costf = node_west->get<irr::core::vector3df>("Position").get().Y - node->get<irr::core::vector3df>("Position").get().Y;
        unsigned int cost = (unsigned int)(costf * 100000.0f);
        node.get()->addAdjNode(node_west, cost);
      }
      if(z_i != 0)
      {
        node_north = nodes[x_i + (z_i-1) * (h->getSize().Width/inv_resolution)];
        float costf = node_north->get<irr::core::vector3df>("Position").get().Y - node->get<irr::core::vector3df>("Position").get().Y;
        unsigned int cost = (unsigned int)(costf * 100000.0f);
        node.get()->addAdjNode(node_north, cost);
      }
      if(x_i != (h->getSize().Width/inv_resolution)-1)
      {
        node_east = nodes[x_i+1 + z_i * (h->getSize().Width/inv_resolution)];
        float costf = node_east->get<irr::core::vector3df>("Position").get().Y - node->get<irr::core::vector3df>("Position").get().Y;
        unsigned int cost = (unsigned int)(costf * 100000.0f);
        node.get()->addAdjNode(node_east, cost);
      }
      if(z_i != (h->getSize().Width/inv_resolution)-1)
      {
        node_south = nodes[x_i + (z_i+1) * (h->getSize().Width/inv_resolution)];
        float costf = node_south->get<irr::core::vector3df>("Position").get().Y - node->get<irr::core::vector3df>("Position").get().Y;
        unsigned int cost = (unsigned int)(costf * 100000.0f);
        node.get()->addAdjNode(node_south, cost);
      }
    }
  }
}
