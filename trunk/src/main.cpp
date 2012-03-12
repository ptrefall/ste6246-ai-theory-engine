#include "Entity\EntityManager.h"
#include "Entity\Entity.h"

#include "Entity\Components\Cube.h"
#include "Entity\Components\AnimateRotation.h"

#include <Irrlicht\irrlicht.h>
#include <iostream>
#include <string>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(int argc, char **argv)
{
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

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	smgr->setAmbientLight(SColorf(0.2f, 0.2f, 0.2f));
	smgr->setShadowColor(video::SColor(150,0,0,0));
	smgr->getParameters()->setAttribute(scene::ALLOW_ZWRITE_ON_TRANSPARENT, true);
	smgr->addCameraSceneNode();

	//////////////////////////////////////////
	// TOTEM INITIALIZING
	//////////////////////////////////////////
	EntityManagerPtr emgr = std::make_shared<EntityManager>();

	//Do a simple entity test:
	EntityPtr entity = emgr->create();
	{
		//Components
		auto node = entity->addComponent(std::make_shared<Component::Cube>(entity, "Shape", smgr));
		auto rotate = entity->addComponent(std::make_shared<Component::AnimateRotation>(entity, "Animation", smgr));

		//Component Properties

		//Shared Properties
		entity->get<vector3df>("Position") = vector3df(0.0f, 0.0f, 20.0f);
		
		//Initialize
		node->initialize();
		node->getNode()->setMaterialTexture(0, driver->getTexture((resourceDirectory + "Textures\\t351sml.jpg").c_str()));
		node->getNode()->setMaterialFlag(video::EMF_LIGHTING, false);
	}

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
