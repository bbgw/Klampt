#ifndef OBJECT_POSE_WIDGET_H
#define OBJECT_POSE_WIDGET_H

#include <GLdraw/Widget.h>
#include <GLdraw/TransformWidget.h>
#include <robotics/IK.h>
#include "ViewRigidObject.h"

/** @addtogroup View */
/** @{ */

/** A widget that allows full posing and editing of the robot config including
 * IK constraints and base motion.
 */
class RigidObjectPoseWidget : public GLDraw::WidgetSet
{
public:
  RigidObjectPoseWidget();
  RigidObjectPoseWidget(RigidObject* object,ViewRigidObject* viewObject);
  void Set(RigidObject* object,ViewRigidObject* viewObject);

  const RigidTransform& Pose() const { return poser.T; }
  void SetPose(const RigidTransform& q);

  virtual void DrawGL(Camera::Viewport& viewport);
  virtual bool BeginDrag(int x,int y,Camera::Viewport& viewport,double& distance);
  virtual void Drag(int dx,int dy,Camera::Viewport& viewport);
  virtual void EndDrag();
  virtual void Keypress(char c);

  RigidObject* rigidObject;
  GLDraw::TransformWidget poser;
};

/** @} */

#endif
