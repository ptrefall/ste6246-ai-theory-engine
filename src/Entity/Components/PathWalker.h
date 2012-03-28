#pragma once

#include "../Entity.h"

#include <Totem/Component.h>
#include <Irrlicht\irrlicht.h>

#include <string>

namespace Component
{
	class PathWalker : public Totem::Component<PathWalker>
	{
	public:
    PathWalker(const EntityPtr &owner, const std::string &name, irr::scene::ISceneManager *smgr);
		virtual ~PathWalker();

		void initialize();

    void update(const float &dt) override;

	private:
		EntityWPtr owner;
		irr::scene::ISceneManager *smgr;

    Totem::Property<irr::scene::ISceneNode*> node;
    Totem::PropertyList<irr::scene::ISceneNode*> path_gizmos;
    irr::scene::ISceneNodeAnimator* anim;

    unsigned int path_index;
    unsigned int next_index;

    irr::core::vector3df p1;
    irr::core::vector3df p2;
	};
}
