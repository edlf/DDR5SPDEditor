#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "ddr5spd_structs.h"

void MainWindow::wipeXMPProfile1() {
  spd->xmpBundle.setXMP1Enabled(false);
  spd->xmpBundle.profile1.wipeProfile();
  reloadXMP1Tab();
}

void MainWindow::loadSampleXMPProfile1() {
  spd->xmpBundle.setXMP1Enabled(true);
  spd->xmpBundle.profile1.resetProfile();
  reloadXMP1Tab();
}

void MainWindow::importXMPProfile1() {
  if (spd == nullptr) {
    return;
  }

  spd->xmpBundle.profile1.import(importXMPProfile());
  reloadXMP1Tab();
}

void MainWindow::exportXMPProfile1() {
  if (spd != nullptr) {
    exportXMPProfile(spd->xmpBundle.profile1.getCopy());
  }
}

void MainWindow::reloadXMP1Tab() {
  // XMP Header
  ui->leProfileName_XMP1->setText(QString::fromStdString(spd->xmpBundle.getXMP1ProfileName()));
  ui->cbEnabled_XMP1->setChecked(spd->xmpBundle.isXMP1Enabled());

  // XMP Profile
  auto &xmp_profile = spd->xmpBundle.profile1;

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
    case CommandRate::Undefined:
      ui->cbCommandRate_XMP1->setCurrentIndex(0);
      break;

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
  ui->ltAA_Ticks_XMP1->setText(QString::number(xmp_profile.gettAA_tick()));
  ui->sbtRCD_XMP1->setValue(xmp_profile.gettRCD());
  ui->ltRCD_Ticks_XMP1->setText(QString::number(xmp_profile.gettRCD_tick()));
  ui->sbtRP_XMP1->setValue(xmp_profile.gettRP());
  ui->ltRP_Ticks_XMP1->setText(QString::number(xmp_profile.gettRP_tick()));
  ui->sbtRAS_XMP1->setValue(xmp_profile.gettRAS());
  ui->ltRAS_Ticks_XMP1->setText(QString::number(xmp_profile.gettRAS_tick()));
  ui->sbtRC_XMP1->setValue(xmp_profile.gettRC());
  ui->ltRC_Ticks_XMP1->setText(QString::number(xmp_profile.gettRC_tick()));
  ui->sbtWR_XMP1->setValue(xmp_profile.gettWR());
  ui->ltWR_Ticks_XMP1->setText(QString::number(xmp_profile.gettWR_tick()));
  ui->sbtRFC1_XMP1->setValue(xmp_profile.gettRFC1());
  ui->ltRFC1_Ticks_XMP1->setText(QString::number(xmp_profile.gettRFC1_tick()));
  ui->sbtRFC2_XMP1->setValue(xmp_profile.gettRFC2());
  ui->ltRFC2_Ticks_XMP1->setText(QString::number(xmp_profile.gettRFC2_tick()));
  ui->sbtRFC_XMP1->setValue(xmp_profile.gettRFC());
  ui->ltRFC_Ticks_XMP1->setText(QString::number(xmp_profile.gettRFC_tick()));
  ui->sbtRRD_L_XMP1->setValue(xmp_profile.gettRRD_L());
  ui->sbtRRD_L_LCLK_XMP1->setValue(xmp_profile.gettRRD_L_lowerLimit());
  ui->ltRRD_L_Ticks_XMP1->setText(QString::number(xmp_profile.gettRRD_L_tick()));
  ui->sbtCCD_L_XMP1->setValue(xmp_profile.gettCCD_L());
  ui->sbtCCD_L_LCLK_XMP1->setValue(xmp_profile.gettCCD_L_lowerLimit());
  ui->ltCCD_L_Ticks_XMP1->setText(QString::number(xmp_profile.gettCCD_L_tick()));
  ui->sbtCCD_L_WR_XMP1->setValue(xmp_profile.gettCCD_L_WR());
  ui->sbtCCD_L_WR_LCLK_XMP1->setValue(xmp_profile.gettCCD_L_WR_lowerLimit());
  ui->ltCCD_L_WR_Ticks_XMP1->setText(QString::number(xmp_profile.gettCCD_L_WR_tick()));
  ui->sbtCCD_L_WR2_XMP1->setValue(xmp_profile.gettCCD_L_WR2());
  ui->sbtCCD_L_WR2_LCLK_XMP1->setValue(xmp_profile.gettCCD_L_WR2_lowerLimit());
  ui->ltCCD_L_WR2_Ticks_XMP1->setText(QString::number(xmp_profile.gettCCD_L_WR2_tick()));
  ui->sbtFAW_XMP1->setValue(xmp_profile.gettFAW());
  ui->sbtFAW_LCLK_XMP1->setValue(xmp_profile.gettFAW_lowerLimit());
  ui->ltFAW_Ticks_XMP1->setText(QString::number(xmp_profile.gettFAW_tick()));
  ui->sbtCCD_L_WTR_XMP1->setValue(xmp_profile.gettCCD_L_WTR());
  ui->sbtCCD_L_WTR_LCLK_XMP1->setValue(xmp_profile.gettCCD_L_WTR_lowerLimit());
  ui->ltCCD_L_WTR_Ticks_XMP1->setText(QString::number(xmp_profile.gettCCD_L_WTR_tick()));
  ui->sbtCCD_S_WTR_XMP1->setValue(xmp_profile.gettCCD_S_WTR());
  ui->sbtCCD_S_WTR_LCLK_XMP1->setValue(xmp_profile.gettCCD_S_WTR_lowerLimit());
  ui->ltCCD_S_WTR_Ticks_XMP1->setText(QString::number(xmp_profile.gettCCD_S_WTR_tick()));
  ui->sbtRTP_XMP1->setValue(xmp_profile.gettRTP());
  ui->sbtRTP_LCLK_XMP1->setValue(xmp_profile.gettRTP_lowerLimit());
  ui->ltRTP_Ticks_XMP1->setText(QString::number(xmp_profile.gettRTP_tick()));
}

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

void MainWindow::on_sbVDD_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.setVDD(value);
}

void MainWindow::on_sbVDDQ_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.setVDDQ(value);
}

void MainWindow::on_sbVPP_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.setVPP(value);
}

void MainWindow::on_sbVmemctrl_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.setVMEMCtrl(value);
}

void MainWindow::on_spinMinCycleTime_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.setMinCycleTime(value);

  QString frequencyStr = QString::number(spd->xmpBundle.profile1.getFrequency()) + " MHz";
  QString mtStr = QString::number(spd->xmpBundle.profile1.getMT()) + " MT/s";

  ui->lFrequencyValue_XMP1->setText(frequencyStr);
  ui->lMTValue_XMP1->setText(mtStr);
}

void MainWindow::on_sbVDD_XMP1_editingFinished() {
  ui->sbVDD_XMP1->setValue(spd->xmpBundle.profile1.getVDD());
}

void MainWindow::on_sbVDDQ_XMP1_editingFinished() {
  ui->sbVDDQ_XMP1->setValue(spd->xmpBundle.profile1.getVDDQ());
}

void MainWindow::on_sbVPP_XMP1_editingFinished() {
  ui->sbVPP_XMP1->setValue(spd->xmpBundle.profile1.getVPP());
}

void MainWindow::on_sbVmemctrl_XMP1_editingFinished() {
  ui->sbVmemctrl_XMP1->setValue(spd->xmpBundle.profile1.getVMEMCtrl());
}

void MainWindow::on_spinMinCycleTime_XMP1_editingFinished() {
  ui->spinMinCycleTime_XMP1->setValue(spd->xmpBundle.profile1.getMinCycleTime());

  QString frequencyStr = QString::number(spd->xmpBundle.profile1.getFrequency()) + " MHz";
  QString mtStr = QString::number(spd->xmpBundle.profile1.getMT()) + " MT/s";

  ui->lFrequencyValue_XMP1->setText(frequencyStr);
  ui->lMTValue_XMP1->setText(mtStr);
}

void MainWindow::on_cbCommandRate_XMP1_currentIndexChanged(int index) {
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

void MainWindow::on_cbCL20_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(20, value);
}
void MainWindow::on_cbCL22_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(22, value);
}
void MainWindow::on_cbCL24_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(24, value);
}
void MainWindow::on_cbCL26_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(26, value);
}
void MainWindow::on_cbCL28_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(28, value);
}
void MainWindow::on_cbCL30_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(30, value);
}
void MainWindow::on_cbCL32_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(32, value);
}
void MainWindow::on_cbCL34_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(34, value);
}
void MainWindow::on_cbCL36_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(36, value);
}
void MainWindow::on_cbCL38_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(38, value);
}
void MainWindow::on_cbCL40_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(40, value);
}
void MainWindow::on_cbCL42_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(42, value);
}
void MainWindow::on_cbCL44_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(44, value);
}
void MainWindow::on_cbCL46_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(46, value);
}
void MainWindow::on_cbCL48_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(48, value);
}
void MainWindow::on_cbCL50_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(50, value);
}
void MainWindow::on_cbCL52_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(52, value);
}
void MainWindow::on_cbCL54_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(54, value);
}
void MainWindow::on_cbCL56_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(56, value);
}
void MainWindow::on_cbCL58_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(58, value);
}
void MainWindow::on_cbCL60_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(60, value);
}
void MainWindow::on_cbCL62_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(62, value);
}
void MainWindow::on_cbCL64_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(64, value);
}
void MainWindow::on_cbCL66_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(66, value);
}
void MainWindow::on_cbCL68_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(68, value);
}
void MainWindow::on_cbCL70_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(70, value);
}
void MainWindow::on_cbCL72_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(72, value);
}
void MainWindow::on_cbCL74_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(74, value);
}
void MainWindow::on_cbCL76_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(76, value);
}
void MainWindow::on_cbCL78_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(78, value);
}
void MainWindow::on_cbCL80_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(80, value);
}
void MainWindow::on_cbCL82_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(82, value);
}
void MainWindow::on_cbCL84_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(84, value);
}
void MainWindow::on_cbCL86_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(86, value);
}
void MainWindow::on_cbCL88_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(88, value);
}
void MainWindow::on_cbCL90_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(90, value);
}
void MainWindow::on_cbCL92_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(92, value);
}
void MainWindow::on_cbCL94_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(94, value);
}
void MainWindow::on_cbCL96_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(96, value);
}
void MainWindow::on_cbCL98_XMP1_toggled(bool value) {
  spd->xmpBundle.profile1.setCLSupported(98, value);
}

void MainWindow::on_sbtAA_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settAA(value);
  ui->ltAA_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettAA_tick()));
}

void MainWindow::on_sbtRCD_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settRCD(value);
  ui->ltRCD_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRCD_tick()));
}

void MainWindow::on_sbtRP_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settRP(value);
  ui->ltRP_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRP_tick()));
}

void MainWindow::on_sbtRAS_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settRAS(value);
  ui->ltRAS_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRAS_tick()));
}

void MainWindow::on_sbtRC_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settRC(value);
  ui->ltRC_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRC_tick()));
}

void MainWindow::on_sbtWR_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settWR(value);
  ui->ltWR_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettWR_tick()));
}

void MainWindow::on_sbtRFC1_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settRFC1(value);
  ui->ltRFC1_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRFC1_tick()));
}

void MainWindow::on_sbtRFC2_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settRFC2(value);
  ui->ltRFC2_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRFC2_tick()));
}

void MainWindow::on_sbtRFC_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settRFC(value);
  ui->ltRFC_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRFC_tick()));
}

void MainWindow::on_sbtRRD_L_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settRRD_L(value);
  ui->ltRRD_L_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRRD_L()));
}

void MainWindow::on_sbtRRD_L_LCLK_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settRRD_L_lowerLimit(value);
}

void MainWindow::on_sbtCCD_L_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settCCD_L(value);
  ui->ltCCD_L_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettCCD_L_tick()));
}

void MainWindow::on_sbtCCD_L_LCLK_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settCCD_L_lowerLimit(value);
}

void MainWindow::on_sbtCCD_L_WR_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settCCD_L_WR(value);
  ui->ltCCD_L_WR_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettCCD_L_WR_tick()));
}

void MainWindow::on_sbtCCD_L_WR_LCLK_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settCCD_L_WR_lowerLimit(value);
}

void MainWindow::on_sbtCCD_L_WR2_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settCCD_L_WR2(value);
  ui->ltCCD_L_WR2_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettCCD_L_WR2_tick()));
}

void MainWindow::on_sbtCCD_L_WR2_LCLK_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settCCD_L_WR2_lowerLimit(value);
}

void MainWindow::on_sbtFAW_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settFAW(value);
  ui->ltFAW_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettFAW_tick()));
}

void MainWindow::on_sbtFAW_LCLK_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settFAW_lowerLimit(value);
}

void MainWindow::on_sbtCCD_L_WTR_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settCCD_L_WTR(value);
  ui->ltCCD_L_WTR_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettCCD_L_WTR_tick()));
}

void MainWindow::on_sbtCCD_L_WTR_LCLK_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settCCD_L_WTR_lowerLimit(value);
}

void MainWindow::on_sbtCCD_S_WTR_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settCCD_S_WTR(value);
  ui->ltCCD_S_WTR_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtCCD_S_WTR_LCLK_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settCCD_S_WTR_lowerLimit(value);
  ui->ltCCD_S_WTR_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtRTP_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settRTP(value);
  ui->ltRTP_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRTP_tick()));
}

void MainWindow::on_sbtRTP_LCLK_XMP1_valueChanged(int value) {
  spd->xmpBundle.profile1.settRTP_lowerLimit(value);
}

void MainWindow::on_sbtAA_XMP1_editingFinished() {
  ui->sbtAA_XMP1->setValue(spd->xmpBundle.profile1.gettAA());
  ui->ltAA_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettAA_tick()));
}

void MainWindow::on_sbtRCD_XMP1_editingFinished() {
  ui->sbtRCD_XMP1->setValue(spd->xmpBundle.profile1.gettRCD());
  ui->ltRCD_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRCD_tick()));
}

void MainWindow::on_sbtRP_XMP1_editingFinished() {
  ui->sbtRP_XMP1->setValue(spd->xmpBundle.profile1.gettRP());
  ui->ltRP_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRP_tick()));
}

void MainWindow::on_sbtRAS_XMP1_editingFinished() {
  ui->sbtRAS_XMP1->setValue(spd->xmpBundle.profile1.gettRAS());
  ui->ltRAS_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRAS_tick()));
}

void MainWindow::on_sbtRC_XMP1_editingFinished() {
  ui->sbtRC_XMP1->setValue(spd->xmpBundle.profile1.gettRC());
  ui->ltRC_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRC_tick()));
}

void MainWindow::on_sbtWR_XMP1_editingFinished() {
  ui->sbtWR_XMP1->setValue(spd->xmpBundle.profile1.gettWR());
  ui->ltWR_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettWR_tick()));
}

void MainWindow::on_sbtRFC1_XMP1_editingFinished() {
  ui->sbtRFC1_XMP1->setValue(spd->xmpBundle.profile1.gettAA());
  spd->xmpBundle.profile1.settRFC1(ui->sbtRFC1_XMP1->value());
  ui->ltRFC1_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRFC1_tick()));
}

void MainWindow::on_sbtRFC2_XMP1_editingFinished() {
  ui->sbtRFC2_XMP1->setValue(spd->xmpBundle.profile1.gettRFC2());
  ui->ltRFC2_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRFC2_tick()));
}

void MainWindow::on_sbtRFC_XMP1_editingFinished() {
  ui->sbtRFC_XMP1->setValue(spd->xmpBundle.profile1.gettRFC());
  ui->ltRFC_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRFC_tick()));
}

void MainWindow::on_sbtRRD_L_XMP1_editingFinished() {
  ui->sbtRRD_L_XMP1->setValue(spd->xmpBundle.profile1.gettRRD_L());
  ui->ltRRD_L_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRRD_L_tick()));
}

void MainWindow::on_sbtRRD_L_LCLK_XMP1_editingFinished() {
  ui->sbtRRD_L_LCLK_XMP1->setValue(spd->xmpBundle.profile1.gettRRD_L_lowerLimit());
}

void MainWindow::on_sbtCCD_L_XMP1_editingFinished() {
  ui->sbtCCD_L_XMP1->setValue(spd->xmpBundle.profile1.gettCCD_L());
  ui->ltCCD_L_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettCCD_L_tick()));
}

void MainWindow::on_sbtCCD_L_LCLK_XMP1_editingFinished() {
  ui->sbtCCD_L_LCLK_XMP1->setValue(spd->xmpBundle.profile1.gettCCD_L_lowerLimit());
}

void MainWindow::on_sbtCCD_L_WR_XMP1_editingFinished() {
  ui->sbtCCD_L_WR_XMP1->setValue(spd->xmpBundle.profile1.gettCCD_L_WR());
  ui->ltCCD_L_WR_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettCCD_L_WR_tick()));
}

void MainWindow::on_sbtCCD_L_WR_LCLK_XMP1_editingFinished() {
  ui->sbtCCD_L_WR_LCLK_XMP1->setValue(spd->xmpBundle.profile1.gettCCD_L_WR_lowerLimit());
}

void MainWindow::on_sbtCCD_L_WR2_XMP1_editingFinished() {
  ui->sbtCCD_L_WR2_XMP1->setValue(spd->xmpBundle.profile1.gettCCD_L_WR2());
  ui->ltCCD_L_WR2_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettCCD_L_WR2_tick()));
}

void MainWindow::on_sbtCCD_L_WR2_LCLK_XMP1_editingFinished() {
  ui->sbtCCD_L_WR2_LCLK_XMP1->setValue(spd->xmpBundle.profile1.gettCCD_L_WR2_lowerLimit());
}

void MainWindow::on_sbtFAW_XMP1_editingFinished() {
  ui->sbtFAW_XMP1->setValue(spd->xmpBundle.profile1.gettFAW());
  ui->ltFAW_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettFAW_tick()));
}

void MainWindow::on_sbtFAW_LCLK_XMP1_editingFinished() {
  ui->sbtFAW_LCLK_XMP1->setValue(spd->xmpBundle.profile1.gettFAW_lowerLimit());
}

void MainWindow::on_sbtCCD_L_WTR_XMP1_editingFinished() {
  ui->sbtCCD_L_WTR_XMP1->setValue(spd->xmpBundle.profile1.gettCCD_L_WTR());
  ui->ltCCD_L_WTR_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettCCD_L_WTR_tick()));
}

void MainWindow::on_sbtCCD_L_WTR_LCLK_XMP1_editingFinished() {
  ui->sbtCCD_L_WTR_LCLK_XMP1->setValue(spd->xmpBundle.profile1.gettCCD_L_WTR_lowerLimit());
}

void MainWindow::on_sbtCCD_S_WTR_XMP1_editingFinished() {
  ui->sbtCCD_S_WTR_XMP1->setValue(spd->xmpBundle.profile1.gettCCD_S_WTR());
  ui->ltCCD_S_WTR_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtCCD_S_WTR_LCLK_XMP1_editingFinished() {
  ui->sbtCCD_S_WTR_LCLK_XMP1->setValue(spd->xmpBundle.profile1.gettCCD_S_WTR_lowerLimit());
  ui->ltCCD_S_WTR_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtRTP_XMP1_editingFinished() {
  ui->sbtRTP_XMP1->setValue(spd->xmpBundle.profile1.gettRTP());
  ui->ltRTP_Ticks_XMP1->setText(QString::number(spd->xmpBundle.profile1.gettRTP_tick()));
}

void MainWindow::on_sbtRTP_LCLK_XMP1_editingFinished() {
  ui->sbtRTP_LCLK_XMP1->setValue(spd->xmpBundle.profile1.gettRTP_lowerLimit());
}
