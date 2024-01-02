#include "mainwindow.h"
#include "utilities.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    disableUI();
    clearUI();

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
        reloadUI();
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
    clearUI();

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

void MainWindow::disableUI() {
    // Tabs
    ui->tabWidget->setCurrentWidget(ui->tabJEDEC);
    ui->tabJEDEC->setDisabled(true);
    ui->tabXMPP1->setDisabled(true);
    ui->tabXMPP2->setDisabled(true);
    ui->tabXMPP3->setDisabled(true);
    ui->tabXMPU1->setDisabled(true);
    ui->tabXMPU2->setDisabled(true);
}

void MainWindow::enableUI() {
    ui->tabJEDEC->activateWindow();
    ui->tabJEDEC->setDisabled(false);
    if(spd != nullptr) {
        if (spd->isXMPPresent())
        {
            ui->tabXMPP1->setDisabled(false);
            ui->tabXMPP2->setDisabled(false);
            ui->tabXMPP3->setDisabled(false);
            ui->tabXMPU1->setDisabled(false);
            ui->tabXMPU2->setDisabled(false);
        }
    }
}

void MainWindow::clearUI() {
    QString emptyValue = "-";

    // Frequency
    ui->spinMinCycleTime->clear();
    ui->spinMaxCycleTime->clear();
    ui->labelFrequencyValue->setText(emptyValue);
    ui->labelMTValue->setText(emptyValue);

    // CAS
    ui->cbCL20->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL22->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL24->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL26->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL28->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL30->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL32->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL34->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL36->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL38->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL40->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL42->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL44->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL46->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL48->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL50->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL52->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL54->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL56->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL58->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL60->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL62->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL64->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL66->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL68->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL70->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL72->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL74->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL76->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL78->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL80->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL82->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL84->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL86->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL88->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL90->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL92->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL94->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL96->setChecked(spd->getCLSupportedDDR5(false));
    ui->cbCL98->setChecked(spd->getCLSupportedDDR5(false));

    ui->spinBoxtAA->setValue(0);
    ui->labeltAA_Ticks->setText(emptyValue);
    ui->spinBoxtRCD->setValue(0);
    ui->labeltRCD_Ticks->setText(emptyValue);
    ui->spinBoxtRP->setValue(0);
    ui->labeltRP_Ticks->setText(emptyValue);
    ui->spinBoxtRAS->setValue(0);
    ui->labeltRAS_Ticks->setText(emptyValue);
    ui->spinBoxtRC->setValue(0);
    ui->labeltRC_Ticks->setText(emptyValue);
    ui->spinBoxtWR->setValue(0);
    ui->labeltWR_Ticks->setText(emptyValue);
    ui->spinBoxtRFC1->setValue(0);
    ui->labeltRFC1_Ticks->setText(emptyValue);
    ui->spinBoxtRFC2->setValue(0);
    ui->labeltRFC2_Ticks->setText(emptyValue);
    ui->spinBoxtRFC->setValue(0);
    ui->labeltRFC_Ticks->setText(emptyValue);
    ui->spinBoxtRRD_L->setValue(0);
    ui->spinBoxtRRD_L_LCLK->setValue(0);
    ui->labeltRRD_L_Ticks->setText(emptyValue);
    ui->spinBoxtCCD_L->setValue(0);
    ui->spinBoxtCCD_L_LCLK->setValue(0);
    ui->labeltCCD_L_Ticks->setText(emptyValue);
    ui->spinBoxtCCDL_L_WR->setValue(0);
    ui->spinBoxtCCDL_L_WR_LCLK->setValue(0);
    ui->labeltCCDL_L_WR_Ticks->setText(emptyValue);
    ui->spinBoxtCCDL_L_WR2->setValue(0);
    ui->spinBoxtCCDL_L_WR2_LCLK->setValue(0);
    ui->labeltCCDL_L_WR2_Ticks->setText(emptyValue);
    ui->spinBoxtFAW->setValue(0);
    ui->spinBoxtFAW_LCLK->setValue(0);
    ui->labeltFAW_Ticks->setText(emptyValue);
    ui->spinBoxtCCD_L_WTR->setValue(0);
    ui->spinBoxtCCD_L_WTR_LCLK->setValue(0);
    ui->labeltCCD_L_WTR_Ticks->setText(emptyValue);
    ui->spinBoxtCCD_S_WTR->setValue(0);
    ui->spinBoxtCCD_S_WTR_LCLK->setValue(0);
    ui->labeltCCD_S_WTR_Ticks->setText(emptyValue);
    ui->spinBoxtRTP->setValue(0);
    ui->spinBoxtRTP_LCLK->setValue(0);
    ui->labeltRTP_Ticks->setText(emptyValue);
}

void MainWindow::reloadUI(){
    // TODO
    ui->spinMinCycleTime->setValue(spd->getMinCycleTime());
    ui->spinMaxCycleTime->setValue(spd->getMaxCycleTime());

    const unsigned int frequency = spd->getFrequency();
    QString frequencyStr = QString::number(spd->getFrequency()) + " MHz";
    QString mtStr = QString::number(spd->getMT()) + " MT/s";

    ui->labelFrequencyValue->setText(frequencyStr);
    ui->labelMTValue->setText(mtStr);
    ui->cbCL20->setChecked(spd->getCLSupportedDDR5(20));
    ui->cbCL22->setChecked(spd->getCLSupportedDDR5(22));
    ui->cbCL24->setChecked(spd->getCLSupportedDDR5(24));
    ui->cbCL26->setChecked(spd->getCLSupportedDDR5(26));
    ui->cbCL28->setChecked(spd->getCLSupportedDDR5(28));
    ui->cbCL30->setChecked(spd->getCLSupportedDDR5(30));
    ui->cbCL32->setChecked(spd->getCLSupportedDDR5(32));
    ui->cbCL34->setChecked(spd->getCLSupportedDDR5(34));
    ui->cbCL36->setChecked(spd->getCLSupportedDDR5(36));
    ui->cbCL38->setChecked(spd->getCLSupportedDDR5(38));
    ui->cbCL40->setChecked(spd->getCLSupportedDDR5(40));
    ui->cbCL42->setChecked(spd->getCLSupportedDDR5(42));
    ui->cbCL44->setChecked(spd->getCLSupportedDDR5(44));
    ui->cbCL46->setChecked(spd->getCLSupportedDDR5(46));
    ui->cbCL48->setChecked(spd->getCLSupportedDDR5(48));
    ui->cbCL50->setChecked(spd->getCLSupportedDDR5(50));
    ui->cbCL52->setChecked(spd->getCLSupportedDDR5(52));
    ui->cbCL54->setChecked(spd->getCLSupportedDDR5(54));
    ui->cbCL56->setChecked(spd->getCLSupportedDDR5(56));
    ui->cbCL58->setChecked(spd->getCLSupportedDDR5(58));
    ui->cbCL60->setChecked(spd->getCLSupportedDDR5(60));
    ui->cbCL62->setChecked(spd->getCLSupportedDDR5(62));
    ui->cbCL64->setChecked(spd->getCLSupportedDDR5(64));
    ui->cbCL66->setChecked(spd->getCLSupportedDDR5(66));
    ui->cbCL68->setChecked(spd->getCLSupportedDDR5(68));
    ui->cbCL70->setChecked(spd->getCLSupportedDDR5(70));
    ui->cbCL72->setChecked(spd->getCLSupportedDDR5(72));
    ui->cbCL74->setChecked(spd->getCLSupportedDDR5(74));
    ui->cbCL76->setChecked(spd->getCLSupportedDDR5(76));
    ui->cbCL78->setChecked(spd->getCLSupportedDDR5(78));
    ui->cbCL80->setChecked(spd->getCLSupportedDDR5(80));
    ui->cbCL82->setChecked(spd->getCLSupportedDDR5(82));
    ui->cbCL84->setChecked(spd->getCLSupportedDDR5(84));
    ui->cbCL86->setChecked(spd->getCLSupportedDDR5(86));
    ui->cbCL88->setChecked(spd->getCLSupportedDDR5(88));
    ui->cbCL90->setChecked(spd->getCLSupportedDDR5(90));
    ui->cbCL92->setChecked(spd->getCLSupportedDDR5(92));
    ui->cbCL94->setChecked(spd->getCLSupportedDDR5(94));
    ui->cbCL96->setChecked(spd->getCLSupportedDDR5(96));
    ui->cbCL98->setChecked(spd->getCLSupportedDDR5(98));

    ui->spinBoxtAA->setValue(spd->gettAA());
    ui->labeltAA_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettAA(), frequency)));
    ui->spinBoxtRCD->setValue(spd->gettRCD());
    ui->labeltRCD_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRCD(), frequency)));
    ui->spinBoxtRP->setValue(spd->gettRP());
    ui->labeltRP_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRP(), frequency)));
    ui->spinBoxtRAS->setValue(spd->gettRAS());
    ui->labeltRAS_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRAS(), frequency)));
    ui->spinBoxtRC->setValue(spd->gettRC());
    ui->labeltRC_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRC(), frequency)));
    ui->spinBoxtWR->setValue(spd->gettWR());
    ui->labeltWR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettWR(), frequency)));
    ui->spinBoxtRFC1->setValue(spd->gettRFC1_slr());
    ui->labeltRFC1_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRFC1_slr(), frequency)));
    ui->spinBoxtRFC2->setValue(spd->gettRFC2_slr());
    ui->labeltRFC2_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRFC2_slr(), frequency)));
    ui->spinBoxtRFC->setValue(spd->gettRFCsb_slr());
    ui->labeltRFC_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRFCsb_slr(), frequency)));
    ui->spinBoxtRRD_L->setValue(spd->gettRRD_L());
    ui->spinBoxtRRD_L_LCLK->setValue(spd->gettRRD_L_lowerLimit());
    ui->labeltRRD_L_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRRD_L(), frequency)));
    ui->spinBoxtCCD_L->setValue(spd->gettCCD_L());
    ui->spinBoxtCCD_L_LCLK->setValue(spd->gettCCD_L_lowerLimit());
    ui->labeltCCD_L_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettCCD_L(), frequency)));
    ui->spinBoxtCCDL_L_WR->setValue(spd->gettCCD_L_WR());
    ui->spinBoxtCCDL_L_WR_LCLK->setValue(spd->gettCCD_L_WR_lowerLimit());
    ui->labeltCCDL_L_WR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettCCD_L_WR(), frequency)));
    ui->spinBoxtCCDL_L_WR2->setValue(spd->gettCCD_L_WR2());
    ui->spinBoxtCCDL_L_WR2_LCLK->setValue(spd->gettCCD_L_WR2_lowerLimit());
    ui->labeltCCDL_L_WR2_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettCCD_L_WR2(), frequency)));
    ui->spinBoxtFAW->setValue(spd->gettFAW());
    ui->spinBoxtFAW_LCLK->setValue(spd->gettFAW_lowerLimit());
    ui->labeltFAW_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettFAW(), frequency)));
    ui->spinBoxtCCD_L_WTR->setValue(spd->gettCCD_L_WTR());
    ui->spinBoxtCCD_L_WTR_LCLK->setValue(spd->gettCCD_L_WTR_lowerLimit());
    ui->labeltCCD_L_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettCCD_L_WTR(), frequency)));
    ui->spinBoxtCCD_S_WTR->setValue(spd->gettCCD_S_WTR());
    ui->spinBoxtCCD_S_WTR_LCLK->setValue(spd->gettCCD_S_WTR_lowerLimit());
    ui->labeltCCD_S_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettCCD_S_WTR(), frequency)));
    ui->spinBoxtRTP->setValue(spd->gettRTP());
    ui->spinBoxtRTP_LCLK->setValue(spd->gettRTP_lowerLimit());
    ui->labeltRTP_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRTP(), frequency)));
}
