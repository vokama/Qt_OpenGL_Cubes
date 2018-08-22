#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGridLayout *renderingLayout = new QGridLayout(ui->RenderingSpace);
    m_viewport = new RenderWidget(ui->RenderingSpace);
    renderingLayout->addWidget(m_viewport);
}

MainWindow::~MainWindow()
{
    delete ui;
}
