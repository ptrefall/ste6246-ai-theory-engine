#include <ft2build.h>
#include FT_FREETYPE_H

#include <Irrlicht\irrlicht.h>

#include <GA\GASStateGA.h>
#include <GA\GA3DBinStrGenome.h>
#include <iostream>

#include <ClanLib\core.h>

#include <SceneNode\HealthSceneNode.h>
#include <SceneNode\CGridSceneNode.h>
#include <SceneNode\Weather\irrWeatherManager.h>
#include <SceneNode\TAnimSprite.h>
#include <SceneNode\GraphSceneNode.h>

#include <GUI/CIrrRocketGUI.h>

#include <Entity\EntityManager.h>
#include <Entity\Entity.h>
#include <Entity\Components\Health.h>
#include <Entity\Components\Sprite.h>
#include <Totem\ComponentFactory.h>

//#include <GeneticAlg\Genome\ProsumerGenome.h>

#include <GeneticAlg\ProsumerGeneticAlg.h>
#include <GeneticAlg\GAManager.h>

#include <mgl/mgl_zb.h>
//#include <mgl/data.h>

#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//float Objective(GAGenome &);

int main(int argc, char **argv)
{
	CL_SetupCore clanlib_core_setup;

	/*for(int ii=1; ii<argc; ii++) 
	{
		if(strcmp(argv[ii++],"seed") == 0) {
			GARandomSeed((unsigned int)atoi(argv[ii]));
		}
	}
	int width    = 10;
	int height   = 10;
	int depth   = 3;
	int popsize  = 30;
	int ngen     = 100;
	float preplace = 1.0;
	float pmut   = 0.001;
	float pcross = 0.9;
	GA3DBinaryStringGenome genome(width, height, depth, Objective);

	GASteadyStateGA ga(genome);
	ga.minimize();
	ga.populationSize(popsize);
	ga.pReplacement(preplace);
	ga.nGenerations(ngen);
	ga.pMutation(pmut);
	ga.pCrossover(pcross);
	ga.scoreFilename("../../bin/bog.dat");	// name of file for scores
	ga.scoreFrequency(10);	// keep the scores of every 10th generation
	ga.flushFrequency(50);	// specify how often to write the score to disk
	ga.selectScores(GAStatistics::AllScores);
	GAGenome &individual = ga.population().individual(0);*/

	//{
	/*ProsumerGenome genome; //default constructor
	std::cout << "genome after creation:\n" << genome << std::endl;

	int popsize  = 300;
	int ngen     = 30;
	float preplace = 0.1;
	float pmut   = 0.02;
	float pcross = 0.35;

	GASteadyStateGA ga(genome);
	ga.minimize();
	ga.populationSize(popsize);
	ga.pReplacement(preplace);
	ga.nGenerations(ngen);
	ga.pMutation(pmut);
	ga.pCrossover(pcross);
	ga.scoreFilename("../../bin/bog.dat");	// name of file for scores
	ga.scoreFrequency(1);	// keep the scores of every 10th generation
	ga.flushFrequency(50);	// specify how often to write the score to disk
	ga.selectScores(GAStatistics::Maximum|GAStatistics::Minimum);
	GANoScaling scalor;
	ga.scaling(scalor);
	GARankSelector selector;
	ga.selector(selector);*/


	/*genome.initialize();  // test the initializer
	std::cout << "genome after initialization:\n" << genome << std::endl;

	genome.mutate(0.99f);      // test the mutator
	std::cout << "genome after mutation:\n" << genome << std::endl;

	ProsumerGenome* a = new ProsumerGenome(genome);   // test copy constructor
	ProsumerGenome* b = new ProsumerGenome(genome);

	ProsumerGenome* c = static_cast<ProsumerGenome*>(genome.clone(GAGenome::CONTENTS));
	std::cout << "clone contents:\n" << *c << "\n";
	ProsumerGenome* d = static_cast<ProsumerGenome*>(genome.clone(GAGenome::ATTRIBUTES));
	std::cout << "clone attributes:\n" << *d << "\n";

	a->initialize();
	b->initialize();
	std::cout << "parents:\n" << *a << "\n" << *b << "\n";

	ProsumerGenome::Cross(*a, *b, c, d);   // test two child crossover
	std::cout << "children of crossover:\n" << *c << "\n" << *d << "\n";
	ProsumerGenome::Cross(*a, *b, c, 0);   // test single child crossover
	std::cout << "child of crossover:\n" << *c << "\n";

	a->compare(*b);       // test the comparator

	delete a;
	delete b;
	delete c;
	delete d;
	}*/

	//RgbGeneticAlg ga(10, 0.75, 0.2, 0.01);
	/*ProsumerGeneticAlg ga(	100,		//Population Size 
							0.0,		//Fitness threshold
							0.05,		//Chance for crossover
							1,			//Max children from crossover
							0.05,		//Chance for mutation
							0.1,		//Start saldo
							3.0,		//Øk
							1.0,		//Ep
							24000.0,	//Ef
							0.1,		//Flex
							0);			//Policy
	ga.initialize();*/

	char a;
	std::cout << "Do you want to draw the scene with 1) Software, or 2) OpenGL renderer?" << std::endl;
	std::cin >> a;

	IrrlichtDevice *device = 0x0;
	if(a == '1')
		device = createDevice( video::EDT_BURNINGSVIDEO, dimension2d<u32>(800,600), 16, false, false, false, 0);
	else if(a == '2')
		device = createDevice( video::EDT_OPENGL, dimension2d<u32>(1920,1080), 32, false, false, false, 0);
	
	if(!device)
		return -1;

	device->setWindowCaption(L"TradingAgent");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	smgr->setShadowColor(video::SColor(150,0,0,0));
	smgr->getParameters()->setAttribute(scene::ALLOW_ZWRITE_ON_TRANSPARENT, true);

	//IMeshManipulator *meshManip = driver->getMeshManipulator();

	// create light
	/*{
		ISceneNode * node = smgr->addLightSceneNode(0, core::vector3df(0,0,0),
				video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 800.0f);
		scene::ISceneNodeAnimator* anim = 0;
		anim = smgr->createFlyCircleAnimator (core::vector3df(0,10,0),100.0f, 0.0003f);
		node->addAnimator(anim);
		anim->drop();

		// attach billboard to light

		node = smgr->addBillboardSceneNode(node, core::dimension2d<f32>(50, 50));
		node->setMaterialFlag(video::EMF_LIGHTING, false);
		node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		node->setMaterialTexture(0, driver->getTexture("../../bin/resources/Particle/particlewhite.bmp"));
	}*/

	scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
            "../../bin/resources/Terrain/terrain-heightmap.bmp",
            0,                                      // parent node
            -1,                                     // node id
            core::vector3df(-512.f, 100.f, -512.f),         // position
            core::vector3df(0.f, 0.f, 0.f),         // rotation
            core::vector3df(10.f, 1.0f, 10.f),      // scale
            video::SColor ( 255, 255, 255, 255 ),   // vertexColor
            5,                                      // maxLOD
            scene::ETPS_17,                         // patchSize
            4                                       // smoothFactor
            );

	mglGraphZB gr;
	gr.SetSize(512, 512);
	mglData y(10,3);
	y.Modify("0.8*sin(pi*(2*x+y/2))+0.2*rnd");
	gr.Org=mglPoint(0,0);
	gr.Box();
	gr.Bars(y);
	//gr.WriteBMP("test.bmp");
	unsigned char *bits = const_cast<unsigned char*>(gr.GetBits());

	IImage *graph_plot_image = driver->createImageFromData(ECF_R8G8B8, dimension2d<u32>(gr.GetWidth(), gr.GetHeight()), bits);
	ITexture *graph_plot_tex = driver->addTexture("graph_plot", graph_plot_image);

	ISceneNode *cube = smgr->addCubeSceneNode(100.0f);
	if(cube)
	{
		cube->setMaterialTexture(0, graph_plot_tex);
		cube->setMaterialFlag(video::EMF_LIGHTING, false);
		
		/*scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(core::vector3df(0,0.01f,0));
        if (anim)
        {
                cube->addAnimator(anim);
                anim->drop();
        }*/

		cube->setPosition(vector3df(0.0f, 0.0f, 200.0f));
		float sh = terrain->getHeight(cube->getPosition().X, cube->getPosition().Z);
		cube->setPosition(vector3df(0.0f, sh+100.0f, 200.0f));
	}

    terrain->setMaterialFlag(video::EMF_LIGHTING, true);
    terrain->setMaterialTexture(0,
                    driver->getTexture("../../bin/resources/Terrain/terrain_dl.tga"));
    terrain->setMaterialTexture(1,
                    driver->getTexture("../../bin/resources/Terrain/detailmap3.jpg"));
    terrain->setMaterialType(video::EMT_DETAIL_MAP);
    terrain->scaleTexture(4.0f, 1280.0f);

	//ICameraSceneNode *camera = smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
	//ICameraSceneNode *camera = smgr->addCameraSceneNodeMaya(0, -1500.0f, 200.0f, 1500.0f);
	ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 0.25f);
	camera->setPosition(vector3df(0, 0, -40));
	float spawn_height = terrain->getHeight(camera->getPosition().X, camera->getPosition().Z);
	camera->setPosition(vector3df(0.0f, spawn_height+30.0f, -40.0f));
	if(a == '2')
		camera->setFarValue(100000);

	//Collide camera with terrain
	scene::ITriangleSelector* selector = smgr->createTerrainTriangleSelector(terrain, 0);
	terrain->setTriangleSelector(selector);
	scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
            selector, camera, core::vector3df(10,10,10),
            core::vector3df(0,0,0),
            core::vector3df(0,10,0));
    selector->drop();
    camera->addAnimator(anim);
    anim->drop();

	//const float spawn_height = 175.0f;

	//ISceneNode *tower = smgr->addSceneNode("Tower");
	/*{
		IAnimatedMesh* mesh = smgr->getMesh("../../bin/resources/Mesh/Tower/turret_base3.3ds");
		meshManip->recalculateTangents(mesh, true, true, true);
		IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh, tower );
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, true);
			node->setMaterialFlag(EMF_FOG_ENABLE, true);
			node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
			//node->addShadowVolumeSceneNode();

			node->setMaterialTexture( 0, driver->getTexture("../../bin/resources/Mesh/Tower/Base_Diffuse.tga") );
			node->setRotation(vector3df(-90.0f, 0.0f, 0.0f));

			node->setPosition(vector3df(10.0f, 0.0f, 0.0f));
			float spawn_height = terrain->getHeight(node->getPosition().X, node->getPosition().Z);
			node->setPosition(vector3df(10.0f, spawn_height, 0.0f));
		}
	}
	{
		IAnimatedMesh* mesh = smgr->getMesh("../../bin/resources/Mesh/Tower/turret_head6.3ds");
		meshManip->recalculateTangents(mesh, true, true, true);
		IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh, tower );
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, true);
			node->setMaterialFlag(EMF_FOG_ENABLE, true);
			node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
			//node->addShadowVolumeSceneNode();
			node->setMaterialTexture( 0, driver->getTexture("../../bin/resources/Mesh/Tower/Head_Diffuse.tga") );
			node->setRotation(vector3df(-90.0f, 0.0f, 0.0f));
			node->setPosition(vector3df(10.0f, 0.0f, 0.0f));
			float spawn_height = terrain->getHeight(node->getPosition().X, node->getPosition().Z);
			node->setPosition(vector3df(10.0f, spawn_height+6.0f, 0.0f));
		}
	}
	{
		IAnimatedMesh* mesh = smgr->getMesh("../../bin/resources/Mesh/Tower/turret_gun6.3ds");
		meshManip->recalculateTangents(mesh, true, true, true);
		IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh, tower );
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, true);
			node->setMaterialFlag(EMF_FOG_ENABLE, true);
			node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
			//node->addShadowVolumeSceneNode();
			node->setMaterialTexture( 0, driver->getTexture("../../bin/resources/Mesh/Tower/Weapon_Diffuse.tga") );
			node->setRotation(vector3df(-90.0f, 0.0f, 0.0f));
			node->setPosition(vector3df(10.0f, 0.0f, 0.0f));
			float spawn_height = terrain->getHeight(node->getPosition().X, node->getPosition().Z);
			node->setPosition(vector3df(10.0f, spawn_height+8.0f, 0.0f));
		}
	}*/

	/*{
		IAnimatedMesh* mesh = smgr->getMesh("../../bin/resources/Mesh/Beast/beast.ms3d");
		meshManip->recalculateTangents(mesh, true, true, true);
		IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh, tower );
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, true);
			node->setMaterialFlag(EMF_FOG_ENABLE, true);
			node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
			//node->addShadowVolumeSceneNode();

			node->setAnimationSpeed(30.0f);
			node->setFrameLoop(1, 400);
			node->setMaterialTexture( 0, driver->getTexture("../../bin/resources/Mesh/Beast/beast1.jpg") );
			//node->setRotation(vector3df(-90.0f, 0.0f, 0.0f));
			node->setPosition(vector3df(-20.0f, 0.0f, 0.0f));
			float spawn_height = terrain->getHeight(node->getPosition().X, node->getPosition().Z);
			node->setPosition(vector3df(-20.0f, spawn_height, 0.0f));
			node->setScale(vector3df(0.2f, 0.2f, 0.2f));

			scene::ISceneCollisionManager* coll = smgr->getSceneCollisionManager();
			HealthSceneNode *healthbar = new scene::HealthSceneNode(node,smgr,-1,coll,50,10,vector3df(0,100,0));
			healthbar->setProgress(60);
			healthbar->setScale(vector3df(0.02f, 0.02f, 0.02f));
		}
	}*/

	//////////////////////////////////////////
	// WEATHER INITIALIZING
	//////////////////////////////////////////
	irrWeatherManager *weatherMgr = 0x0;
	if(a == '1')
	{
		ISceneNode *sky = smgr->addSkyDomeSceneNode( driver->getTexture("../../bin/resources/Sky/skydome.jpg"),16,16, 1.0f, 2.0f);
		sky->setMaterialFlag(EMF_LIGHTING, false);
		//sky->drop();
	}
	else
	{
		driver->setFog(SColor(0, 255, 255, 255), EFT_FOG_LINEAR, 8000.0f, 40000.0f, 0.01f, true, true);
		weatherMgr = new irrWeatherManager(device);
		weatherMgr->getAtmosphere()->setUpdateFog(true);
		weatherMgr->getAtmosphere()->setSkyImage("../../bin/resources/Sky/skydome.jpg");
		weatherMgr->getAtmosphere()->setDaysPerDay(400);

		SCloudCreationInfo info;
		info.setDefaults();
		info.textureNames.push_back(stringc("../../bin/resources/Clouds/cumulus2.png"));
		info.textureNames.push_back(stringc("../../bin/resources/Clouds/cumulus3.png"));
		info.textureName = "../../bin/resources/Clouds/cumulus2.png";
		info.seed = device->getTimer()->getTime();
		info.numParticles = 10;

		ICloudLayer* layer = weatherMgr->addCloudLayer(vector3df(0,10000,0), info, 50, false);

		//info.textureNames.clear();
		info.textureName = "../../bin/resources/Clouds/cumulus1.png";
		weatherMgr->addCloudLayer(vector3df(0,19000,0), info, 80, false);
	}

	/*scene::CGridSceneNode* grid = new scene::CGridSceneNode(smgr->getRootSceneNode(), smgr);
	grid->setMaterialFlag(EMF_LIGHTING, false);
	grid->drop();*/

	/*GraphSceneNode *graph = new GraphSceneNode(smgr->getRootSceneNode(), smgr);
	for(unsigned int i = 0; i < 100.0f; i++)
	{
		graph->AddPlotPoint(vector3df(i*10.0f,sin(i*0.01f),0.0f));
	}
	graph->RegenerateGraph();
	graph->setMaterialFlag(EMF_LIGHTING, false);*/
	

	//////////////////////////////////////////
	// TOTEM INITIALIZING
	//////////////////////////////////////////
	Totem::ComponentFactory factory;
	Components::Health::RegisterToFactory(factory);
	Components::Sprite::RegisterToFactory(factory);
	EntityManager emgr(*terrain);

	///////////////////////////////
	// POPULATION
	///////////////////////////////
	GAManager gaMgr(smgr,emgr, factory);
	gaMgr.initialize();
	std::cout << "Genearation	ProsumerSaldo	EconomicCapacity	EnergyConsumption	ProsumerPopulationSize	ProsumerDeaths	SupplierSaldo	PriceOffer	CustomerCount	PriceStrategy	SupplierPopulationSize	SupplierDeaths" << std::endl;
	/*for(unsigned int i = 0; i < 100; i++)
	{
		gaMgr.trade();
		if(gaMgr.evolve())
			break;
	}*/

	/*try{
		Entity &entity = emgr.create(factory);
		entity.addComponent<EntityManager, ISceneManager>("Health", emgr, *smgr);
		if(a == '1')
		{
			entity.addComponent<ISceneNode, ISceneManager, std::string>(Components::Sprite::Type(), 
				*smgr->getRootSceneNode(), *smgr, std::string("../../bin/resources/Particle/Particle.tga"), vector2di(64,64));
		}
		else
		{
			entity.addComponent<ISceneNode, ISceneManager, std::string>(Components::Sprite::Type(), 
				*smgr->getRootSceneNode(), *smgr, std::string("../../bin/resources/Sprites/goblin_001.png"), vector2di(72,97));
		}
		entity.sendEvent0(T_HashedString("LOAD"));
	}catch(std::exception &e){
		std::cout << e.what() << std::endl;
	}

	try{
		Entity &entity = emgr.create(factory);
		entity.addComponent<EntityManager, ISceneManager>("Health", emgr, *smgr);
		if(a == '1')
		{
			entity.addComponent<ISceneNode, ISceneManager, std::string>(Components::Sprite::Type(), 
				*smgr->getRootSceneNode(), *smgr, std::string("../../bin/resources/Particle/Particle.tga"), vector2di(64,64));
		}
		else
		{
			entity.addComponent<ISceneNode, ISceneManager, std::string>(Components::Sprite::Type(), 
				*smgr->getRootSceneNode(), *smgr, std::string("../../bin/resources/Sprites/human_001.png"), vector2di(72,97));
		}
		entity.sendEvent0(T_HashedString("LOAD"));
		entity.getProperty<vector3df>("Position") = vector3df(40,0,0);
	}catch(std::exception &e){
		std::cout << e.what() << std::endl;
	}

	try{
		Entity &entity = emgr.create(factory);
		entity.addComponent<EntityManager, ISceneManager>("Health", emgr, *smgr);
		if(a == '1')
		{
			entity.addComponent<ISceneNode, ISceneManager, std::string, vector2di>(Components::Sprite::Type(), 
				*smgr->getRootSceneNode(), *smgr, std::string("../../bin/resources/Particle/Particle.tga"), vector2di(64,64));
		}
		else
		{
			entity.addComponent<ISceneNode, ISceneManager, std::string>(Components::Sprite::Type(), 
				*smgr->getRootSceneNode(), *smgr, std::string("../../bin/resources/Sprites/human_002.png"), vector2di(72,97));
		}
		entity.sendEvent0(T_HashedString("LOAD"));
		entity.getProperty<vector3df>("Position") = vector3df(30,0,0);
	}catch(std::exception &e){
		std::cout << e.what() << std::endl;
	}*/

	//////////////////////////////////////////
	// GUI INITIALIZING
	//////////////////////////////////////////
	CIrrRocketGUI *rocket_gui = 0x0;
	if(a == '1')
	{
		guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
                rect<s32>(10,10,260,22), true);
	}
	else
	{
		rocket_gui = new CIrrRocketGUI(device);
	}

	ITexture *logo = driver->getTexture("../../bin/resources/Gui/images/logo2.png");
	IGUIImage *logo_gui = guienv->addImage(logo, core::position2d<s32>(driver->getScreenSize().Width/2 - logo->getOriginalSize().Width/2,
												 driver->getScreenSize().Height/2 - logo->getOriginalSize().Height/2), true);
	int logo_alpha = 255;
	logo_gui->setColor(SColor(logo_alpha,255,255,255));

	device->getCursorControl()->setVisible(false);

	double ga_accum = 0.0;
	double ga_update_speed = 1.0;
	bool ga_stop = false;

	double accum_time = 0.0;
	double logo_fade_start_accum = 0.0;
	double logo_fade_at = 6.0;
	//int generation = 0;
	while(device->run())
	{
		if (!device->isWindowActive())
			device->yield();

		double fps_ms = 1.0 / (double)driver->getFPS();
		//device->setWindowCaption((const wchar_t*)(std::string("TradingAgent") + std::stringHelp::int_to_text(driver->getFPS())).c_str());

		if(fps_ms < 0.1)
		{
			accum_time += fps_ms;
			logo_fade_start_accum += fps_ms;
			ga_accum += fps_ms;
		}

		if(logo_fade_start_accum >= logo_fade_at)
		{
			logo_alpha--;
			if(logo_alpha < 0)
				logo_gui->setEnabled(false);
			else
				logo_gui->setColor(SColor(logo_alpha,255,255,255));
		}


		if(!ga_stop && ga_accum > ga_update_speed)
		{
			ga_accum = 0.0;
			gaMgr.trade();
			ga_stop = gaMgr.evolve();
		}
				

		/*if(accum_time > 10.0)
		{
			accum_time = 0.0;*/
		/*if(generation <= ngen)
		{
			ga.evolve();
			const ProsumerGenome &prosumer = static_cast<const ProsumerGenome &>(ga.statistics().bestIndividual());
			std::cout << "Best prosumer of generation " << generation << ":\n" << prosumer << "\n";
			generation++;
		}*/
		//}*/

		/*if(accum_time > 0.1f)
		{
			
			//void *bits = cube->getMaterial(0).getTexture(0)->lock();
			//memset(bits, 0, gr.GetWidth()*gr.GetHeight());
			
			gr.NewFrame();

			gr.Box();
			sprintf(frame_script,"sin(pi*x+%g*pi)",0.2*0);
			dat.Modify(frame_script);
			gr.Plot(dat, "b");
			gr.EndFrame();
			//gr.WriteBMP("test.bmp");
			//bits = const_cast<unsigned char*>(gr.GetBits());
			//memcpy(bits, gr.GetBits(), gr.GetWidth()*gr.GetHeight());

			unsigned char *bits = const_cast<unsigned char*>(gr.GetBits());

			IImage *img = driver->createImageFromData(ECF_R8G8B8, dimension2d<u32>(gr.GetWidth(), gr.GetHeight()), bits);
			ITexture *tex = driver->addTexture("graph_plot", img);

			//cube->getMaterial(0).getTexture(0)->unlock();
			cube->setMaterialTexture(0, tex);

			accum_time = 0.0f;
		}*/

		if(weatherMgr)
			weatherMgr->updateWeather();
		//emgr.update((float)fps_ms);

		driver->beginScene(true, true, SColor(255,100,101,140));
		smgr->drawAll();
		if(rocket_gui)
			rocket_gui->run();
		//else
			guienv->drawAll();
		driver->endScene();


	}
	delete weatherMgr;
	device->drop();
	return 0;
}

/*float Objective(GAGenome &g) 
{
	GA3DBinaryStringGenome & genome = (GA3DBinaryStringGenome &)g;
	
	float score = 0.0;
	int count = 0;
	
	for(int i = 0; i<genome.width(); i++)
	{
		for(int j = 0; j<genome.height(); j++)
		{
			for(int k = 0; k<genome.depth(); k++)
			{
				if(genome.gene(i,j,k) == 0 && count%2 == 0)
					score += 1.0;
				if(genome.gene(i,j,k) == 1 && count%2 != 0)
					score += 1.0;
				count++;
			}
		}
	}
	return score;
}*/
