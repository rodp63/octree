#include "scenemodifier.h"
#include "tools.h"
#include "region-octree.h"

#include <QGuiApplication>
#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtGui/QScreen>
#include <Qt3DExtras/qtorusmesh.h>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qpointlight.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>
#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>

using namespace std;

const size_t depth = 7;
char sample_path[] = "../files/sample.obj";


void build_tree(Qt3DCore::QEntity *entity)
{ 
  pair<Point<float>, Point<float> > bounds = tools::GetBounds<float>(sample_path);
  Octree<float,depth> tree(bounds.first, bounds.second);
  
  int cntIn = tools::ManagePoints<float, depth>(tree, INSERT, sample_path);
  cout << cntIn << " inserted points" << endl;

  tree.dfs(entity);
}


int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
  Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();
    
  view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    
  QWidget *container = QWidget::createWindowContainer(view);
  QSize screenSize = view->screen()->size();

  QWidget *widget = new QWidget;
  QHBoxLayout *hLayout = new QHBoxLayout(widget);
  hLayout->addWidget(container, 1);

  widget->setWindowTitle(QStringLiteral("Octree visualization v1.0"));

  Qt3DRender::QCamera *cameraEntity = view->camera();
  cameraEntity->setPosition(QVector3D(35, 45, 30)); // Max Bound
  cameraEntity->setViewCenter(QVector3D(0, -10, -35)); // minBound

  Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
  Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
  light->setColor("white");
  light->setIntensity(3);
  lightEntity->addComponent(light);
  Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
  lightTransform->setTranslation(cameraEntity->position());
  lightEntity->addComponent(lightTransform);

  Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
  camController->setCamera(cameraEntity);

  build_tree(rootEntity);

  view->setRootEntity(rootEntity);

  widget->show();
  widget->resize(1200, 800);

  return app.exec();
}
