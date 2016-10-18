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
    scene->addItem(r);

    r = new TestRect();
    r->rect = QRectF(45,-30,10,10);
    scene->addItem(r);

    r = new TestRect();
    r->rect = QRectF(45,30,10,10);
    scene->addItem(r);

    /*
    QGraphicsEllipseItem *e1 = new QGraphicsEllipseItem(0,0,20,10);
    e1->setPen(QPen(QColor(20,250,50)));
    e1->setFlag(QGraphicsItem::ItemIsSelectable);

    scene->addItem(e1);

    e1 = new QGraphicsEllipseItem(-50,-50,100,10);

    //e1->setPen(QPen(QColor(250,50,20)));
    //e1->setFlag(QGraphicsItem::ItemIsMovable);
    e1->setFlag(QGraphicsItem::ItemIsSelectable);

    scene->addItem(e1);

    scene->addRect(-1000,-1000,2000,2000);
    */

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
