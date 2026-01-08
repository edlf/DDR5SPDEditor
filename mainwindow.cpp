#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "ddr5spd_structs.h"
#include "utilities.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
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

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::exit() {
  qApp->exit();
}

void MainWindow::openFile() {
  QString fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath(), "SPD Files (*.spd *.bin);;All Files (*.*)");
  if (!fileName.isEmpty()) {
    // do something with the selected file
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
      QMessageBox::critical(this, appName, tr("Failed to load file."));
    }

    size_t expectedBytes = 0;

    switch (file.size()) {
      // Regular 1K eeprom size
      case ddr5_structs::eepromBaseSize:
        expectedBytes = ddr5_structs::eepromBaseSize;
        break;
      // CUDIMM 2K size?
      case ddr5_structs::eepromExtendedSize:
        expectedBytes = ddr5_structs::eepromExtendedSize;
        break;
      default:
        QMessageBox::critical(this, appName, tr("Invalid SPD file size."));
        break;
    }

    QByteArray contents = file.readAll();

    if (spd != nullptr) {
      delete (spd);
    }

    if (contents.length() != expectedBytes) {
      QMessageBox::critical(this, appName, tr("Failed to fully load file."));
      return;
    }

    // TODO: Find proper way to do this
    QByteArray spdRawBytes = contents.sliced(0x0, ddr5_structs::eepromBaseSize);
    ddr5_structs::SPD_Struct rawSPD = *reinterpret_cast<ddr5_structs::SPD_Struct *>(spdRawBytes.data());

    if (rawSPD.memoryType != 0x12) {
      QMessageBox::critical(this, appName, tr("Invalid memory type in SPD."));
      return;
    }

    switch (rawSPD.moduleType) {
      case 0x02:  // ModuleType::UnbufferedDIMM
        break;

      case 0x03:  // ModuleType::SO_DIMM
        break;

      case 0x05:  // ModuleType::CUDIMM
        QMessageBox::warning(this, appName, tr("CUDIMM detected. High change this will mangle your SPD!"));
        break;

      default:
        QMessageBox::warning(this, appName,
                             tr("Untested module type, only UDIMM or SODIMM memory has been "
                                "tested.\nHigh change this will mangle your SPD!"));
        break;
    }

    QByteArray extraData;

    switch (expectedBytes) {
      // Regular 1K eeprom size
      case ddr5_structs::eepromBaseSize:
        spd = new DDR5SPD(rawSPD);
        break;
      // 2K EEPROM keep bytes past 0x400
      case ddr5_structs::eepromExtendedSize:
        extraData = contents.sliced(ddr5_structs::eepromBaseSize, ddr5_structs::eepromBaseSize);
        spd = new DDR5SPD(rawSPD, extraData);
        break;
      default:
        QMessageBox::critical(this, appName, tr("Should never happen.."));
        break;
    }

    if (!spd->isCRCValid()) {
      QMessageBox::warning(this, appName, tr("JEDEC section checksum error, will be fixed by saving."));
    }

    enableUI();
    reloadUI();
  }
}

void MainWindow::saveFile() {
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
        QMessageBox::critical(this, appName, tr("Failed to save file."));
      }

      if (file.isWritable()) {
        QByteArray bytes = spd->getBytes();
        file.write(bytes, bytes.length());
        file.close();
      } else {
        QMessageBox::critical(this, appName, tr("Failed to save file (read only?)."));
      }
    }
  }
}

void MainWindow::closeFile() {
  disableUI();
  clearUI();

  if (spd != nullptr) {
    delete (spd);
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
      QMessageBox::critical(this, appName, tr("Failed to load file."));
    }

    if (file.size() != EXPOProfileSize) {
      QMessageBox::critical(this, appName, tr("Invalid EXPO profile file size."));
    }

    QByteArray contents = file.readAll();

    if (contents.length() != EXPOProfileSize) {
      QMessageBox::critical(this, appName, tr("Invalid EXPO profile file size."));
    } else {
      EXPO_ProfileStruct readProfile = *reinterpret_cast<EXPO_ProfileStruct *>(contents.data());
      return readProfile;
    }
  }

  EXPO_ProfileStruct empty{};
  return empty;
}

void MainWindow::exportEXPOProfile(const EXPO_ProfileStruct &expoProfile) {
  // Actually save
  QString fileName = QFileDialog::getSaveFileName(this, "Save EXPO File", QDir::currentPath(), "EXPO Files (*.expo *.bin);;All Files (*.*)");

  if (!fileName.isEmpty()) {
    // save contents to the selected file
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
      QMessageBox::critical(this, appName, tr("Failed to save file."));
    }

    if (file.isWritable()) {
      file.write(reinterpret_cast<const char *>(&expoProfile), EXPOProfileSize);
      file.close();
    } else {
      QMessageBox::critical(this, appName, tr("Failed to save file (read only?)."));
    }
  }
}

void MainWindow::importEXPOProfile1FromXMP1() {
  if (spd == nullptr) {
    return;
  }

  if (!spd->isEXPOPresent()) {
    QMessageBox::critical(this, appName, tr("EXPO is not present, please create EXPO block first."));
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
    QMessageBox::critical(this, appName, tr("EXPO is not present, please create EXPO block first."));
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
    QMessageBox::critical(this, appName, tr("EXPO is not present, please create EXPO block first."));
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
    QMessageBox::critical(this, appName, tr("EXPO is not present, please create EXPO block first."));
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
    QMessageBox::critical(this, appName, tr("EXPO is not present, please create EXPO block first."));
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
    QMessageBox::critical(this, appName, tr("EXPO is not present, please create EXPO block first."));
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

void MainWindow::exportXMPProfile(const XMP_ProfileStruct &xmpProfile) {
  // Actually save
  QString fileName = QFileDialog::getSaveFileName(this, "Save XMP File", QDir::currentPath(), "XMP Files (*.xmp *.bin);;All Files (*.*)");

  if (!fileName.isEmpty()) {
    // save contents to the selected file
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
      QMessageBox::critical(this, appName, tr("Failed to save file."));
    }

    if (file.isWritable()) {
      file.write(reinterpret_cast<const char *>(&xmpProfile), XMPProfileSize);
      file.close();
    } else {
      QMessageBox::critical(this, appName, tr("Failed to save file (read only?)."));
    }
  }
}

void MainWindow::exportXMPProfile1() {
  if (spd != nullptr) {
    exportXMPProfile(spd->xmpBundle.profile1.getCopy());
  }
}

void MainWindow::exportXMPProfile2() {
  if (spd != nullptr) {
    exportXMPProfile(spd->xmpBundle.profile2.getCopy());
  }
}

void MainWindow::exportXMPProfile3() {
  if ((spd != nullptr) && (!spd->isEXPOPresent())) {
    exportXMPProfile(spd->xmpBundle.profile3.getCopy());
  }
}

void MainWindow::exportXMPProfileU1() {
  if ((spd != nullptr) && (!spd->isEXPOPresent())) {
    exportXMPProfile(spd->xmpBundle.profileUser1.getCopy());
  }
}

void MainWindow::exportXMPProfileU2() {
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
      QMessageBox::critical(this, appName, tr("Failed to load file."));
    }

    if (file.size() != XMPProfileSize) {
      QMessageBox::critical(this, appName, tr("Invalid XMP 3.0 profile file size."));
    }

    QByteArray contents = file.readAll();

    if (contents.length() != XMPProfileSize) {
      QMessageBox::critical(this, appName, tr("Invalid XMP 3.0 profile file size."));
    } else {
      XMP_ProfileStruct readProfile = *reinterpret_cast<XMP_ProfileStruct *>(contents.data());
      return readProfile;
    }
  }

  XMP_ProfileStruct empty{};
  return empty;
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

bool MainWindow::saveFileEnabled() {
  return spd != nullptr;
}

bool MainWindow::closeFileEnabled() {
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

  if (spd->isXMPPresent()) {
    toggleXMPUI(true, spd->isEXPOPresent());
  }

  if (spd->isEXPOPresent()) {
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
  ui->spinBoxtAA_Ticks->setValue(0);
  ui->spinBoxtRCD->setValue(0);
  ui->spinBoxtRCD_Ticks->setValue(0);
  ui->spinBoxtRP->setValue(0);
  ui->spinBoxtRP_Ticks->setValue(0);
  ui->spinBoxtRAS->setValue(0);
  ui->spinBoxtRAS_Ticks->setValue(0);
  ui->spinBoxtRC->setValue(0);
  ui->spinBoxtRC_Ticks->setValue(0);
  ui->spinBoxtWR->setValue(0);
  ui->spinBoxtWR_Ticks->setValue(0);
  ui->spinBoxtRFC1->setValue(0);
  ui->spinBoxtRFC1_Ticks->setValue(0);
  ui->spinBoxtRFC2->setValue(0);
  ui->spinBoxtRFC2_Ticks->setValue(0);
  ui->spinBoxtRFC->setValue(0);
  ui->spinBoxtRFC_Ticks->setValue(0);
  ui->spinBoxtRRD_L->setValue(0);
  ui->spinBoxtRRD_L_LCLK->setValue(0);
  ui->spinBoxtRRD_L_Ticks->setValue(0);
  ui->spinBoxtCCD_L->setValue(0);
  ui->spinBoxtCCD_L_LCLK->setValue(0);
  ui->spinBoxtCCD_L_Ticks->setValue(0);
  ui->spinBoxtCCD_L_WR->setValue(0);
  ui->spinBoxtCCD_L_WR_LCLK->setValue(0);
  ui->spinBoxtCCD_L_WR_Ticks->setValue(0);
  ui->spinBoxtCCD_L_WR2->setValue(0);
  ui->spinBoxtCCD_L_WR2_LCLK->setValue(0);
  ui->spinBoxtCCD_L_WR2_Ticks->setValue(0);
  ui->spinBoxtFAW->setValue(0);
  ui->spinBoxtFAW_LCLK->setValue(0);
  ui->spinBoxtFAW_Ticks->setValue(0);
  ui->spinBoxtCCD_L_WTR->setValue(0);
  ui->spinBoxtCCD_L_WTR_LCLK->setValue(0);
  ui->spinBoxtCCD_L_WTR_Ticks->setValue(0);
  ui->spinBoxtCCD_S_WTR->setValue(0);
  ui->spinBoxtCCD_S_WTR_LCLK->setValue(0);
  ui->spinBoxtCCD_S_WTR_Ticks->setValue(0);
  ui->spinBoxtRTP->setValue(0);
  ui->spinBoxtRTP_LCLK->setValue(0);
  ui->spinBoxtRTP_Ticks->setValue(0);
}

void MainWindow::reloadUI() {
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

// EXPO <-> Conversion
XMP_ProfileStruct MainWindow::importXMPProfileFromEXPO(const EXPO_ProfileStruct &expo) {
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
