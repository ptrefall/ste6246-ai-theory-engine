#include "Cube.h"

using namespace Component;

Cube::Cube(const EntityPtr &owner, const std::string &name, irr::scene::ISceneManager *smgr)
	: Totem::Component<Cube>(name), owner(owner), smgr(smgr)
{
	size = this->add<float>("Size", 10.0f);
	
	node = owner->add<irr::scene::ISceneNode*>("Node", nullptr);
	parent = owner->add<irr::scene::ISceneNode*>("ParentNode", nullptr);
	position = owner->add<irr::core::vector3df>("Position", irr::core::vector3df());
	rotation = owner->add<irr::core::vector3df>("Rotation", irr::core::vector3df());
	scale = owner->add<irr::core::vector3df>("Scale", irr::core::vector3df(1.0f));

	position.valueChanged().connect(this, &Cube::OnPositionChanged);
	rotation.valueChanged().connect(this, &Cube::OnRotationChanged);
	scale.valueChanged().connect(this, &Cube::OnScaleChanged);
}

Cube::~Cube()
{
}

void Cube::initialize()
{
	node = smgr->addCubeSceneNode(size, parent.get(), -1, position.get(), rotation.get(), scale.get());
	irr::scene::ISceneNodeAnimator *animator = smgr->createRotationAnimator(irr::core::vector3df(0.0f, 1.0f, 0.0f));
	node.get()->addAnimator(animator);
}

void Cube::OnPositionChanged(const irr::core::vector3df &oldValue, const irr::core::vector3df &newValue)
{
	if(node.get() == nullptr)
		return;

	node.get()->setPosition(newValue);
}

void Cube::OnRotationChanged(const irr::core::vector3df &oldValue, const irr::core::vector3df &newValue)
{
	if(node.get() == nullptr)
		return;

	node.get()->setRotation(newValue);
}

void Cube::OnScaleChanged(const irr::core::vector3df &oldValue, const irr::core::vector3df &newValue)
{
	if(node.get() == nullptr)
		return;

	node.get()->setScale(newValue);
}
