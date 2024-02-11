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

    void wipeXMP();
    void wipeXMPProfile1();
    void wipeXMPProfile2();
    void wipeXMPProfile3();
    void wipeXMPProfileU1();
    void wipeXMPProfileU2();

    void loadSampleXMPProfile1();
    void loadSampleXMPProfile2();
    void loadSampleXMPProfile3();
    void loadSampleXMPProfileU1();
    void loadSampleXMPProfileU2();

    void enableXMPMagicBits();
    void disableXMPMagicBits();

    void reloadUI();
    void reloadJEDECTab();
    void reloadXMP1Tab();
    void reloadXMP2Tab();
    void reloadXMP3Tab();
    void reloadXMPU1Tab();
    void reloadXMPU2Tab();

private:
    void clearUI();
    void disableUI();
    void enableUI();
    void toggleUI(const bool);
    void toggleXMPUI(const bool);

    unsigned short minCycle;

    DDR5SPD* spd = nullptr;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
