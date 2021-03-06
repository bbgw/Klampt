#ifndef VIEW_ROBOT_H
#define VIEW_ROBOT_H

#include <GLdraw/GLColor.h>
#include <GLdraw/GLDisplayList.h>
#include <GLdraw/GeometryAppearance.h>
#include "Modeling/Robot.h"

/** @ingroup View
 * @brief Draws the robot (potentially color-coded)
 */
struct ViewRobot
{
  ViewRobot(Robot* robot=NULL);
  ~ViewRobot();
  void Draw(Robot* robot);
  void Draw();
  void DrawLink_Local(int i,bool keepAppearance=true);  //draws the geometry in its local frame
  void DrawLink_World(int i,bool keepAppearance=true);  //draws the geometry in the world frame
  void DrawCenterOfMass(Real radius = 0.05);
  void DrawLinkCenterOfMass(int i,Real radius = 0.05);
  void DrawLinkFrames(Real size = 0.1);
  void DrawLinkSkeleton();
  void DrawTorques(const Vector& t);
  void SetColors(const GLDraw::GLColor& c);
  void SetColor(int i,const GLDraw::GLColor& c);
  void SetGrey();
  void SetTorqueColors(const Vector& t);

  Robot* robot;
  vector<GLDraw::GeometryAppearance> linkAppearance;
};

#endif
