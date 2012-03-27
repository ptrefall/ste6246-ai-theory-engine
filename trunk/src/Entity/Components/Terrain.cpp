#include "Terrain.h"

using namespace Component;

Terrain::Terrain(const EntityPtr &owner, const std::string &name, irr::scene::ISceneManager *smgr)
	: Totem::Component<Terrain>(name), owner(owner), smgr(smgr)
{
  heightmap = owner->add<std::string>("Heightmap", std::string());
	size = this->add<float>("Size", 10.0f);
	
	node = owner->add<irr::scene::ISceneNode*>("Node", nullptr);
  terrain = owner->add<irr::scene::ITerrainSceneNode*>("Terrain", nullptr);
	parent = owner->add<irr::scene::ISceneNode*>("ParentNode", nullptr);
	position = owner->add<irr::core::vector3df>("Position", irr::core::vector3df());
	rotation = owner->add<irr::core::vector3df>("Rotation", irr::core::vector3df());
	scale = owner->add<irr::core::vector3df>("Scale", irr::core::vector3df(1.0f));

	position.valueChanged().connect(this, &Terrain::OnPositionChanged);
	rotation.valueChanged().connect(this, &Terrain::OnRotationChanged);
	scale.valueChanged().connect(this, &Terrain::OnScaleChanged);
}

Terrain::~Terrain()
{
}

void Terrain::initialize()
{
  if(heightmap.get().empty())
    return;

  terrain = smgr->addTerrainSceneNode(heightmap.get().c_str(), parent.get(), -1, position.get(), rotation.get(), scale.get());
  node = terrain;
}

void Terrain::OnPositionChanged(const irr::core::vector3df &oldValue, const irr::core::vector3df &newValue)
{
	if(node.get() == nullptr)
		return;

	node.get()->setPosition(newValue);
}

void Terrain::OnRotationChanged(const irr::core::vector3df &oldValue, const irr::core::vector3df &newValue)
{
	if(node.get() == nullptr)
		return;

	node.get()->setRotation(newValue);
}

void Terrain::OnScaleChanged(const irr::core::vector3df &oldValue, const irr::core::vector3df &newValue)
{
	if(node.get() == nullptr)
		return;

	node.get()->setScale(newValue);
}

