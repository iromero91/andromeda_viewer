#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "viewers/andromeda_scene.h"
#include "viewers/andromeda_view.h"

#include <QGraphicsEllipseItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setInteractive(true);

    ui->graphicsView->getScene()->setSceneRect(-1000,-1000,2000,2000);

    // Uncomment to set dark background
    //ui->graphicsView->getScene()->setBackgroundColor(QColor(25,25,25));

    connect(ui->graphicsView,SIGNAL(cursorPositionChanged(QPointF)),this,SLOT(cursorPosChanged(QPointF)));

    setWindowTitle("AndromEDA Viewer");
}

void MainWindow::cursorPosChanged(QPointF pos)
{
    QPointF origin = ui->graphicsView->getCursorOrigin();
    QPointF delta = pos - origin;

    QString msg = "Pos (";

    msg += QString::number(pos.x(),'f',2) + ",";
    msg += QString::number(pos.y(),'f',2) + ")";

    msg += " Delta (";
    msg += QString::number(delta.x(),'f',2) + ",";
    msg += QString::number(delta.y(),'f',2) + ")";

    ui->statusBar->showMessage(msg);
}

MainWindow::~MainWindow()
{
    delete ui;
}
