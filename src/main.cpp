#include "Entity\EntityManager.h"
#include "Entity\Entity.h"

#include <Irrlicht\irrlicht.h>
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(int argc, char **argv)
{
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

	smgr->setShadowColor(video::SColor(150,0,0,0));
	smgr->getParameters()->setAttribute(scene::ALLOW_ZWRITE_ON_TRANSPARENT, true);

	//////////////////////////////////////////
	// TOTEM INITIALIZING
	//////////////////////////////////////////
	EntityManagerPtr emgr = std::make_shared<EntityManager>();

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
