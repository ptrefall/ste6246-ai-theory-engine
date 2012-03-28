#include "Entity\EntityManager.h"
#include "Entity\Entity.h"

#include "Entity\Components\Cube.h"
#include "Entity\Components\AnimatedMesh.h"
#include "Entity\Components\AnimateRotation.h"
#include "Entity\Components\Textured.h"
#include "Entity\Components\Terrain.h"
#include "Entity\Components\TerrainWalker.h"
#include "Entity\Components\TerrainNavGraph.h"
#include "Entity\Components\PathFinder.h"
#include "Entity\Components\PathWalker.h"

#include "Algorithms\Search\DepthFirst.h"
#include "Algorithms\Search\BredthFirst.h"

#include <Irrlicht\irrlicht.h>
#include <iostream>
#include <string>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

char choose_hero()
{
  char hero_type;
  std::cout << "Do you want to be a) a turtle or b) a dwarf?" << std::endl;
  std::cin >> hero_type;
  if(hero_type != 'a' && hero_type != 'b')
    hero_type = choose_hero();

  return hero_type;
}

char choose_search()
{
  char search_type;
  std::cout << "Do you want to use a) depth first b) bredth first, or c) A* search algorithm?" << std::endl;
  std::cin >> search_type;
  if(search_type != 'a' && search_type != 'b' && search_type != 'c')
    search_type = choose_search();

  return search_type;
}

int main(int argc, char **argv)
{
  char hero_type = choose_hero();
  char search_type = choose_search();

	//////////////////////////////////////////
	// SET UP SAFE RESOURCE DIRECTORY LOOKUP
	//////////////////////////////////////////
	std::string resourceDirectory = argv[0];
	auto pos = resourceDirectory.find_last_of("/");
	if(pos == resourceDirectory.npos)
		pos = resourceDirectory.find_last_of("\\");
	if(pos == resourceDirectory.npos)
		return -1;
	resourceDirectory = resourceDirectory.substr(0, pos);
	
	pos = resourceDirectory.find_last_of("/");
	if(pos == resourceDirectory.npos)
		pos = resourceDirectory.find_last_of("\\");
	if(pos == resourceDirectory.npos)
		return -1;
	resourceDirectory = resourceDirectory.substr(0, pos+1);

	resourceDirectory = resourceDirectory + "Resources\\";

	//////////////////////////////////////////
	// IRRLICHT INITIALIZING
	//////////////////////////////////////////
	IrrlichtDevice *device = createDevice( video::EDT_OPENGL, dimension2d<u32>(1920,1080), 32, false, false, false, 0);
	if(!device)
		return -1;

	device->setWindowCaption(L"AI Theory Engine 2012");
  device->getTimer()->start();

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	smgr->setAmbientLight(SColorf(0.2f, 0.2f, 0.2f));
	smgr->setShadowColor(video::SColor(150,0,0,0));
	//smgr->getParameters()->setAttribute(scene::ALLOW_ZWRITE_ON_TRANSPARENT, true);
	ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS();
  camera->setFarValue(100000.0f);

  std::string tex_dir = resourceDirectory + "Textures\\";
  ITexture *top = driver->getTexture((tex_dir+"skybox_top.tga").c_str());
  smgr->addSkyBoxSceneNode(top,
                           top,
                           driver->getTexture((tex_dir+"skybox_west.tga").c_str()),
                           driver->getTexture((tex_dir+"skybox_east.tga").c_str()),
                           driver->getTexture((tex_dir+"skybox_north.tga").c_str()),
                           driver->getTexture((tex_dir+"skybox_south.tga").c_str()));

	//////////////////////////////////////////
	// TOTEM INITIALIZING
	//////////////////////////////////////////
	EntityManagerPtr emgr = std::make_shared<EntityManager>();

	//Do a simple entity test:
  Component::TerrainNavGraphPtr navgraph; //We'll need access to this later for pathfinders
  Component::TerrainPtr terrain; //We'll need access to this later for walking on the terrain correctly

	EntityPtr terrain_entity = emgr->create();
	{
		//Components
    terrain = terrain_entity->addComponent(std::make_shared<Component::Terrain>(terrain_entity, "Node", smgr));
		terrain_entity->addComponent(std::make_shared<Component::Textured>(terrain_entity, "Textured", driver, resourceDirectory));
    navgraph = terrain_entity->addComponent(std::make_shared<Component::TerrainNavGraph>(terrain_entity, "Graph", smgr, driver));

		//Component Properties

		//Shared Properties
    terrain_entity->get<std::string>("Heightmap") = resourceDirectory + "Textures\\heightmap.tga";
    terrain_entity->get<vector3df>("Scale") = vector3df(20.0f, 2.0f, 20.0f);
		
		//Shared PropertyLists
		auto textures = terrain_entity->getList<std::string>("Textures");
		textures.push_back("terrain.tga");
    textures.push_back("detail.tga");
    auto materialTypes = terrain_entity->getList<unsigned int>("MaterialTypes");
    materialTypes.push_back(video::EMT_SOLID);
    materialTypes.push_back(video::EMT_DETAIL_MAP);
    auto textureScales = terrain_entity->getList<vector2df>("TextureScales");
    textureScales.push_back(vector2df(1.0f, 1.0f));
    textureScales.push_back(vector2df(1.0f, 20.0f));
		
		//Initialize
    unsigned int start_time = device->getTimer()->getRealTime();
		terrain->initialize();
    unsigned int execution_time = device->getTimer()->getRealTime() - start_time;
    std::cout << "Generated Terrain in " << (float)execution_time/1000.0f << " seconds!" << std::endl;

    start_time = device->getTimer()->getRealTime();
    navgraph->initialize();
    execution_time = device->getTimer()->getRealTime() - start_time;
    std::cout << "Generated Terrain Nav Mesh in " << (float)execution_time/1000.0f << " seconds!" << std::endl;
    //terrain_entity->get<vector3df>("Position") = -terrain->getTerrain()->getTerrainCenter();
	}
  
  EntityPtr goal_entity = emgr->create();
  {
    //Components
    auto cube = goal_entity->addComponent(std::make_shared<Component::Cube>(goal_entity, "Node", smgr));
		goal_entity->addComponent(std::make_shared<Component::AnimateRotation>(goal_entity, "Animation", smgr));
		goal_entity->addComponent(std::make_shared<Component::Textured>(goal_entity, "Textured", driver, resourceDirectory));
    auto terrainWalker = goal_entity->addComponent(std::make_shared<Component::TerrainWalker>(goal_entity, "TerrainWalker", smgr, terrain->getTerrain()));

    //Component Properties

		//Shared Properties
    goal_entity->get<vector3df>("Position") = vector3df(2600.0f, 600.0f, 2200.0f);
    goal_entity->get<vector3df>("Scale") = vector3df(1.0f, 4.0f, 1.0f);

    //Shared PropertyLists
		auto textures = goal_entity->getList<std::string>("Textures");
		textures.push_back("t351sml.jpg");
    auto materialTypes = goal_entity->getList<unsigned int>("MaterialTypes");
    materialTypes.push_back(video::EMT_SOLID);

     //Initialize
    unsigned int start_time = device->getTimer()->getRealTime();
    cube->initialize();
    unsigned int execution_time = device->getTimer()->getRealTime() - start_time;
    std::cout << "Generated Cube in " << (float)execution_time/1000.0f << " seconds!" << std::endl;
    terrainWalker->initialize();
  }

  EntityPtr agent_entity = emgr->create();
  {
    //Components
    std::string mesh_name = resourceDirectory+"Meshes\\";
    if(hero_type == 'a')
      mesh_name += "turtle1.ms3d";
    else if(hero_type == 'b')
      mesh_name += "dwarf2.x";
    else
    {
      return -1;
    }

    auto mesh = agent_entity->addComponent(std::make_shared<Component::AnimatedMesh>(agent_entity, "Node", smgr, mesh_name));
    agent_entity->addComponent(std::make_shared<Component::Textured>(agent_entity, "Textured", driver, resourceDirectory));
    auto terrainWalker = agent_entity->addComponent(std::make_shared<Component::TerrainWalker>(agent_entity, "TerrainWalker", smgr, terrain->getTerrain()));
    auto pathfinder = agent_entity->addComponent(std::make_shared<Component::PathFinder>(agent_entity, "PathFinder", smgr, navgraph->getGraph()));
    auto pathwalker = agent_entity->addComponent(std::make_shared<Component::PathWalker>(agent_entity, "PathWalker", smgr));

    //Component Properties
		//Shared Properties
    agent_entity->get<vector3df>("Position") = vector3df(2600.0f, 600.0f, 1400.0f);
    
    if(hero_type == 'a')
      agent_entity->get<vector3df>("Scale") = vector3df(2.0f, 2.0f, 2.0f);
    else if(hero_type == 'b')
      agent_entity->get<vector3df>("Scale") = vector3df(5.0f, 5.0f, 5.0f);
    else
    {
      return -1;
    }

    //Shared PropertyLists
    auto textures = agent_entity->getList<std::string>("Textures");
    if(hero_type == 'a')
      textures.push_back("turtle1.png");
    else if(hero_type == 'b')
      textures.push_back("dwarf2.jpg");
    else
    {
      return -1;
    }
    auto materialTypes = agent_entity->getList<unsigned int>("MaterialTypes");
    materialTypes.push_back(video::EMT_SOLID);

    //Initialize
    if(search_type == 'a')
      mesh->initialize(1,11);
    else if(search_type == 'b')
      mesh->initialize(16,26);
    else
      return -1;

    terrainWalker->initialize();

    unsigned int start_time = device->getTimer()->getRealTime();
    if(search_type == 'a')
      pathfinder->initialize(goal_entity, std::make_shared<Algorithms::Search::DepthFirst>());
    else if(search_type == 'b')
      pathfinder->initialize(goal_entity, std::make_shared<Algorithms::Search::BredthFirst>());
    else
      return -1;
    unsigned int execution_time = device->getTimer()->getRealTime() - start_time;
    std::cout << "Generated Path in " << (float)execution_time/1000.0f << " seconds!" << std::endl;

    pathwalker->initialize();
  }

  /*irr::scene::ITriangleSelector *selector = smgr->createTerrainTriangleSelector(terrain->getTerrain(), 0);
  terrain->getTerrain()->setTriangleSelector(selector);
  irr::scene::ISceneNodeAnimator *anim = smgr->createCollisionResponseAnimator(selector, camera);
  selector->drop();
  camera->addAnimator(anim);
  anim->drop();*/

  camera->setPosition( vector3df(2600.0f, 600.0f, 1500.0f) );

	//////////////////////////////////////////
	// GUI INITIALIZING
	//////////////////////////////////////////
	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!", rect<s32>(10,10,260,22), true);

	//////////////////////////////////////////
	// HEARTBEAT
	//////////////////////////////////////////
	while(device->run())
	{
		if (!device->isWindowActive())
			device->yield();

		double fps_ms = 1.0 / (double)driver->getFPS();	
		emgr->update(fps_ms);

		driver->beginScene(true, true, SColor(255,100,101,140));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();


	}

	//////////////////////////////////////////
	// CLEANUP
	//////////////////////////////////////////
	device->drop();
	return 0;
}

