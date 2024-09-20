#include "mainwindow.h"
#include "utilities.h"
#include "ddr5spd_structs.h"
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
    connect(ui->actionCreate_XMP_Block, &QAction::triggered, this, &MainWindow::createXMPBlock);
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

    connect(ui->actionExportProfile1, &QAction::triggered, this, &MainWindow::exportXMPProfile1);
    connect(ui->actionExportProfile2, &QAction::triggered, this, &MainWindow::exportXMPProfile2);
    connect(ui->actionExportProfile3, &QAction::triggered, this, &MainWindow::exportXMPProfile3);
    connect(ui->actionExportUserProfile1, &QAction::triggered, this, &MainWindow::exportXMPProfileU1);
    connect(ui->actionExportUserProfile2, &QAction::triggered, this, &MainWindow::exportXMPProfileU2);

    connect(ui->actionImportProfile1, &QAction::triggered, this, &MainWindow::importXMPProfile1);
    connect(ui->actionImportProfile2, &QAction::triggered, this, &MainWindow::importXMPProfile2);
    connect(ui->actionImportProfile3, &QAction::triggered, this, &MainWindow::importXMPProfile3);
    connect(ui->actionImportUserProfile1, &QAction::triggered, this, &MainWindow::importXMPProfileU1);
    connect(ui->actionImportUserProfile2, &QAction::triggered, this, &MainWindow::importXMPProfileU2);

    // EXPO menu
    connect(ui->actionWipeEXPOregion, &QAction::triggered, this, &MainWindow::wipeEXPO);
    connect(ui->actionExportEXPOProfile1, &QAction::triggered, this, &MainWindow::exportEXPOProfile1);
    connect(ui->actionExportEXPOProfile2, &QAction::triggered, this, &MainWindow::exportEXPOProfile2);
    connect(ui->actionImportEXPOProfile1, &QAction::triggered, this, &MainWindow::importEXPOProfile1);
    connect(ui->actionImportEXPOProfile2, &QAction::triggered, this, &MainWindow::importEXPOProfile2);
    connect(ui->actionCreate_EXPO_block, &QAction::triggered, this, &MainWindow::createEXPOBlock);
    connect(ui->actionCopyXMP1ToExpo1, &QAction::triggered, this, &MainWindow::importEXPOProfile1FromXMP1);
    connect(ui->actionCopyXMP2ToExpo1, &QAction::triggered, this, &MainWindow::importEXPOProfile1FromXMP2);
    connect(ui->actionCopyXMPU2ToExpo1, &QAction::triggered, this, &MainWindow::importEXPOProfile1FromXMPU2);
    connect(ui->actionCopyXMP1ToExpo2, &QAction::triggered, this, &MainWindow::importEXPOProfile2FromXMP1);
    connect(ui->actionCopyXMP2ToExpo2, &QAction::triggered, this, &MainWindow::importEXPOProfile2FromXMP2);
    connect(ui->actionCopyXMPU2ToExpo2, &QAction::triggered, this, &MainWindow::importEXPOProfile2FromXMPU2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exit(){
    qApp->exit();
}

void MainWindow::openFile(){
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath(), "SPD Files (*.spd *.bin);;All Files (*.*)");
    if (!fileName.isEmpty()) {
        // do something with the selected file
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(
                this,
                appName,
                tr("Failed to load file.") );
        }

        if (file.size() != ddr5_structs::eepromSize) {
            QMessageBox::critical(
                this,
                appName,
                tr("Invalid SPD file size.") );
        }

        QByteArray contents = file.readAll();

        if (spd != nullptr) {
            delete(spd);
        }

        if (contents.length() != ddr5_structs::eepromSize) {
            QMessageBox::critical(
                this,
                appName,
                tr("Failed to fully load file.") );
            return;
        }

        // TODO: Find proper way to do this
        ddr5_structs::SPD_Struct rawSPD = *reinterpret_cast<ddr5_structs::SPD_Struct*>(contents.data());

        if (rawSPD.memoryType != 0x12) {
            QMessageBox::critical(
                this,
                appName,
                tr("Invalid memory type in SPD.") );
            return;
        }

        if (!(rawSPD.moduleType == 0x02 || rawSPD.moduleType == 0x03)) {
            QMessageBox::warning(
                this,
                appName,
                tr("Untested module type, only UDIMM or SODIMM memory has been tested.") );
            return;
        }

        spd = new DDR5SPD(rawSPD);

        if (!spd->isCRCValid()) {
            QMessageBox::warning(
                this,
                appName,
                tr("JEDEC section checksum error, will be fixed by saving.") );
        }

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
        if (spd->isEXPOPresent()) {
            spd->expoBundle.fixCRC();
        }

        // Actually save
        QString fileName = QFileDialog::getSaveFileName(this, "Save File", QDir::currentPath(), "SPD Files (*.spd *.bin);;All Files (*.*)");
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
                file.write(spd->getPointerToStruct(), ddr5_structs::eepromSize);
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

void MainWindow::createXMPBlock() {
    spd->xmpBundle.resetXMPtoSample();
    reloadSPD();
    reloadUI();
}

void MainWindow::wipeXMP() {
    spd->xmpBundle.wipe();

    // Reload SPD
    spd = new DDR5SPD(spd->spdStruct);

    reloadXMP1Tab();
    reloadXMP2Tab();
    reloadXMP3Tab();
    reloadXMPU1Tab();
    reloadXMPU2Tab();

    toggleXMPUI(true, spd->isEXPOPresent());
}

void MainWindow::createEXPOBlock() {
    spd->expoBundle.resetAndCreateSample();
    reloadSPD();
    reloadUI();
}

void MainWindow::wipeEXPO() {
    spd->expoBundle.wipe();
    reloadSPD();
    reloadUI();
}

EXPO_ProfileStruct MainWindow::importEXPOProfile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath(), "EXPO Files (*.expo *.bin);;All Files (*.*)");

    if (!fileName.isEmpty()) {
        // do something with the selected file
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(
                this,
                appName,
                tr("Failed to load file.") );
        }

        if (file.size() != EXPOProfileSize) {
            QMessageBox::critical(
                this,
                appName,
                tr("Invalid EXPO profile file size.") );
        }

        QByteArray contents = file.readAll();

        if (contents.length() != EXPOProfileSize) {
            QMessageBox::critical(
                this,
                appName,
                tr("Invalid EXPO profile file size.") );
        } else {
            EXPO_ProfileStruct readProfile = *reinterpret_cast<EXPO_ProfileStruct*>(contents.data());
            return readProfile;
        }
    }

    EXPO_ProfileStruct empty{};
    return empty;
}

void MainWindow::exportEXPOProfile(const EXPO_ProfileStruct& expoProfile) {
    // Actually save
    QString fileName = QFileDialog::getSaveFileName(this, "Save EXPO File", QDir::currentPath(), "EXPO Files (*.expo *.bin);;All Files (*.*)");

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
            file.write(reinterpret_cast<const char*>(&expoProfile), EXPOProfileSize);
            file.close();
        } else {
            QMessageBox::critical(
                this,
                appName,
                tr("Failed to save file (read only?).") );
        }
    }
}

void MainWindow::importEXPOProfile1FromXMP1() {
    if (spd == nullptr) {
        return;
    }

    if (!spd->isEXPOPresent()) {
        QMessageBox::critical(
            this,
            appName,
            tr("EXPO is not present, please create EXPO block first.") );
        return;
    }

    if (spd->xmpBundle.isXMP1Enabled()) {
        spd->expoBundle.profile1.copyFromXMP(spd->xmpBundle.profile1.getCopy());
    }

    reloadSPD();
    reloadUI();
}

void MainWindow::importEXPOProfile1FromXMP2() {
    if (spd == nullptr) {
        return;
    }

    if (!spd->isEXPOPresent()) {
        QMessageBox::critical(
            this,
            appName,
            tr("EXPO is not present, please create EXPO block first.") );
        return;
    }

    if (spd->xmpBundle.isXMP2Enabled()) {
        spd->expoBundle.profile1.copyFromXMP(spd->xmpBundle.profile2.getCopy());
    }

    reloadSPD();
    reloadUI();
}

void MainWindow::importEXPOProfile1FromXMPU2() {
    if (spd == nullptr) {
        return;
    }

    if (!spd->isEXPOPresent()) {
        QMessageBox::critical(
            this,
            appName,
            tr("EXPO is not present, please create EXPO block first.") );
        return;
    }

    if (spd->xmpBundle.isXMPUser2Present()) {
        spd->expoBundle.profile1.copyFromXMP(spd->xmpBundle.profileUser2.getCopy());
    }

    reloadSPD();
    reloadUI();
}

void MainWindow::importEXPOProfile2FromXMP1() {
    if (spd == nullptr) {
        return;
    }

    if (!spd->isEXPOPresent()) {
        QMessageBox::critical(
            this,
            appName,
            tr("EXPO is not present, please create EXPO block first.") );
        return;
    }

    if (spd->xmpBundle.isXMP1Enabled()) {
        spd->expoBundle.profile1.copyFromXMP(spd->xmpBundle.profile1.getCopy());
    }

    reloadSPD();
    reloadUI();
}

void MainWindow::importEXPOProfile2FromXMP2() {
    if (spd == nullptr) {
        return;
    }

    if (!spd->isEXPOPresent()) {
        QMessageBox::critical(
            this,
            appName,
            tr("EXPO is not present, please create EXPO block first.") );
        return;
    }

    if (spd->xmpBundle.isXMP2Enabled()) {
        spd->expoBundle.profile1.copyFromXMP(spd->xmpBundle.profile2.getCopy());
    }

    reloadSPD();
    reloadUI();
}

void MainWindow::importEXPOProfile2FromXMPU2() {
    if (spd == nullptr) {
        return;
    }

    if (!spd->isEXPOPresent()) {
        QMessageBox::critical(
            this,
            appName,
            tr("EXPO is not present, please create EXPO block first.") );
        return;
    }

    if (spd->xmpBundle.isXMPUser2Present()) {
        spd->expoBundle.profile1.copyFromXMP(spd->xmpBundle.profileUser2.getCopy());
    }

    reloadSPD();
    reloadUI();
}

void MainWindow::exportEXPOProfile1() {
    if (spd != nullptr) {
        exportEXPOProfile(spd->expoBundle.profile1.getCopy());
    }
}

void MainWindow::exportEXPOProfile2() {
    if (spd != nullptr) {
        exportEXPOProfile(spd->expoBundle.profile2.getCopy());
    }
}

void MainWindow::importEXPOProfile1() {
    if (spd == nullptr) {
        return;
    }

    spd->expoBundle.profile1.import(importEXPOProfile());
    reloadEXPO1Tab();
}

void MainWindow::importEXPOProfile2() {
    if (spd == nullptr) {
        return;
    }

    spd->expoBundle.profile2.import(importEXPOProfile());
    reloadEXPO2Tab();
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

void MainWindow::exportXMPProfile(const XMP_ProfileStruct& xmpProfile) {
    // Actually save
    QString fileName = QFileDialog::getSaveFileName(this, "Save XMP File", QDir::currentPath(), "XMP Files (*.xmp *.bin);;All Files (*.*)");

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
            file.write(reinterpret_cast<const char*>(&xmpProfile), XMPProfileSize);
            file.close();
        } else {
            QMessageBox::critical(
                this,
                appName,
                tr("Failed to save file (read only?).") );
        }
    }
}

void MainWindow::exportXMPProfile1(){
    if (spd != nullptr) {
        exportXMPProfile(spd->xmpBundle.profile1.getCopy());
    }
}

void MainWindow::exportXMPProfile2(){
    if (spd != nullptr) {
        exportXMPProfile(spd->xmpBundle.profile2.getCopy());
    }
}

void MainWindow::exportXMPProfile3(){
    if ((spd != nullptr) && (!spd->isEXPOPresent())) {
        exportXMPProfile(spd->xmpBundle.profile3.getCopy());
    }
}

void MainWindow::exportXMPProfileU1(){
    if ((spd != nullptr) && (!spd->isEXPOPresent())) {
        exportXMPProfile(spd->xmpBundle.profileUser1.getCopy());
    }
}

void MainWindow::exportXMPProfileU2(){
    if (spd != nullptr) {
        exportXMPProfile(spd->xmpBundle.profileUser2.getCopy());
    }
}

XMP_ProfileStruct MainWindow::importXMPProfile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath(), "XMP Profile Files (*.xmp *.bin);;All Files (*.*)");

    if (!fileName.isEmpty()) {
        // do something with the selected file
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(
                this,
                appName,
                tr("Failed to load file.") );
        }

        if (file.size() != XMPProfileSize) {
            QMessageBox::critical(
                this,
                appName,
                tr("Invalid XMP 3.0 profile file size.") );
        }

        QByteArray contents = file.readAll();

        if (contents.length() != XMPProfileSize) {
            QMessageBox::critical(
                this,
                appName,
                tr("Invalid XMP 3.0 profile file size.") );
        } else {
            XMP_ProfileStruct readProfile = *reinterpret_cast<XMP_ProfileStruct*>(contents.data());
            return readProfile;
        }
    }

    XMP_ProfileStruct empty{};
    return empty;
}

void MainWindow::importXMPProfile1(){
    if (spd == nullptr) {
        return;
    }

    spd->xmpBundle.profile1.import(importXMPProfile());
    reloadXMP1Tab();
}

void MainWindow::importXMPProfile2(){
    if (spd == nullptr) {
        return;
    }

    spd->xmpBundle.profile2.import(importXMPProfile());
    reloadXMP2Tab();
}

void MainWindow::importXMPProfile3(){
    if ((spd == nullptr) ||  (spd->isEXPOPresent())) {
        return;
    }

    spd->xmpBundle.profile3.import(importXMPProfile());
    reloadXMP3Tab();
}

void MainWindow::importXMPProfileU1(){
    if ((spd == nullptr) ||  (spd->isEXPOPresent())) {
        return;
    }

    spd->xmpBundle.profileUser1.import(importXMPProfile());
    reloadXMPU1Tab();
}

void MainWindow::importXMPProfileU2(){
    if (spd == nullptr) {
        return;
    }

    spd->xmpBundle.profileUser2.import(importXMPProfile());
    reloadXMPU2Tab();
}

void MainWindow::enableXMPMagicBits() {
    spd->xmpBundle.enableMagic();
    reloadSPD();
    reloadUI();
}

void MainWindow::disableXMPMagicBits() {
    spd->xmpBundle.clearMagic();
    reloadSPD();
    reloadUI();
}

bool MainWindow::saveFileEnabled(){
    return spd != nullptr;
}

bool MainWindow::closeFileEnabled(){
    return spd != nullptr;
}

void MainWindow::toggleUI(const bool status) {
    bool disabled = !status;

    ui->tabJEDEC->setDisabled(disabled);
    ui->tabMisc->setDisabled(disabled);

    ui->actionSave->setDisabled(disabled);
    ui->actionClose->setDisabled(disabled);
    ui->actionEnableXMPmagic->setDisabled(disabled);
    ui->actionDisableXMPmagic->setDisabled(disabled);
    ui->actionWipeXMPregion->setDisabled(disabled);
    ui->actionWipeEXPOregion->setDisabled(disabled);
    ui->actionCreate_XMP_Block->setDisabled(disabled);
}

void MainWindow::toggleXMPUI(const bool status, const bool expoPresent) {
    bool disabled = !status;

    ui->actionWipeProfile1->setDisabled(disabled);
    ui->actionLoadSampleProfile1->setDisabled(disabled);
    ui->actionExportProfile1->setDisabled(disabled);
    ui->actionImportProfile1->setDisabled(disabled);
    ui->tabXMPP1->setDisabled(disabled);

    ui->actionWipeProfile2->setDisabled(disabled);
    ui->actionLoadSampleProfile2->setDisabled(disabled);
    ui->actionExportProfile2->setDisabled(disabled);
    ui->actionImportProfile2->setDisabled(disabled);
    ui->tabXMPP2->setDisabled(disabled);


    if (!expoPresent) {
        ui->actionWipeProfile3->setDisabled(disabled);
        ui->actionLoadSampleProfile3->setDisabled(disabled);
        ui->actionExportProfile3->setDisabled(disabled);
        ui->actionImportProfile3->setDisabled(disabled);
        ui->tabXMPP3->setDisabled(disabled);

        ui->actionWipeProfileU1->setDisabled(disabled);
        ui->actionLoadSampleProfileU1->setDisabled(disabled);
        ui->actionExportUserProfile1->setDisabled(disabled);
        ui->actionImportUserProfile1->setDisabled(disabled);
        ui->tabXMPU1->setDisabled(disabled);
    }

    ui->actionWipeProfileU2->setDisabled(disabled);
    ui->actionLoadSampleProfileU2->setDisabled(disabled);
    ui->actionExportUserProfile2->setDisabled(disabled);
    ui->actionImportUserProfile2->setDisabled(disabled);
    ui->tabXMPU2->setDisabled(disabled);
}

void MainWindow::toggleEXPOUI(const bool status) {
    bool disabled = !status;

    ui->tabEXPO1->setDisabled(disabled);
    ui->tabEXPO2->setDisabled(disabled);
    ui->actionWipeEXPOregion->setDisabled(disabled);

    ui->actionExportEXPOProfile1->setDisabled(disabled);
    ui->actionImportEXPOProfile1->setDisabled(disabled);
    ui->actionExportEXPOProfile2->setDisabled(disabled);
    ui->actionImportEXPOProfile2->setDisabled(disabled);

    ui->actionCopyXMP1ToExpo1->setDisabled(disabled);
    ui->actionCopyXMP2ToExpo1->setDisabled(disabled);
    ui->actionCopyXMPU2ToExpo1->setDisabled(disabled);
    ui->actionCopyXMP1ToExpo2->setDisabled(disabled);
    ui->actionCopyXMP2ToExpo2->setDisabled(disabled);
    ui->actionCopyXMPU2ToExpo2->setDisabled(disabled);
}

void MainWindow::disableUI() {
    ui->tabWidget->setCurrentWidget(ui->tabJEDEC);
    toggleUI(false);
    toggleXMPUI(false, false);
    toggleEXPOUI(false);
}

void MainWindow::enableUI() {
    if (spd == nullptr) {
        return;
    }

    // Menus
    toggleUI(true);

    reloadXMP_EXPO();

    // Go to JEDEC tab
    ui->tabJEDEC->activateWindow();
}

void MainWindow::reloadSPD() {
    if (spd == nullptr) {
        return;
    }

    // Reload SPD
    spd = new DDR5SPD(spd->spdStruct);
}

void MainWindow::reloadXMP_EXPO() {
    if (spd == nullptr) {
        return;
    }

    if (spd->isXMPPresent())
    {
        toggleXMPUI(true, spd->isEXPOPresent());
    }

    if (spd->isEXPOPresent())
    {
        toggleEXPOUI(true);
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
    if (spd->isEXPOPresent()) {
        return;
    }

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
    if (spd->isEXPOPresent()) {
        return;
    }

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

void MainWindow::reloadEXPO1Tab() {
    EXPO_Profile dummy;

    // EXPO Header
    EXPO_Profile& expo_profile = spd->isEXPOPresent() ? spd->expoBundle.profile1 : dummy;
    ui->cbEnabled_EXPO1->setChecked(spd->expoBundle.isEXPO1Enabled());

    // EXPO Profile
    const unsigned int minCycleTime = expo_profile.getMinCycleTime();
    ui->spinMinCycleTime_EXPO1->setValue(minCycleTime);
    QString frequencyStr = QString::number(expo_profile.getFrequency()) + " MHz";
    QString mtStr = QString::number(expo_profile.getMT()) + " MT/s";
    ui->lFrequencyValue_EXPO1->setText(frequencyStr);
    ui->lMTValue_EXPO1->setText(mtStr);

    // Voltages
    ui->sbVDD_EXPO1->setValue(expo_profile.getVDD());
    ui->sbVDDQ_EXPO1->setValue(expo_profile.getVDDQ());
    ui->sbVPP_EXPO1->setValue(expo_profile.getVPP());

    ui->sbtAA_EXPO1->setValue(expo_profile.gettAA());
    ui->ltAA_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettAA(), minCycleTime)));
    ui->sbtRCD_EXPO1->setValue(expo_profile.gettRCD());
    ui->ltRCD_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRCD(), minCycleTime)));
    ui->sbtRP_EXPO1->setValue(expo_profile.gettRP());
    ui->ltRP_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRP(), minCycleTime)));
    ui->sbtRAS_EXPO1->setValue(expo_profile.gettRAS());
    ui->ltRAS_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRAS(), minCycleTime)));
    ui->sbtRC_EXPO1->setValue(expo_profile.gettRC());
    ui->ltRC_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRC(), minCycleTime)));
    ui->sbtWR_EXPO1->setValue(expo_profile.gettWR());
    ui->ltWR_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettWR(), minCycleTime)));
    ui->sbtRFC1_EXPO1->setValue(expo_profile.gettRFC1());
    ui->ltRFC1_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRFC1() * 1000, minCycleTime)));
    ui->sbtRFC2_EXPO1->setValue(expo_profile.gettRFC2());
    ui->ltRFC2_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRFC2() * 1000, minCycleTime)));
    ui->sbtRFC_EXPO1->setValue(expo_profile.gettRFC());
    ui->ltRFC_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRFC() * 1000, minCycleTime)));
    // Enhanced timings
    ui->sbtRRD_L_EXPO1->setValue(expo_profile.gettRRD_L());
    ui->ltRRD_L_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRRD_L(), minCycleTime)));
    ui->sbtCCD_L_EXPO1->setValue(expo_profile.gettCCD_L());
    ui->ltCCD_L_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettCCD_L(), minCycleTime)));
    ui->sbtCCDL_L_WR_EXPO1->setValue(expo_profile.gettCCD_L_WR());
    ui->ltCCDL_L_WR_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettCCD_L_WR(), minCycleTime)));
    ui->sbtCCDL_L_WR2_EXPO1->setValue(expo_profile.gettCCD_L_WR2());
    ui->ltCCDL_L_WR2_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettCCD_L_WR2(), minCycleTime)));
    ui->sbtFAW_EXPO1->setValue(expo_profile.gettFAW());
    ui->ltFAW_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettFAW(), minCycleTime)));
    ui->sbtCCD_L_WTR_EXPO1->setValue(expo_profile.gettCCD_L_WTR());
    ui->ltCCD_L_WTR_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettCCD_L_WTR(), minCycleTime)));
    ui->sbtCCD_S_WTR_EXPO1->setValue(expo_profile.gettCCD_S_WTR());
    ui->ltCCD_S_WTR_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettCCD_S_WTR(), minCycleTime)));
    ui->sbtRTP_EXPO1->setValue(expo_profile.gettRTP());
    ui->ltRTP_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRTP(), minCycleTime)));
}

void MainWindow::reloadEXPO2Tab() {
    EXPO_Profile dummy;

    // EXPO Header
    EXPO_Profile& expo_profile = spd->isEXPOPresent() ? spd->expoBundle.profile2 : dummy;
    ui->cbEnabled_EXPO2->setChecked(spd->expoBundle.isEXPO2Enabled());

    // EXPO Profile
    const unsigned int minCycleTime = expo_profile.getMinCycleTime();
    ui->spinMinCycleTime_EXPO2->setValue(minCycleTime);
    QString frequencyStr = QString::number(expo_profile.getFrequency()) + " MHz";
    QString mtStr = QString::number(expo_profile.getMT()) + " MT/s";
    ui->lFrequencyValue_EXPO2->setText(frequencyStr);
    ui->lMTValue_EXPO2->setText(mtStr);

    // Voltages
    ui->sbVDD_EXPO2->setValue(expo_profile.getVDD());
    ui->sbVDDQ_EXPO2->setValue(expo_profile.getVDDQ());
    ui->sbVPP_EXPO2->setValue(expo_profile.getVPP());

    ui->sbtAA_EXPO2->setValue(expo_profile.gettAA());
    ui->ltAA_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettAA(), minCycleTime)));
    ui->sbtRCD_EXPO2->setValue(expo_profile.gettRCD());
    ui->ltRCD_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRCD(), minCycleTime)));
    ui->sbtRP_EXPO2->setValue(expo_profile.gettRP());
    ui->ltRP_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRP(), minCycleTime)));
    ui->sbtRAS_EXPO2->setValue(expo_profile.gettRAS());
    ui->ltRAS_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRAS(), minCycleTime)));
    ui->sbtRC_EXPO2->setValue(expo_profile.gettRC());
    ui->ltRC_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRC(), minCycleTime)));
    ui->sbtWR_EXPO2->setValue(expo_profile.gettWR());
    ui->ltWR_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettWR(), minCycleTime)));
    ui->sbtRFC1_EXPO2->setValue(expo_profile.gettRFC1());
    ui->ltRFC1_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRFC1() * 1000, minCycleTime)));
    ui->sbtRFC2_EXPO2->setValue(expo_profile.gettRFC2());
    ui->ltRFC2_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRFC2() * 1000, minCycleTime)));
    ui->sbtRFC_EXPO2->setValue(expo_profile.gettRFC());
    ui->ltRFC_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRFC() * 1000, minCycleTime)));
    // Enhanced timings
    ui->sbtRRD_L_EXPO2->setValue(expo_profile.gettRRD_L());
    ui->ltRRD_L_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRRD_L(), minCycleTime)));
    ui->sbtCCD_L_EXPO2->setValue(expo_profile.gettCCD_L());
    ui->ltCCD_L_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettCCD_L(), minCycleTime)));
    ui->sbtCCDL_L_WR_EXPO2->setValue(expo_profile.gettCCD_L_WR());
    ui->ltCCDL_L_WR_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettCCD_L_WR(), minCycleTime)));
    ui->sbtCCDL_L_WR2_EXPO2->setValue(expo_profile.gettCCD_L_WR2());
    ui->ltCCDL_L_WR2_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettCCD_L_WR2(), minCycleTime)));
    ui->sbtFAW_EXPO2->setValue(expo_profile.gettFAW());
    ui->ltFAW_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettFAW(), minCycleTime)));
    ui->sbtCCD_L_WTR_EXPO2->setValue(expo_profile.gettCCD_L_WTR());
    ui->ltCCD_L_WTR_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettCCD_L_WTR(), minCycleTime)));
    ui->sbtCCD_S_WTR_EXPO2->setValue(expo_profile.gettCCD_S_WTR());
    ui->ltCCD_S_WTR_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettCCD_S_WTR(), minCycleTime)));
    ui->sbtRTP_EXPO2->setValue(expo_profile.gettRTP());
    ui->ltRTP_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(expo_profile.gettRTP(), minCycleTime)));
}

void MainWindow::reloadMiscTab() {
    update_cbFormFactor();
    update_cbDensity();
    update_cbBankGroup();
    update_cbBanksPerBankGroup();
    update_cbColumnAddresses();
    update_cbRowAddresses();
    update_cdDeviceWidth();

    ui->sbManufacturingYear->setValue(spd->getManufacturingYear());
    ui->sbManufacturingWeek->setValue(spd->getManufacturingWeek());
    ui->lePartNumber->setText(QString::fromStdString(spd->getPartNumber()));
}

void MainWindow::reloadUI(){
    if (spd == nullptr) {
        return;
    }

    reloadXMP_EXPO();

    reloadJEDECTab();
    reloadXMP1Tab();
    reloadXMP2Tab();
    reloadXMP3Tab();
    reloadXMPU1Tab();
    reloadXMPU2Tab();
    reloadEXPO1Tab();
    reloadEXPO2Tab();
    reloadMiscTab();
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
void MainWindow::on_leProfileName_XMP1_editingFinished() {
    spd->xmpBundle.setXMP1ProfileName(ui->leProfileName_XMP1->text().toStdString());
}

void MainWindow::on_cbEnabled_XMP1_toggled(bool val) {
    spd->xmpBundle.setXMP1Enabled(val);
}

void MainWindow::on_cbDynamicMemBoost_XMP1_toggled(bool value) {
    spd->xmpBundle.profile1.setIntelDynamicMemoryBoost(value);
}

void MainWindow::on_cbRealTimeMemOC_XMP1_toggled(bool value) {
    spd->xmpBundle.profile1.setRealTimeMemoryFrequencyOC(value);
}

void MainWindow::on_sbVDD_XMP1_editingFinished() {
    spd->xmpBundle.profile1.setVDD(ui->sbVDD_XMP1->value());
}

void MainWindow::on_sbVDDQ_XMP1_editingFinished() {
    spd->xmpBundle.profile1.setVDDQ(ui->sbVDDQ_XMP1->value());
}

void MainWindow::on_sbVPP_XMP1_editingFinished() {
    spd->xmpBundle.profile1.setVPP(ui->sbVPP_XMP1->value());
}

void MainWindow::on_sbVmemctrl_XMP1_editingFinished() {
    spd->xmpBundle.profile1.setVDD(ui->sbVmemctrl_XMP1->value());
}

void MainWindow::on_spinMinCycleTime_XMP1_editingFinished()
{
    spd->xmpBundle.profile1.setMinCycleTime(ui->spinMinCycleTime_XMP1->value());
}

void MainWindow::on_cbCommandRate_XMP1_currentIndexChanged(int index)
{
    switch (index) {
        default:
        case 0:
            spd->xmpBundle.profile1.setCommandRate(CommandRate::Undefined);
            break;

        case 1:
            spd->xmpBundle.profile1.setCommandRate(CommandRate::_1n);
            break;

        case 2:
            spd->xmpBundle.profile1.setCommandRate(CommandRate::_2n);
            break;

        case 3:
            spd->xmpBundle.profile1.setCommandRate(CommandRate::_3n);
            break;
    }
}

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

void MainWindow::on_sbtAA_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settAA(ui->sbtAA_XMP1->value());
    ui->ltAA_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettAA(), spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRCD_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settRCD(ui->sbtRCD_XMP1->value());
    ui->ltRCD_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettRCD(), spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRP_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settRP(ui->sbtRP_XMP1->value());
    ui->ltRP_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettRP(), spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRAS_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settRAS(ui->sbtRAS_XMP1->value());
    ui->ltRAS_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettRAS(), spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRC_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settRC(ui->sbtRC_XMP1->value());
    ui->ltRC_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettRC(), spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtWR_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settWR(ui->sbtWR_XMP1->value());
    ui->ltWR_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettWR(), spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRFC1_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settRFC1(ui->sbtRFC1_XMP1->value());
    ui->ltRFC1_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettRFC1() * 1000, spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRFC2_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settRFC2(ui->sbtRFC2_XMP1->value());
    ui->ltRFC2_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettRFC2() * 1000, spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRFC_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settRFC(ui->sbtRFC_XMP1->value());
    ui->ltRFC_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettRFC() * 1000, spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRRD_L_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settRRD_L(ui->sbtRRD_L_XMP1->value());
    ui->ltRRD_L_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettRRD_L(), spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRRD_L_LCLK_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settRRD_L_lowerLimit(ui->sbtRRD_L_LCLK_XMP1->value());
}

void MainWindow::on_sbtCCD_L_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settCCD_L(ui->sbtCCD_L_XMP1->value());
    ui->ltCCD_L_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettCCD_L(), spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_L_LCLK_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settCCD_L_lowerLimit(ui->sbtCCD_L_LCLK_XMP1->value());
}

void MainWindow::on_sbtCCDL_L_WR_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settCCD_L_WR(ui->sbtCCDL_L_WR_XMP1->value());
    ui->ltCCDL_L_WR_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettCCD_L_WR(), spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtCCDL_L_WR_LCLK_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settCCD_L_WR_lowerLimit(ui->sbtCCDL_L_WR_LCLK_XMP1->value());
}

void MainWindow::on_sbtCCDL_L_WR2_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settCCD_L_WR2(ui->sbtCCDL_L_WR2_XMP1->value());
    ui->ltCCDL_L_WR2_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettCCD_L_WR2(), spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtCCDL_L_WR2_LCLK_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settCCD_L_WR2_lowerLimit(ui->sbtCCDL_L_WR2_LCLK_XMP1->value());
}

void MainWindow::on_sbtFAW_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settFAW(ui->sbtFAW_XMP1->value());
    ui->ltFAW_Ticks_XMP1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettFAW(), spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtFAW_LCLK_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settFAW_lowerLimit(ui->sbtFAW_LCLK_XMP1->value());
}

void MainWindow::on_sbtCCD_L_WTR_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settCCD_L_WTR(ui->sbtCCD_L_WTR_XMP1->value());
    ui->labeltCCD_L_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettCCD_L_WTR(), spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_L_WTR_LCLK_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settCCD_L_WTR_lowerLimit(ui->sbtCCD_L_WTR_LCLK_XMP1->value());
}

void MainWindow::on_sbtCCD_S_WTR_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settCCD_S_WTR(ui->sbtCCD_S_WTR_XMP1->value());
    ui->labeltCCD_S_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettCCD_S_WTR(), spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_S_WTR_LCLK_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settCCD_S_WTR_lowerLimit(ui->sbtCCD_S_WTR_LCLK_XMP1->value());
    ui->labeltCCD_S_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettCCD_S_WTR(), spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRTP_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settRTP(ui->sbtRTP_XMP1->value());
    ui->labeltRTP_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile1.gettRTP(), spd->xmpBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRTP_LCLK_XMP1_editingFinished() {
    spd->xmpBundle.profile1.settRTP_lowerLimit(ui->sbtRTP_LCLK_XMP1->value());
}

// XMP2
void MainWindow::on_leProfileName_XMP2_editingFinished() {
    spd->xmpBundle.setXMP2ProfileName(ui->leProfileName_XMP2->text().toStdString());
}

void MainWindow::on_cbEnabled_XMP2_toggled(bool val) {
    spd->xmpBundle.setXMP2Enabled(val);
}

void MainWindow::on_cbDynamicMemBoost_XMP2_toggled(bool value) {
    spd->xmpBundle.profile2.setIntelDynamicMemoryBoost(value);
}

void MainWindow::on_cbRealTimeMemOC_XMP2_toggled(bool value) {
    spd->xmpBundle.profile2.setRealTimeMemoryFrequencyOC(value);
}

void MainWindow::on_sbVDD_XMP2_editingFinished() {
    spd->xmpBundle.profile2.setVDD(ui->sbVDD_XMP2->value());
}

void MainWindow::on_sbVDDQ_XMP2_editingFinished() {
    spd->xmpBundle.profile2.setVDDQ(ui->sbVDDQ_XMP2->value());
}

void MainWindow::on_sbVPP_XMP2_editingFinished() {
    spd->xmpBundle.profile2.setVPP(ui->sbVPP_XMP2->value());
}

void MainWindow::on_sbVmemctrl_XMP2_editingFinished() {
    spd->xmpBundle.profile2.setVDD(ui->sbVmemctrl_XMP2->value());
}

void MainWindow::on_spinMinCycleTime_XMP2_editingFinished()
{
    spd->xmpBundle.profile2.setMinCycleTime(ui->spinMinCycleTime_XMP2->value());
}

void MainWindow::on_cbCommandRate_XMP2_currentIndexChanged(int index)
{
    switch (index) {
    default:
    case 0:
            spd->xmpBundle.profile2.setCommandRate(CommandRate::Undefined);
            break;

    case 1:
            spd->xmpBundle.profile2.setCommandRate(CommandRate::_1n);
            break;

    case 2:
            spd->xmpBundle.profile2.setCommandRate(CommandRate::_2n);
            break;

    case 3:
            spd->xmpBundle.profile2.setCommandRate(CommandRate::_3n);
            break;
    }
}

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

void MainWindow::on_sbtAA_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settAA(ui->sbtAA_XMP2->value());
    ui->ltAA_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettAA(), spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRCD_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settRCD(ui->sbtRCD_XMP2->value());
    ui->ltRCD_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettRCD(), spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRP_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settRP(ui->sbtRP_XMP2->value());
    ui->ltRP_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettRP(), spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRAS_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settRAS(ui->sbtRAS_XMP2->value());
    ui->ltRAS_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettRAS(), spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRC_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settRC(ui->sbtRC_XMP2->value());
    ui->ltRC_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettRC(), spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtWR_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settWR(ui->sbtWR_XMP2->value());
    ui->ltWR_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettWR(), spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRFC1_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settRFC1(ui->sbtRFC1_XMP2->value());
    ui->ltRFC1_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettRFC1() * 1000, spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRFC2_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settRFC2(ui->sbtRFC2_XMP2->value());
    ui->ltRFC2_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettRFC2() * 1000, spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRFC_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settRFC(ui->sbtRFC_XMP2->value());
    ui->ltRFC_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettRFC() * 1000, spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRRD_L_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settRRD_L(ui->sbtRRD_L_XMP2->value());
    ui->ltRRD_L_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettRRD_L(), spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRRD_L_LCLK_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settRRD_L_lowerLimit(ui->sbtRRD_L_LCLK_XMP2->value());
}

void MainWindow::on_sbtCCD_L_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settCCD_L(ui->sbtCCD_L_XMP2->value());
    ui->ltCCD_L_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettCCD_L(), spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_L_LCLK_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settCCD_L_lowerLimit(ui->sbtCCD_L_LCLK_XMP2->value());
}

void MainWindow::on_sbtCCDL_L_WR_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settCCD_L_WR(ui->sbtCCDL_L_WR_XMP2->value());
    ui->ltCCDL_L_WR_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettCCD_L_WR(), spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtCCDL_L_WR_LCLK_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settCCD_L_WR_lowerLimit(ui->sbtCCDL_L_WR_LCLK_XMP2->value());
}

void MainWindow::on_sbtCCDL_L_WR2_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settCCD_L_WR2(ui->sbtCCDL_L_WR2_XMP2->value());
    ui->ltCCDL_L_WR2_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettCCD_L_WR2(), spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtCCDL_L_WR2_LCLK_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settCCD_L_WR2_lowerLimit(ui->sbtCCDL_L_WR2_LCLK_XMP2->value());
}

void MainWindow::on_sbtFAW_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settFAW(ui->sbtFAW_XMP2->value());
    ui->ltFAW_Ticks_XMP2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettFAW(), spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtFAW_LCLK_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settFAW_lowerLimit(ui->sbtFAW_LCLK_XMP2->value());
}

void MainWindow::on_sbtCCD_L_WTR_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settCCD_L_WTR(ui->sbtCCD_L_WTR_XMP2->value());
    ui->labeltCCD_L_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettCCD_L_WTR(), spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_L_WTR_LCLK_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settCCD_L_WTR_lowerLimit(ui->sbtCCD_L_WTR_LCLK_XMP2->value());
}

void MainWindow::on_sbtCCD_S_WTR_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settCCD_S_WTR(ui->sbtCCD_S_WTR_XMP2->value());
    ui->labeltCCD_S_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettCCD_S_WTR(), spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_S_WTR_LCLK_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settCCD_S_WTR_lowerLimit(ui->sbtCCD_S_WTR_LCLK_XMP2->value());
    ui->labeltCCD_S_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettCCD_S_WTR(), spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRTP_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settRTP(ui->sbtRTP_XMP2->value());
    ui->labeltRTP_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile2.gettRTP(), spd->xmpBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRTP_LCLK_XMP2_editingFinished() {
    spd->xmpBundle.profile2.settRTP_lowerLimit(ui->sbtRTP_LCLK_XMP2->value());
}

// XMP3
void MainWindow::on_leProfileName_XMP3_editingFinished() {
    spd->xmpBundle.setXMP3ProfileName(ui->leProfileName_XMP3->text().toStdString());
}

void MainWindow::on_cbEnabled_XMP3_toggled(bool val) {
    spd->xmpBundle.setXMP3Enabled(val);
}

void MainWindow::on_cbDynamicMemBoost_XMP3_toggled(bool value) {
    spd->xmpBundle.profile3.setIntelDynamicMemoryBoost(value);
}

void MainWindow::on_cbRealTimeMemOC_XMP3_toggled(bool value) {
    spd->xmpBundle.profile3.setRealTimeMemoryFrequencyOC(value);
}

void MainWindow::on_sbVDD_XMP3_editingFinished() {
    spd->xmpBundle.profile3.setVDD(ui->sbVDD_XMP3->value());
}

void MainWindow::on_sbVDDQ_XMP3_editingFinished() {
    spd->xmpBundle.profile3.setVDDQ(ui->sbVDDQ_XMP3->value());
}

void MainWindow::on_sbVPP_XMP3_editingFinished() {
    spd->xmpBundle.profile3.setVPP(ui->sbVPP_XMP3->value());
}

void MainWindow::on_sbVmemctrl_XMP3_editingFinished() {
    spd->xmpBundle.profile3.setVDD(ui->sbVmemctrl_XMP3->value());
}

void MainWindow::on_spinMinCycleTime_XMP3_editingFinished()
{
    spd->xmpBundle.profile3.setMinCycleTime(ui->spinMinCycleTime_XMP3->value());
}

void MainWindow::on_cbCommandRate_XMP3_currentIndexChanged(int index)
{
    switch (index) {
    default:
    case 0:
            spd->xmpBundle.profile3.setCommandRate(CommandRate::Undefined);
            break;

    case 1:
            spd->xmpBundle.profile3.setCommandRate(CommandRate::_1n);
            break;

    case 2:
            spd->xmpBundle.profile3.setCommandRate(CommandRate::_2n);
            break;

    case 3:
            spd->xmpBundle.profile3.setCommandRate(CommandRate::_3n);
            break;
    }
}

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

void MainWindow::on_sbtAA_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settAA(ui->sbtAA_XMP3->value());
    ui->ltAA_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettAA(), spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtRCD_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settRCD(ui->sbtRCD_XMP3->value());
    ui->ltRCD_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettRCD(), spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtRP_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settRP(ui->sbtRP_XMP3->value());
    ui->ltRP_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettRP(), spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtRAS_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settRAS(ui->sbtRAS_XMP3->value());
    ui->ltRAS_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettRAS(), spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtRC_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settRC(ui->sbtRC_XMP3->value());
    ui->ltRC_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettRC(), spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtWR_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settWR(ui->sbtWR_XMP3->value());
    ui->ltWR_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettWR(), spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtRFC1_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settRFC1(ui->sbtRFC1_XMP3->value());
    ui->ltRFC1_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettRFC1() * 1000, spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtRFC2_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settRFC2(ui->sbtRFC2_XMP3->value());
    ui->ltRFC2_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettRFC2() * 1000, spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtRFC_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settRFC(ui->sbtRFC_XMP3->value());
    ui->ltRFC_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettRFC() * 1000, spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtRRD_L_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settRRD_L(ui->sbtRRD_L_XMP3->value());
    ui->ltRRD_L_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettRRD_L(), spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtRRD_L_LCLK_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settRRD_L_lowerLimit(ui->sbtRRD_L_LCLK_XMP3->value());
}

void MainWindow::on_sbtCCD_L_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settCCD_L(ui->sbtCCD_L_XMP3->value());
    ui->ltCCD_L_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettCCD_L(), spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_L_LCLK_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settCCD_L_lowerLimit(ui->sbtCCD_L_LCLK_XMP3->value());
}

void MainWindow::on_sbtCCDL_L_WR_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settCCD_L_WR(ui->sbtCCDL_L_WR_XMP3->value());
    ui->ltCCDL_L_WR_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettCCD_L_WR(), spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtCCDL_L_WR_LCLK_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settCCD_L_WR_lowerLimit(ui->sbtCCDL_L_WR_LCLK_XMP3->value());
}

void MainWindow::on_sbtCCDL_L_WR2_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settCCD_L_WR2(ui->sbtCCDL_L_WR2_XMP3->value());
    ui->ltCCDL_L_WR2_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettCCD_L_WR2(), spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtCCDL_L_WR2_LCLK_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settCCD_L_WR2_lowerLimit(ui->sbtCCDL_L_WR2_LCLK_XMP3->value());
}

void MainWindow::on_sbtFAW_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settFAW(ui->sbtFAW_XMP3->value());
    ui->ltFAW_Ticks_XMP3->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettFAW(), spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtFAW_LCLK_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settFAW_lowerLimit(ui->sbtFAW_LCLK_XMP3->value());
}

void MainWindow::on_sbtCCD_L_WTR_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settCCD_L_WTR(ui->sbtCCD_L_WTR_XMP3->value());
    ui->labeltCCD_L_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettCCD_L_WTR(), spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_L_WTR_LCLK_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settCCD_L_WTR_lowerLimit(ui->sbtCCD_L_WTR_LCLK_XMP3->value());
}

void MainWindow::on_sbtCCD_S_WTR_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settCCD_S_WTR(ui->sbtCCD_S_WTR_XMP3->value());
    ui->labeltCCD_S_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettCCD_S_WTR(), spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_S_WTR_LCLK_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settCCD_S_WTR_lowerLimit(ui->sbtCCD_S_WTR_LCLK_XMP3->value());
    ui->labeltCCD_S_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettCCD_S_WTR(), spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtRTP_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settRTP(ui->sbtRTP_XMP3->value());
    ui->labeltRTP_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profile3.gettRTP(), spd->xmpBundle.profile3.getMinCycleTime())));
}

void MainWindow::on_sbtRTP_LCLK_XMP3_editingFinished() {
    spd->xmpBundle.profile3.settRTP_lowerLimit(ui->sbtRTP_LCLK_XMP3->value());
}

// XMP User 1
void MainWindow::on_cbDynamicMemBoost_XMPU1_toggled(bool value) {
    spd->xmpBundle.profileUser1.setIntelDynamicMemoryBoost(value);
}

void MainWindow::on_cbRealTimeMemOC_XMPU1_toggled(bool value) {
    spd->xmpBundle.profileUser1.setRealTimeMemoryFrequencyOC(value);
}

void MainWindow::on_sbVDD_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.setVDD(ui->sbVDD_XMPU1->value());
}

void MainWindow::on_sbVDDQ_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.setVDDQ(ui->sbVDDQ_XMPU1->value());
}

void MainWindow::on_sbVPP_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.setVPP(ui->sbVPP_XMPU1->value());
}

void MainWindow::on_sbVmemctrl_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.setVDD(ui->sbVmemctrl_XMPU1->value());
}

void MainWindow::on_spinMinCycleTime_XMPU1_editingFinished()
{
    spd->xmpBundle.profileUser1.setMinCycleTime(ui->spinMinCycleTime_XMPU1->value());
}

void MainWindow::on_cbCommandRate_XMPU1_currentIndexChanged(int index)
{
    switch (index) {
        default:
        case 0:
            spd->xmpBundle.profileUser1.setCommandRate(CommandRate::Undefined);
            break;

        case 1:
            spd->xmpBundle.profileUser1.setCommandRate(CommandRate::_1n);
            break;

        case 2:
            spd->xmpBundle.profileUser1.setCommandRate(CommandRate::_2n);
            break;

        case 3:
            spd->xmpBundle.profileUser1.setCommandRate(CommandRate::_3n);
            break;
    }
}

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

void MainWindow::on_sbtAA_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settAA(ui->sbtAA_XMPU1->value());
    ui->ltAA_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettAA(), spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtRCD_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settRCD(ui->sbtRCD_XMPU1->value());
    ui->ltRCD_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettRCD(), spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtRP_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settRP(ui->sbtRP_XMPU1->value());
    ui->ltRP_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettRP(), spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtRAS_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settRAS(ui->sbtRAS_XMPU1->value());
    ui->ltRAS_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettRAS(), spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtRC_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settRC(ui->sbtRC_XMPU1->value());
    ui->ltRC_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettRC(), spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtWR_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settWR(ui->sbtWR_XMPU1->value());
    ui->ltWR_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettWR(), spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtRFC1_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settRFC1(ui->sbtRFC1_XMPU1->value());
    ui->ltRFC1_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettRFC1() * 1000, spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtRFC2_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settRFC2(ui->sbtRFC2_XMPU1->value());
    ui->ltRFC2_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettRFC2() * 1000, spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtRFC_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settRFC(ui->sbtRFC_XMPU1->value());
    ui->ltRFC_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettRFC() * 1000, spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtRRD_L_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settRRD_L(ui->sbtRRD_L_XMPU1->value());
    ui->ltRRD_L_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettRRD_L(), spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtRRD_L_LCLK_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settRRD_L_lowerLimit(ui->sbtRRD_L_LCLK_XMPU1->value());
}

void MainWindow::on_sbtCCD_L_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settCCD_L(ui->sbtCCD_L_XMPU1->value());
    ui->ltCCD_L_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettCCD_L(), spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_L_LCLK_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settCCD_L_lowerLimit(ui->sbtCCD_L_LCLK_XMPU1->value());
}

void MainWindow::on_sbtCCDL_L_WR_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settCCD_L_WR(ui->sbtCCDL_L_WR_XMPU1->value());
    ui->ltCCDL_L_WR_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettCCD_L_WR(), spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtCCDL_L_WR_LCLK_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settCCD_L_WR_lowerLimit(ui->sbtCCDL_L_WR_LCLK_XMPU1->value());
}

void MainWindow::on_sbtCCDL_L_WR2_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settCCD_L_WR2(ui->sbtCCDL_L_WR2_XMPU1->value());
    ui->ltCCDL_L_WR2_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettCCD_L_WR2(), spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtCCDL_L_WR2_LCLK_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settCCD_L_WR2_lowerLimit(ui->sbtCCDL_L_WR2_LCLK_XMPU1->value());
}

void MainWindow::on_sbtFAW_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settFAW(ui->sbtFAW_XMPU1->value());
    ui->ltFAW_Ticks_XMPU1->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettFAW(), spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtFAW_LCLK_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settFAW_lowerLimit(ui->sbtFAW_LCLK_XMPU1->value());
}

void MainWindow::on_sbtCCD_L_WTR_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settCCD_L_WTR(ui->sbtCCD_L_WTR_XMPU1->value());
    ui->labeltCCD_L_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettCCD_L_WTR(), spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_L_WTR_LCLK_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settCCD_L_WTR_lowerLimit(ui->sbtCCD_L_WTR_LCLK_XMPU1->value());
}

void MainWindow::on_sbtCCD_S_WTR_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settCCD_S_WTR(ui->sbtCCD_S_WTR_XMPU1->value());
    ui->labeltCCD_S_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettCCD_S_WTR(), spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_S_WTR_LCLK_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settCCD_S_WTR_lowerLimit(ui->sbtCCD_S_WTR_LCLK_XMPU1->value());
    ui->labeltCCD_S_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettCCD_S_WTR(), spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtRTP_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settRTP(ui->sbtRTP_XMPU1->value());
    ui->labeltRTP_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser1.gettRTP(), spd->xmpBundle.profileUser1.getMinCycleTime())));
}

void MainWindow::on_sbtRTP_LCLK_XMPU1_editingFinished() {
    spd->xmpBundle.profileUser1.settRTP_lowerLimit(ui->sbtRTP_LCLK_XMPU1->value());
}

// XMP User 2
void MainWindow::on_cbDynamicMemBoost_XMPU2_toggled(bool value) {
    spd->xmpBundle.profileUser2.setIntelDynamicMemoryBoost(value);
}

void MainWindow::on_cbRealTimeMemOC_XMPU2_toggled(bool value) {
    spd->xmpBundle.profileUser2.setRealTimeMemoryFrequencyOC(value);
}

void MainWindow::on_sbVDD_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.setVDD(ui->sbVDD_XMPU2->value());
}

void MainWindow::on_sbVDDQ_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.setVDDQ(ui->sbVDDQ_XMPU2->value());
}

void MainWindow::on_sbVPP_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.setVPP(ui->sbVPP_XMPU2->value());
}

void MainWindow::on_sbVmemctrl_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.setVDD(ui->sbVmemctrl_XMPU2->value());
}

void MainWindow::on_spinMinCycleTime_XMPU2_editingFinished()
{
    spd->xmpBundle.profileUser2.setMinCycleTime(ui->spinMinCycleTime_XMPU2->value());
}

void MainWindow::on_cbCommandRate_XMPU2_currentIndexChanged(int index)
{
    switch (index) {
    default:
    case 0:
            spd->xmpBundle.profileUser2.setCommandRate(CommandRate::Undefined);
            break;

    case 1:
            spd->xmpBundle.profileUser2.setCommandRate(CommandRate::_1n);
            break;

    case 2:
            spd->xmpBundle.profileUser2.setCommandRate(CommandRate::_2n);
            break;

    case 3:
            spd->xmpBundle.profileUser2.setCommandRate(CommandRate::_3n);
            break;
    }
}

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

void MainWindow::on_sbtAA_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settAA(ui->sbtAA_XMPU2->value());
    ui->ltAA_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettAA(), spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtRCD_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settRCD(ui->sbtRCD_XMPU2->value());
    ui->ltRCD_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettRCD(), spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtRP_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settRP(ui->sbtRP_XMPU2->value());
    ui->ltRP_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettRP(), spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtRAS_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settRAS(ui->sbtRAS_XMPU2->value());
    ui->ltRAS_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettRAS(), spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtRC_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settRC(ui->sbtRC_XMPU2->value());
    ui->ltRC_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettRC(), spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtWR_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settWR(ui->sbtWR_XMPU2->value());
    ui->ltWR_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettWR(), spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtRFC1_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settRFC1(ui->sbtRFC1_XMPU2->value());
    ui->ltRFC1_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettRFC1() * 1000, spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtRFC2_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settRFC2(ui->sbtRFC2_XMPU2->value());
    ui->ltRFC2_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettRFC2() * 1000, spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtRFC_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settRFC(ui->sbtRFC_XMPU2->value());
    ui->ltRFC_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettRFC() * 1000, spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtRRD_L_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settRRD_L(ui->sbtRRD_L_XMPU2->value());
    ui->ltRRD_L_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettRRD_L(), spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtRRD_L_LCLK_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settRRD_L_lowerLimit(ui->sbtRRD_L_LCLK_XMPU2->value());
}

void MainWindow::on_sbtCCD_L_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settCCD_L(ui->sbtCCD_L_XMPU2->value());
    ui->ltCCD_L_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettCCD_L(), spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_L_LCLK_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settCCD_L_lowerLimit(ui->sbtCCD_L_LCLK_XMPU2->value());
}

void MainWindow::on_sbtCCDL_L_WR_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settCCD_L_WR(ui->sbtCCDL_L_WR_XMPU2->value());
    ui->ltCCDL_L_WR_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettCCD_L_WR(), spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtCCDL_L_WR_LCLK_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settCCD_L_WR_lowerLimit(ui->sbtCCDL_L_WR_LCLK_XMPU2->value());
}

void MainWindow::on_sbtCCDL_L_WR2_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settCCD_L_WR2(ui->sbtCCDL_L_WR2_XMPU2->value());
    ui->ltCCDL_L_WR2_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettCCD_L_WR2(), spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtCCDL_L_WR2_LCLK_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settCCD_L_WR2_lowerLimit(ui->sbtCCDL_L_WR2_LCLK_XMPU2->value());
}

void MainWindow::on_sbtFAW_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settFAW(ui->sbtFAW_XMPU2->value());
    ui->ltFAW_Ticks_XMPU2->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettFAW(), spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtFAW_LCLK_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settFAW_lowerLimit(ui->sbtFAW_LCLK_XMPU2->value());
}

void MainWindow::on_sbtCCD_L_WTR_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settCCD_L_WTR(ui->sbtCCD_L_WTR_XMPU2->value());
    ui->labeltCCD_L_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettCCD_L_WTR(), spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_L_WTR_LCLK_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settCCD_L_WTR_lowerLimit(ui->sbtCCD_L_WTR_LCLK_XMPU2->value());
}

void MainWindow::on_sbtCCD_S_WTR_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settCCD_S_WTR(ui->sbtCCD_S_WTR_XMPU2->value());
    ui->labeltCCD_S_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettCCD_S_WTR(), spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_S_WTR_LCLK_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settCCD_S_WTR_lowerLimit(ui->sbtCCD_S_WTR_LCLK_XMPU2->value());
    ui->labeltCCD_S_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettCCD_S_WTR(), spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtRTP_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settRTP(ui->sbtRTP_XMPU2->value());
    ui->labeltRTP_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->xmpBundle.profileUser2.gettRTP(), spd->xmpBundle.profileUser2.getMinCycleTime())));
}

void MainWindow::on_sbtRTP_LCLK_XMPU2_editingFinished() {
    spd->xmpBundle.profileUser2.settRTP_lowerLimit(ui->sbtRTP_LCLK_XMPU2->value());
}

// EXPO1
void MainWindow::on_cbEnabled_EXPO1_toggled(bool val) {
    spd->expoBundle.setEXPO1Enabled(val);
}

void MainWindow::on_sbVDD_EXPO1_editingFinished() {
    spd->expoBundle.profile1.setVDD(ui->sbVDD_EXPO1->value());
}

void MainWindow::on_sbVDDQ_EXPO1_editingFinished() {
    spd->expoBundle.profile1.setVDDQ(ui->sbVDDQ_EXPO1->value());
}

void MainWindow::on_sbVPP_EXPO1_editingFinished() {
    spd->expoBundle.profile1.setVPP(ui->sbVPP_EXPO1->value());
}

void MainWindow::on_spinMinCycleTime_EXPO1_editingFinished()
{
    spd->expoBundle.profile1.setMinCycleTime(ui->spinMinCycleTime_EXPO1->value());
}

void MainWindow::on_sbtAA_EXPO1_editingFinished() {
    spd->expoBundle.profile1.settAA(ui->sbtAA_EXPO1->value());
    ui->ltAA_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile1.gettAA(), spd->expoBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRCD_EXPO1_editingFinished() {
    spd->expoBundle.profile1.settRCD(ui->sbtRCD_EXPO1->value());
    ui->ltRCD_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile1.gettRCD(), spd->expoBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRP_EXPO1_editingFinished() {
    spd->expoBundle.profile1.settRP(ui->sbtRP_EXPO1->value());
    ui->ltRP_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile1.gettRP(), spd->expoBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRAS_EXPO1_editingFinished() {
    spd->expoBundle.profile1.settRAS(ui->sbtRAS_EXPO1->value());
    ui->ltRAS_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile1.gettRAS(), spd->expoBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRC_EXPO1_editingFinished() {
    spd->expoBundle.profile1.settRC(ui->sbtRC_EXPO1->value());
    ui->ltRC_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile1.gettRC(), spd->expoBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtWR_EXPO1_editingFinished() {
    spd->expoBundle.profile1.settWR(ui->sbtWR_EXPO1->value());
    ui->ltWR_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile1.gettWR(), spd->expoBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRFC1_EXPO1_editingFinished() {
    spd->expoBundle.profile1.settRFC1(ui->sbtRFC1_EXPO1->value());
    ui->ltRFC1_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile1.gettRFC1() * 1000, spd->expoBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRFC2_EXPO1_editingFinished() {
    spd->expoBundle.profile1.settRFC2(ui->sbtRFC2_EXPO1->value());
    ui->ltRFC2_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile1.gettRFC2() * 1000, spd->expoBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRFC_EXPO1_editingFinished() {
    spd->expoBundle.profile1.settRFC(ui->sbtRFC_EXPO1->value());
    ui->ltRFC_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile1.gettRFC() * 1000, spd->expoBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRRD_L_EXPO1_editingFinished() {
    spd->expoBundle.profile1.settRRD_L(ui->sbtRRD_L_EXPO1->value());
    ui->ltRRD_L_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile1.gettRRD_L(), spd->expoBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_L_EXPO1_editingFinished() {
    spd->expoBundle.profile1.settCCD_L(ui->sbtCCD_L_EXPO1->value());
    ui->ltCCD_L_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile1.gettCCD_L(), spd->expoBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtCCDL_L_WR_EXPO1_editingFinished() {
    spd->expoBundle.profile1.settCCD_L_WR(ui->sbtCCDL_L_WR_EXPO1->value());
    ui->ltCCDL_L_WR_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile1.gettCCD_L_WR(), spd->expoBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtCCDL_L_WR2_EXPO1_editingFinished() {
    spd->expoBundle.profile1.settCCD_L_WR2(ui->sbtCCDL_L_WR2_EXPO1->value());
    ui->ltCCDL_L_WR2_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile1.gettCCD_L_WR2(), spd->expoBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtFAW_EXPO1_editingFinished() {
    spd->expoBundle.profile1.settFAW(ui->sbtFAW_EXPO1->value());
    ui->ltFAW_Ticks_EXPO1->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile1.gettFAW(), spd->expoBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_L_WTR_EXPO1_editingFinished() {
    spd->expoBundle.profile1.settCCD_L_WTR(ui->sbtCCD_L_WTR_EXPO1->value());
    ui->labeltCCD_L_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile1.gettCCD_L_WTR(), spd->expoBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_S_WTR_EXPO1_editingFinished() {
    spd->expoBundle.profile1.settCCD_S_WTR(ui->sbtCCD_S_WTR_EXPO1->value());
    ui->labeltCCD_S_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile1.gettCCD_S_WTR(), spd->expoBundle.profile1.getMinCycleTime())));
}

void MainWindow::on_sbtRTP_EXPO1_editingFinished() {
    spd->expoBundle.profile1.settRTP(ui->sbtRTP_EXPO1->value());
    ui->labeltRTP_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile1.gettRTP(), spd->expoBundle.profile1.getMinCycleTime())));
}

// EXPO2
void MainWindow::on_cbEnabled_EXPO2_toggled(bool val) {
    spd->expoBundle.setEXPO2Enabled(val);
}

void MainWindow::on_sbVDD_EXPO2_editingFinished() {
    spd->expoBundle.profile2.setVDD(ui->sbVDD_EXPO2->value());
}

void MainWindow::on_sbVDDQ_EXPO2_editingFinished() {
    spd->expoBundle.profile2.setVDDQ(ui->sbVDDQ_EXPO2->value());
}

void MainWindow::on_sbVPP_EXPO2_editingFinished() {
    spd->expoBundle.profile2.setVPP(ui->sbVPP_EXPO2->value());
}

void MainWindow::on_spinMinCycleTime_EXPO2_editingFinished()
{
    spd->expoBundle.profile2.setMinCycleTime(ui->spinMinCycleTime_EXPO2->value());
}

void MainWindow::on_sbtAA_EXPO2_editingFinished() {
    spd->expoBundle.profile2.settAA(ui->sbtAA_EXPO2->value());
    ui->ltAA_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile2.gettAA(), spd->expoBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRCD_EXPO2_editingFinished() {
    spd->expoBundle.profile2.settRCD(ui->sbtRCD_EXPO2->value());
    ui->ltRCD_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile2.gettRCD(), spd->expoBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRP_EXPO2_editingFinished() {
    spd->expoBundle.profile2.settRP(ui->sbtRP_EXPO2->value());
    ui->ltRP_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile2.gettRP(), spd->expoBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRAS_EXPO2_editingFinished() {
    spd->expoBundle.profile2.settRAS(ui->sbtRAS_EXPO2->value());
    ui->ltRAS_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile2.gettRAS(), spd->expoBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRC_EXPO2_editingFinished() {
    spd->expoBundle.profile2.settRC(ui->sbtRC_EXPO2->value());
    ui->ltRC_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile2.gettRC(), spd->expoBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtWR_EXPO2_editingFinished() {
    spd->expoBundle.profile2.settWR(ui->sbtWR_EXPO2->value());
    ui->ltWR_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile2.gettWR(), spd->expoBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRFC1_EXPO2_editingFinished() {
    spd->expoBundle.profile2.settRFC1(ui->sbtRFC1_EXPO2->value());
    ui->ltRFC1_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile2.gettRFC1() * 1000, spd->expoBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRFC2_EXPO2_editingFinished() {
    spd->expoBundle.profile2.settRFC2(ui->sbtRFC2_EXPO2->value());
    ui->ltRFC2_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile2.gettRFC2() * 1000, spd->expoBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRFC_EXPO2_editingFinished() {
    spd->expoBundle.profile2.settRFC(ui->sbtRFC_EXPO2->value());
    ui->ltRFC_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile2.gettRFC() * 1000, spd->expoBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRRD_L_EXPO2_editingFinished() {
    spd->expoBundle.profile2.settRRD_L(ui->sbtRRD_L_EXPO2->value());
    ui->ltRRD_L_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile2.gettRRD_L(), spd->expoBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_L_EXPO2_editingFinished() {
    spd->expoBundle.profile2.settCCD_L(ui->sbtCCD_L_EXPO2->value());
    ui->ltCCD_L_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile2.gettCCD_L(), spd->expoBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtCCDL_L_WR_EXPO2_editingFinished() {
    spd->expoBundle.profile2.settCCD_L_WR(ui->sbtCCDL_L_WR_EXPO2->value());
    ui->ltCCDL_L_WR_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile2.gettCCD_L_WR(), spd->expoBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtCCDL_L_WR2_EXPO2_editingFinished() {
    spd->expoBundle.profile2.settCCD_L_WR2(ui->sbtCCDL_L_WR2_EXPO2->value());
    ui->ltCCDL_L_WR2_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile2.gettCCD_L_WR2(), spd->expoBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtFAW_EXPO2_editingFinished() {
    spd->expoBundle.profile2.settFAW(ui->sbtFAW_EXPO2->value());
    ui->ltFAW_Ticks_EXPO2->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile2.gettFAW(), spd->expoBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_L_WTR_EXPO2_editingFinished() {
    spd->expoBundle.profile2.settCCD_L_WTR(ui->sbtCCD_L_WTR_EXPO2->value());
    ui->labeltCCD_L_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile2.gettCCD_L_WTR(), spd->expoBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtCCD_S_WTR_EXPO2_editingFinished() {
    spd->expoBundle.profile2.settCCD_S_WTR(ui->sbtCCD_S_WTR_EXPO2->value());
    ui->labeltCCD_S_WTR_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile2.gettCCD_S_WTR(), spd->expoBundle.profile2.getMinCycleTime())));
}

void MainWindow::on_sbtRTP_EXPO2_editingFinished() {
    spd->expoBundle.profile2.settRTP(ui->sbtRTP_EXPO2->value());
    ui->labeltRTP_Ticks->setText(QString::number(utilities::TimeToTicksDDR5(spd->expoBundle.profile2.gettRTP(), spd->expoBundle.profile2.getMinCycleTime())));
}

// EXPO <-> Conversion
XMP_ProfileStruct MainWindow::importXMPProfileFromEXPO(const EXPO_ProfileStruct& expo) {
    XMP_ProfileStruct result;
    result.vdd = expo.vdd;
    result.vddq = expo.vddq;
    result.vpp = expo.vpp;
    result.vmemctrl = utilities::ConvertVoltageToByteDDR5(110);
    result.minCycleTime = expo.minCycleTime;

    // Attempt to guess right CL
    unsigned short CL = utilities::TimeToTicksDDR5(expo.tAA, expo.minCycleTime);

    if (CL % 2 != 0) {
        CL++;
    }

    result.tAA = expo.tAA;
    result.tRCD = expo.tRCD;
    result.tRP = expo.tRP;
    result.tRAS = expo.tRAS;
    result.tRC = expo.tRC;
    result.tWR = expo.tWR;
    result.tRFC1 = expo.tRFC1;
    result.tRFC2 = expo.tRFC2;
    result.tRFC = expo.tRFC;
    result.tRRD_L = expo.tRRD_L;
    result.tCCD_L = expo.tCCD_L;
    result.tCCD_L_WR = expo.tCCD_L_WR;
    result.tCCD_L_WR2 = expo.tCCD_L_WR2;
    result.tFAW = expo.tFAW;
    result.tCCD_L_WTR = expo.tCCD_L_WTR;
    result.tCCD_S_WTR = expo.tCCD_S_WTR;
    result.tRTP = expo.tRTP;

    // Load default values
    result.tRRD_L_lowerLimit = 8;
    result.tCCD_L_WR_lowerLimit = 32;
    result.tCCD_L_WR2_lowerLimit = 16;
    result.tCCD_L_WTR_lowerLimit = 16;
    result.tCCD_S_WTR_lowerLimit = 4;
    result.tCCD_L_lowerLimit = 8;
    result.tRTP_lowerLimit = 12;
    result.tFAW_lowerLimit = 32;
    // setDimmsChannel(1);
    // result.commandRate = CommandRate::_2n;

    return result;
}

// Misc
void MainWindow::update_cbFormFactor() {
    switch (spd->getFormFactor()) {
        case FormFactor::RDIMM:
            ui->cbFormFactor->setCurrentIndex(0);
            break;

        case FormFactor::UDIMM:
            ui->cbFormFactor->setCurrentIndex(1);
            break;

        case FormFactor::SODIMM:
            ui->cbFormFactor->setCurrentIndex(2);
            break;

        case FormFactor::LRDIMM:
            ui->cbFormFactor->setCurrentIndex(3);
            break;

        case FormFactor::CUDIMM:
            ui->cbFormFactor->setCurrentIndex(4);
            break;

        case FormFactor::CSODIMM:
            ui->cbFormFactor->setCurrentIndex(5);
            break;

        case FormFactor::MRDIMM:
            ui->cbFormFactor->setCurrentIndex(6);
            break;

        case FormFactor::CAMM2:
            ui->cbFormFactor->setCurrentIndex(7);
            break;

        case FormFactor::DDIMM:
            ui->cbFormFactor->setCurrentIndex(8);
            break;

        case FormFactor::Solder_down:
            ui->cbFormFactor->setCurrentIndex(9);
            break;

        default:
            break;
    }
}

void MainWindow::setDensity(const unsigned int val) {
    unsigned int max =  ui->cdDensity->count();
    if (val <= max) {
        ui->cdDensity->setCurrentIndex(val);
    }
}

void MainWindow::update_cbDensity() {
    switch (spd->getDensity()) {
        case Density::_0Gb:
            setDensity(0);
            break;

        case Density::_4Gb:
            setDensity(1);
            break;

        case Density::_8Gb:
            setDensity(2);
            break;

        case Density::_12Gb:
            setDensity(3);
            break;

        case Density::_16Gb:
            setDensity(4);
            break;

        case Density::_24Gb:
            setDensity(5);
            break;

        case Density::_32Gb:
            setDensity(6);
            break;

        case Density::_48Gb:
            setDensity(7);
            break;

        case Density::_64Gb:
            setDensity(8);
            break;

        default:
            break;
    }
}

void MainWindow::on_cbFormFactor_currentIndexChanged(int index) {
    switch (index) {
        case 0:
            spd->setFormFactor(FormFactor::RDIMM);
            break;
        case 1:
            spd->setFormFactor(FormFactor::UDIMM);
            break;
        case 2:
            spd->setFormFactor(FormFactor::SODIMM);
            break;
        case 3:
            spd->setFormFactor(FormFactor::LRDIMM);
            break;
        case 4:
            spd->setFormFactor(FormFactor::CUDIMM);
            break;
        case 5:
            spd->setFormFactor(FormFactor::CSODIMM);
            break;
        case 6:
            spd->setFormFactor(FormFactor::MRDIMM);
            break;
        case 7:
            spd->setFormFactor(FormFactor::CAMM2);
            break;
        case 8:
            spd->setFormFactor(FormFactor::DDIMM);
            break;
        case 9:
            spd->setFormFactor(FormFactor::Solder_down);
            break;

        default:
            break;
    }

    update_cbFormFactor();
}

void MainWindow::on_cdDensity_currentIndexChanged(int index) {
    switch (index) {
        case 0:
            spd->setDensity(Density::_0Gb);
            break;

        case 1:
            spd->setDensity(Density::_4Gb);
            break;

        case 2:
            spd->setDensity(Density::_8Gb);
            break;

        case 3:
            spd->setDensity(Density::_12Gb);
            break;

        case 4:
            spd->setDensity(Density::_16Gb);
            break;

        case 5:
            spd->setDensity(Density::_24Gb);
            break;

        case 6:
            spd->setDensity(Density::_32Gb);
            break;

        case 7:
            spd->setDensity(Density::_48Gb);
            break;

        case 8:
            spd->setDensity(Density::_64Gb);
            break;

        default:
            break;
    }

    update_cbDensity();
}

void MainWindow::on_cbBankGroup_currentIndexChanged(int index) {
    spd->setBankGroups(bankGroupsBitsMap[index]);
    update_cbBankGroup();
}

void MainWindow::on_cbBanksPerBankGroup_currentIndexChanged(int index) {
    spd->setBanksPerBankGroup(banksPerBankGroupBitsMap[index]);
    update_cbBanksPerBankGroup();
}

void MainWindow::on_cbColumnAddresses_currentIndexChanged(int index) {
    spd->setColumnAddresses(columnAddressBitsMap[index]);
    update_cbColumnAddresses();
}

void MainWindow::on_cbRowAddresses_currentIndexChanged(int index) {
    spd->setRowAddresses(columnAddressBitsMap[index]);
    update_cbRowAddresses();
}

void MainWindow::on_cdDeviceWidth_currentIndexChanged(int index) {
    spd->setDeviceWidth(deviceWidthMap[index]);
    update_cdDeviceWidth();
}

void MainWindow::on_sbManufacturingYear_editingFinished() {
    spd->setManufacturingYear(ui->sbManufacturingYear->value());
    ui->sbManufacturingYear->setValue(spd->getManufacturingYear());
}

void MainWindow::on_sbManufacturingWeek_editingFinished() {
    spd->setManufacturingWeek(ui->sbManufacturingWeek->value());
    ui->sbManufacturingWeek->setValue(spd->getManufacturingWeek());
}

void MainWindow::on_lePartNumber_editingFinished() {
    QString val = ui->lePartNumber->text();
    spd->setPartNumber(val.toStdString());
    val = QString::fromStdString(spd->getPartNumber());
    ui->lePartNumber->setText(val);
}

void MainWindow::update_cbBankGroup() {
    int val = std::distance(bankGroupsBitsMap.begin(),
                            std::find(bankGroupsBitsMap.begin(),
                                      bankGroupsBitsMap.end(),
                                      spd->getBankGroups()));

    ui->cbBankGroup->setCurrentIndex(val);
}

void MainWindow::update_cbBanksPerBankGroup() {
    int val = std::distance(banksPerBankGroupBitsMap.begin(),
                            std::find(banksPerBankGroupBitsMap.begin(),
                                      banksPerBankGroupBitsMap.end(),
                                      spd->getBanksPerBankGroup()));

    ui->cbBanksPerBankGroup->setCurrentIndex(val);
}

void MainWindow::update_cbColumnAddresses() {
    int val = std::distance(columnAddressBitsMap.begin(),
                            std::find(columnAddressBitsMap.begin(),
                                      columnAddressBitsMap.end(),
                                      spd->getColumnAddresses()));

    ui->cbColumnAddresses->setCurrentIndex(val);
}

void MainWindow::update_cbRowAddresses() {
    int val = std::distance(rowAddressBitsMap.begin(),
                            std::find(rowAddressBitsMap.begin(),
                                      rowAddressBitsMap.end(),
                                      spd->getRowAddresses()));

    ui->cbRowAddresses->setCurrentIndex(val);

}

void MainWindow::update_cdDeviceWidth() {
    int val = std::distance(deviceWidthMap.begin(),
                            std::find(deviceWidthMap.begin(),
                                      deviceWidthMap.end(),
                                      spd->getDeviceWidth()));

    ui->cdDeviceWidth->setCurrentIndex(val);
}
