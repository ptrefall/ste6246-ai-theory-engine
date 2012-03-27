#include "Textured.h"

using namespace Component;

Textured::Textured(const EntityPtr &owner, const std::string &name, irr::video::IVideoDriver* driver, const std::string &res_dir)
	: Totem::Component<Textured>(name), owner(owner), driver(driver), res_dir(res_dir)
{
	textures = owner->addList<std::string>("Textures");
  materialType = owner->addList<unsigned int>("MaterialTypes");
  textureScale = owner->addList<irr::core::vector2df>("TextureScales");
	node = owner->add<irr::scene::ISceneNode*>("Node", nullptr);
  terrain = owner->add<irr::scene::ITerrainSceneNode*>("Terrain", nullptr);
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
  {
		node.get()->setMaterialTexture(i, driver->getTexture((res_dir + "Textures\\" + textures.get().at(i)).c_str()));
    if(materialType.size() > i)
      node.get()->setMaterialType((irr::video::E_MATERIAL_TYPE)materialType.get().at(i));
    if(textureScale.size() > i)
      terrain.get()->scaleTexture(textureScale.get().at(i).X, textureScale.get().at(i).Y);
  }

	node.get()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}
