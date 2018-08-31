#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

#include "renderwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addObject();
    void selectObject(QListWidgetItem *curObj, QListWidgetItem *prevObj);

private:
    Ui::MainWindow *ui;

    RenderWidget *m_viewport;
};

#endif // MAINWINDOW_H
