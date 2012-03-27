#include "TerrainWalker.h"

using namespace Component;

TerrainWalker::TerrainWalker(const EntityPtr &owner, const std::string &name, irr::scene::ISceneManager *smgr, irr::scene::ITerrainSceneNode *terrain)
	: Totem::Component<TerrainWalker>(name), owner(owner), smgr(smgr), terrain(terrain)
{
  node = owner->add<irr::scene::ISceneNode*>("Node", nullptr);
}

TerrainWalker::~TerrainWalker()
{
}

void TerrainWalker::initialize()
{
  irr::scene::ITriangleSelector *selector = smgr->createTerrainTriangleSelector(terrain, 0);
  terrain->setTriangleSelector(selector);

  irr::scene::ISceneNodeAnimator *anim = smgr->createCollisionResponseAnimator(selector, node.get());
  selector->drop();
  node.get()->addAnimator(anim);
  anim->drop();
}

void TerrainWalker::update(const float &dt)
{
  irr::core::vector3df pos = node.get()->getPosition();
  pos.Y = terrain->getHeight(pos.X, pos.Z);// + (node.get()->getBoundingBox().getExtent().Y / 2.0f);
  node.get()->setPosition(pos);
}
