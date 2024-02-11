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

    // File menu
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionSave, &QAction::enabledChanged, this, &MainWindow::saveFileEnabled);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::closeFile);
    connect(ui->actionClose, &QAction::enabledChanged, this, &MainWindow::closeFileEnabled);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exit);

    // XMP menu
    connect(ui->actionEnableXMPmagic, &QAction::triggered, this, &MainWindow::enableXMPMagicBits);
    connect(ui->actionDisableXMPmagic, &QAction::triggered, this, &MainWindow::disableXMPMagicBits);
    connect(ui->actionWipeXMPregion, &QAction::triggered, this, &MainWindow::wipeXMP);

    connect(ui->actionWipeProfile1, &QAction::triggered, this, &MainWindow::wipeXMPProfile1);
    connect(ui->actionWipeProfile2, &QAction::triggered, this, &MainWindow::wipeXMPProfile2);
    connect(ui->actionWipeProfile3, &QAction::triggered, this, &MainWindow::wipeXMPProfile3);
    connect(ui->actionWipeProfileU1, &QAction::triggered, this, &MainWindow::wipeXMPProfileU1);
    connect(ui->actionWipeProfileU2, &QAction::triggered, this, &MainWindow::wipeXMPProfileU2);

    connect(ui->actionLoadSampleProfile1, &QAction::triggered, this, &MainWindow::loadSampleXMPProfile1);
    connect(ui->actionLoadSampleProfile2, &QAction::triggered, this, &MainWindow::loadSampleXMPProfile2);
    connect(ui->actionLoadSampleProfile3, &QAction::triggered, this, &MainWindow::loadSampleXMPProfile3);
    connect(ui->actionLoadSampleProfileU1, &QAction::triggered, this, &MainWindow::loadSampleXMPProfileU1);
    connect(ui->actionLoadSampleProfileU2, &QAction::triggered, this, &MainWindow::loadSampleXMPProfileU2);
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
        DDR5SPD::SPD_Struct rawSPD = *reinterpret_cast<DDR5SPD::SPD_Struct*>(contents.data());
        spd = new DDR5SPD(rawSPD);

        enableUI();
        reloadUI();
    }
}

void MainWindow::saveFile(){
    if (spd != nullptr) {
        // Fix Checksums
        spd->fixCRC();
        if (spd->isXMPPresent()) {
            spd->xmpBundle.fixCRCs();
        }

        // Actually save
        QString fileName = QFileDialog::getSaveFileName(this, "Save File", QDir::currentPath(), "SPD Files (*.spd, *.bin);;All Files (*.*)");
        if (!fileName.isEmpty()) {
            // save contents to the selected file
            QFile file(fileName);

            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::critical(
                    this,
                    appName,
                    tr("Failed to save file.") );
            }

            if (file.isWritable()) {
                file.write(spd->getPointerToStruct(), DDR5SPD::eepromSize);
                file.close();
            } else {
                QMessageBox::critical(
                    this,
                    appName,
                    tr("Failed to save file (read only?).") );
            }
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

void MainWindow::wipeXMP() {
    spd->xmpBundle.wipe();
    reloadXMP1Tab();
    reloadXMP2Tab();
    reloadXMP3Tab();
    reloadXMPU1Tab();
    reloadXMPU2Tab();
}

void MainWindow::wipeXMPProfile1() {
    spd->xmpBundle.setXMP1Enabled(false);
    spd->xmpBundle.profile1.wipeProfile();
    reloadXMP1Tab();
}
void MainWindow::wipeXMPProfile2() {
    spd->xmpBundle.setXMP2Enabled(false);
    spd->xmpBundle.profile2.wipeProfile();
    reloadXMP2Tab();
}
void MainWindow::wipeXMPProfile3() {
    spd->xmpBundle.setXMP3Enabled(false);
    spd->xmpBundle.profile3.wipeProfile();
    reloadXMP3Tab();
}
void MainWindow::wipeXMPProfileU1() {
    spd->xmpBundle.profileUser1.wipeProfile();
    reloadXMPU1Tab();
}
void MainWindow::wipeXMPProfileU2() {
    spd->xmpBundle.profileUser2.wipeProfile();
    reloadXMPU2Tab();
}

void MainWindow::loadSampleXMPProfile1() {
    spd->xmpBundle.setXMP1Enabled(true);
    spd->xmpBundle.profile1.resetProfile();
    reloadXMP1Tab();
}

void MainWindow::loadSampleXMPProfile2() {
    spd->xmpBundle.setXMP2Enabled(true);
    spd->xmpBundle.profile2.resetProfile();
    reloadXMP2Tab();
}

void MainWindow::loadSampleXMPProfile3() {
    spd->xmpBundle.setXMP3Enabled(true);
    spd->xmpBundle.profile3.resetProfile();
    reloadXMP3Tab();
}

void MainWindow::loadSampleXMPProfileU1() {
    spd->xmpBundle.profileUser1.resetProfile();
    reloadXMPU1Tab();
}

void MainWindow::loadSampleXMPProfileU2() {
    spd->xmpBundle.profileUser2.resetProfile();
    reloadXMP2Tab();
}

void MainWindow::enableXMPMagicBits() {
    spd->xmpBundle.enableMagic();
}

void MainWindow::disableXMPMagicBits() {
    spd->xmpBundle.clearMagic();
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

void MainWindow::toggleUI(const bool status) {
    bool disabled = !status;

    ui->tabJEDEC->setDisabled(disabled);
    ui->tabXMPP1->setDisabled(disabled);
    ui->tabXMPP2->setDisabled(disabled);
    ui->tabXMPP3->setDisabled(disabled);
    ui->tabXMPU1->setDisabled(disabled);
    ui->tabXMPU2->setDisabled(disabled);

    ui->actionSave->setDisabled(disabled);
    ui->actionClose->setDisabled(disabled);
    ui->actionEnableXMPmagic->setDisabled(disabled);
    ui->actionDisableXMPmagic->setDisabled(disabled);
    ui->actionWipeXMPregion->setDisabled(disabled);
}

void MainWindow::toggleXMPUI(const bool status) {
    bool disabled = !status;

    ui->actionWipeProfile1->setDisabled(disabled);
    ui->actionWipeProfile2->setDisabled(disabled);
    ui->actionWipeProfile3->setDisabled(disabled);
    ui->actionWipeProfileU1->setDisabled(disabled);
    ui->actionWipeProfileU2->setDisabled(disabled);
    ui->actionLoadSampleProfile1->setDisabled(disabled);
    ui->actionLoadSampleProfile2->setDisabled(disabled);
    ui->actionLoadSampleProfile3->setDisabled(disabled);
    ui->actionLoadSampleProfileU1->setDisabled(disabled);
    ui->actionLoadSampleProfileU2->setDisabled(disabled);

    ui->tabXMPP1->setDisabled(disabled);
    ui->tabXMPP2->setDisabled(disabled);
    ui->tabXMPP3->setDisabled(disabled);
    ui->tabXMPU1->setDisabled(disabled);
    ui->tabXMPU2->setDisabled(disabled);
}

void MainWindow::disableUI() {
    ui->tabWidget->setCurrentWidget(ui->tabJEDEC);
    toggleUI(false);
    toggleXMPUI(false);
}

void MainWindow::enableUI() {
    if(spd == nullptr) {
        return;
    }

    // Menus
    toggleUI(true);

    if (spd->isXMPPresent())
    {
        toggleXMPUI(true);
    }

    // Go to JEDEC tab
    ui->tabJEDEC->activateWindow();
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
    // XMP Header
    ui->leProfileName_XMP1->setText(QString::fromStdString(spd->xmpBundle.getXMP1ProfileName()));
    ui->cbEnabled_XMP1->setChecked(spd->xmpBundle.isXMP1Enabled());

    // XMP Profile
    auto& xmp_profile = spd->xmpBundle.profile1;

    const unsigned int minCycleTime = xmp_profile.getMinCycleTime();
    ui->spinMinCycleTime_XMP1->setValue(minCycleTime);
    QString frequencyStr = QString::number(xmp_profile.getFrequency()) + " MHz";
    QString mtStr = QString::number(xmp_profile.getMT()) + " MT/s";
    ui->lFrequencyValue_XMP1->setText(frequencyStr);
    ui->lMTValue_XMP1->setText(mtStr);

    ui->cbDynamicMemBoost_XMP1->setChecked(xmp_profile.getIntelDynamicMemoryBoost());
    ui->cbRealTimeMemOC_XMP1->setChecked(xmp_profile.getRealTimeMemoryFrequencyOC());

    switch (xmp_profile.getCommandRate()) {
        default:
        case CommandRate::_1n:
            ui->cbCommandRate_XMP1->setCurrentIndex(1);
            break;

        case CommandRate::_2n:
            ui->cbCommandRate_XMP1->setCurrentIndex(2);
            break;

        case CommandRate::_3n:
            ui->cbCommandRate_XMP1->setCurrentIndex(3);
            break;
    }

    // Voltages
    ui->sbVDD_XMP1->setValue(xmp_profile.getVDD());
    ui->sbVDDQ_XMP1->setValue(xmp_profile.getVDDQ());
    ui->sbVPP_XMP1->setValue(xmp_profile.getVPP());
    ui->sbVmemctrl_XMP1->setValue(xmp_profile.getVMEMCtrl());

    // CAS
    ui->cbCL20_XMP1->setChecked(xmp_profile.getCLSupported(20));
    ui->cbCL22_XMP1->setChecked(xmp_profile.getCLSupported(22));
    ui->cbCL24_XMP1->setChecked(xmp_profile.getCLSupported(24));
    ui->cbCL26_XMP1->setChecked(xmp_profile.getCLSupported(26));
    ui->cbCL28_XMP1->setChecked(xmp_profile.getCLSupported(28));
    ui->cbCL30_XMP1->setChecked(xmp_profile.getCLSupported(30));
    ui->cbCL32_XMP1->setChecked(xmp_profile.getCLSupported(32));
    ui->cbCL34_XMP1->setChecked(xmp_profile.getCLSupported(34));
    ui->cbCL36_XMP1->setChecked(xmp_profile.getCLSupported(36));
    ui->cbCL38_XMP1->setChecked(xmp_profile.getCLSupported(38));
    ui->cbCL40_XMP1->setChecked(xmp_profile.getCLSupported(40));
    ui->cbCL42_XMP1->setChecked(xmp_profile.getCLSupported(42));
    ui->cbCL44_XMP1->setChecked(xmp_profile.getCLSupported(44));
    ui->cbCL46_XMP1->setChecked(xmp_profile.getCLSupported(46));
    ui->cbCL48_XMP1->setChecked(xmp_profile.getCLSupported(48));
    ui->cbCL50_XMP1->setChecked(xmp_profile.getCLSupported(50));
    ui->cbCL52_XMP1->setChecked(xmp_profile.getCLSupported(52));
    ui->cbCL54_XMP1->setChecked(xmp_profile.getCLSupported(54));
    ui->cbCL56_XMP1->setChecked(xmp_profile.getCLSupported(56));
    ui->cbCL58_XMP1->setChecked(xmp_profile.getCLSupported(58));
    ui->cbCL60_XMP1->setChecked(xmp_profile.getCLSupported(60));
    ui->cbCL62_XMP1->setChecked(xmp_profile.getCLSupported(62));
    ui->cbCL64_XMP1->setChecked(xmp_profile.getCLSupported(64));
    ui->cbCL66_XMP1->setChecked(xmp_profile.getCLSupported(66));
    ui->cbCL68_XMP1->setChecked(xmp_profile.getCLSupported(68));
    ui->cbCL70_XMP1->setChecked(xmp_profile.getCLSupported(70));
    ui->cbCL72_XMP1->setChecked(xmp_profile.getCLSupported(72));
    ui->cbCL74_XMP1->setChecked(xmp_profile.getCLSupported(74));
    ui->cbCL76_XMP1->setChecked(xmp_profile.getCLSupported(76));
    ui->cbCL78_XMP1->setChecked(xmp_profile.getCLSupported(78));
    ui->cbCL80_XMP1->setChecked(xmp_profile.getCLSupported(80));
    ui->cbCL82_XMP1->setChecked(xmp_profile.getCLSupported(82));
    ui->cbCL84_XMP1->setChecked(xmp_profile.getCLSupported(84));
    ui->cbCL86_XMP1->setChecked(xmp_profile.getCLSupported(86));
    ui->cbCL88_XMP1->setChecked(xmp_profile.getCLSupported(88));
    ui->cbCL90_XMP1->setChecked(xmp_profile.getCLSupported(90));
    ui->cbCL92_XMP1->setChecked(xmp_profile.getCLSupported(92));
    ui->cbCL94_XMP1->setChecked(xmp_profile.getCLSupported(94));
    ui->cbCL96_XMP1->setChecked(xmp_profile.getCLSupported(96));
    ui->cbCL98_XMP1->setChecked(xmp_profile.getCLSupported(98));

    ui->sbtAA_XMP1->setValue(xmp_profile.gettAA());
    ui->ltAA_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettAA(), minCycleTime)));
    ui->sbtRCD_XMP1->setValue(xmp_profile.gettRCD());
    ui->ltRCD_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRCD(), minCycleTime)));
    ui->sbtRP_XMP1->setValue(xmp_profile.gettRP());
    ui->ltRP_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRP(), minCycleTime)));
    ui->sbtRAS_XMP1->setValue(xmp_profile.gettRAS());
    ui->ltRAS_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRAS(), minCycleTime)));
    ui->sbtRC_XMP1->setValue(xmp_profile.gettRC());
    ui->ltRC_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRC(), minCycleTime)));
    ui->sbtWR_XMP1->setValue(xmp_profile.gettWR());
    ui->ltWR_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettWR(), minCycleTime)));
    ui->sbtRFC1_XMP1->setValue(xmp_profile.gettRFC1());
    ui->ltRFC1_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRFC1() * 1000, minCycleTime)));
    ui->sbtRFC2_XMP1->setValue(xmp_profile.gettRFC2());
    ui->ltRFC2_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRFC2() * 1000, minCycleTime)));
    ui->sbtRFC_XMP1->setValue(xmp_profile.gettRFC());
    ui->ltRFC_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRFC() * 1000, minCycleTime)));
    ui->sbtRRD_L_XMP1->setValue(xmp_profile.gettRRD_L());
    ui->sbtRRD_L_LCLK_XMP1->setValue(xmp_profile.gettRRD_L_lowerLimit());
    ui->ltRRD_L_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRRD_L(), minCycleTime)));
    ui->sbtCCD_L_XMP1->setValue(xmp_profile.gettCCD_L());
    ui->sbtCCD_L_LCLK_XMP1->setValue(xmp_profile.gettCCD_L_lowerLimit());
    ui->ltCCD_L_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L(), minCycleTime)));
    ui->sbtCCDL_L_WR_XMP1->setValue(xmp_profile.gettCCD_L_WR());
    ui->sbtCCDL_L_WR_LCLK_XMP1->setValue(xmp_profile.gettCCD_L_WR_lowerLimit());
    ui->ltCCDL_L_WR_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L_WR(), minCycleTime)));
    ui->sbtCCDL_L_WR2_XMP1->setValue(xmp_profile.gettCCD_L_WR2());
    ui->sbtCCDL_L_WR2_LCLK_XMP1->setValue(xmp_profile.gettCCD_L_WR2_lowerLimit());
    ui->ltCCDL_L_WR2_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L_WR2(), minCycleTime)));
    ui->sbtFAW_XMP1->setValue(xmp_profile.gettFAW());
    ui->sbtFAW_LCLK_XMP1->setValue(xmp_profile.gettFAW_lowerLimit());
    ui->ltFAW_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettFAW(), minCycleTime)));
    ui->sbtCCD_L_WTR_XMP1->setValue(xmp_profile.gettCCD_L_WTR());
    ui->sbtCCD_L_WTR_LCLK_XMP1->setValue(xmp_profile.gettCCD_L_WTR_lowerLimit());
    ui->ltCCD_L_WTR_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L_WTR(), minCycleTime)));
    ui->sbtCCD_S_WTR_XMP1->setValue(xmp_profile.gettCCD_S_WTR());
    ui->sbtCCD_S_WTR_LCLK_XMP1->setValue(xmp_profile.gettCCD_S_WTR_lowerLimit());
    ui->ltCCD_S_WTR_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_S_WTR(), minCycleTime)));
    ui->sbtRTP_XMP1->setValue(xmp_profile.gettRTP());
    ui->sbtRTP_LCLK_XMP1->setValue(xmp_profile.gettRTP_lowerLimit());
    ui->ltRTP_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRTP(), minCycleTime)));
}

void MainWindow::reloadXMP2Tab() {
    // XMP Header
    ui->leProfileName_XMP2->setText(QString::fromStdString(spd->xmpBundle.getXMP2ProfileName()));
    ui->cbEnabled_XMP2->setChecked(spd->xmpBundle.isXMP2Enabled());

    // XMP Profile
    auto& xmp_profile = spd->xmpBundle.profile2;

    const unsigned int minCycleTime = xmp_profile.getMinCycleTime();
    ui->spinMinCycleTime_XMP2->setValue(minCycleTime);
    QString frequencyStr = QString::number(xmp_profile.getFrequency()) + " MHz";
    QString mtStr = QString::number(xmp_profile.getMT()) + " MT/s";
    ui->lFrequencyValue_XMP2->setText(frequencyStr);
    ui->lMTValue_XMP2->setText(mtStr);

    ui->cbDynamicMemBoost_XMP2->setChecked(xmp_profile.getIntelDynamicMemoryBoost());
    ui->cbRealTimeMemOC_XMP2->setChecked(xmp_profile.getRealTimeMemoryFrequencyOC());
    // ui->cbCommandRate_XMP2->setCurrentIndex(xmp_profile.getCommandRate());

    switch (xmp_profile.getCommandRate()) {
    default:
    case CommandRate::_1n:
            ui->cbCommandRate_XMP2->setCurrentIndex(1);
            break;

    case CommandRate::_2n:
            ui->cbCommandRate_XMP2->setCurrentIndex(2);
            break;

    case CommandRate::_3n:
            ui->cbCommandRate_XMP2->setCurrentIndex(3);
            break;
    }

    // Voltages
    ui->sbVDD_XMP2->setValue(xmp_profile.getVDD());
    ui->sbVDDQ_XMP2->setValue(xmp_profile.getVDDQ());
    ui->sbVPP_XMP2->setValue(xmp_profile.getVPP());
    ui->sbVmemctrl_XMP2->setValue(xmp_profile.getVMEMCtrl());

    // CAS
    ui->cbCL20_XMP2->setChecked(xmp_profile.getCLSupported(20));
    ui->cbCL22_XMP2->setChecked(xmp_profile.getCLSupported(22));
    ui->cbCL24_XMP2->setChecked(xmp_profile.getCLSupported(24));
    ui->cbCL26_XMP2->setChecked(xmp_profile.getCLSupported(26));
    ui->cbCL28_XMP2->setChecked(xmp_profile.getCLSupported(28));
    ui->cbCL30_XMP2->setChecked(xmp_profile.getCLSupported(30));
    ui->cbCL32_XMP2->setChecked(xmp_profile.getCLSupported(32));
    ui->cbCL34_XMP2->setChecked(xmp_profile.getCLSupported(34));
    ui->cbCL36_XMP2->setChecked(xmp_profile.getCLSupported(36));
    ui->cbCL38_XMP2->setChecked(xmp_profile.getCLSupported(38));
    ui->cbCL40_XMP2->setChecked(xmp_profile.getCLSupported(40));
    ui->cbCL42_XMP2->setChecked(xmp_profile.getCLSupported(42));
    ui->cbCL44_XMP2->setChecked(xmp_profile.getCLSupported(44));
    ui->cbCL46_XMP2->setChecked(xmp_profile.getCLSupported(46));
    ui->cbCL48_XMP2->setChecked(xmp_profile.getCLSupported(48));
    ui->cbCL50_XMP2->setChecked(xmp_profile.getCLSupported(50));
    ui->cbCL52_XMP2->setChecked(xmp_profile.getCLSupported(52));
    ui->cbCL54_XMP2->setChecked(xmp_profile.getCLSupported(54));
    ui->cbCL56_XMP2->setChecked(xmp_profile.getCLSupported(56));
    ui->cbCL58_XMP2->setChecked(xmp_profile.getCLSupported(58));
    ui->cbCL60_XMP2->setChecked(xmp_profile.getCLSupported(60));
    ui->cbCL62_XMP2->setChecked(xmp_profile.getCLSupported(62));
    ui->cbCL64_XMP2->setChecked(xmp_profile.getCLSupported(64));
    ui->cbCL66_XMP2->setChecked(xmp_profile.getCLSupported(66));
    ui->cbCL68_XMP2->setChecked(xmp_profile.getCLSupported(68));
    ui->cbCL70_XMP2->setChecked(xmp_profile.getCLSupported(70));
    ui->cbCL72_XMP2->setChecked(xmp_profile.getCLSupported(72));
    ui->cbCL74_XMP2->setChecked(xmp_profile.getCLSupported(74));
    ui->cbCL76_XMP2->setChecked(xmp_profile.getCLSupported(76));
    ui->cbCL78_XMP2->setChecked(xmp_profile.getCLSupported(78));
    ui->cbCL80_XMP2->setChecked(xmp_profile.getCLSupported(80));
    ui->cbCL82_XMP2->setChecked(xmp_profile.getCLSupported(82));
    ui->cbCL84_XMP2->setChecked(xmp_profile.getCLSupported(84));
    ui->cbCL86_XMP2->setChecked(xmp_profile.getCLSupported(86));
    ui->cbCL88_XMP2->setChecked(xmp_profile.getCLSupported(88));
    ui->cbCL90_XMP2->setChecked(xmp_profile.getCLSupported(90));
    ui->cbCL92_XMP2->setChecked(xmp_profile.getCLSupported(92));
    ui->cbCL94_XMP2->setChecked(xmp_profile.getCLSupported(94));
    ui->cbCL96_XMP2->setChecked(xmp_profile.getCLSupported(96));
    ui->cbCL98_XMP2->setChecked(xmp_profile.getCLSupported(98));

    ui->sbtAA_XMP2->setValue(xmp_profile.gettAA());
    ui->ltAA_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettAA(), minCycleTime)));
    ui->sbtRCD_XMP2->setValue(xmp_profile.gettRCD());
    ui->ltRCD_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRCD(), minCycleTime)));
    ui->sbtRP_XMP2->setValue(xmp_profile.gettRP());
    ui->ltRP_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRP(), minCycleTime)));
    ui->sbtRAS_XMP2->setValue(xmp_profile.gettRAS());
    ui->ltRAS_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRAS(), minCycleTime)));
    ui->sbtRC_XMP2->setValue(xmp_profile.gettRC());
    ui->ltRC_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRC(), minCycleTime)));
    ui->sbtWR_XMP2->setValue(xmp_profile.gettWR());
    ui->ltWR_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettWR(), minCycleTime)));
    ui->sbtRFC1_XMP2->setValue(xmp_profile.gettRFC1());
    ui->ltRFC1_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRFC1() * 1000, minCycleTime)));
    ui->sbtRFC2_XMP2->setValue(xmp_profile.gettRFC2());
    ui->ltRFC2_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRFC2() * 1000, minCycleTime)));
    ui->sbtRFC_XMP2->setValue(xmp_profile.gettRFC());
    ui->ltRFC_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRFC() * 1000, minCycleTime)));
    ui->sbtRRD_L_XMP2->setValue(xmp_profile.gettRRD_L());
    ui->sbtRRD_L_LCLK_XMP2->setValue(xmp_profile.gettRRD_L_lowerLimit());
    ui->ltRRD_L_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRRD_L(), minCycleTime)));
    ui->sbtCCD_L_XMP2->setValue(xmp_profile.gettCCD_L());
    ui->sbtCCD_L_LCLK_XMP2->setValue(xmp_profile.gettCCD_L_lowerLimit());
    ui->ltCCD_L_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L(), minCycleTime)));
    ui->sbtCCDL_L_WR_XMP2->setValue(xmp_profile.gettCCD_L_WR());
    ui->sbtCCDL_L_WR_LCLK_XMP2->setValue(xmp_profile.gettCCD_L_WR_lowerLimit());
    ui->ltCCDL_L_WR_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L_WR(), minCycleTime)));
    ui->sbtCCDL_L_WR2_XMP2->setValue(xmp_profile.gettCCD_L_WR2());
    ui->sbtCCDL_L_WR2_LCLK_XMP2->setValue(xmp_profile.gettCCD_L_WR2_lowerLimit());
    ui->ltCCDL_L_WR2_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L_WR2(), minCycleTime)));
    ui->sbtFAW_XMP2->setValue(xmp_profile.gettFAW());
    ui->sbtFAW_LCLK_XMP2->setValue(xmp_profile.gettFAW_lowerLimit());
    ui->ltFAW_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettFAW(), minCycleTime)));
    ui->sbtCCD_L_WTR_XMP2->setValue(xmp_profile.gettCCD_L_WTR());
    ui->sbtCCD_L_WTR_LCLK_XMP2->setValue(xmp_profile.gettCCD_L_WTR_lowerLimit());
    ui->ltCCD_L_WTR_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L_WTR(), minCycleTime)));
    ui->sbtCCD_S_WTR_XMP2->setValue(xmp_profile.gettCCD_S_WTR());
    ui->sbtCCD_S_WTR_LCLK_XMP2->setValue(xmp_profile.gettCCD_S_WTR_lowerLimit());
    ui->ltCCD_S_WTR_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_S_WTR(), minCycleTime)));
    ui->sbtRTP_XMP2->setValue(xmp_profile.gettRTP());
    ui->sbtRTP_LCLK_XMP2->setValue(xmp_profile.gettRTP_lowerLimit());
    ui->ltRTP_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRTP(), minCycleTime)));
}

void MainWindow::reloadXMP3Tab() {
    // XMP Header
    ui->leProfileName_XMP3->setText(QString::fromStdString(spd->xmpBundle.getXMP3ProfileName()));
    ui->cbEnabled_XMP3->setChecked(spd->xmpBundle.isXMP3Enabled());

    // XMP Profile
    auto& xmp_profile = spd->xmpBundle.profile3;

    const unsigned int minCycleTime = xmp_profile.getMinCycleTime();
    ui->spinMinCycleTime_XMP3->setValue(minCycleTime);
    QString frequencyStr = QString::number(xmp_profile.getFrequency()) + " MHz";
    QString mtStr = QString::number(xmp_profile.getMT()) + " MT/s";
    ui->lFrequencyValue_XMP3->setText(frequencyStr);
    ui->lMTValue_XMP3->setText(mtStr);

    ui->cbDynamicMemBoost_XMP3->setChecked(xmp_profile.getIntelDynamicMemoryBoost());
    ui->cbRealTimeMemOC_XMP3->setChecked(xmp_profile.getRealTimeMemoryFrequencyOC());
    // ui->cbCommandRate_XMP3->setCurrentIndex(xmp_profile.getCommandRate());

    switch (xmp_profile.getCommandRate()) {
    default:
    case CommandRate::_1n:
            ui->cbCommandRate_XMP3->setCurrentIndex(1);
            break;

    case CommandRate::_2n:
            ui->cbCommandRate_XMP3->setCurrentIndex(2);
            break;

    case CommandRate::_3n:
            ui->cbCommandRate_XMP3->setCurrentIndex(3);
            break;
    }

    // Voltages
    ui->sbVDD_XMP3->setValue(xmp_profile.getVDD());
    ui->sbVDDQ_XMP3->setValue(xmp_profile.getVDDQ());
    ui->sbVPP_XMP3->setValue(xmp_profile.getVPP());
    ui->sbVmemctrl_XMP3->setValue(xmp_profile.getVMEMCtrl());

    // CAS
    ui->cbCL20_XMP3->setChecked(xmp_profile.getCLSupported(20));
    ui->cbCL22_XMP3->setChecked(xmp_profile.getCLSupported(22));
    ui->cbCL24_XMP3->setChecked(xmp_profile.getCLSupported(24));
    ui->cbCL26_XMP3->setChecked(xmp_profile.getCLSupported(26));
    ui->cbCL28_XMP3->setChecked(xmp_profile.getCLSupported(28));
    ui->cbCL30_XMP3->setChecked(xmp_profile.getCLSupported(30));
    ui->cbCL32_XMP3->setChecked(xmp_profile.getCLSupported(32));
    ui->cbCL34_XMP3->setChecked(xmp_profile.getCLSupported(34));
    ui->cbCL36_XMP3->setChecked(xmp_profile.getCLSupported(36));
    ui->cbCL38_XMP3->setChecked(xmp_profile.getCLSupported(38));
    ui->cbCL40_XMP3->setChecked(xmp_profile.getCLSupported(40));
    ui->cbCL42_XMP3->setChecked(xmp_profile.getCLSupported(42));
    ui->cbCL44_XMP3->setChecked(xmp_profile.getCLSupported(44));
    ui->cbCL46_XMP3->setChecked(xmp_profile.getCLSupported(46));
    ui->cbCL48_XMP3->setChecked(xmp_profile.getCLSupported(48));
    ui->cbCL50_XMP3->setChecked(xmp_profile.getCLSupported(50));
    ui->cbCL52_XMP3->setChecked(xmp_profile.getCLSupported(52));
    ui->cbCL54_XMP3->setChecked(xmp_profile.getCLSupported(54));
    ui->cbCL56_XMP3->setChecked(xmp_profile.getCLSupported(56));
    ui->cbCL58_XMP3->setChecked(xmp_profile.getCLSupported(58));
    ui->cbCL60_XMP3->setChecked(xmp_profile.getCLSupported(60));
    ui->cbCL62_XMP3->setChecked(xmp_profile.getCLSupported(62));
    ui->cbCL64_XMP3->setChecked(xmp_profile.getCLSupported(64));
    ui->cbCL66_XMP3->setChecked(xmp_profile.getCLSupported(66));
    ui->cbCL68_XMP3->setChecked(xmp_profile.getCLSupported(68));
    ui->cbCL70_XMP3->setChecked(xmp_profile.getCLSupported(70));
    ui->cbCL72_XMP3->setChecked(xmp_profile.getCLSupported(72));
    ui->cbCL74_XMP3->setChecked(xmp_profile.getCLSupported(74));
    ui->cbCL76_XMP3->setChecked(xmp_profile.getCLSupported(76));
    ui->cbCL78_XMP3->setChecked(xmp_profile.getCLSupported(78));
    ui->cbCL80_XMP3->setChecked(xmp_profile.getCLSupported(80));
    ui->cbCL82_XMP3->setChecked(xmp_profile.getCLSupported(82));
    ui->cbCL84_XMP3->setChecked(xmp_profile.getCLSupported(84));
    ui->cbCL86_XMP3->setChecked(xmp_profile.getCLSupported(86));
    ui->cbCL88_XMP3->setChecked(xmp_profile.getCLSupported(88));
    ui->cbCL90_XMP3->setChecked(xmp_profile.getCLSupported(90));
    ui->cbCL92_XMP3->setChecked(xmp_profile.getCLSupported(92));
    ui->cbCL94_XMP3->setChecked(xmp_profile.getCLSupported(94));
    ui->cbCL96_XMP3->setChecked(xmp_profile.getCLSupported(96));
    ui->cbCL98_XMP3->setChecked(xmp_profile.getCLSupported(98));

    ui->sbtAA_XMP3->setValue(xmp_profile.gettAA());
    ui->ltAA_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettAA(), minCycleTime)));
    ui->sbtRCD_XMP3->setValue(xmp_profile.gettRCD());
    ui->ltRCD_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRCD(), minCycleTime)));
    ui->sbtRP_XMP3->setValue(xmp_profile.gettRP());
    ui->ltRP_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRP(), minCycleTime)));
    ui->sbtRAS_XMP3->setValue(xmp_profile.gettRAS());
    ui->ltRAS_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRAS(), minCycleTime)));
    ui->sbtRC_XMP3->setValue(xmp_profile.gettRC());
    ui->ltRC_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRC(), minCycleTime)));
    ui->sbtWR_XMP3->setValue(xmp_profile.gettWR());
    ui->ltWR_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettWR(), minCycleTime)));
    ui->sbtRFC1_XMP3->setValue(xmp_profile.gettRFC1());
    ui->ltRFC1_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRFC1() * 1000, minCycleTime)));
    ui->sbtRFC2_XMP3->setValue(xmp_profile.gettRFC2());
    ui->ltRFC2_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRFC2() * 1000, minCycleTime)));
    ui->sbtRFC_XMP3->setValue(xmp_profile.gettRFC());
    ui->ltRFC_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRFC() * 1000, minCycleTime)));
    ui->sbtRRD_L_XMP3->setValue(xmp_profile.gettRRD_L());
    ui->sbtRRD_L_LCLK_XMP3->setValue(xmp_profile.gettRRD_L_lowerLimit());
    ui->ltRRD_L_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRRD_L(), minCycleTime)));
    ui->sbtCCD_L_XMP3->setValue(xmp_profile.gettCCD_L());
    ui->sbtCCD_L_LCLK_XMP3->setValue(xmp_profile.gettCCD_L_lowerLimit());
    ui->ltCCD_L_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L(), minCycleTime)));
    ui->sbtCCDL_L_WR_XMP3->setValue(xmp_profile.gettCCD_L_WR());
    ui->sbtCCDL_L_WR_LCLK_XMP3->setValue(xmp_profile.gettCCD_L_WR_lowerLimit());
    ui->ltCCDL_L_WR_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L_WR(), minCycleTime)));
    ui->sbtCCDL_L_WR2_XMP3->setValue(xmp_profile.gettCCD_L_WR2());
    ui->sbtCCDL_L_WR2_LCLK_XMP3->setValue(xmp_profile.gettCCD_L_WR2_lowerLimit());
    ui->ltCCDL_L_WR2_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L_WR2(), minCycleTime)));
    ui->sbtFAW_XMP3->setValue(xmp_profile.gettFAW());
    ui->sbtFAW_LCLK_XMP3->setValue(xmp_profile.gettFAW_lowerLimit());
    ui->ltFAW_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettFAW(), minCycleTime)));
    ui->sbtCCD_L_WTR_XMP3->setValue(xmp_profile.gettCCD_L_WTR());
    ui->sbtCCD_L_WTR_LCLK_XMP3->setValue(xmp_profile.gettCCD_L_WTR_lowerLimit());
    ui->ltCCD_L_WTR_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L_WTR(), minCycleTime)));
    ui->sbtCCD_S_WTR_XMP3->setValue(xmp_profile.gettCCD_S_WTR());
    ui->sbtCCD_S_WTR_LCLK_XMP3->setValue(xmp_profile.gettCCD_S_WTR_lowerLimit());
    ui->ltCCD_S_WTR_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_S_WTR(), minCycleTime)));
    ui->sbtRTP_XMP3->setValue(xmp_profile.gettRTP());
    ui->sbtRTP_LCLK_XMP3->setValue(xmp_profile.gettRTP_lowerLimit());
    ui->ltRTP_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRTP(), minCycleTime)));
}

void MainWindow::reloadXMPU1Tab() {
    // ui->cbEnabled_XMPU1->setChecked(spd->xmpBundle.isXMP1Enabled());

    // XMP Profile
    auto& xmp_profile = spd->xmpBundle.profileUser1;

    const unsigned int minCycleTime = xmp_profile.getMinCycleTime();
    ui->spinMinCycleTime_XMPU1->setValue(minCycleTime);
    QString frequencyStr = QString::number(xmp_profile.getFrequency()) + " MHz";
    QString mtStr = QString::number(xmp_profile.getMT()) + " MT/s";
    ui->lFrequencyValue_XMPU1->setText(frequencyStr);
    ui->lMTValue_XMPU1->setText(mtStr);

    ui->cbDynamicMemBoost_XMPU1->setChecked(xmp_profile.getIntelDynamicMemoryBoost());
    ui->cbRealTimeMemOC_XMPU1->setChecked(xmp_profile.getRealTimeMemoryFrequencyOC());
    // ui->cbCommandRate_XMPU1->setCurrentIndex(xmp_profile.getCommandRate());

    switch (xmp_profile.getCommandRate()) {
    default:
    case CommandRate::_1n:
            ui->cbCommandRate_XMPU1->setCurrentIndex(1);
            break;

    case CommandRate::_2n:
            ui->cbCommandRate_XMPU1->setCurrentIndex(2);
            break;

    case CommandRate::_3n:
            ui->cbCommandRate_XMPU1->setCurrentIndex(3);
            break;
    }

    // Voltages
    ui->sbVDD_XMPU1->setValue(xmp_profile.getVDD());
    ui->sbVDDQ_XMPU1->setValue(xmp_profile.getVDDQ());
    ui->sbVPP_XMPU1->setValue(xmp_profile.getVPP());
    ui->sbVmemctrl_XMPU1->setValue(xmp_profile.getVMEMCtrl());

    // CAS
    ui->cbCL20_XMPU1->setChecked(xmp_profile.getCLSupported(20));
    ui->cbCL22_XMPU1->setChecked(xmp_profile.getCLSupported(22));
    ui->cbCL24_XMPU1->setChecked(xmp_profile.getCLSupported(24));
    ui->cbCL26_XMPU1->setChecked(xmp_profile.getCLSupported(26));
    ui->cbCL28_XMPU1->setChecked(xmp_profile.getCLSupported(28));
    ui->cbCL30_XMPU1->setChecked(xmp_profile.getCLSupported(30));
    ui->cbCL32_XMPU1->setChecked(xmp_profile.getCLSupported(32));
    ui->cbCL34_XMPU1->setChecked(xmp_profile.getCLSupported(34));
    ui->cbCL36_XMPU1->setChecked(xmp_profile.getCLSupported(36));
    ui->cbCL38_XMPU1->setChecked(xmp_profile.getCLSupported(38));
    ui->cbCL40_XMPU1->setChecked(xmp_profile.getCLSupported(40));
    ui->cbCL42_XMPU1->setChecked(xmp_profile.getCLSupported(42));
    ui->cbCL44_XMPU1->setChecked(xmp_profile.getCLSupported(44));
    ui->cbCL46_XMPU1->setChecked(xmp_profile.getCLSupported(46));
    ui->cbCL48_XMPU1->setChecked(xmp_profile.getCLSupported(48));
    ui->cbCL50_XMPU1->setChecked(xmp_profile.getCLSupported(50));
    ui->cbCL52_XMPU1->setChecked(xmp_profile.getCLSupported(52));
    ui->cbCL54_XMPU1->setChecked(xmp_profile.getCLSupported(54));
    ui->cbCL56_XMPU1->setChecked(xmp_profile.getCLSupported(56));
    ui->cbCL58_XMPU1->setChecked(xmp_profile.getCLSupported(58));
    ui->cbCL60_XMPU1->setChecked(xmp_profile.getCLSupported(60));
    ui->cbCL62_XMPU1->setChecked(xmp_profile.getCLSupported(62));
    ui->cbCL64_XMPU1->setChecked(xmp_profile.getCLSupported(64));
    ui->cbCL66_XMPU1->setChecked(xmp_profile.getCLSupported(66));
    ui->cbCL68_XMPU1->setChecked(xmp_profile.getCLSupported(68));
    ui->cbCL70_XMPU1->setChecked(xmp_profile.getCLSupported(70));
    ui->cbCL72_XMPU1->setChecked(xmp_profile.getCLSupported(72));
    ui->cbCL74_XMPU1->setChecked(xmp_profile.getCLSupported(74));
    ui->cbCL76_XMPU1->setChecked(xmp_profile.getCLSupported(76));
    ui->cbCL78_XMPU1->setChecked(xmp_profile.getCLSupported(78));
    ui->cbCL80_XMPU1->setChecked(xmp_profile.getCLSupported(80));
    ui->cbCL82_XMPU1->setChecked(xmp_profile.getCLSupported(82));
    ui->cbCL84_XMPU1->setChecked(xmp_profile.getCLSupported(84));
    ui->cbCL86_XMPU1->setChecked(xmp_profile.getCLSupported(86));
    ui->cbCL88_XMPU1->setChecked(xmp_profile.getCLSupported(88));
    ui->cbCL90_XMPU1->setChecked(xmp_profile.getCLSupported(90));
    ui->cbCL92_XMPU1->setChecked(xmp_profile.getCLSupported(92));
    ui->cbCL94_XMPU1->setChecked(xmp_profile.getCLSupported(94));
    ui->cbCL96_XMPU1->setChecked(xmp_profile.getCLSupported(96));
    ui->cbCL98_XMPU1->setChecked(xmp_profile.getCLSupported(98));

    ui->sbtAA_XMPU1->setValue(xmp_profile.gettAA());
    ui->ltAA_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettAA(), minCycleTime)));
    ui->sbtRCD_XMPU1->setValue(xmp_profile.gettRCD());
    ui->ltRCD_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRCD(), minCycleTime)));
    ui->sbtRP_XMPU1->setValue(xmp_profile.gettRP());
    ui->ltRP_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRP(), minCycleTime)));
    ui->sbtRAS_XMPU1->setValue(xmp_profile.gettRAS());
    ui->ltRAS_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRAS(), minCycleTime)));
    ui->sbtRC_XMPU1->setValue(xmp_profile.gettRC());
    ui->ltRC_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRC(), minCycleTime)));
    ui->sbtWR_XMPU1->setValue(xmp_profile.gettWR());
    ui->ltWR_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettWR(), minCycleTime)));
    ui->sbtRFC1_XMPU1->setValue(xmp_profile.gettRFC1());
    ui->ltRFC1_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRFC1() * 1000, minCycleTime)));
    ui->sbtRFC2_XMPU1->setValue(xmp_profile.gettRFC2());
    ui->ltRFC2_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRFC2() * 1000, minCycleTime)));
    ui->sbtRFC_XMPU1->setValue(xmp_profile.gettRFC());
    ui->ltRFC_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRFC() * 1000, minCycleTime)));
    ui->sbtRRD_L_XMPU1->setValue(xmp_profile.gettRRD_L());
    ui->sbtRRD_L_LCLK_XMPU1->setValue(xmp_profile.gettRRD_L_lowerLimit());
    ui->ltRRD_L_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRRD_L(), minCycleTime)));
    ui->sbtCCD_L_XMPU1->setValue(xmp_profile.gettCCD_L());
    ui->sbtCCD_L_LCLK_XMPU1->setValue(xmp_profile.gettCCD_L_lowerLimit());
    ui->ltCCD_L_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L(), minCycleTime)));
    ui->sbtCCDL_L_WR_XMPU1->setValue(xmp_profile.gettCCD_L_WR());
    ui->sbtCCDL_L_WR_LCLK_XMPU1->setValue(xmp_profile.gettCCD_L_WR_lowerLimit());
    ui->ltCCDL_L_WR_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L_WR(), minCycleTime)));
    ui->sbtCCDL_L_WR2_XMPU1->setValue(xmp_profile.gettCCD_L_WR2());
    ui->sbtCCDL_L_WR2_LCLK_XMPU1->setValue(xmp_profile.gettCCD_L_WR2_lowerLimit());
    ui->ltCCDL_L_WR2_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L_WR2(), minCycleTime)));
    ui->sbtFAW_XMPU1->setValue(xmp_profile.gettFAW());
    ui->sbtFAW_LCLK_XMPU1->setValue(xmp_profile.gettFAW_lowerLimit());
    ui->ltFAW_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettFAW(), minCycleTime)));
    ui->sbtCCD_L_WTR_XMPU1->setValue(xmp_profile.gettCCD_L_WTR());
    ui->sbtCCD_L_WTR_LCLK_XMPU1->setValue(xmp_profile.gettCCD_L_WTR_lowerLimit());
    ui->ltCCD_L_WTR_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L_WTR(), minCycleTime)));
    ui->sbtCCD_S_WTR_XMPU1->setValue(xmp_profile.gettCCD_S_WTR());
    ui->sbtCCD_S_WTR_LCLK_XMPU1->setValue(xmp_profile.gettCCD_S_WTR_lowerLimit());
    ui->ltCCD_S_WTR_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_S_WTR(), minCycleTime)));
    ui->sbtRTP_XMPU1->setValue(xmp_profile.gettRTP());
    ui->sbtRTP_LCLK_XMPU1->setValue(xmp_profile.gettRTP_lowerLimit());
    ui->ltRTP_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRTP(), minCycleTime)));
}

void MainWindow::reloadXMPU2Tab() {
    // ui->cbEnabled_XMPU2->setChecked(spd->xmpBundle.isXMP1Enabled());

    // XMP Profile
    auto& xmp_profile = spd->xmpBundle.profileUser2;

    const unsigned int minCycleTime = xmp_profile.getMinCycleTime();
    ui->spinMinCycleTime_XMPU2->setValue(minCycleTime);
    QString frequencyStr = QString::number(xmp_profile.getFrequency()) + " MHz";
    QString mtStr = QString::number(xmp_profile.getMT()) + " MT/s";
    ui->lFrequencyValue_XMPU2->setText(frequencyStr);
    ui->lMTValue_XMPU2->setText(mtStr);

    ui->cbDynamicMemBoost_XMPU2->setChecked(xmp_profile.getIntelDynamicMemoryBoost());
    ui->cbRealTimeMemOC_XMPU2->setChecked(xmp_profile.getRealTimeMemoryFrequencyOC());
    // ui->cbCommandRate_XMPU2->setCurrentIndex(xmp_profile.getCommandRate());

    switch (xmp_profile.getCommandRate()) {
    default:
    case CommandRate::_1n:
            ui->cbCommandRate_XMPU2->setCurrentIndex(1);
            break;

    case CommandRate::_2n:
            ui->cbCommandRate_XMPU2->setCurrentIndex(2);
            break;

    case CommandRate::_3n:
            ui->cbCommandRate_XMPU2->setCurrentIndex(3);
            break;
    }

    // Voltages
    ui->sbVDD_XMPU2->setValue(xmp_profile.getVDD());
    ui->sbVDDQ_XMPU2->setValue(xmp_profile.getVDDQ());
    ui->sbVPP_XMPU2->setValue(xmp_profile.getVPP());
    ui->sbVmemctrl_XMPU2->setValue(xmp_profile.getVMEMCtrl());

    // CAS
    ui->cbCL20_XMPU2->setChecked(xmp_profile.getCLSupported(20));
    ui->cbCL22_XMPU2->setChecked(xmp_profile.getCLSupported(22));
    ui->cbCL24_XMPU2->setChecked(xmp_profile.getCLSupported(24));
    ui->cbCL26_XMPU2->setChecked(xmp_profile.getCLSupported(26));
    ui->cbCL28_XMPU2->setChecked(xmp_profile.getCLSupported(28));
    ui->cbCL30_XMPU2->setChecked(xmp_profile.getCLSupported(30));
    ui->cbCL32_XMPU2->setChecked(xmp_profile.getCLSupported(32));
    ui->cbCL34_XMPU2->setChecked(xmp_profile.getCLSupported(34));
    ui->cbCL36_XMPU2->setChecked(xmp_profile.getCLSupported(36));
    ui->cbCL38_XMPU2->setChecked(xmp_profile.getCLSupported(38));
    ui->cbCL40_XMPU2->setChecked(xmp_profile.getCLSupported(40));
    ui->cbCL42_XMPU2->setChecked(xmp_profile.getCLSupported(42));
    ui->cbCL44_XMPU2->setChecked(xmp_profile.getCLSupported(44));
    ui->cbCL46_XMPU2->setChecked(xmp_profile.getCLSupported(46));
    ui->cbCL48_XMPU2->setChecked(xmp_profile.getCLSupported(48));
    ui->cbCL50_XMPU2->setChecked(xmp_profile.getCLSupported(50));
    ui->cbCL52_XMPU2->setChecked(xmp_profile.getCLSupported(52));
    ui->cbCL54_XMPU2->setChecked(xmp_profile.getCLSupported(54));
    ui->cbCL56_XMPU2->setChecked(xmp_profile.getCLSupported(56));
    ui->cbCL58_XMPU2->setChecked(xmp_profile.getCLSupported(58));
    ui->cbCL60_XMPU2->setChecked(xmp_profile.getCLSupported(60));
    ui->cbCL62_XMPU2->setChecked(xmp_profile.getCLSupported(62));
    ui->cbCL64_XMPU2->setChecked(xmp_profile.getCLSupported(64));
    ui->cbCL66_XMPU2->setChecked(xmp_profile.getCLSupported(66));
    ui->cbCL68_XMPU2->setChecked(xmp_profile.getCLSupported(68));
    ui->cbCL70_XMPU2->setChecked(xmp_profile.getCLSupported(70));
    ui->cbCL72_XMPU2->setChecked(xmp_profile.getCLSupported(72));
    ui->cbCL74_XMPU2->setChecked(xmp_profile.getCLSupported(74));
    ui->cbCL76_XMPU2->setChecked(xmp_profile.getCLSupported(76));
    ui->cbCL78_XMPU2->setChecked(xmp_profile.getCLSupported(78));
    ui->cbCL80_XMPU2->setChecked(xmp_profile.getCLSupported(80));
    ui->cbCL82_XMPU2->setChecked(xmp_profile.getCLSupported(82));
    ui->cbCL84_XMPU2->setChecked(xmp_profile.getCLSupported(84));
    ui->cbCL86_XMPU2->setChecked(xmp_profile.getCLSupported(86));
    ui->cbCL88_XMPU2->setChecked(xmp_profile.getCLSupported(88));
    ui->cbCL90_XMPU2->setChecked(xmp_profile.getCLSupported(90));
    ui->cbCL92_XMPU2->setChecked(xmp_profile.getCLSupported(92));
    ui->cbCL94_XMPU2->setChecked(xmp_profile.getCLSupported(94));
    ui->cbCL96_XMPU2->setChecked(xmp_profile.getCLSupported(96));
    ui->cbCL98_XMPU2->setChecked(xmp_profile.getCLSupported(98));

    ui->sbtAA_XMPU2->setValue(xmp_profile.gettAA());
    ui->ltAA_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettAA(), minCycleTime)));
    ui->sbtRCD_XMPU2->setValue(xmp_profile.gettRCD());
    ui->ltRCD_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRCD(), minCycleTime)));
    ui->sbtRP_XMPU2->setValue(xmp_profile.gettRP());
    ui->ltRP_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRP(), minCycleTime)));
    ui->sbtRAS_XMPU2->setValue(xmp_profile.gettRAS());
    ui->ltRAS_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRAS(), minCycleTime)));
    ui->sbtRC_XMPU2->setValue(xmp_profile.gettRC());
    ui->ltRC_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRC(), minCycleTime)));
    ui->sbtWR_XMPU2->setValue(xmp_profile.gettWR());
    ui->ltWR_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettWR(), minCycleTime)));
    ui->sbtRFC1_XMPU2->setValue(xmp_profile.gettRFC1());
    ui->ltRFC1_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRFC1() * 1000, minCycleTime)));
    ui->sbtRFC2_XMPU2->setValue(xmp_profile.gettRFC2());
    ui->ltRFC2_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRFC2() * 1000, minCycleTime)));
    ui->sbtRFC_XMPU2->setValue(xmp_profile.gettRFC());
    ui->ltRFC_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRFC() * 1000, minCycleTime)));
    ui->sbtRRD_L_XMPU2->setValue(xmp_profile.gettRRD_L());
    ui->sbtRRD_L_LCLK_XMPU2->setValue(xmp_profile.gettRRD_L_lowerLimit());
    ui->ltRRD_L_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRRD_L(), minCycleTime)));
    ui->sbtCCD_L_XMPU2->setValue(xmp_profile.gettCCD_L());
    ui->sbtCCD_L_LCLK_XMPU2->setValue(xmp_profile.gettCCD_L_lowerLimit());
    ui->ltCCD_L_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L(), minCycleTime)));
    ui->sbtCCDL_L_WR_XMPU2->setValue(xmp_profile.gettCCD_L_WR());
    ui->sbtCCDL_L_WR_LCLK_XMPU2->setValue(xmp_profile.gettCCD_L_WR_lowerLimit());
    ui->ltCCDL_L_WR_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L_WR(), minCycleTime)));
    ui->sbtCCDL_L_WR2_XMPU2->setValue(xmp_profile.gettCCD_L_WR2());
    ui->sbtCCDL_L_WR2_LCLK_XMPU2->setValue(xmp_profile.gettCCD_L_WR2_lowerLimit());
    ui->ltCCDL_L_WR2_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L_WR2(), minCycleTime)));
    ui->sbtFAW_XMPU2->setValue(xmp_profile.gettFAW());
    ui->sbtFAW_LCLK_XMPU2->setValue(xmp_profile.gettFAW_lowerLimit());
    ui->ltFAW_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettFAW(), minCycleTime)));
    ui->sbtCCD_L_WTR_XMPU2->setValue(xmp_profile.gettCCD_L_WTR());
    ui->sbtCCD_L_WTR_LCLK_XMPU2->setValue(xmp_profile.gettCCD_L_WTR_lowerLimit());
    ui->ltCCD_L_WTR_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_L_WTR(), minCycleTime)));
    ui->sbtCCD_S_WTR_XMPU2->setValue(xmp_profile.gettCCD_S_WTR());
    ui->sbtCCD_S_WTR_LCLK_XMPU2->setValue(xmp_profile.gettCCD_S_WTR_lowerLimit());
    ui->ltCCD_S_WTR_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettCCD_S_WTR(), minCycleTime)));
    ui->sbtRTP_XMPU2->setValue(xmp_profile.gettRTP());
    ui->sbtRTP_LCLK_XMPU2->setValue(xmp_profile.gettRTP_lowerLimit());
    ui->ltRTP_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(xmp_profile.gettRTP(), minCycleTime)));
}

void MainWindow::reloadUI(){
    reloadJEDECTab();
    reloadXMP1Tab();
    reloadXMP2Tab();
    reloadXMP3Tab();
    reloadXMPU1Tab();
    reloadXMPU2Tab();
}

// JEDEC
void MainWindow::on_spinMinCycleTime_editingFinished() {
    spd->setMinCycleTime(ui->spinMinCycleTime->value());
}

void MainWindow::on_spinMaxCycleTime_editingFinished() {
    spd->setMaxCycleTime(ui->spinMaxCycleTime->value());
}

void MainWindow::on_cbCL20_toggled(bool value) { spd->setCLSupported(20, value); }
void MainWindow::on_cbCL22_toggled(bool value) { spd->setCLSupported(22, value); }
void MainWindow::on_cbCL24_toggled(bool value) { spd->setCLSupported(24, value); }
void MainWindow::on_cbCL26_toggled(bool value) { spd->setCLSupported(26, value); }
void MainWindow::on_cbCL28_toggled(bool value) { spd->setCLSupported(28, value); }
void MainWindow::on_cbCL30_toggled(bool value) { spd->setCLSupported(30, value); }
void MainWindow::on_cbCL32_toggled(bool value) { spd->setCLSupported(32, value); }
void MainWindow::on_cbCL34_toggled(bool value) { spd->setCLSupported(34, value); }
void MainWindow::on_cbCL36_toggled(bool value) { spd->setCLSupported(36, value); }
void MainWindow::on_cbCL38_toggled(bool value) { spd->setCLSupported(38, value); }
void MainWindow::on_cbCL40_toggled(bool value) { spd->setCLSupported(40, value); }
void MainWindow::on_cbCL42_toggled(bool value) { spd->setCLSupported(42, value); }
void MainWindow::on_cbCL44_toggled(bool value) { spd->setCLSupported(44, value); }
void MainWindow::on_cbCL46_toggled(bool value) { spd->setCLSupported(46, value); }
void MainWindow::on_cbCL48_toggled(bool value) { spd->setCLSupported(48, value); }
void MainWindow::on_cbCL50_toggled(bool value) { spd->setCLSupported(50, value); }
void MainWindow::on_cbCL52_toggled(bool value) { spd->setCLSupported(52, value); }
void MainWindow::on_cbCL54_toggled(bool value) { spd->setCLSupported(54, value); }
void MainWindow::on_cbCL56_toggled(bool value) { spd->setCLSupported(56, value); }
void MainWindow::on_cbCL58_toggled(bool value) { spd->setCLSupported(58, value); }
void MainWindow::on_cbCL60_toggled(bool value) { spd->setCLSupported(60, value); }
void MainWindow::on_cbCL62_toggled(bool value) { spd->setCLSupported(62, value); }
void MainWindow::on_cbCL64_toggled(bool value) { spd->setCLSupported(64, value); }
void MainWindow::on_cbCL66_toggled(bool value) { spd->setCLSupported(66, value); }
void MainWindow::on_cbCL68_toggled(bool value) { spd->setCLSupported(68, value); }
void MainWindow::on_cbCL70_toggled(bool value) { spd->setCLSupported(70, value); }
void MainWindow::on_cbCL72_toggled(bool value) { spd->setCLSupported(72, value); }
void MainWindow::on_cbCL74_toggled(bool value) { spd->setCLSupported(74, value); }
void MainWindow::on_cbCL76_toggled(bool value) { spd->setCLSupported(76, value); }
void MainWindow::on_cbCL78_toggled(bool value) { spd->setCLSupported(78, value); }
void MainWindow::on_cbCL80_toggled(bool value) { spd->setCLSupported(80, value); }
void MainWindow::on_cbCL82_toggled(bool value) { spd->setCLSupported(82, value); }
void MainWindow::on_cbCL84_toggled(bool value) { spd->setCLSupported(84, value); }
void MainWindow::on_cbCL86_toggled(bool value) { spd->setCLSupported(86, value); }
void MainWindow::on_cbCL88_toggled(bool value) { spd->setCLSupported(88, value); }
void MainWindow::on_cbCL90_toggled(bool value) { spd->setCLSupported(90, value); }
void MainWindow::on_cbCL92_toggled(bool value) { spd->setCLSupported(92, value); }
void MainWindow::on_cbCL94_toggled(bool value) { spd->setCLSupported(94, value); }
void MainWindow::on_cbCL96_toggled(bool value) { spd->setCLSupported(96, value); }
void MainWindow::on_cbCL98_toggled(bool value) { spd->setCLSupported(98, value); }

void MainWindow::on_spinBoxtAA_editingFinished() {
    spd->settAA(ui->spinBoxtAA->value());
    ui->labeltAA_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettAA(), spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtRCD_editingFinished() {
    spd->settRCD(ui->spinBoxtRCD->value());
    ui->labeltRCD_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRCD(), spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtRP_editingFinished() {
    spd->settRP(ui->spinBoxtRP->value());
    ui->labeltRP_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRP(), spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtRAS_editingFinished() {
    spd->settRAS(ui->spinBoxtRAS->value());
    ui->labeltRAS_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRAS(), spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtRC_editingFinished() {
    spd->settRC(ui->spinBoxtRC->value());
    ui->labeltRC_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRC(), spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtWR_editingFinished() {
    spd->settWR(ui->spinBoxtWR->value());
    ui->labeltWR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettWR(), spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtRFC1_editingFinished() {
    spd->settRFC1_slr(ui->spinBoxtRFC1->value());
    ui->labeltRFC1_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRFC1_slr() * 1000, spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtRFC2_editingFinished() {
    spd->settRFC2_slr(ui->spinBoxtRFC2->value());
    ui->labeltRFC2_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRFC2_slr() * 1000, spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtRFC_editingFinished() {
    spd->settRFCsb_slr(ui->spinBoxtRFC->value());
    ui->labeltRFC_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRFCsb_slr() * 1000, spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtRRD_L_editingFinished() {
    spd->settRRD_L(ui->spinBoxtRRD_L->value());
    ui->labeltRRD_L_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRRD_L(), spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtRRD_L_LCLK_editingFinished() {
    spd->settRRD_L_lowerLimit(ui->spinBoxtRRD_L_LCLK->value());
}

void MainWindow::on_spinBoxtCCD_L_editingFinished() {
    spd->settCCD_L(ui->spinBoxtCCD_L->value());
    ui->labeltCCD_L_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettCCD_L(), spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtCCD_L_LCLK_editingFinished() {
    spd->settCCD_L_lowerLimit(ui->spinBoxtCCD_L_LCLK->value());
}

void MainWindow::on_spinBoxtCCDL_L_WR_editingFinished() {
    spd->settCCD_L_WR(ui->spinBoxtCCDL_L_WR->value());
    ui->labeltCCDL_L_WR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettCCD_L_WR(), spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtCCDL_L_WR_LCLK_editingFinished() {
    spd->settCCD_L_WR_lowerLimit(ui->spinBoxtCCDL_L_WR_LCLK->value());
}

void MainWindow::on_spinBoxtCCDL_L_WR2_editingFinished() {
    spd->settCCD_L_WR2(ui->spinBoxtCCDL_L_WR2->value());
    ui->labeltCCDL_L_WR2_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettCCD_L_WR2(), spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtCCDL_L_WR2_LCLK_editingFinished() {
    spd->settCCD_L_WR2_lowerLimit(ui->spinBoxtCCDL_L_WR2_LCLK->value());
}

void MainWindow::on_spinBoxtFAW_editingFinished() {
    spd->settFAW(ui->spinBoxtFAW->value());
    ui->labeltFAW_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettFAW(), spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtFAW_LCLK_editingFinished() {
    spd->settFAW_lowerLimit(ui->spinBoxtFAW_LCLK->value());
}

void MainWindow::on_spinBoxtCCD_L_WTR_editingFinished() {
    spd->settCCD_L_WTR(ui->spinBoxtCCD_L_WTR->value());
    ui->labeltCCD_L_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettCCD_L_WTR(), spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtCCD_L_WTR_LCLK_editingFinished() {
    spd->settCCD_L_WTR_lowerLimit(ui->spinBoxtCCD_L_WTR_LCLK->value());
}

void MainWindow::on_spinBoxtCCD_S_WTR_editingFinished() {
    spd->settCCD_S_WTR(ui->spinBoxtCCD_S_WTR->value());
    ui->labeltCCD_S_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettCCD_S_WTR(), spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtCCD_S_WTR_LCLK_editingFinished() {
    spd->settCCD_S_WTR_lowerLimit(ui->spinBoxtCCD_S_WTR_LCLK->value());
    ui->labeltCCD_S_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettCCD_S_WTR(), spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtRTP_editingFinished() {
    spd->settRTP(ui->spinBoxtRTP->value());
    ui->labeltRTP_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->gettRTP(), spd->getMinCycleTime())));
}

void MainWindow::on_spinBoxtRTP_LCLK_editingFinished() {
    spd->settRTP_lowerLimit(ui->spinBoxtRTP_LCLK->value());
}

// XMP1
void MainWindow::on_cbCL20_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(20, value); }
void MainWindow::on_cbCL22_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(22, value); }
void MainWindow::on_cbCL24_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(24, value); }
void MainWindow::on_cbCL26_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(26, value); }
void MainWindow::on_cbCL28_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(28, value); }
void MainWindow::on_cbCL30_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(30, value); }
void MainWindow::on_cbCL32_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(32, value); }
void MainWindow::on_cbCL34_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(34, value); }
void MainWindow::on_cbCL36_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(36, value); }
void MainWindow::on_cbCL38_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(38, value); }
void MainWindow::on_cbCL40_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(40, value); }
void MainWindow::on_cbCL42_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(42, value); }
void MainWindow::on_cbCL44_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(44, value); }
void MainWindow::on_cbCL46_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(46, value); }
void MainWindow::on_cbCL48_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(48, value); }
void MainWindow::on_cbCL50_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(50, value); }
void MainWindow::on_cbCL52_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(52, value); }
void MainWindow::on_cbCL54_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(54, value); }
void MainWindow::on_cbCL56_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(56, value); }
void MainWindow::on_cbCL58_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(58, value); }
void MainWindow::on_cbCL60_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(60, value); }
void MainWindow::on_cbCL62_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(62, value); }
void MainWindow::on_cbCL64_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(64, value); }
void MainWindow::on_cbCL66_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(66, value); }
void MainWindow::on_cbCL68_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(68, value); }
void MainWindow::on_cbCL70_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(70, value); }
void MainWindow::on_cbCL72_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(72, value); }
void MainWindow::on_cbCL74_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(74, value); }
void MainWindow::on_cbCL76_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(76, value); }
void MainWindow::on_cbCL78_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(78, value); }
void MainWindow::on_cbCL80_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(80, value); }
void MainWindow::on_cbCL82_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(82, value); }
void MainWindow::on_cbCL84_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(84, value); }
void MainWindow::on_cbCL86_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(86, value); }
void MainWindow::on_cbCL88_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(88, value); }
void MainWindow::on_cbCL90_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(90, value); }
void MainWindow::on_cbCL92_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(92, value); }
void MainWindow::on_cbCL94_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(94, value); }
void MainWindow::on_cbCL96_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(96, value); }
void MainWindow::on_cbCL98_XMP1_toggled(bool value) { spd->xmpBundle.profile1.setCLSupported(98, value); }

void MainWindow::on_cbCL20_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(20, value); }
void MainWindow::on_cbCL22_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(22, value); }
void MainWindow::on_cbCL24_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(24, value); }
void MainWindow::on_cbCL26_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(26, value); }
void MainWindow::on_cbCL28_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(28, value); }
void MainWindow::on_cbCL30_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(30, value); }
void MainWindow::on_cbCL32_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(32, value); }
void MainWindow::on_cbCL34_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(34, value); }
void MainWindow::on_cbCL36_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(36, value); }
void MainWindow::on_cbCL38_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(38, value); }
void MainWindow::on_cbCL40_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(40, value); }
void MainWindow::on_cbCL42_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(42, value); }
void MainWindow::on_cbCL44_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(44, value); }
void MainWindow::on_cbCL46_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(46, value); }
void MainWindow::on_cbCL48_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(48, value); }
void MainWindow::on_cbCL50_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(50, value); }
void MainWindow::on_cbCL52_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(52, value); }
void MainWindow::on_cbCL54_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(54, value); }
void MainWindow::on_cbCL56_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(56, value); }
void MainWindow::on_cbCL58_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(58, value); }
void MainWindow::on_cbCL60_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(60, value); }
void MainWindow::on_cbCL62_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(62, value); }
void MainWindow::on_cbCL64_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(64, value); }
void MainWindow::on_cbCL66_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(66, value); }
void MainWindow::on_cbCL68_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(68, value); }
void MainWindow::on_cbCL70_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(70, value); }
void MainWindow::on_cbCL72_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(72, value); }
void MainWindow::on_cbCL74_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(74, value); }
void MainWindow::on_cbCL76_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(76, value); }
void MainWindow::on_cbCL78_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(78, value); }
void MainWindow::on_cbCL80_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(80, value); }
void MainWindow::on_cbCL82_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(82, value); }
void MainWindow::on_cbCL84_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(84, value); }
void MainWindow::on_cbCL86_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(86, value); }
void MainWindow::on_cbCL88_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(88, value); }
void MainWindow::on_cbCL90_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(90, value); }
void MainWindow::on_cbCL92_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(92, value); }
void MainWindow::on_cbCL94_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(94, value); }
void MainWindow::on_cbCL96_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(96, value); }
void MainWindow::on_cbCL98_XMP2_toggled(bool value) { spd->xmpBundle.profile2.setCLSupported(98, value); }

void MainWindow::on_cbCL20_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(20, value); }
void MainWindow::on_cbCL22_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(22, value); }
void MainWindow::on_cbCL24_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(24, value); }
void MainWindow::on_cbCL26_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(26, value); }
void MainWindow::on_cbCL28_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(28, value); }
void MainWindow::on_cbCL30_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(30, value); }
void MainWindow::on_cbCL32_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(32, value); }
void MainWindow::on_cbCL34_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(34, value); }
void MainWindow::on_cbCL36_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(36, value); }
void MainWindow::on_cbCL38_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(38, value); }
void MainWindow::on_cbCL40_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(40, value); }
void MainWindow::on_cbCL42_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(42, value); }
void MainWindow::on_cbCL44_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(44, value); }
void MainWindow::on_cbCL46_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(46, value); }
void MainWindow::on_cbCL48_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(48, value); }
void MainWindow::on_cbCL50_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(50, value); }
void MainWindow::on_cbCL52_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(52, value); }
void MainWindow::on_cbCL54_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(54, value); }
void MainWindow::on_cbCL56_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(56, value); }
void MainWindow::on_cbCL58_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(58, value); }
void MainWindow::on_cbCL60_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(60, value); }
void MainWindow::on_cbCL62_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(62, value); }
void MainWindow::on_cbCL64_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(64, value); }
void MainWindow::on_cbCL66_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(66, value); }
void MainWindow::on_cbCL68_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(68, value); }
void MainWindow::on_cbCL70_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(70, value); }
void MainWindow::on_cbCL72_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(72, value); }
void MainWindow::on_cbCL74_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(74, value); }
void MainWindow::on_cbCL76_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(76, value); }
void MainWindow::on_cbCL78_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(78, value); }
void MainWindow::on_cbCL80_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(80, value); }
void MainWindow::on_cbCL82_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(82, value); }
void MainWindow::on_cbCL84_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(84, value); }
void MainWindow::on_cbCL86_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(86, value); }
void MainWindow::on_cbCL88_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(88, value); }
void MainWindow::on_cbCL90_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(90, value); }
void MainWindow::on_cbCL92_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(92, value); }
void MainWindow::on_cbCL94_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(94, value); }
void MainWindow::on_cbCL96_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(96, value); }
void MainWindow::on_cbCL98_XMP3_toggled(bool value) { spd->xmpBundle.profile3.setCLSupported(98, value); }

void MainWindow::on_cbCL20_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(20, value); }
void MainWindow::on_cbCL22_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(22, value); }
void MainWindow::on_cbCL24_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(24, value); }
void MainWindow::on_cbCL26_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(26, value); }
void MainWindow::on_cbCL28_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(28, value); }
void MainWindow::on_cbCL30_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(30, value); }
void MainWindow::on_cbCL32_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(32, value); }
void MainWindow::on_cbCL34_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(34, value); }
void MainWindow::on_cbCL36_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(36, value); }
void MainWindow::on_cbCL38_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(38, value); }
void MainWindow::on_cbCL40_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(40, value); }
void MainWindow::on_cbCL42_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(42, value); }
void MainWindow::on_cbCL44_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(44, value); }
void MainWindow::on_cbCL46_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(46, value); }
void MainWindow::on_cbCL48_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(48, value); }
void MainWindow::on_cbCL50_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(50, value); }
void MainWindow::on_cbCL52_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(52, value); }
void MainWindow::on_cbCL54_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(54, value); }
void MainWindow::on_cbCL56_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(56, value); }
void MainWindow::on_cbCL58_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(58, value); }
void MainWindow::on_cbCL60_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(60, value); }
void MainWindow::on_cbCL62_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(62, value); }
void MainWindow::on_cbCL64_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(64, value); }
void MainWindow::on_cbCL66_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(66, value); }
void MainWindow::on_cbCL68_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(68, value); }
void MainWindow::on_cbCL70_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(70, value); }
void MainWindow::on_cbCL72_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(72, value); }
void MainWindow::on_cbCL74_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(74, value); }
void MainWindow::on_cbCL76_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(76, value); }
void MainWindow::on_cbCL78_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(78, value); }
void MainWindow::on_cbCL80_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(80, value); }
void MainWindow::on_cbCL82_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(82, value); }
void MainWindow::on_cbCL84_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(84, value); }
void MainWindow::on_cbCL86_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(86, value); }
void MainWindow::on_cbCL88_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(88, value); }
void MainWindow::on_cbCL90_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(90, value); }
void MainWindow::on_cbCL92_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(92, value); }
void MainWindow::on_cbCL94_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(94, value); }
void MainWindow::on_cbCL96_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(96, value); }
void MainWindow::on_cbCL98_XMPU1_toggled(bool value) { spd->xmpBundle.profileUser1.setCLSupported(98, value); }

void MainWindow::on_cbCL20_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(20, value); }
void MainWindow::on_cbCL22_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(22, value); }
void MainWindow::on_cbCL24_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(24, value); }
void MainWindow::on_cbCL26_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(26, value); }
void MainWindow::on_cbCL28_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(28, value); }
void MainWindow::on_cbCL30_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(30, value); }
void MainWindow::on_cbCL32_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(32, value); }
void MainWindow::on_cbCL34_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(34, value); }
void MainWindow::on_cbCL36_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(36, value); }
void MainWindow::on_cbCL38_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(38, value); }
void MainWindow::on_cbCL40_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(40, value); }
void MainWindow::on_cbCL42_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(42, value); }
void MainWindow::on_cbCL44_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(44, value); }
void MainWindow::on_cbCL46_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(46, value); }
void MainWindow::on_cbCL48_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(48, value); }
void MainWindow::on_cbCL50_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(50, value); }
void MainWindow::on_cbCL52_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(52, value); }
void MainWindow::on_cbCL54_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(54, value); }
void MainWindow::on_cbCL56_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(56, value); }
void MainWindow::on_cbCL58_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(58, value); }
void MainWindow::on_cbCL60_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(60, value); }
void MainWindow::on_cbCL62_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(62, value); }
void MainWindow::on_cbCL64_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(64, value); }
void MainWindow::on_cbCL66_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(66, value); }
void MainWindow::on_cbCL68_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(68, value); }
void MainWindow::on_cbCL70_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(70, value); }
void MainWindow::on_cbCL72_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(72, value); }
void MainWindow::on_cbCL74_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(74, value); }
void MainWindow::on_cbCL76_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(76, value); }
void MainWindow::on_cbCL78_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(78, value); }
void MainWindow::on_cbCL80_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(80, value); }
void MainWindow::on_cbCL82_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(82, value); }
void MainWindow::on_cbCL84_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(84, value); }
void MainWindow::on_cbCL86_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(86, value); }
void MainWindow::on_cbCL88_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(88, value); }
void MainWindow::on_cbCL90_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(90, value); }
void MainWindow::on_cbCL92_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(92, value); }
void MainWindow::on_cbCL94_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(94, value); }
void MainWindow::on_cbCL96_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(96, value); }
void MainWindow::on_cbCL98_XMPU2_toggled(bool value) { spd->xmpBundle.profileUser2.setCLSupported(98, value); }
