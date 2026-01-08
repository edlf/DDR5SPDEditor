#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "ddr5spd_structs.h"

void MainWindow::importXMPProfileU2() {
  if (spd == nullptr) {
    return;
  }

  spd->xmpBundle.profileUser2.import(importXMPProfile());
  reloadXMPU2Tab();
}

void MainWindow::reloadXMPU2Tab() {
  // XMP Profile
  auto &xmp_profile = spd->xmpBundle.profileUser2;

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
    case CommandRate::Undefined:
      ui->cbCommandRate_XMPU2->setCurrentIndex(0);
      break;

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
  ui->ltAA_Ticks_XMPU2->setText(QString::number(xmp_profile.gettAA_tick()));
  ui->sbtRCD_XMPU2->setValue(xmp_profile.gettRCD());
  ui->ltRCD_Ticks_XMPU2->setText(QString::number(xmp_profile.gettRCD_tick()));
  ui->sbtRP_XMPU2->setValue(xmp_profile.gettRP());
  ui->ltRP_Ticks_XMPU2->setText(QString::number(xmp_profile.gettRP_tick()));
  ui->sbtRAS_XMPU2->setValue(xmp_profile.gettRAS());
  ui->ltRAS_Ticks_XMPU2->setText(QString::number(xmp_profile.gettRAS_tick()));
  ui->sbtRC_XMPU2->setValue(xmp_profile.gettRC());
  ui->ltRC_Ticks_XMPU2->setText(QString::number(xmp_profile.gettRC_tick()));
  ui->sbtWR_XMPU2->setValue(xmp_profile.gettWR());
  ui->ltWR_Ticks_XMPU2->setText(QString::number(xmp_profile.gettWR_tick()));
  ui->sbtRFC1_XMPU2->setValue(xmp_profile.gettRFC1());
  ui->ltRFC1_Ticks_XMPU2->setText(QString::number(xmp_profile.gettRFC1_tick()));
  ui->sbtRFC2_XMPU2->setValue(xmp_profile.gettRFC2());
  ui->ltRFC2_Ticks_XMPU2->setText(QString::number(xmp_profile.gettRFC2_tick()));
  ui->sbtRFC_XMPU2->setValue(xmp_profile.gettRFC());
  ui->ltRFC_Ticks_XMPU2->setText(QString::number(xmp_profile.gettRFC_tick()));
  ui->sbtRRD_L_XMPU2->setValue(xmp_profile.gettRRD_L());
  ui->sbtRRD_L_LCLK_XMPU2->setValue(xmp_profile.gettRRD_L_lowerLimit());
  ui->ltRRD_L_Ticks_XMPU2->setText(QString::number(xmp_profile.gettRRD_L_tick()));
  ui->sbtCCD_L_XMPU2->setValue(xmp_profile.gettCCD_L());
  ui->sbtCCD_L_LCLK_XMPU2->setValue(xmp_profile.gettCCD_L_lowerLimit());
  ui->ltCCD_L_Ticks_XMPU2->setText(QString::number(xmp_profile.gettCCD_L_tick()));
  ui->sbtCCD_L_WR_XMPU2->setValue(xmp_profile.gettCCD_L_WR());
  ui->sbtCCD_L_WR_LCLK_XMPU2->setValue(xmp_profile.gettCCD_L_WR_lowerLimit());
  ui->ltCCD_L_WR_Ticks_XMPU2->setText(QString::number(xmp_profile.gettCCD_L_WR_tick()));
  ui->sbtCCD_L_WR2_XMPU2->setValue(xmp_profile.gettCCD_L_WR2());
  ui->sbtCCD_L_WR2_LCLK_XMPU2->setValue(xmp_profile.gettCCD_L_WR2_lowerLimit());
  ui->ltCCD_L_WR2_Ticks_XMPU2->setText(QString::number(xmp_profile.gettCCD_L_WR2_tick()));
  ui->sbtFAW_XMPU2->setValue(xmp_profile.gettFAW());
  ui->sbtFAW_LCLK_XMPU2->setValue(xmp_profile.gettFAW_lowerLimit());
  ui->ltFAW_Ticks_XMPU2->setText(QString::number(xmp_profile.gettFAW_tick()));
  ui->sbtCCD_L_WTR_XMPU2->setValue(xmp_profile.gettCCD_L_WTR());
  ui->sbtCCD_L_WTR_LCLK_XMPU2->setValue(xmp_profile.gettCCD_L_WTR_lowerLimit());
  ui->ltCCD_L_WTR_Ticks_XMPU2->setText(QString::number(xmp_profile.gettCCD_L_WTR_tick()));
  ui->sbtCCD_S_WTR_XMPU2->setValue(xmp_profile.gettCCD_S_WTR());
  ui->sbtCCD_S_WTR_LCLK_XMPU2->setValue(xmp_profile.gettCCD_S_WTR_lowerLimit());
  ui->ltCCD_S_WTR_Ticks_XMPU2->setText(QString::number(xmp_profile.gettCCD_S_WTR_tick()));
  ui->sbtRTP_XMPU2->setValue(xmp_profile.gettRTP());
  ui->sbtRTP_LCLK_XMPU2->setValue(xmp_profile.gettRTP_lowerLimit());
  ui->ltRTP_Ticks_XMPU2->setText(QString::number(xmp_profile.gettRTP_tick()));
}

void MainWindow::on_cbDynamicMemBoost_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setIntelDynamicMemoryBoost(value);
}

void MainWindow::on_cbRealTimeMemOC_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setRealTimeMemoryFrequencyOC(value);
}

void MainWindow::on_sbVDD_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.setVDD(value);
}

void MainWindow::on_sbVDDQ_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.setVDDQ(value);
}

void MainWindow::on_sbVPP_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.setVPP(value);
}

void MainWindow::on_sbVmemctrl_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.setVMEMCtrl(value);
}

void MainWindow::on_spinMinCycleTime_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.setMinCycleTime(value);

  QString frequencyStr = QString::number(spd->xmpBundle.profileUser2.getFrequency()) + " MHz";
  QString mtStr = QString::number(spd->xmpBundle.profileUser2.getMT()) + " MT/s";

  ui->lFrequencyValue_XMPU2->setText(frequencyStr);
  ui->lMTValue_XMPU2->setText(mtStr);
}

void MainWindow::on_sbVDD_XMPU2_editingFinished() {
  ui->sbVDD_XMPU2->setValue(spd->xmpBundle.profileUser2.getVDD());
}

void MainWindow::on_sbVDDQ_XMPU2_editingFinished() {
  ui->sbVDDQ_XMPU2->setValue(spd->xmpBundle.profileUser2.getVDDQ());
}

void MainWindow::on_sbVPP_XMPU2_editingFinished() {
  ui->sbVPP_XMPU2->setValue(spd->xmpBundle.profileUser2.getVPP());
}

void MainWindow::on_sbVmemctrl_XMPU2_editingFinished() {
  ui->sbVmemctrl_XMPU2->setValue(spd->xmpBundle.profileUser2.getVMEMCtrl());
}

void MainWindow::on_spinMinCycleTime_XMPU2_editingFinished() {
  ui->spinMinCycleTime_XMPU2->setValue(spd->xmpBundle.profileUser2.getMinCycleTime());

  QString frequencyStr = QString::number(spd->xmpBundle.profileUser2.getFrequency()) + " MHz";
  QString mtStr = QString::number(spd->xmpBundle.profileUser2.getMT()) + " MT/s";

  ui->lFrequencyValue_XMPU2->setText(frequencyStr);
  ui->lMTValue_XMPU2->setText(mtStr);
}

void MainWindow::on_cbCommandRate_XMPU2_currentIndexChanged(int index) {
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

void MainWindow::on_cbCL20_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(20, value);
}
void MainWindow::on_cbCL22_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(22, value);
}
void MainWindow::on_cbCL24_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(24, value);
}
void MainWindow::on_cbCL26_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(26, value);
}
void MainWindow::on_cbCL28_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(28, value);
}
void MainWindow::on_cbCL30_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(30, value);
}
void MainWindow::on_cbCL32_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(32, value);
}
void MainWindow::on_cbCL34_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(34, value);
}
void MainWindow::on_cbCL36_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(36, value);
}
void MainWindow::on_cbCL38_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(38, value);
}
void MainWindow::on_cbCL40_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(40, value);
}
void MainWindow::on_cbCL42_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(42, value);
}
void MainWindow::on_cbCL44_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(44, value);
}
void MainWindow::on_cbCL46_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(46, value);
}
void MainWindow::on_cbCL48_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(48, value);
}
void MainWindow::on_cbCL50_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(50, value);
}
void MainWindow::on_cbCL52_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(52, value);
}
void MainWindow::on_cbCL54_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(54, value);
}
void MainWindow::on_cbCL56_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(56, value);
}
void MainWindow::on_cbCL58_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(58, value);
}
void MainWindow::on_cbCL60_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(60, value);
}
void MainWindow::on_cbCL62_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(62, value);
}
void MainWindow::on_cbCL64_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(64, value);
}
void MainWindow::on_cbCL66_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(66, value);
}
void MainWindow::on_cbCL68_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(68, value);
}
void MainWindow::on_cbCL70_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(70, value);
}
void MainWindow::on_cbCL72_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(72, value);
}
void MainWindow::on_cbCL74_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(74, value);
}
void MainWindow::on_cbCL76_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(76, value);
}
void MainWindow::on_cbCL78_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(78, value);
}
void MainWindow::on_cbCL80_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(80, value);
}
void MainWindow::on_cbCL82_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(82, value);
}
void MainWindow::on_cbCL84_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(84, value);
}
void MainWindow::on_cbCL86_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(86, value);
}
void MainWindow::on_cbCL88_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(88, value);
}
void MainWindow::on_cbCL90_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(90, value);
}
void MainWindow::on_cbCL92_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(92, value);
}
void MainWindow::on_cbCL94_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(94, value);
}
void MainWindow::on_cbCL96_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(96, value);
}
void MainWindow::on_cbCL98_XMPU2_toggled(bool value) {
  spd->xmpBundle.profileUser2.setCLSupported(98, value);
}

void MainWindow::on_sbtAA_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settAA(value);
  ui->ltAA_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettAA_tick()));
}

void MainWindow::on_sbtRCD_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settRCD(value);
  ui->ltRCD_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRCD_tick()));
}

void MainWindow::on_sbtRP_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settRP(value);
  ui->ltRP_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRP_tick()));
}

void MainWindow::on_sbtRAS_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settRAS(value);
  ui->ltRAS_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRAS_tick()));
}

void MainWindow::on_sbtRC_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settRC(value);
  ui->ltRC_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRC_tick()));
}

void MainWindow::on_sbtWR_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settWR(value);
  ui->ltWR_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettWR_tick()));
}

void MainWindow::on_sbtRFC1_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settRFC1(value);
  ui->ltRFC1_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRFC1_tick()));
}

void MainWindow::on_sbtRFC2_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settRFC2(value);
  ui->ltRFC2_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRFC2_tick()));
}

void MainWindow::on_sbtRFC_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settRFC(value);
  ui->ltRFC_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRFC_tick()));
}

void MainWindow::on_sbtRRD_L_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settRRD_L(value);
  ui->ltRRD_L_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRRD_L()));
}

void MainWindow::on_sbtRRD_L_LCLK_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settRRD_L_lowerLimit(value);
}

void MainWindow::on_sbtCCD_L_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settCCD_L(value);
  ui->ltCCD_L_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettCCD_L_tick()));
}

void MainWindow::on_sbtCCD_L_LCLK_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settCCD_L_lowerLimit(value);
}

void MainWindow::on_sbtCCD_L_WR_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settCCD_L_WR(value);
  ui->ltCCD_L_WR_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettCCD_L_WR_tick()));
}

void MainWindow::on_sbtCCD_L_WR_LCLK_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settCCD_L_WR_lowerLimit(value);
}

void MainWindow::on_sbtCCD_L_WR2_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settCCD_L_WR2(value);
  ui->ltCCD_L_WR2_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettCCD_L_WR2_tick()));
}

void MainWindow::on_sbtCCD_L_WR2_LCLK_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settCCD_L_WR2_lowerLimit(value);
}

void MainWindow::on_sbtFAW_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settFAW(value);
  ui->ltFAW_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettFAW_tick()));
}

void MainWindow::on_sbtFAW_LCLK_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settFAW_lowerLimit(value);
}

void MainWindow::on_sbtCCD_L_WTR_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settCCD_L_WTR(value);
  ui->ltCCD_L_WTR_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettCCD_L_WTR_tick()));
}

void MainWindow::on_sbtCCD_L_WTR_LCLK_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settCCD_L_WTR_lowerLimit(value);
}

void MainWindow::on_sbtCCD_S_WTR_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settCCD_S_WTR(value);
  ui->ltCCD_S_WTR_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtCCD_S_WTR_LCLK_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settCCD_S_WTR_lowerLimit(value);
  ui->ltCCD_S_WTR_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtRTP_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settRTP(value);
  ui->ltRTP_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRTP_tick()));
}

void MainWindow::on_sbtRTP_LCLK_XMPU2_valueChanged(int value) {
  spd->xmpBundle.profileUser2.settRTP_lowerLimit(value);
}

void MainWindow::on_sbtAA_XMPU2_editingFinished() {
  ui->sbtAA_XMPU2->setValue(spd->xmpBundle.profileUser2.gettAA());
  ui->ltAA_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettAA_tick()));
}

void MainWindow::on_sbtRCD_XMPU2_editingFinished() {
  ui->sbtRCD_XMPU2->setValue(spd->xmpBundle.profileUser2.gettRCD());
  ui->ltRCD_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRCD_tick()));
}

void MainWindow::on_sbtRP_XMPU2_editingFinished() {
  ui->sbtRP_XMPU2->setValue(spd->xmpBundle.profileUser2.gettRP());
  ui->ltRP_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRP_tick()));
}

void MainWindow::on_sbtRAS_XMPU2_editingFinished() {
  ui->sbtRAS_XMPU2->setValue(spd->xmpBundle.profileUser2.gettRAS());
  ui->ltRAS_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRAS_tick()));
}

void MainWindow::on_sbtRC_XMPU2_editingFinished() {
  ui->sbtRC_XMPU2->setValue(spd->xmpBundle.profileUser2.gettRC());
  ui->ltRC_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRC_tick()));
}

void MainWindow::on_sbtWR_XMPU2_editingFinished() {
  ui->sbtWR_XMPU2->setValue(spd->xmpBundle.profileUser2.gettWR());
  ui->ltWR_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettWR_tick()));
}

void MainWindow::on_sbtRFC1_XMPU2_editingFinished() {
  ui->sbtRFC1_XMPU2->setValue(spd->xmpBundle.profileUser2.gettAA());
  spd->xmpBundle.profileUser2.settRFC1(ui->sbtRFC1_XMPU2->value());
  ui->ltRFC1_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRFC1_tick()));
}

void MainWindow::on_sbtRFC2_XMPU2_editingFinished() {
  ui->sbtRFC2_XMPU2->setValue(spd->xmpBundle.profileUser2.gettRFC2());
  ui->ltRFC2_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRFC2_tick()));
}

void MainWindow::on_sbtRFC_XMPU2_editingFinished() {
  ui->sbtRFC_XMPU2->setValue(spd->xmpBundle.profileUser2.gettRFC());
  ui->ltRFC_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRFC_tick()));
}

void MainWindow::on_sbtRRD_L_XMPU2_editingFinished() {
  ui->sbtRRD_L_XMPU2->setValue(spd->xmpBundle.profileUser2.gettRRD_L());
  ui->ltRRD_L_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRRD_L_tick()));
}

void MainWindow::on_sbtRRD_L_LCLK_XMPU2_editingFinished() {
  ui->sbtRRD_L_LCLK_XMPU2->setValue(spd->xmpBundle.profileUser2.gettRRD_L_lowerLimit());
}

void MainWindow::on_sbtCCD_L_XMPU2_editingFinished() {
  ui->sbtCCD_L_XMPU2->setValue(spd->xmpBundle.profileUser2.gettCCD_L());
  ui->ltCCD_L_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettCCD_L_tick()));
}

void MainWindow::on_sbtCCD_L_LCLK_XMPU2_editingFinished() {
  ui->sbtCCD_L_LCLK_XMPU2->setValue(spd->xmpBundle.profileUser2.gettCCD_L_lowerLimit());
}

void MainWindow::on_sbtCCD_L_WR_XMPU2_editingFinished() {
  ui->sbtCCD_L_WR_XMPU2->setValue(spd->xmpBundle.profileUser2.gettCCD_L_WR());
  ui->ltCCD_L_WR_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettCCD_L_WR_tick()));
}

void MainWindow::on_sbtCCD_L_WR_LCLK_XMPU2_editingFinished() {
  ui->sbtCCD_L_WR_LCLK_XMPU2->setValue(spd->xmpBundle.profileUser2.gettCCD_L_WR_lowerLimit());
}

void MainWindow::on_sbtCCD_L_WR2_XMPU2_editingFinished() {
  ui->sbtCCD_L_WR2_XMPU2->setValue(spd->xmpBundle.profileUser2.gettCCD_L_WR2());
  ui->ltCCD_L_WR2_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettCCD_L_WR2_tick()));
}

void MainWindow::on_sbtCCD_L_WR2_LCLK_XMPU2_editingFinished() {
  ui->sbtCCD_L_WR2_LCLK_XMPU2->setValue(spd->xmpBundle.profileUser2.gettCCD_L_WR2_lowerLimit());
}

void MainWindow::on_sbtFAW_XMPU2_editingFinished() {
  ui->sbtFAW_XMPU2->setValue(spd->xmpBundle.profileUser2.gettFAW());
  ui->ltFAW_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettFAW_tick()));
}

void MainWindow::on_sbtFAW_LCLK_XMPU2_editingFinished() {
  ui->sbtFAW_LCLK_XMPU2->setValue(spd->xmpBundle.profileUser2.gettFAW_lowerLimit());
}

void MainWindow::on_sbtCCD_L_WTR_XMPU2_editingFinished() {
  ui->sbtCCD_L_WTR_XMPU2->setValue(spd->xmpBundle.profileUser2.gettCCD_L_WTR());
  ui->ltCCD_L_WTR_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettCCD_L_WTR_tick()));
}

void MainWindow::on_sbtCCD_L_WTR_LCLK_XMPU2_editingFinished() {
  ui->sbtCCD_L_WTR_LCLK_XMPU2->setValue(spd->xmpBundle.profileUser2.gettCCD_L_WTR_lowerLimit());
}

void MainWindow::on_sbtCCD_S_WTR_XMPU2_editingFinished() {
  ui->sbtCCD_S_WTR_XMPU2->setValue(spd->xmpBundle.profileUser2.gettCCD_S_WTR());
  ui->ltCCD_S_WTR_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtCCD_S_WTR_LCLK_XMPU2_editingFinished() {
  ui->sbtCCD_S_WTR_LCLK_XMPU2->setValue(spd->xmpBundle.profileUser2.gettCCD_S_WTR_lowerLimit());
  ui->ltCCD_S_WTR_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtRTP_XMPU2_editingFinished() {
  ui->sbtRTP_XMPU2->setValue(spd->xmpBundle.profileUser2.gettRTP());
  ui->ltRTP_Ticks_XMPU2->setText(QString::number(spd->xmpBundle.profileUser2.gettRTP_tick()));
}

void MainWindow::on_sbtRTP_LCLK_XMPU2_editingFinished() {
  ui->sbtRTP_LCLK_XMPU2->setValue(spd->xmpBundle.profileUser2.gettRTP_lowerLimit());
}
