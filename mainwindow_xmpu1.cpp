#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "ddr5spd_structs.h"

void MainWindow::wipeXMPProfileU1() {
  spd->xmpBundle.profileUser1.wipeProfile();
  reloadXMPU1Tab();
}

void MainWindow::loadSampleXMPProfileU1() {
  spd->xmpBundle.profileUser1.resetProfile();
  reloadXMPU1Tab();
}

void MainWindow::importXMPProfileU1() {
  if ((spd == nullptr) || (spd->isEXPOPresent())) {
    return;
  }

  spd->xmpBundle.profileUser1.import(importXMPProfile());
  reloadXMPU1Tab();
}

void MainWindow::exportXMPProfileU1() {
  if ((spd != nullptr) && (!spd->isEXPOPresent())) {
    exportXMPProfile(spd->xmpBundle.profileUser1.getCopy());
  }
}

void MainWindow::reloadXMPU1Tab() {
  if (spd->isEXPOPresent()) {
    return;
  }

  // XMP Profile
  auto &xmp_profile = spd->xmpBundle.profileUser1;

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
    case CommandRate::Undefined:
      ui->cbCommandRate_XMPU1->setCurrentIndex(0);
      break;
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
  ui->ltAA_Ticks_XMPU1->setText(QString::number(xmp_profile.gettAA_tick()));
  ui->sbtRCD_XMPU1->setValue(xmp_profile.gettRCD());
  ui->ltRCD_Ticks_XMPU1->setText(QString::number(xmp_profile.gettRCD_tick()));
  ui->sbtRP_XMPU1->setValue(xmp_profile.gettRP());
  ui->ltRP_Ticks_XMPU1->setText(QString::number(xmp_profile.gettRP_tick()));
  ui->sbtRAS_XMPU1->setValue(xmp_profile.gettRAS());
  ui->ltRAS_Ticks_XMPU1->setText(QString::number(xmp_profile.gettRAS_tick()));
  ui->sbtRC_XMPU1->setValue(xmp_profile.gettRC());
  ui->ltRC_Ticks_XMPU1->setText(QString::number(xmp_profile.gettRC_tick()));
  ui->sbtWR_XMPU1->setValue(xmp_profile.gettWR());
  ui->ltWR_Ticks_XMPU1->setText(QString::number(xmp_profile.gettWR_tick()));
  ui->sbtRFC1_XMPU1->setValue(xmp_profile.gettRFC1());
  ui->ltRFC1_Ticks_XMPU1->setText(QString::number(xmp_profile.gettRFC1_tick()));
  ui->sbtRFC2_XMPU1->setValue(xmp_profile.gettRFC2());
  ui->ltRFC2_Ticks_XMPU1->setText(QString::number(xmp_profile.gettRFC2_tick()));
  ui->sbtRFC_XMPU1->setValue(xmp_profile.gettRFC());
  ui->ltRFC_Ticks_XMPU1->setText(QString::number(xmp_profile.gettRFC_tick()));
  ui->sbtRRD_L_XMPU1->setValue(xmp_profile.gettRRD_L());
  ui->sbtRRD_L_LCLK_XMPU1->setValue(xmp_profile.gettRRD_L_lowerLimit());
  ui->ltRRD_L_Ticks_XMPU1->setText(QString::number(xmp_profile.gettRRD_L_tick()));
  ui->sbtCCD_L_XMPU1->setValue(xmp_profile.gettCCD_L());
  ui->sbtCCD_L_LCLK_XMPU1->setValue(xmp_profile.gettCCD_L_lowerLimit());
  ui->ltCCD_L_Ticks_XMPU1->setText(QString::number(xmp_profile.gettCCD_L_tick()));
  ui->sbtCCD_L_WR_XMPU1->setValue(xmp_profile.gettCCD_L_WR());
  ui->sbtCCD_L_WR_LCLK_XMPU1->setValue(xmp_profile.gettCCD_L_WR_lowerLimit());
  ui->ltCCD_L_WR_Ticks_XMPU1->setText(QString::number(xmp_profile.gettCCD_L_WR_tick()));
  ui->sbtCCD_L_WR2_XMPU1->setValue(xmp_profile.gettCCD_L_WR2());
  ui->sbtCCD_L_WR2_LCLK_XMPU1->setValue(xmp_profile.gettCCD_L_WR2_lowerLimit());
  ui->ltCCD_L_WR2_Ticks_XMPU1->setText(QString::number(xmp_profile.gettCCD_L_WR2_tick()));
  ui->sbtFAW_XMPU1->setValue(xmp_profile.gettFAW());
  ui->sbtFAW_LCLK_XMPU1->setValue(xmp_profile.gettFAW_lowerLimit());
  ui->ltFAW_Ticks_XMPU1->setText(QString::number(xmp_profile.gettFAW_tick()));
  ui->sbtCCD_L_WTR_XMPU1->setValue(xmp_profile.gettCCD_L_WTR());
  ui->sbtCCD_L_WTR_LCLK_XMPU1->setValue(xmp_profile.gettCCD_L_WTR_lowerLimit());
  ui->ltCCD_L_WTR_Ticks_XMPU1->setText(QString::number(xmp_profile.gettCCD_L_WTR_tick()));
  ui->sbtCCD_S_WTR_XMPU1->setValue(xmp_profile.gettCCD_S_WTR());
  ui->sbtCCD_S_WTR_LCLK_XMPU1->setValue(xmp_profile.gettCCD_S_WTR_lowerLimit());
  ui->ltCCD_S_WTR_Ticks_XMPU1->setText(QString::number(xmp_profile.gettCCD_S_WTR_tick()));
  ui->sbtRTP_XMPU1->setValue(xmp_profile.gettRTP());
  ui->sbtRTP_LCLK_XMPU1->setValue(xmp_profile.gettRTP_lowerLimit());
  ui->ltRTP_Ticks_XMPU1->setText(QString::number(xmp_profile.gettRTP_tick()));
}

void MainWindow::on_cbDynamicMemBoost_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setIntelDynamicMemoryBoost(value);
}

void MainWindow::on_cbRealTimeMemOC_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setRealTimeMemoryFrequencyOC(value);
}

void MainWindow::on_sbVDD_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.setVDD(value);
}

void MainWindow::on_sbVDDQ_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.setVDDQ(value);
}

void MainWindow::on_sbVPP_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.setVPP(value);
}

void MainWindow::on_sbVmemctrl_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.setVMEMCtrl(value);
}

void MainWindow::on_spinMinCycleTime_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.setMinCycleTime(value);

  QString frequencyStr = QString::number(spd->xmpBundle.profileUser1.getFrequency()) + " MHz";
  QString mtStr = QString::number(spd->xmpBundle.profileUser1.getMT()) + " MT/s";

  ui->lFrequencyValue_XMPU1->setText(frequencyStr);
  ui->lMTValue_XMPU1->setText(mtStr);
}

void MainWindow::on_sbVDD_XMPU1_editingFinished() {
  ui->sbVDD_XMPU1->setValue(spd->xmpBundle.profileUser1.getVDD());
}

void MainWindow::on_sbVDDQ_XMPU1_editingFinished() {
  ui->sbVDDQ_XMPU1->setValue(spd->xmpBundle.profileUser1.getVDDQ());
}

void MainWindow::on_sbVPP_XMPU1_editingFinished() {
  ui->sbVPP_XMPU1->setValue(spd->xmpBundle.profileUser1.getVPP());
}

void MainWindow::on_sbVmemctrl_XMPU1_editingFinished() {
  ui->sbVmemctrl_XMPU1->setValue(spd->xmpBundle.profileUser1.getVMEMCtrl());
}

void MainWindow::on_spinMinCycleTime_XMPU1_editingFinished() {
  ui->spinMinCycleTime_XMPU1->setValue(spd->xmpBundle.profileUser1.getMinCycleTime());

  QString frequencyStr = QString::number(spd->xmpBundle.profileUser1.getFrequency()) + " MHz";
  QString mtStr = QString::number(spd->xmpBundle.profileUser1.getMT()) + " MT/s";

  ui->lFrequencyValue_XMPU1->setText(frequencyStr);
  ui->lMTValue_XMPU1->setText(mtStr);
}

void MainWindow::on_cbCommandRate_XMPU1_currentIndexChanged(int index) {
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

void MainWindow::on_cbCL20_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(20, value);
}
void MainWindow::on_cbCL22_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(22, value);
}
void MainWindow::on_cbCL24_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(24, value);
}
void MainWindow::on_cbCL26_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(26, value);
}
void MainWindow::on_cbCL28_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(28, value);
}
void MainWindow::on_cbCL30_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(30, value);
}
void MainWindow::on_cbCL32_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(32, value);
}
void MainWindow::on_cbCL34_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(34, value);
}
void MainWindow::on_cbCL36_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(36, value);
}
void MainWindow::on_cbCL38_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(38, value);
}
void MainWindow::on_cbCL40_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(40, value);
}
void MainWindow::on_cbCL42_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(42, value);
}
void MainWindow::on_cbCL44_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(44, value);
}
void MainWindow::on_cbCL46_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(46, value);
}
void MainWindow::on_cbCL48_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(48, value);
}
void MainWindow::on_cbCL50_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(50, value);
}
void MainWindow::on_cbCL52_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(52, value);
}
void MainWindow::on_cbCL54_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(54, value);
}
void MainWindow::on_cbCL56_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(56, value);
}
void MainWindow::on_cbCL58_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(58, value);
}
void MainWindow::on_cbCL60_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(60, value);
}
void MainWindow::on_cbCL62_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(62, value);
}
void MainWindow::on_cbCL64_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(64, value);
}
void MainWindow::on_cbCL66_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(66, value);
}
void MainWindow::on_cbCL68_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(68, value);
}
void MainWindow::on_cbCL70_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(70, value);
}
void MainWindow::on_cbCL72_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(72, value);
}
void MainWindow::on_cbCL74_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(74, value);
}
void MainWindow::on_cbCL76_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(76, value);
}
void MainWindow::on_cbCL78_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(78, value);
}
void MainWindow::on_cbCL80_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(80, value);
}
void MainWindow::on_cbCL82_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(82, value);
}
void MainWindow::on_cbCL84_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(84, value);
}
void MainWindow::on_cbCL86_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(86, value);
}
void MainWindow::on_cbCL88_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(88, value);
}
void MainWindow::on_cbCL90_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(90, value);
}
void MainWindow::on_cbCL92_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(92, value);
}
void MainWindow::on_cbCL94_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(94, value);
}
void MainWindow::on_cbCL96_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(96, value);
}
void MainWindow::on_cbCL98_XMPU1_toggled(bool value) {
  spd->xmpBundle.profileUser1.setCLSupported(98, value);
}

void MainWindow::on_sbtAA_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settAA(value);
  ui->ltAA_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettAA_tick()));
}

void MainWindow::on_sbtRCD_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settRCD(value);
  ui->ltRCD_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRCD_tick()));
}

void MainWindow::on_sbtRP_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settRP(value);
  ui->ltRP_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRP_tick()));
}

void MainWindow::on_sbtRAS_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settRAS(value);
  ui->ltRAS_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRAS_tick()));
}

void MainWindow::on_sbtRC_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settRC(value);
  ui->ltRC_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRC_tick()));
}

void MainWindow::on_sbtWR_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settWR(value);
  ui->ltWR_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettWR_tick()));
}

void MainWindow::on_sbtRFC1_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settRFC1(value);
  ui->ltRFC1_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRFC1_tick()));
}

void MainWindow::on_sbtRFC2_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settRFC2(value);
  ui->ltRFC2_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRFC2_tick()));
}

void MainWindow::on_sbtRFC_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settRFC(value);
  ui->ltRFC_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRFC_tick()));
}

void MainWindow::on_sbtRRD_L_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settRRD_L(value);
  ui->ltRRD_L_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRRD_L()));
}

void MainWindow::on_sbtRRD_L_LCLK_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settRRD_L_lowerLimit(value);
}

void MainWindow::on_sbtCCD_L_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settCCD_L(value);
  ui->ltCCD_L_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettCCD_L_tick()));
}

void MainWindow::on_sbtCCD_L_LCLK_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settCCD_L_lowerLimit(value);
}

void MainWindow::on_sbtCCD_L_WR_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settCCD_L_WR(value);
  ui->ltCCD_L_WR_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettCCD_L_WR_tick()));
}

void MainWindow::on_sbtCCD_L_WR_LCLK_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settCCD_L_WR_lowerLimit(value);
}

void MainWindow::on_sbtCCD_L_WR2_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settCCD_L_WR2(value);
  ui->ltCCD_L_WR2_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettCCD_L_WR2_tick()));
}

void MainWindow::on_sbtCCD_L_WR2_LCLK_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settCCD_L_WR2_lowerLimit(value);
}

void MainWindow::on_sbtFAW_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settFAW(value);
  ui->ltFAW_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettFAW_tick()));
}

void MainWindow::on_sbtFAW_LCLK_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settFAW_lowerLimit(value);
}

void MainWindow::on_sbtCCD_L_WTR_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settCCD_L_WTR(value);
  ui->ltCCD_L_WTR_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettCCD_L_WTR_tick()));
}

void MainWindow::on_sbtCCD_L_WTR_LCLK_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settCCD_L_WTR_lowerLimit(value);
}

void MainWindow::on_sbtCCD_S_WTR_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settCCD_S_WTR(value);
  ui->ltCCD_S_WTR_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtCCD_S_WTR_LCLK_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settCCD_S_WTR_lowerLimit(value);
  ui->ltCCD_S_WTR_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtRTP_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settRTP(value);
  ui->ltRTP_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRTP_tick()));
}

void MainWindow::on_sbtRTP_LCLK_XMPU1_valueChanged(int value) {
  spd->xmpBundle.profileUser1.settRTP_lowerLimit(value);
}

void MainWindow::on_sbtAA_XMPU1_editingFinished() {
  ui->sbtAA_XMPU1->setValue(spd->xmpBundle.profileUser1.gettAA());
  ui->ltAA_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettAA_tick()));
}

void MainWindow::on_sbtRCD_XMPU1_editingFinished() {
  ui->sbtRCD_XMPU1->setValue(spd->xmpBundle.profileUser1.gettRCD());
  ui->ltRCD_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRCD_tick()));
}

void MainWindow::on_sbtRP_XMPU1_editingFinished() {
  ui->sbtRP_XMPU1->setValue(spd->xmpBundle.profileUser1.gettRP());
  ui->ltRP_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRP_tick()));
}

void MainWindow::on_sbtRAS_XMPU1_editingFinished() {
  ui->sbtRAS_XMPU1->setValue(spd->xmpBundle.profileUser1.gettRAS());
  ui->ltRAS_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRAS_tick()));
}

void MainWindow::on_sbtRC_XMPU1_editingFinished() {
  ui->sbtRC_XMPU1->setValue(spd->xmpBundle.profileUser1.gettRC());
  ui->ltRC_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRC_tick()));
}

void MainWindow::on_sbtWR_XMPU1_editingFinished() {
  ui->sbtWR_XMPU1->setValue(spd->xmpBundle.profileUser1.gettWR());
  ui->ltWR_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettWR_tick()));
}

void MainWindow::on_sbtRFC1_XMPU1_editingFinished() {
  ui->sbtRFC1_XMPU1->setValue(spd->xmpBundle.profileUser1.gettAA());
  spd->xmpBundle.profileUser1.settRFC1(ui->sbtRFC1_XMPU1->value());
  ui->ltRFC1_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRFC1_tick()));
}

void MainWindow::on_sbtRFC2_XMPU1_editingFinished() {
  ui->sbtRFC2_XMPU1->setValue(spd->xmpBundle.profileUser1.gettRFC2());
  ui->ltRFC2_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRFC2_tick()));
}

void MainWindow::on_sbtRFC_XMPU1_editingFinished() {
  ui->sbtRFC_XMPU1->setValue(spd->xmpBundle.profileUser1.gettRFC());
  ui->ltRFC_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRFC_tick()));
}

void MainWindow::on_sbtRRD_L_XMPU1_editingFinished() {
  ui->sbtRRD_L_XMPU1->setValue(spd->xmpBundle.profileUser1.gettRRD_L());
  ui->ltRRD_L_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRRD_L_tick()));
}

void MainWindow::on_sbtRRD_L_LCLK_XMPU1_editingFinished() {
  ui->sbtRRD_L_LCLK_XMPU1->setValue(spd->xmpBundle.profileUser1.gettRRD_L_lowerLimit());
}

void MainWindow::on_sbtCCD_L_XMPU1_editingFinished() {
  ui->sbtCCD_L_XMPU1->setValue(spd->xmpBundle.profileUser1.gettCCD_L());
  ui->ltCCD_L_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettCCD_L_tick()));
}

void MainWindow::on_sbtCCD_L_LCLK_XMPU1_editingFinished() {
  ui->sbtCCD_L_LCLK_XMPU1->setValue(spd->xmpBundle.profileUser1.gettCCD_L_lowerLimit());
}

void MainWindow::on_sbtCCD_L_WR_XMPU1_editingFinished() {
  ui->sbtCCD_L_WR_XMPU1->setValue(spd->xmpBundle.profileUser1.gettCCD_L_WR());
  ui->ltCCD_L_WR_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettCCD_L_WR_tick()));
}

void MainWindow::on_sbtCCD_L_WR_LCLK_XMPU1_editingFinished() {
  ui->sbtCCD_L_WR_LCLK_XMPU1->setValue(spd->xmpBundle.profileUser1.gettCCD_L_WR_lowerLimit());
}

void MainWindow::on_sbtCCD_L_WR2_XMPU1_editingFinished() {
  ui->sbtCCD_L_WR2_XMPU1->setValue(spd->xmpBundle.profileUser1.gettCCD_L_WR2());
  ui->ltCCD_L_WR2_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettCCD_L_WR2_tick()));
}

void MainWindow::on_sbtCCD_L_WR2_LCLK_XMPU1_editingFinished() {
  ui->sbtCCD_L_WR2_LCLK_XMPU1->setValue(spd->xmpBundle.profileUser1.gettCCD_L_WR2_lowerLimit());
}

void MainWindow::on_sbtFAW_XMPU1_editingFinished() {
  ui->sbtFAW_XMPU1->setValue(spd->xmpBundle.profileUser1.gettFAW());
  ui->ltFAW_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettFAW_tick()));
}

void MainWindow::on_sbtFAW_LCLK_XMPU1_editingFinished() {
  ui->sbtFAW_LCLK_XMPU1->setValue(spd->xmpBundle.profileUser1.gettFAW_lowerLimit());
}

void MainWindow::on_sbtCCD_L_WTR_XMPU1_editingFinished() {
  ui->sbtCCD_L_WTR_XMPU1->setValue(spd->xmpBundle.profileUser1.gettCCD_L_WTR());
  ui->ltCCD_L_WTR_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettCCD_L_WTR_tick()));
}

void MainWindow::on_sbtCCD_L_WTR_LCLK_XMPU1_editingFinished() {
  ui->sbtCCD_L_WTR_LCLK_XMPU1->setValue(spd->xmpBundle.profileUser1.gettCCD_L_WTR_lowerLimit());
}

void MainWindow::on_sbtCCD_S_WTR_XMPU1_editingFinished() {
  ui->sbtCCD_S_WTR_XMPU1->setValue(spd->xmpBundle.profileUser1.gettCCD_S_WTR());
  ui->ltCCD_S_WTR_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtCCD_S_WTR_LCLK_XMPU1_editingFinished() {
  ui->sbtCCD_S_WTR_LCLK_XMPU1->setValue(spd->xmpBundle.profileUser1.gettCCD_S_WTR_lowerLimit());
  ui->ltCCD_S_WTR_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtRTP_XMPU1_editingFinished() {
  ui->sbtRTP_XMPU1->setValue(spd->xmpBundle.profileUser1.gettRTP());
  ui->ltRTP_Ticks_XMPU1->setText(QString::number(spd->xmpBundle.profileUser1.gettRTP_tick()));
}

void MainWindow::on_sbtRTP_LCLK_XMPU1_editingFinished() {
  ui->sbtRTP_LCLK_XMPU1->setValue(spd->xmpBundle.profileUser1.gettRTP_lowerLimit());
}
