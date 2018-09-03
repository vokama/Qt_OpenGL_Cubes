#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cube.h"

#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGridLayout *renderingLayout = new QGridLayout(ui->RenderingSpace);
    m_viewport = new RenderWidget(ui->RenderingSpace);
    renderingLayout->addWidget(m_viewport);

    ui->CubesList->setSelectionMode(QAbstractItemView::SingleSelection);

    QObject::connect(ui->AddObject, SIGNAL(clicked()), this, SLOT(addObject()));
    QObject::connect(ui->CubesList, SIGNAL(currentRowChanged(int)),
                     this, SLOT(selectObject(int)));
    QObject::connect(ui->RemoveObject, SIGNAL(clicked()), this, SLOT(removeObject()));

    srand(time(NULL));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addObject()
{
    static int objID = 0;
    std::string cubeName = std::to_string(objID++);
    QListWidgetItem *cubeItem = new QListWidgetItem(cubeName.c_str(), ui->CubesList);

    QVector3D turn(rand() % 360, rand() % 360, rand() % 360);
    QVector3D center(rand() % 100, rand() % 100, rand() % 100);

    QMatrix4x4 rot;
    rot.rotate(turn.x(), 1, 0, 0);
    rot.rotate(turn.y(), 0, 1, 0);
    rot.rotate(turn.z(), 0, 0, 1);

    CubeInstance instance{center, rot};
    m_viewport->m_cube->addInstance(instance);

    QList<QVariant> displayData;
    displayData.append(center);
    for (size_t i = 0; i < cubeVertexCount; i++) {
        displayData.append(center + rot * cubeVertices[i]);
    }
    cubeItem->setData(QListWidgetItem::UserType, displayData);
}

#define VEC_TO_STR(vec) QString("%1  %2  %3").arg((vec)[0]).arg((vec)[1]).arg((vec)[2])

void MainWindow::selectObject(int row)
{
    if (row < 0)
        return;

    m_viewport->m_cube->selectInstance(row);

    QListWidgetItem *curObj = ui->CubesList->item(row);

    QList<QVariant> displayData = curObj->data(QListWidgetItem::UserType).toList();

    QVector3D center = qvariant_cast<QVector3D>(displayData.at(0));
    ui->CenterValue->setText(VEC_TO_STR(center));

    ui->Vertex1Value->setText(VEC_TO_STR(qvariant_cast<QVector3D>(displayData.at(1))));
    ui->Vertex2Value->setText(VEC_TO_STR(qvariant_cast<QVector3D>(displayData.at(2))));
    ui->Vertex3Value->setText(VEC_TO_STR(qvariant_cast<QVector3D>(displayData.at(3))));
    ui->Vertex4Value->setText(VEC_TO_STR(qvariant_cast<QVector3D>(displayData.at(4))));
    ui->Vertex5Value->setText(VEC_TO_STR(qvariant_cast<QVector3D>(displayData.at(5))));
    ui->Vertex6Value->setText(VEC_TO_STR(qvariant_cast<QVector3D>(displayData.at(6))));
    ui->Vertex7Value->setText(VEC_TO_STR(qvariant_cast<QVector3D>(displayData.at(7))));
    ui->Vertex8Value->setText(VEC_TO_STR(qvariant_cast<QVector3D>(displayData.at(8))));
}

void MainWindow::removeObject()
{
    int row = ui->CubesList->currentRow();
    if (row < 0)
        return;

    m_viewport->m_cube->removeInstance(row);

    delete ui->CubesList->item(row);
}
