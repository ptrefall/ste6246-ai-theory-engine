#include "Sprite.h"

#include <iostream>

using namespace Components;
using namespace Totem;

Sprite::Sprite(Entity &owner, const std::string &name, irr::scene::ISceneNode& parent, irr::scene::ISceneManager& smgr, std::string &filename, irr::core::vector2di &frame_dimension)
: Component(name), owner(owner), spriteNode(0x0), filename(filename), smgr(smgr)
{
	anim_speed_property = owner.addProperty<int>("AnimSpeed", 400);
	sceneNode = owner.addProperty<irr::scene::ISceneNode*>("SceneNode", 0x0);
	position_property = owner.addProperty<irr::core::vector3df>("Position", irr::core::vector3df());

	/*health_property = owner.addProperty<float>("Health", 100.0f);
	maxhealth_property = owner.addProperty<float>("MaxHealth", 100.0f);

    health_property.valueChanged().connect(this, &Sprite::onHealthChanged);*/
	position_property.valueChanged().connect(this, &Sprite::onPositionChanged);

	spriteNode = new irr::scene::TAnimSprite(smgr.getRootSceneNode(), &smgr, 668);
	spriteNode->Load(filename.c_str(), frame_dimension.X, frame_dimension.Y); // 72,97);
	spriteNode->SetSpeed(anim_speed_property.get());

	spriteNode->setPosition(position_property.get());
	float spwn_height = owner.getTerrain().getHeight(spriteNode->getPosition().X, spriteNode->getPosition().Z);
	position_property.set(position_property.get() + irr::core::vector3df(0, spwn_height, 0), false, false);
	spriteNode->setPosition(position_property.get());

	spriteNode->setScale(irr::core::vector3df(45,45,00));
	spriteNode->setDebugDataVisible(irr::scene::EDS_BBOX);
	spriteNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	spriteNode->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);

	sceneNode = spriteNode;
}

Sprite::~Sprite()
{
}

void Sprite::update(const float &dt)
{
	spriteNode->Update(irr::scene::ESD_SOUTH);
}

void Sprite::onPositionChanged(const irr::core::vector3df &oldValue, const irr::core::vector3df &newValue)
{
	spriteNode->setPosition(newValue);
	float spwn_height = owner.getTerrain().getHeight(spriteNode->getPosition().X, spriteNode->getPosition().Z);
	position_property.set(newValue + irr::core::vector3df(0, spwn_height, 0), false, false);
	spriteNode->setPosition(position_property.get());
}
