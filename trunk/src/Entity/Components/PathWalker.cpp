#include "PathWalker.h"

using namespace Component;

using namespace irr;
using namespace core;

PathWalker::PathWalker(const EntityPtr &owner, const std::string &name, irr::scene::ISceneManager *smgr)
	: Totem::Component<PathWalker>(name), owner(owner), smgr(smgr), path_index(0), next_index(0), anim(nullptr)
{
  node = owner->add<irr::scene::ISceneNode*>("Node", nullptr);
  path_gizmos = owner->addList<irr::scene::ISceneNode*>("PathGizmos");
}

PathWalker::~PathWalker()
{
}

void PathWalker::initialize()
{
  irr::core::vector3df p1 = path_gizmos.get().at(path_index)->getPosition();
  irr::core::vector3df p2 = p1;
  for(unsigned int i = path_index+1; i<path_gizmos.size(); i++)
  {
    p2 = path_gizmos.get().at(path_index+i)->getPosition();
    if(p2 != p1)
    {
      next_index = i;
      break;
    }
  }

  anim = smgr->createFlyStraightAnimator(p1, p2, 1000, false);
  if (anim)
  {
    node.get()->addAnimator(anim);
  }
}

void PathWalker::update(const float &dt)
{
  if(anim == nullptr)
    return;

  irr::scene::ISceneNode *n = node.get();
  if(anim && anim->hasFinished())
  {
    //Remove path animator
    n->removeAnimator(anim);

    if(next_index >= path_gizmos.size()-1)
      return;

    //Add new path
    path_index = next_index;
    p1 = p2;
    for(unsigned int i = path_index+1; i<path_gizmos.size(); i++)
    {
      if(i >= path_gizmos.size())
        return;
      p2 = path_gizmos.get().at(i)->getPosition();
      if(p2 != p1)
      {
        next_index = i;
        break;
      }
    }

    anim = smgr->createFlyStraightAnimator(p1, p2, 1000, false);
    if (anim)
      n->addAnimator(anim);
  }

  //Make our walker face in the direction of the walking path
  core::vector3df nodePos = p2 - n->getPosition();
  float rot = atan(nodePos.Z/nodePos.X) * (180.0f / irr::core::PI);
  if((p2.X - n->getPosition().X) > 0) {
    rot = 90 - rot;
  } else if((p2.X - n->getPosition().X) < 0) {
    rot = -90 - rot;
  }
  //rot -= 90;
  n->setRotation(vector3df(0,rot,0));
}
