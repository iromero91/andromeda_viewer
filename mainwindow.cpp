#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "andromeda_scene.h"
#include "andromeda_view.h"
#include "andromeda_drawable.h"

#include <QGraphicsEllipseItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    AndromedaScene *scene = new AndromedaScene();

    scene->setBackgroundColor(QColor(200,225,245));
    scene->setSceneRect(-1000,-1000,2000,2000);

    ui->graphicsView->setScene(scene);

    TestRect *r = new TestRect();
    r->rect = QRectF(-100,-100,200,175);
    //scene->addItem(r);

    r = new TestRect();
    r->rect = QRectF(45,-30,10,10);
    //scene->addItem(r);

    r = new TestRect();
    r->rect = QRectF(45,30,100,10);
    //scene->addItem(r);

    ui->graphicsView->setInteractive(true);

    connect(ui->graphicsView,SIGNAL(cursorPositionChanged(QPointF)),this,SLOT(cursorPosChanged(QPointF)));

    setWindowTitle("AndromEDA Viewer");
}

void MainWindow::cursorPosChanged(QPointF pos)
{
    ui->statusBar->showMessage("x: " + QString::number(pos.x(),'f',2) + ", y: " + QString::number(pos.y(),'f',2));
}

MainWindow::~MainWindow()
{
    delete ui;
}
