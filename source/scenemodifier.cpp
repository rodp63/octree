#include "scenemodifier.h"

#include <QtCore/QDebug>

SceneModifier::SceneModifier(Qt3DCore::QEntity *rootEntity, float a, float b, float c, float d)
    : m_rootEntity(rootEntity), x(a), y(b), z(c), s(d)
{

  cuboid = new Qt3DExtras::QCuboidMesh();

  cuboidTransform = new Qt3DCore::QTransform();
  cuboidTransform->setScale(s);
  cuboidTransform->setTranslation(QVector3D(x, y, z));

  cuboidMaterial = new Qt3DExtras::QPhongMaterial();
  cuboidMaterial->setDiffuse(QColor(QRgb(0x665423)));

  m_cuboidEntity = new Qt3DCore::QEntity(m_rootEntity);
  m_cuboidEntity->addComponent(cuboid);
  m_cuboidEntity->addComponent(cuboidMaterial);
  m_cuboidEntity->addComponent(cuboidTransform);

}

SceneModifier::~SceneModifier()
{
  delete cuboid;
  delete cuboidTransform;
  delete cuboidMaterial;
}
