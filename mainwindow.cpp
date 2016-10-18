#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "andromeda_scene.h"
#include "andromeda_view.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    AndromedaScene *scene = new AndromedaScene();

    scene->setBackgroundColor(QColor(200,225,245));
    scene->setSceneRect(-1000,-1000,2000,2000);

    ui->graphicsView->setScene(scene);


    scene->addEllipse(0,0,20,10);
    scene->addEllipse(-50,-50,100,10);

    scene->addRect(-1000,-1000,2000,2000);

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
