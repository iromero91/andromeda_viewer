#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "viewers/andromeda_scene.h"
#include "viewers/andromeda_view.h"

#include "base/andromeda_object.h"

#include <QGraphicsEllipseItem>

#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setInteractive(true);

    ui->graphicsView->getScene()->setSceneRect(-1000,-1000,2000,2000);

    // Uncomment to set dark background
    //ui->graphicsView->getScene()->setBackgroundColor(QColor(25,25,25));

    connect(ui->graphicsView->scene(), SIGNAL(selectionChanged()), this, SLOT(selectionChanged()));
    connect(ui->graphicsView,SIGNAL(cursorPositionChanged(QPointF)),this,SLOT(cursorPosChanged(QPointF)));

    connect(ui->ellipseButton, SIGNAL(released()), ui->graphicsView, SLOT(drawEllipse()));
    connect(ui->rectLine, SIGNAL(released()), ui->graphicsView, SLOT(drawRect()));
    connect(ui->polyButton, SIGNAL(released()), ui->graphicsView, SLOT(drawPolyline()));

    setWindowTitle("AndromEDA Viewer");

    ui->prop->setReadOnly(true);
    ui->graphicsView->setFocus();

    QPixmap p = QCursor(Qt::ArrowCursor).pixmap();

    qDebug() << p.width() << p.height();
}

// This is just a crazy hack to show property inspection
// Please delete this :/
void MainWindow::selectionChanged()
{
    QList<QGraphicsItem*> items = ui->graphicsView->scene()->selectedItems();

    ui->prop->clear();
    ui->json->clear();

    if (items.count() == 1)
    {
        AndromedaObject *obj = qgraphicsitem_cast<ADrawableBase*>(items.first());

        if (nullptr != obj)
        {
            QStringList lines;
            QString text = "";

            foreach (QMetaProperty p, obj->getProperties())
            {
                text = QString(p.name()) + " : " + obj->property(p.name()).toString();
                lines.append(text);
            }

            ui->prop->clear();
            ui->prop->insertPlainText(lines.join("\n"));

            ui->json->insertPlainText(obj->encodedString());
        }
    }
    else if (items.count() > 1)
    {
        ui->prop->insertPlainText(
                    QString::number(items.count()) +
                    QString(" items selected"));
    }
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
