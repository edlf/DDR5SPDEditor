#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "ddr5spd_structs.h"

void MainWindow::importXMPProfile2() {
  if (spd == nullptr) {
    return;
  }

  spd->xmpBundle.profile2.import(importXMPProfile());
  reloadXMP2Tab();
}

void MainWindow::reloadXMP2Tab() {
  // XMP Header
  ui->leProfileName_XMP2->setText(QString::fromStdString(spd->xmpBundle.getXMP2ProfileName()));
  ui->cbEnabled_XMP2->setChecked(spd->xmpBundle.isXMP2Enabled());

  // XMP Profile
  auto &xmp_profile = spd->xmpBundle.profile2;

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
    case CommandRate::Undefined:
      ui->cbCommandRate_XMP2->setCurrentIndex(0);
      break;

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
  ui->ltAA_Ticks_XMP2->setText(QString::number(xmp_profile.gettAA_tick()));
  ui->sbtRCD_XMP2->setValue(xmp_profile.gettRCD());
  ui->ltRCD_Ticks_XMP2->setText(QString::number(xmp_profile.gettRCD_tick()));
  ui->sbtRP_XMP2->setValue(xmp_profile.gettRP());
  ui->ltRP_Ticks_XMP2->setText(QString::number(xmp_profile.gettRP_tick()));
  ui->sbtRAS_XMP2->setValue(xmp_profile.gettRAS());
  ui->ltRAS_Ticks_XMP2->setText(QString::number(xmp_profile.gettRAS_tick()));
  ui->sbtRC_XMP2->setValue(xmp_profile.gettRC());
  ui->ltRC_Ticks_XMP2->setText(QString::number(xmp_profile.gettRC_tick()));
  ui->sbtWR_XMP2->setValue(xmp_profile.gettWR());
  ui->ltWR_Ticks_XMP2->setText(QString::number(xmp_profile.gettWR_tick()));
  ui->sbtRFC1_XMP2->setValue(xmp_profile.gettRFC1());
  ui->ltRFC1_Ticks_XMP2->setText(QString::number(xmp_profile.gettRFC1_tick()));
  ui->sbtRFC2_XMP2->setValue(xmp_profile.gettRFC2());
  ui->ltRFC2_Ticks_XMP2->setText(QString::number(xmp_profile.gettRFC2_tick()));
  ui->sbtRFC_XMP2->setValue(xmp_profile.gettRFC());
  ui->ltRFC_Ticks_XMP2->setText(QString::number(xmp_profile.gettRFC_tick()));
  ui->sbtRRD_L_XMP2->setValue(xmp_profile.gettRRD_L());
  ui->sbtRRD_L_LCLK_XMP2->setValue(xmp_profile.gettRRD_L_lowerLimit());
  ui->ltRRD_L_Ticks_XMP2->setText(QString::number(xmp_profile.gettRRD_L_tick()));
  ui->sbtCCD_L_XMP2->setValue(xmp_profile.gettCCD_L());
  ui->sbtCCD_L_LCLK_XMP2->setValue(xmp_profile.gettCCD_L_lowerLimit());
  ui->ltCCD_L_Ticks_XMP2->setText(QString::number(xmp_profile.gettCCD_L_tick()));
  ui->sbtCCD_L_WR_XMP2->setValue(xmp_profile.gettCCD_L_WR());
  ui->sbtCCD_L_WR_LCLK_XMP2->setValue(xmp_profile.gettCCD_L_WR_lowerLimit());
  ui->ltCCD_L_WR_Ticks_XMP2->setText(QString::number(xmp_profile.gettCCD_L_WR_tick()));
  ui->sbtCCD_L_WR2_XMP2->setValue(xmp_profile.gettCCD_L_WR2());
  ui->sbtCCD_L_WR2_LCLK_XMP2->setValue(xmp_profile.gettCCD_L_WR2_lowerLimit());
  ui->ltCCD_L_WR2_Ticks_XMP2->setText(QString::number(xmp_profile.gettCCD_L_WR2_tick()));
  ui->sbtFAW_XMP2->setValue(xmp_profile.gettFAW());
  ui->sbtFAW_LCLK_XMP2->setValue(xmp_profile.gettFAW_lowerLimit());
  ui->ltFAW_Ticks_XMP2->setText(QString::number(xmp_profile.gettFAW_tick()));
  ui->sbtCCD_L_WTR_XMP2->setValue(xmp_profile.gettCCD_L_WTR());
  ui->sbtCCD_L_WTR_LCLK_XMP2->setValue(xmp_profile.gettCCD_L_WTR_lowerLimit());
  ui->ltCCD_L_WTR_Ticks_XMP2->setText(QString::number(xmp_profile.gettCCD_L_WTR_tick()));
  ui->sbtCCD_S_WTR_XMP2->setValue(xmp_profile.gettCCD_S_WTR());
  ui->sbtCCD_S_WTR_LCLK_XMP2->setValue(xmp_profile.gettCCD_S_WTR_lowerLimit());
  ui->ltCCD_S_WTR_Ticks_XMP2->setText(QString::number(xmp_profile.gettCCD_S_WTR_tick()));
  ui->sbtRTP_XMP2->setValue(xmp_profile.gettRTP());
  ui->sbtRTP_LCLK_XMP2->setValue(xmp_profile.gettRTP_lowerLimit());
  ui->ltRTP_Ticks_XMP2->setText(QString::number(xmp_profile.gettRTP_tick()));
}

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

void MainWindow::on_sbVDD_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.setVDD(value);
}

void MainWindow::on_sbVDDQ_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.setVDDQ(value);
}

void MainWindow::on_sbVPP_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.setVPP(value);
}

void MainWindow::on_sbVmemctrl_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.setVMEMCtrl(value);
}

void MainWindow::on_spinMinCycleTime_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.setMinCycleTime(value);

  QString frequencyStr = QString::number(spd->xmpBundle.profile2.getFrequency()) + " MHz";
  QString mtStr = QString::number(spd->xmpBundle.profile2.getMT()) + " MT/s";

  ui->lFrequencyValue_XMP2->setText(frequencyStr);
  ui->lMTValue_XMP2->setText(mtStr);
}

void MainWindow::on_sbVDD_XMP2_editingFinished() {
  ui->sbVDD_XMP2->setValue(spd->xmpBundle.profile2.getVDD());
}

void MainWindow::on_sbVDDQ_XMP2_editingFinished() {
  ui->sbVDDQ_XMP2->setValue(spd->xmpBundle.profile2.getVDDQ());
}

void MainWindow::on_sbVPP_XMP2_editingFinished() {
  ui->sbVPP_XMP2->setValue(spd->xmpBundle.profile2.getVPP());
}

void MainWindow::on_sbVmemctrl_XMP2_editingFinished() {
  ui->sbVmemctrl_XMP2->setValue(spd->xmpBundle.profile2.getVMEMCtrl());
}

void MainWindow::on_spinMinCycleTime_XMP2_editingFinished() {
  ui->spinMinCycleTime_XMP2->setValue(spd->xmpBundle.profile2.getMinCycleTime());

  QString frequencyStr = QString::number(spd->xmpBundle.profile2.getFrequency()) + " MHz";
  QString mtStr = QString::number(spd->xmpBundle.profile2.getMT()) + " MT/s";

  ui->lFrequencyValue_XMP2->setText(frequencyStr);
  ui->lMTValue_XMP2->setText(mtStr);
}

void MainWindow::on_cbCommandRate_XMP2_currentIndexChanged(int index) {
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

void MainWindow::on_cbCL20_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(20, value);
}
void MainWindow::on_cbCL22_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(22, value);
}
void MainWindow::on_cbCL24_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(24, value);
}
void MainWindow::on_cbCL26_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(26, value);
}
void MainWindow::on_cbCL28_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(28, value);
}
void MainWindow::on_cbCL30_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(30, value);
}
void MainWindow::on_cbCL32_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(32, value);
}
void MainWindow::on_cbCL34_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(34, value);
}
void MainWindow::on_cbCL36_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(36, value);
}
void MainWindow::on_cbCL38_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(38, value);
}
void MainWindow::on_cbCL40_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(40, value);
}
void MainWindow::on_cbCL42_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(42, value);
}
void MainWindow::on_cbCL44_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(44, value);
}
void MainWindow::on_cbCL46_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(46, value);
}
void MainWindow::on_cbCL48_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(48, value);
}
void MainWindow::on_cbCL50_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(50, value);
}
void MainWindow::on_cbCL52_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(52, value);
}
void MainWindow::on_cbCL54_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(54, value);
}
void MainWindow::on_cbCL56_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(56, value);
}
void MainWindow::on_cbCL58_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(58, value);
}
void MainWindow::on_cbCL60_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(60, value);
}
void MainWindow::on_cbCL62_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(62, value);
}
void MainWindow::on_cbCL64_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(64, value);
}
void MainWindow::on_cbCL66_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(66, value);
}
void MainWindow::on_cbCL68_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(68, value);
}
void MainWindow::on_cbCL70_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(70, value);
}
void MainWindow::on_cbCL72_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(72, value);
}
void MainWindow::on_cbCL74_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(74, value);
}
void MainWindow::on_cbCL76_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(76, value);
}
void MainWindow::on_cbCL78_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(78, value);
}
void MainWindow::on_cbCL80_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(80, value);
}
void MainWindow::on_cbCL82_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(82, value);
}
void MainWindow::on_cbCL84_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(84, value);
}
void MainWindow::on_cbCL86_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(86, value);
}
void MainWindow::on_cbCL88_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(88, value);
}
void MainWindow::on_cbCL90_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(90, value);
}
void MainWindow::on_cbCL92_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(92, value);
}
void MainWindow::on_cbCL94_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(94, value);
}
void MainWindow::on_cbCL96_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(96, value);
}
void MainWindow::on_cbCL98_XMP2_toggled(bool value) {
  spd->xmpBundle.profile2.setCLSupported(98, value);
}

void MainWindow::on_sbtAA_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settAA(value);
  ui->ltAA_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettAA_tick()));
}

void MainWindow::on_sbtRCD_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settRCD(value);
  ui->ltRCD_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRCD_tick()));
}

void MainWindow::on_sbtRP_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settRP(value);
  ui->ltRP_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRP_tick()));
}

void MainWindow::on_sbtRAS_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settRAS(value);
  ui->ltRAS_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRAS_tick()));
}

void MainWindow::on_sbtRC_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settRC(value);
  ui->ltRC_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRC_tick()));
}

void MainWindow::on_sbtWR_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settWR(value);
  ui->ltWR_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettWR_tick()));
}

void MainWindow::on_sbtRFC1_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settRFC1(value);
  ui->ltRFC1_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRFC1_tick()));
}

void MainWindow::on_sbtRFC2_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settRFC2(value);
  ui->ltRFC2_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRFC2_tick()));
}

void MainWindow::on_sbtRFC_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settRFC(value);
  ui->ltRFC_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRFC_tick()));
}

void MainWindow::on_sbtRRD_L_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settRRD_L(value);
  ui->ltRRD_L_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRRD_L()));
}

void MainWindow::on_sbtRRD_L_LCLK_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settRRD_L_lowerLimit(value);
}

void MainWindow::on_sbtCCD_L_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settCCD_L(value);
  ui->ltCCD_L_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettCCD_L_tick()));
}

void MainWindow::on_sbtCCD_L_LCLK_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settCCD_L_lowerLimit(value);
}

void MainWindow::on_sbtCCD_L_WR_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settCCD_L_WR(value);
  ui->ltCCD_L_WR_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettCCD_L_WR_tick()));
}

void MainWindow::on_sbtCCD_L_WR_LCLK_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settCCD_L_WR_lowerLimit(value);
}

void MainWindow::on_sbtCCD_L_WR2_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settCCD_L_WR2(value);
  ui->ltCCD_L_WR2_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettCCD_L_WR2_tick()));
}

void MainWindow::on_sbtCCD_L_WR2_LCLK_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settCCD_L_WR2_lowerLimit(value);
}

void MainWindow::on_sbtFAW_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settFAW(value);
  ui->ltFAW_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettFAW_tick()));
}

void MainWindow::on_sbtFAW_LCLK_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settFAW_lowerLimit(value);
}

void MainWindow::on_sbtCCD_L_WTR_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settCCD_L_WTR(value);
  ui->ltCCD_L_WTR_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettCCD_L_WTR_tick()));
}

void MainWindow::on_sbtCCD_L_WTR_LCLK_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settCCD_L_WTR_lowerLimit(value);
}

void MainWindow::on_sbtCCD_S_WTR_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settCCD_S_WTR(value);
  ui->ltCCD_S_WTR_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtCCD_S_WTR_LCLK_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settCCD_S_WTR_lowerLimit(value);
  ui->ltCCD_S_WTR_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtRTP_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settRTP(value);
  ui->ltRTP_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRTP_tick()));
}

void MainWindow::on_sbtRTP_LCLK_XMP2_valueChanged(int value) {
  spd->xmpBundle.profile2.settRTP_lowerLimit(value);
}

void MainWindow::on_sbtAA_XMP2_editingFinished() {
  ui->sbtAA_XMP2->setValue(spd->xmpBundle.profile2.gettAA());
  ui->ltAA_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettAA_tick()));
}

void MainWindow::on_sbtRCD_XMP2_editingFinished() {
  ui->sbtRCD_XMP2->setValue(spd->xmpBundle.profile2.gettRCD());
  ui->ltRCD_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRCD_tick()));
}

void MainWindow::on_sbtRP_XMP2_editingFinished() {
  ui->sbtRP_XMP2->setValue(spd->xmpBundle.profile2.gettRP());
  ui->ltRP_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRP_tick()));
}

void MainWindow::on_sbtRAS_XMP2_editingFinished() {
  ui->sbtRAS_XMP2->setValue(spd->xmpBundle.profile2.gettRAS());
  ui->ltRAS_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRAS_tick()));
}

void MainWindow::on_sbtRC_XMP2_editingFinished() {
  ui->sbtRC_XMP2->setValue(spd->xmpBundle.profile2.gettRC());
  ui->ltRC_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRC_tick()));
}

void MainWindow::on_sbtWR_XMP2_editingFinished() {
  ui->sbtWR_XMP2->setValue(spd->xmpBundle.profile2.gettWR());
  ui->ltWR_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettWR_tick()));
}

void MainWindow::on_sbtRFC1_XMP2_editingFinished() {
  ui->sbtRFC1_XMP2->setValue(spd->xmpBundle.profile2.gettAA());
  spd->xmpBundle.profile2.settRFC1(ui->sbtRFC1_XMP2->value());
  ui->ltRFC1_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRFC1_tick()));
}

void MainWindow::on_sbtRFC2_XMP2_editingFinished() {
  ui->sbtRFC2_XMP2->setValue(spd->xmpBundle.profile2.gettRFC2());
  ui->ltRFC2_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRFC2_tick()));
}

void MainWindow::on_sbtRFC_XMP2_editingFinished() {
  ui->sbtRFC_XMP2->setValue(spd->xmpBundle.profile2.gettRFC());
  ui->ltRFC_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRFC_tick()));
}

void MainWindow::on_sbtRRD_L_XMP2_editingFinished() {
  ui->sbtRRD_L_XMP2->setValue(spd->xmpBundle.profile2.gettRRD_L());
  ui->ltRRD_L_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRRD_L_tick()));
}

void MainWindow::on_sbtRRD_L_LCLK_XMP2_editingFinished() {
  ui->sbtRRD_L_LCLK_XMP2->setValue(spd->xmpBundle.profile2.gettRRD_L_lowerLimit());
}

void MainWindow::on_sbtCCD_L_XMP2_editingFinished() {
  ui->sbtCCD_L_XMP2->setValue(spd->xmpBundle.profile2.gettCCD_L());
  ui->ltCCD_L_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettCCD_L_tick()));
}

void MainWindow::on_sbtCCD_L_LCLK_XMP2_editingFinished() {
  ui->sbtCCD_L_LCLK_XMP2->setValue(spd->xmpBundle.profile2.gettCCD_L_lowerLimit());
}

void MainWindow::on_sbtCCD_L_WR_XMP2_editingFinished() {
  ui->sbtCCD_L_WR_XMP2->setValue(spd->xmpBundle.profile2.gettCCD_L_WR());
  ui->ltCCD_L_WR_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettCCD_L_WR_tick()));
}

void MainWindow::on_sbtCCD_L_WR_LCLK_XMP2_editingFinished() {
  ui->sbtCCD_L_WR_LCLK_XMP2->setValue(spd->xmpBundle.profile2.gettCCD_L_WR_lowerLimit());
}

void MainWindow::on_sbtCCD_L_WR2_XMP2_editingFinished() {
  ui->sbtCCD_L_WR2_XMP2->setValue(spd->xmpBundle.profile2.gettCCD_L_WR2());
  ui->ltCCD_L_WR2_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettCCD_L_WR2_tick()));
}

void MainWindow::on_sbtCCD_L_WR2_LCLK_XMP2_editingFinished() {
  ui->sbtCCD_L_WR2_LCLK_XMP2->setValue(spd->xmpBundle.profile2.gettCCD_L_WR2_lowerLimit());
}

void MainWindow::on_sbtFAW_XMP2_editingFinished() {
  ui->sbtFAW_XMP2->setValue(spd->xmpBundle.profile2.gettFAW());
  ui->ltFAW_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettFAW_tick()));
}

void MainWindow::on_sbtFAW_LCLK_XMP2_editingFinished() {
  ui->sbtFAW_LCLK_XMP2->setValue(spd->xmpBundle.profile2.gettFAW_lowerLimit());
}

void MainWindow::on_sbtCCD_L_WTR_XMP2_editingFinished() {
  ui->sbtCCD_L_WTR_XMP2->setValue(spd->xmpBundle.profile2.gettCCD_L_WTR());
  ui->ltCCD_L_WTR_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettCCD_L_WTR_tick()));
}

void MainWindow::on_sbtCCD_L_WTR_LCLK_XMP2_editingFinished() {
  ui->sbtCCD_L_WTR_LCLK_XMP2->setValue(spd->xmpBundle.profile2.gettCCD_L_WTR_lowerLimit());
}

void MainWindow::on_sbtCCD_S_WTR_XMP2_editingFinished() {
  ui->sbtCCD_S_WTR_XMP2->setValue(spd->xmpBundle.profile2.gettCCD_S_WTR());
  ui->ltCCD_S_WTR_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtCCD_S_WTR_LCLK_XMP2_editingFinished() {
  ui->sbtCCD_S_WTR_LCLK_XMP2->setValue(spd->xmpBundle.profile2.gettCCD_S_WTR_lowerLimit());
  ui->ltCCD_S_WTR_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtRTP_XMP2_editingFinished() {
  ui->sbtRTP_XMP2->setValue(spd->xmpBundle.profile2.gettRTP());
  ui->ltRTP_Ticks_XMP2->setText(QString::number(spd->xmpBundle.profile2.gettRTP_tick()));
}

void MainWindow::on_sbtRTP_LCLK_XMP2_editingFinished() {
  ui->sbtRTP_LCLK_XMP2->setValue(spd->xmpBundle.profile2.gettRTP_lowerLimit());
}
