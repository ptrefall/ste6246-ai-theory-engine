#include "AnimatedMesh.h"

using namespace Component;

AnimatedMesh::AnimatedMesh(const EntityPtr &owner, const std::string &name, irr::scene::ISceneManager *smgr, const std::string &mesh)
	: Totem::Component<AnimatedMesh>(name), owner(owner), smgr(smgr), mesh_filename(mesh)
{
	size = this->add<float>("Size", 10.0f);
	
	node = owner->add<irr::scene::ISceneNode*>("Node", nullptr);
	parent = owner->add<irr::scene::ISceneNode*>("ParentNode", nullptr);
	position = owner->add<irr::core::vector3df>("Position", irr::core::vector3df());
	rotation = owner->add<irr::core::vector3df>("Rotation", irr::core::vector3df());
	scale = owner->add<irr::core::vector3df>("Scale", irr::core::vector3df(1.0f));

	position.valueChanged().connect(this, &AnimatedMesh::OnPositionChanged);
	rotation.valueChanged().connect(this, &AnimatedMesh::OnRotationChanged);
	scale.valueChanged().connect(this, &AnimatedMesh::OnScaleChanged);
}

AnimatedMesh::~AnimatedMesh()
{
}

void AnimatedMesh::initialize(unsigned int startframe, unsigned int endframe)
{
	//node = smgr->addCubeSceneNode(size, parent.get(), -1, position.get(), rotation.get(), scale.get());
  irr::scene::IAnimatedMesh *mesh = smgr->getMesh(mesh_filename.c_str());
  irr::scene::IAnimatedMeshSceneNode *anim = smgr->addAnimatedMeshSceneNode(mesh, parent.get(), -1, position.get(), rotation.get(), scale.get());
  anim->setFrameLoop(startframe,endframe);
  node = anim;
}

void AnimatedMesh::OnPositionChanged(const irr::core::vector3df &oldValue, const irr::core::vector3df &newValue)
{
	if(node.get() == nullptr)
		return;

	node.get()->setPosition(newValue);
}

void AnimatedMesh::OnRotationChanged(const irr::core::vector3df &oldValue, const irr::core::vector3df &newValue)
{
	if(node.get() == nullptr)
		return;

	node.get()->setRotation(newValue);
}

void AnimatedMesh::OnScaleChanged(const irr::core::vector3df &oldValue, const irr::core::vector3df &newValue)
{
	if(node.get() == nullptr)
		return;

	node.get()->setScale(newValue);
}
