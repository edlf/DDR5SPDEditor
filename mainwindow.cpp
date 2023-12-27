#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("Welcome", 0);

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionSave, &QAction::enabledChanged, this, &MainWindow::saveFileEnabled);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::closeFile);
    connect(ui->actionClose, &QAction::enabledChanged, this, &MainWindow::closeFileEnabled);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exit(){
    qApp->exit();
}

void MainWindow::openFile(){
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath(), "SPD Files (*.spd, *.bin);;All Files (*.*)");
    if (!fileName.isEmpty()) {
        // do something with the selected file
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(
                this,
                appName,
                tr("Failed to load file.") );
        }

        if (file.size() != DDR5SPD::eepromSize) {
            QMessageBox::critical(
                this,
                appName,
                tr("Invalid SPD file size.") );
        }

        QByteArray contents = file.readAll();

        if (spd != nullptr) {
            delete(spd);
        }
        spd = new DDR5SPD(contents);

        enableUI();
    }
}

void MainWindow::saveFile(){
    if (spd != nullptr) {
        QString fileName = QFileDialog::getSaveFileName(this, "Save File", QDir::currentPath(), "SPD Files (*.spd, *.bin);;All Files (*.*)");
        if (!fileName.isEmpty()) {
            // save contents to the selected file
        }
    }
}

void MainWindow::closeFile(){
    disableUI();

    if (spd != nullptr) {
        delete(spd);
    }
}

bool MainWindow::saveFileEnabled(){
    return spd != nullptr;
}

bool MainWindow::closeFileEnabled(){
    return spd != nullptr;
}


void MainWindow::exportXMP(){
    // TODO
}

void MainWindow::disableUI(){
    // TODO
}
void MainWindow::enableUI(){
    // TODO
}
