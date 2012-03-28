#pragma once

#include <Irrlicht/irrlicht.h>

#include <memory>

namespace Scene
{
  class LineStripNode;
  typedef std::shared_ptr<LineStripNode> LineStripNodePtr;

  class LineStripNode : public irr::scene::ISceneNode
  {
    private:
      irr::core::array<irr::video::S3DVertex> lstVertices;
      irr::core::array<irr::u16> lstIndices;
      irr::core::aabbox3df Box;
      irr::video::SMaterial Material;
      irr::video::IVideoDriver* Driver;

    public:
      LineStripNode(ISceneNode* parent, irr::scene::ISceneManager* smgr, irr::s32 id=-1);
      virtual void OnRegisterSceneNode();
      virtual void render();
      virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
      virtual irr::u32 getMaterialCount();
      virtual irr::video::SMaterial& getMaterial(irr::u32 i);
      virtual void setMaterial(irr::video::SMaterial newMaterial);

      void addPoint(irr::core::vector3df p1, irr::core::vector3df p2, irr::video::SColor color);
  };

}
