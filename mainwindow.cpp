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

    ui->graphicsView->setInteractive(true);

    ui->graphicsView->getScene()->setSceneRect(-1000,-1000,2000,2000);

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
