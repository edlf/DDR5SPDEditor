#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>

#include "ddr5spd.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

const QString appName = "DDR5 SPD Editor";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    void saveFile();
    bool saveFileEnabled();
    void closeFile();
    bool closeFileEnabled();
    void exportXMP();
    void exit();

    void reloadUI();

private:
    void clearUI();
    void disableUI();
    void enableUI();

    unsigned short minCycle;

    DDR5SPD* spd = nullptr;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
