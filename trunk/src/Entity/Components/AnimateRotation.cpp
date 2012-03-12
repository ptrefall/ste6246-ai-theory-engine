#include "AnimateRotation.h"

using namespace Component;

AnimateRotation::AnimateRotation(const EntityPtr &owner, const std::string &name, irr::scene::ISceneManager *smgr)
	: Totem::Component<AnimateRotation>(name), owner(owner), smgr(smgr)
{
	speed = this->add<irr::core::vector3df>("Speed", irr::core::vector3df(0.0f, 1.0f, 0.0f));
	
	node = owner->add<irr::scene::ISceneNode*>("Node", nullptr);
	node.valueChanged().connect(this, &AnimateRotation::OnNodeChanged);
}

AnimateRotation::~AnimateRotation()
{
}

void AnimateRotation::OnNodeChanged(irr::scene::ISceneNode*const &oldValue, irr::scene::ISceneNode*const &newValue)
{
	if(newValue == nullptr)
		return;

	irr::scene::ISceneNodeAnimator *animator = smgr->createRotationAnimator(speed.get());
	node.get()->addAnimator(animator);
	animator->drop();
}
