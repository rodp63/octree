#ifndef SCENEMODIFIER_H
#define SCENEMODIFIER_H

#include <QtCore/QObject>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>

class SceneModifier : public QObject
{
  Q_OBJECT

 public:
  explicit SceneModifier(Qt3DCore::QEntity *rootEntity, float a, float b, float c, float d);
  ~SceneModifier();

 private:

  float x, y, z, s;
  Qt3DCore::QEntity *m_rootEntity;
  Qt3DCore::QEntity *m_cuboidEntity;
  Qt3DCore::QTransform *cuboidTransform;
  
  Qt3DExtras::QCuboidMesh *cuboid;
  Qt3DExtras::QPhongMaterial *cuboidMaterial;

};

#endif // SCENEMODIFIER_H
