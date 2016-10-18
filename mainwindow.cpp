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

    scene->setBackgroundColor(QColor(100,25,45));

    ui->graphicsView->setScene(scene);

    scene->addEllipse(0,0,20,10);
    scene->addEllipse(-50,-50,100,10);
}

MainWindow::~MainWindow()
{
    delete ui;
}
