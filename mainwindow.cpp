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

        if (contents.length() != DDR5SPD::eepromSize) {
            // TODO error out
            return;
        }

        // TODO: Find proper way to do this
        DDR5SPD::RawSPD rawSPD = *reinterpret_cast<DDR5SPD::RawSPD*>(contents.data());
        spd = new DDR5SPD(rawSPD);

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
    ui->tabWidget->setCurrentWidget(ui->tabJEDEC);
    ui->tabJEDEC->setDisabled(true);
    ui->tabXMPP1->setDisabled(true);
    ui->tabXMPP2->setDisabled(true);
    ui->tabXMPP3->setDisabled(true);
    ui->tabXMPU1->setDisabled(true);
    ui->tabXMPU2->setDisabled(true);
}

void MainWindow::enableUI() {
    if(spd == nullptr) {
        return;
    }

    ui->tabJEDEC->activateWindow();
    ui->tabJEDEC->setDisabled(false);

    if (spd->isXMPPresent())
    {
        ui->tabXMPP1->setDisabled(false);
        ui->tabXMPP2->setDisabled(false);
        ui->tabXMPP3->setDisabled(false);
        ui->tabXMPU1->setDisabled(false);
        ui->tabXMPU2->setDisabled(false);
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
    ui->cbCL20->setChecked(spd->getCLSupported(false));
    ui->cbCL22->setChecked(spd->getCLSupported(false));
    ui->cbCL24->setChecked(spd->getCLSupported(false));
    ui->cbCL26->setChecked(spd->getCLSupported(false));
    ui->cbCL28->setChecked(spd->getCLSupported(false));
    ui->cbCL30->setChecked(spd->getCLSupported(false));
    ui->cbCL32->setChecked(spd->getCLSupported(false));
    ui->cbCL34->setChecked(spd->getCLSupported(false));
    ui->cbCL36->setChecked(spd->getCLSupported(false));
    ui->cbCL38->setChecked(spd->getCLSupported(false));
    ui->cbCL40->setChecked(spd->getCLSupported(false));
    ui->cbCL42->setChecked(spd->getCLSupported(false));
    ui->cbCL44->setChecked(spd->getCLSupported(false));
    ui->cbCL46->setChecked(spd->getCLSupported(false));
    ui->cbCL48->setChecked(spd->getCLSupported(false));
    ui->cbCL50->setChecked(spd->getCLSupported(false));
    ui->cbCL52->setChecked(spd->getCLSupported(false));
    ui->cbCL54->setChecked(spd->getCLSupported(false));
    ui->cbCL56->setChecked(spd->getCLSupported(false));
    ui->cbCL58->setChecked(spd->getCLSupported(false));
    ui->cbCL60->setChecked(spd->getCLSupported(false));
    ui->cbCL62->setChecked(spd->getCLSupported(false));
    ui->cbCL64->setChecked(spd->getCLSupported(false));
    ui->cbCL66->setChecked(spd->getCLSupported(false));
    ui->cbCL68->setChecked(spd->getCLSupported(false));
    ui->cbCL70->setChecked(spd->getCLSupported(false));
    ui->cbCL72->setChecked(spd->getCLSupported(false));
    ui->cbCL74->setChecked(spd->getCLSupported(false));
    ui->cbCL76->setChecked(spd->getCLSupported(false));
    ui->cbCL78->setChecked(spd->getCLSupported(false));
    ui->cbCL80->setChecked(spd->getCLSupported(false));
    ui->cbCL82->setChecked(spd->getCLSupported(false));
    ui->cbCL84->setChecked(spd->getCLSupported(false));
    ui->cbCL86->setChecked(spd->getCLSupported(false));
    ui->cbCL88->setChecked(spd->getCLSupported(false));
    ui->cbCL90->setChecked(spd->getCLSupported(false));
    ui->cbCL92->setChecked(spd->getCLSupported(false));
    ui->cbCL94->setChecked(spd->getCLSupported(false));
    ui->cbCL96->setChecked(spd->getCLSupported(false));
    ui->cbCL98->setChecked(spd->getCLSupported(false));

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

void MainWindow::reloadJEDECTab() {
    ui->spinMinCycleTime->setValue(spd->getMinCycleTime());
    ui->spinMaxCycleTime->setValue(spd->getMaxCycleTime());

    const unsigned int frequency = spd->getFrequency();
    QString frequencyStr = QString::number(spd->getFrequency()) + " MHz";
    QString mtStr = QString::number(spd->getMT()) + " MT/s";

    ui->labelFrequencyValue->setText(frequencyStr);
    ui->labelMTValue->setText(mtStr);
    ui->cbCL20->setChecked(spd->getCLSupported(20));
    ui->cbCL22->setChecked(spd->getCLSupported(22));
    ui->cbCL24->setChecked(spd->getCLSupported(24));
    ui->cbCL26->setChecked(spd->getCLSupported(26));
    ui->cbCL28->setChecked(spd->getCLSupported(28));
    ui->cbCL30->setChecked(spd->getCLSupported(30));
    ui->cbCL32->setChecked(spd->getCLSupported(32));
    ui->cbCL34->setChecked(spd->getCLSupported(34));
    ui->cbCL36->setChecked(spd->getCLSupported(36));
    ui->cbCL38->setChecked(spd->getCLSupported(38));
    ui->cbCL40->setChecked(spd->getCLSupported(40));
    ui->cbCL42->setChecked(spd->getCLSupported(42));
    ui->cbCL44->setChecked(spd->getCLSupported(44));
    ui->cbCL46->setChecked(spd->getCLSupported(46));
    ui->cbCL48->setChecked(spd->getCLSupported(48));
    ui->cbCL50->setChecked(spd->getCLSupported(50));
    ui->cbCL52->setChecked(spd->getCLSupported(52));
    ui->cbCL54->setChecked(spd->getCLSupported(54));
    ui->cbCL56->setChecked(spd->getCLSupported(56));
    ui->cbCL58->setChecked(spd->getCLSupported(58));
    ui->cbCL60->setChecked(spd->getCLSupported(60));
    ui->cbCL62->setChecked(spd->getCLSupported(62));
    ui->cbCL64->setChecked(spd->getCLSupported(64));
    ui->cbCL66->setChecked(spd->getCLSupported(66));
    ui->cbCL68->setChecked(spd->getCLSupported(68));
    ui->cbCL70->setChecked(spd->getCLSupported(70));
    ui->cbCL72->setChecked(spd->getCLSupported(72));
    ui->cbCL74->setChecked(spd->getCLSupported(74));
    ui->cbCL76->setChecked(spd->getCLSupported(76));
    ui->cbCL78->setChecked(spd->getCLSupported(78));
    ui->cbCL80->setChecked(spd->getCLSupported(80));
    ui->cbCL82->setChecked(spd->getCLSupported(82));
    ui->cbCL84->setChecked(spd->getCLSupported(84));
    ui->cbCL86->setChecked(spd->getCLSupported(86));
    ui->cbCL88->setChecked(spd->getCLSupported(88));
    ui->cbCL90->setChecked(spd->getCLSupported(90));
    ui->cbCL92->setChecked(spd->getCLSupported(92));
    ui->cbCL94->setChecked(spd->getCLSupported(94));
    ui->cbCL96->setChecked(spd->getCLSupported(96));
    ui->cbCL98->setChecked(spd->getCLSupported(98));

    unsigned int minCycleTime = spd->getMinCycleTime();

    ui->spinBoxtAA->setValue(spd->gettAA());
    ui->labeltAA_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettAA(), minCycleTime)));
    ui->spinBoxtRCD->setValue(spd->gettRCD());
    ui->labeltRCD_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRCD(), minCycleTime)));
    ui->spinBoxtRP->setValue(spd->gettRP());
    ui->labeltRP_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRP(), minCycleTime)));
    ui->spinBoxtRAS->setValue(spd->gettRAS());
    ui->labeltRAS_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRAS(), minCycleTime)));
    ui->spinBoxtRC->setValue(spd->gettRC());
    ui->labeltRC_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRC(), minCycleTime)));
    ui->spinBoxtWR->setValue(spd->gettWR());
    ui->labeltWR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettWR(), minCycleTime)));
    ui->spinBoxtRFC1->setValue(spd->gettRFC1_slr());
    ui->labeltRFC1_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRFC1_slr() * 1000, minCycleTime)));
    ui->spinBoxtRFC2->setValue(spd->gettRFC2_slr());
    ui->labeltRFC2_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRFC2_slr() * 1000, minCycleTime)));
    ui->spinBoxtRFC->setValue(spd->gettRFCsb_slr());
    ui->labeltRFC_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRFCsb_slr() * 1000, minCycleTime)));
    ui->spinBoxtRRD_L->setValue(spd->gettRRD_L());
    ui->spinBoxtRRD_L_LCLK->setValue(spd->gettRRD_L_lowerLimit());
    ui->labeltRRD_L_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRRD_L(), minCycleTime)));
    ui->spinBoxtCCD_L->setValue(spd->gettCCD_L());
    ui->spinBoxtCCD_L_LCLK->setValue(spd->gettCCD_L_lowerLimit());
    ui->labeltCCD_L_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettCCD_L(), minCycleTime)));
    ui->spinBoxtCCDL_L_WR->setValue(spd->gettCCD_L_WR());
    ui->spinBoxtCCDL_L_WR_LCLK->setValue(spd->gettCCD_L_WR_lowerLimit());
    ui->labeltCCDL_L_WR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettCCD_L_WR(), minCycleTime)));
    ui->spinBoxtCCDL_L_WR2->setValue(spd->gettCCD_L_WR2());
    ui->spinBoxtCCDL_L_WR2_LCLK->setValue(spd->gettCCD_L_WR2_lowerLimit());
    ui->labeltCCDL_L_WR2_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettCCD_L_WR2(), minCycleTime)));
    ui->spinBoxtFAW->setValue(spd->gettFAW());
    ui->spinBoxtFAW_LCLK->setValue(spd->gettFAW_lowerLimit());
    ui->labeltFAW_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettFAW(), minCycleTime)));
    ui->spinBoxtCCD_L_WTR->setValue(spd->gettCCD_L_WTR());
    ui->spinBoxtCCD_L_WTR_LCLK->setValue(spd->gettCCD_L_WTR_lowerLimit());
    ui->labeltCCD_L_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettCCD_L_WTR(), minCycleTime)));
    ui->spinBoxtCCD_S_WTR->setValue(spd->gettCCD_S_WTR());
    ui->spinBoxtCCD_S_WTR_LCLK->setValue(spd->gettCCD_S_WTR_lowerLimit());
    ui->labeltCCD_S_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettCCD_S_WTR(), minCycleTime)));
    ui->spinBoxtRTP->setValue(spd->gettRTP());
    ui->spinBoxtRTP_LCLK->setValue(spd->gettRTP_lowerLimit());
    ui->labeltRTP_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRTP(), minCycleTime)));
}

void MainWindow::reloadXMP1Tab() {
    ui->leProfileName_XMP1->setText(QString::fromStdString(spd->xmpBundle.getXMP1ProfileName()));

    // spd->xmpBundle.isXMP1Enabled()
    ui->cbCL20_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(20));
    ui->cbCL22_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(22));
    ui->cbCL24_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(24));
    ui->cbCL26_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(26));
    ui->cbCL28_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(28));
    ui->cbCL30_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(30));
    ui->cbCL32_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(32));
    ui->cbCL34_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(34));
    ui->cbCL36_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(36));
    ui->cbCL38_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(38));
    ui->cbCL40_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(40));
    ui->cbCL42_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(42));
    ui->cbCL44_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(44));
    ui->cbCL46_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(46));
    ui->cbCL48_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(48));
    ui->cbCL50_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(50));
    ui->cbCL52_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(52));
    ui->cbCL54_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(54));
    ui->cbCL56_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(56));
    ui->cbCL58_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(58));
    ui->cbCL60_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(60));
    ui->cbCL62_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(62));
    ui->cbCL64_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(64));
    ui->cbCL66_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(66));
    ui->cbCL68_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(68));
    ui->cbCL70_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(70));
    ui->cbCL72_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(72));
    ui->cbCL74_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(74));
    ui->cbCL76_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(76));
    ui->cbCL78_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(78));
    ui->cbCL80_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(80));
    ui->cbCL82_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(82));
    ui->cbCL84_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(84));
    ui->cbCL86_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(86));
    ui->cbCL88_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(88));
    ui->cbCL90_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(90));
    ui->cbCL92_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(92));
    ui->cbCL94_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(94));
    ui->cbCL96_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(96));
    ui->cbCL98_XMP1->setChecked(spd->xmpBundle.profile1.getCLSupported(98));
}

void MainWindow::reloadXMP2Tab() {
    ui->leProfileName_XMP2->setText(QString::fromStdString(spd->xmpBundle.getXMP2ProfileName()));

    ui->cbCL20_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(20));
    ui->cbCL22_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(22));
    ui->cbCL24_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(24));
    ui->cbCL26_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(26));
    ui->cbCL28_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(28));
    ui->cbCL30_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(30));
    ui->cbCL32_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(32));
    ui->cbCL34_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(34));
    ui->cbCL36_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(36));
    ui->cbCL38_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(38));
    ui->cbCL40_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(40));
    ui->cbCL42_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(42));
    ui->cbCL44_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(44));
    ui->cbCL46_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(46));
    ui->cbCL48_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(48));
    ui->cbCL50_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(50));
    ui->cbCL52_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(52));
    ui->cbCL54_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(54));
    ui->cbCL56_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(56));
    ui->cbCL58_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(58));
    ui->cbCL60_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(60));
    ui->cbCL62_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(62));
    ui->cbCL64_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(64));
    ui->cbCL66_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(66));
    ui->cbCL68_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(68));
    ui->cbCL70_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(70));
    ui->cbCL72_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(72));
    ui->cbCL74_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(74));
    ui->cbCL76_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(76));
    ui->cbCL78_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(78));
    ui->cbCL80_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(80));
    ui->cbCL82_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(82));
    ui->cbCL84_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(84));
    ui->cbCL86_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(86));
    ui->cbCL88_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(88));
    ui->cbCL90_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(90));
    ui->cbCL92_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(92));
    ui->cbCL94_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(94));
    ui->cbCL96_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(96));
    ui->cbCL98_XMP2->setChecked(spd->xmpBundle.profile2.getCLSupported(98));
}

void MainWindow::reloadXMP3Tab() {
    ui->leProfileName_XMP3->setText(QString::fromStdString(spd->xmpBundle.getXMP3ProfileName()));

    ui->cbCL20_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(20));
    ui->cbCL22_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(22));
    ui->cbCL24_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(24));
    ui->cbCL26_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(26));
    ui->cbCL28_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(28));
    ui->cbCL30_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(30));
    ui->cbCL32_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(32));
    ui->cbCL34_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(34));
    ui->cbCL36_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(36));
    ui->cbCL38_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(38));
    ui->cbCL40_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(40));
    ui->cbCL42_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(42));
    ui->cbCL44_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(44));
    ui->cbCL46_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(46));
    ui->cbCL48_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(48));
    ui->cbCL50_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(50));
    ui->cbCL52_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(52));
    ui->cbCL54_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(54));
    ui->cbCL56_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(56));
    ui->cbCL58_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(58));
    ui->cbCL60_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(60));
    ui->cbCL62_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(62));
    ui->cbCL64_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(64));
    ui->cbCL66_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(66));
    ui->cbCL68_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(68));
    ui->cbCL70_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(70));
    ui->cbCL72_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(72));
    ui->cbCL74_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(74));
    ui->cbCL76_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(76));
    ui->cbCL78_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(78));
    ui->cbCL80_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(80));
    ui->cbCL82_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(82));
    ui->cbCL84_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(84));
    ui->cbCL86_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(86));
    ui->cbCL88_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(88));
    ui->cbCL90_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(90));
    ui->cbCL92_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(92));
    ui->cbCL94_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(94));
    ui->cbCL96_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(96));
    ui->cbCL98_XMP3->setChecked(spd->xmpBundle.profile3.getCLSupported(98));
}

void MainWindow::reloadXMPU1Tab() {

}

void MainWindow::reloadXMPU2Tab() {

}

void MainWindow::reloadUI(){
    reloadJEDECTab();
    reloadXMP1Tab();
    reloadXMP2Tab();
    reloadXMP3Tab();
    reloadXMPU1Tab();
    reloadXMPU2Tab();
}
