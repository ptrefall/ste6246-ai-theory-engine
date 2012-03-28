#include "LineStripNode.h"

using namespace Scene;

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

LineStripNode::LineStripNode(ISceneNode* parent, ISceneManager* smgr, s32 id) 
  : ISceneNode(parent,smgr,id)
{
  Driver = SceneManager->getVideoDriver();
  Material.EmissiveColor = SColor(255, 255,0,0);
  if(Parent) 
    Parent->addChild(this);

  updateAbsolutePosition();
  AutomaticCullingState = EAC_OFF;
}

void LineStripNode::OnRegisterSceneNode(){
  if(IsVisible) 
    SceneManager->registerNodeForRendering(this);
  ISceneNode::OnRegisterSceneNode();
}

void LineStripNode::render(){
  // Prep to render
  Driver->setMaterial(Material);
  Driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
  // render
  Driver->drawVertexPrimitiveList(&lstVertices[0], lstVertices.size(), &lstIndices[0], lstIndices.size()-1, video::EVT_STANDARD, EPT_LINE_STRIP, video::EIT_16BIT);
}

const core::aabbox3d<f32>& LineStripNode::getBoundingBox() const{
  return Box;
}
u32 LineStripNode::getMaterialCount(){
  return 1;
}
video::SMaterial& LineStripNode::getMaterial(u32 i){
  return Material;
}
void LineStripNode::setMaterial(video::SMaterial newMaterial){
  Material = newMaterial;
}

void LineStripNode::addPoint(irr::core::vector3df p1, irr::core::vector3df p2, irr::video::SColor color)
{
  lstIndices.push_back(lstVertices.size());
  lstVertices.push_back( S3DVertex(p1, vector3df(0,0,0), color, vector2df(0,0) ));
  //lstIndices.push_back(lstVertices.size());
  //lstVertices.push_back( S3DVertex(p2, vector3df(0,0,0), color, vector2df(0,0) ));
}
