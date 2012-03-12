#include "Textured.h"

using namespace Component;

Textured::Textured(const EntityPtr &owner, const std::string &name, irr::video::IVideoDriver* driver, const std::string &res_dir)
	: Totem::Component<Textured>(name), owner(owner), driver(driver), res_dir(res_dir)
{
	textures = owner->addList<std::string>("Textures");
	node = owner->add<irr::scene::ISceneNode*>("Node", nullptr);
	node.valueChanged().connect(this, &Textured::OnNodeChanged);
}

Textured::~Textured()
{
}

void Textured::OnNodeChanged(irr::scene::ISceneNode*const &oldValue, irr::scene::ISceneNode*const &newValue)
{
	if(newValue == nullptr)
		return;

	for(unsigned int i = 0; i < textures.size(); i++)
		node.get()->setMaterialTexture(i, driver->getTexture((res_dir + "Textures\\" + textures.get().at(i)).c_str()));

	node.get()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}
