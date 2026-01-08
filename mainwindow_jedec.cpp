#include "mainwindow.h"

#include "./ui_mainwindow.h"

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

  ui->spinBoxtAA->setValue(spd->gettAA());
  ui->spinBoxtAA_Ticks->setValue(spd->gettAA_tick());
  ui->spinBoxtRCD->setValue(spd->gettRCD());
  ui->spinBoxtRCD_Ticks->setValue(spd->gettRCD_tick());
  ui->spinBoxtRP->setValue(spd->gettRP());
  ui->spinBoxtRP_Ticks->setValue(spd->gettRP_tick());
  ui->spinBoxtRAS->setValue(spd->gettRAS());
  ui->spinBoxtRAS_Ticks->setValue(spd->gettRAS_tick());
  ui->spinBoxtRC->setValue(spd->gettRC());
  ui->spinBoxtRC_Ticks->setValue(spd->gettRC_tick());
  ui->spinBoxtWR->setValue(spd->gettWR());
  ui->spinBoxtWR_Ticks->setValue(spd->gettWR_tick());
  ui->spinBoxtRFC->setValue(spd->gettRFCsb_slr());
  ui->spinBoxtRFC_Ticks->setValue(spd->gettRFCsb_slr_tick());
  ui->spinBoxtRFC1->setValue(spd->gettRFC1_slr());
  ui->spinBoxtRFC1_Ticks->setValue(spd->gettRFC1_slr_tick());
  ui->spinBoxtRFC2->setValue(spd->gettRFC2_slr());
  ui->spinBoxtRFC2_Ticks->setValue(spd->gettRFC2_slr_tick());
  ui->spinBoxtRRD_L->setValue(spd->gettRRD_L());
  ui->spinBoxtRRD_L_LCLK->setValue(spd->gettRRD_L_lowerLimit());
  ui->spinBoxtRRD_L_Ticks->setValue(spd->gettRRD_L_tick());
  ui->spinBoxtCCD_L->setValue(spd->gettCCD_L());
  ui->spinBoxtCCD_L_LCLK->setValue(spd->gettCCD_L_lowerLimit());
  ui->spinBoxtCCD_L_Ticks->setValue(spd->gettCCD_L_tick());
  ui->spinBoxtCCD_L_WR->setValue(spd->gettCCD_L_WR());
  ui->spinBoxtCCD_L_WR_LCLK->setValue(spd->gettCCD_L_WR_lowerLimit());
  ui->spinBoxtCCD_L_WR_Ticks->setValue(spd->gettCCD_L_WR_tick());
  ui->spinBoxtCCD_L_WR2->setValue(spd->gettCCD_L_WR2());
  ui->spinBoxtCCD_L_WR2_LCLK->setValue(spd->gettCCD_L_WR2_lowerLimit());
  ui->spinBoxtCCD_L_WR2_Ticks->setValue(spd->gettCCD_L_WR2_tick());
  ui->spinBoxtFAW->setValue(spd->gettFAW());
  ui->spinBoxtFAW_LCLK->setValue(spd->gettFAW_lowerLimit());
  ui->spinBoxtFAW_Ticks->setValue(spd->gettFAW_tick());
  ui->spinBoxtCCD_L_WTR->setValue(spd->gettCCD_L_WTR());
  ui->spinBoxtCCD_L_WTR_LCLK->setValue(spd->gettCCD_L_WTR_lowerLimit());
  ui->spinBoxtCCD_L_WTR_Ticks->setValue(spd->gettCCD_L_WTR_tick());
  ui->spinBoxtCCD_S_WTR->setValue(spd->gettCCD_S_WTR());
  ui->spinBoxtCCD_S_WTR_LCLK->setValue(spd->gettCCD_S_WTR_lowerLimit());
  ui->spinBoxtCCD_S_WTR_Ticks->setValue(spd->gettCCD_S_WTR_tick());
  ui->spinBoxtRTP->setValue(spd->gettRTP());
  ui->spinBoxtRTP_LCLK->setValue(spd->gettRTP_lowerLimit());
  ui->spinBoxtRTP_Ticks->setValue(spd->gettRTP_tick());
}

void MainWindow::on_spinMinCycleTime_valueChanged(int value) {
  if (value == spd->getMinCycleTime()) {
    return;
  }

  spd->setMinCycleTime(value);
  QString frequencyStr = QString::number(spd->getFrequency()) + " MHz";
  QString mtStr = QString::number(spd->getMT()) + " MT/s";

  ui->labelFrequencyValue->setText(frequencyStr);
  ui->labelMTValue->setText(mtStr);
}

void MainWindow::on_spinMaxCycleTime_valueChanged(int value) {
  if (value == spd->getMaxCycleTime()) {
    return;
  }

  spd->setMaxCycleTime(value);
  QString frequencyStr = QString::number(spd->getFrequency()) + " MHz";
  QString mtStr = QString::number(spd->getMT()) + " MT/s";

  ui->labelFrequencyValue->setText(frequencyStr);
  ui->labelMTValue->setText(mtStr);
}

void MainWindow::on_spinMinCycleTime_editingFinished() {
  ui->spinMinCycleTime->setValue(spd->getMinCycleTime());
  QString frequencyStr = QString::number(spd->getFrequency()) + " MHz";
  QString mtStr = QString::number(spd->getMT()) + " MT/s";

  ui->labelFrequencyValue->setText(frequencyStr);
  ui->labelMTValue->setText(mtStr);
}

void MainWindow::on_spinMaxCycleTime_editingFinished() {
  ui->spinMaxCycleTime->setValue(spd->getMinCycleTime());
  QString frequencyStr = QString::number(spd->getFrequency()) + " MHz";
  QString mtStr = QString::number(spd->getMT()) + " MT/s";

  ui->labelFrequencyValue->setText(frequencyStr);
  ui->labelMTValue->setText(mtStr);
}

void MainWindow::on_cbCL20_toggled(bool value) {
  spd->setCLSupported(20, value);
}
void MainWindow::on_cbCL22_toggled(bool value) {
  spd->setCLSupported(22, value);
}
void MainWindow::on_cbCL24_toggled(bool value) {
  spd->setCLSupported(24, value);
}
void MainWindow::on_cbCL26_toggled(bool value) {
  spd->setCLSupported(26, value);
}
void MainWindow::on_cbCL28_toggled(bool value) {
  spd->setCLSupported(28, value);
}
void MainWindow::on_cbCL30_toggled(bool value) {
  spd->setCLSupported(30, value);
}
void MainWindow::on_cbCL32_toggled(bool value) {
  spd->setCLSupported(32, value);
}
void MainWindow::on_cbCL34_toggled(bool value) {
  spd->setCLSupported(34, value);
}
void MainWindow::on_cbCL36_toggled(bool value) {
  spd->setCLSupported(36, value);
}
void MainWindow::on_cbCL38_toggled(bool value) {
  spd->setCLSupported(38, value);
}
void MainWindow::on_cbCL40_toggled(bool value) {
  spd->setCLSupported(40, value);
}
void MainWindow::on_cbCL42_toggled(bool value) {
  spd->setCLSupported(42, value);
}
void MainWindow::on_cbCL44_toggled(bool value) {
  spd->setCLSupported(44, value);
}
void MainWindow::on_cbCL46_toggled(bool value) {
  spd->setCLSupported(46, value);
}
void MainWindow::on_cbCL48_toggled(bool value) {
  spd->setCLSupported(48, value);
}
void MainWindow::on_cbCL50_toggled(bool value) {
  spd->setCLSupported(50, value);
}
void MainWindow::on_cbCL52_toggled(bool value) {
  spd->setCLSupported(52, value);
}
void MainWindow::on_cbCL54_toggled(bool value) {
  spd->setCLSupported(54, value);
}
void MainWindow::on_cbCL56_toggled(bool value) {
  spd->setCLSupported(56, value);
}
void MainWindow::on_cbCL58_toggled(bool value) {
  spd->setCLSupported(58, value);
}
void MainWindow::on_cbCL60_toggled(bool value) {
  spd->setCLSupported(60, value);
}
void MainWindow::on_cbCL62_toggled(bool value) {
  spd->setCLSupported(62, value);
}
void MainWindow::on_cbCL64_toggled(bool value) {
  spd->setCLSupported(64, value);
}
void MainWindow::on_cbCL66_toggled(bool value) {
  spd->setCLSupported(66, value);
}
void MainWindow::on_cbCL68_toggled(bool value) {
  spd->setCLSupported(68, value);
}
void MainWindow::on_cbCL70_toggled(bool value) {
  spd->setCLSupported(70, value);
}
void MainWindow::on_cbCL72_toggled(bool value) {
  spd->setCLSupported(72, value);
}
void MainWindow::on_cbCL74_toggled(bool value) {
  spd->setCLSupported(74, value);
}
void MainWindow::on_cbCL76_toggled(bool value) {
  spd->setCLSupported(76, value);
}
void MainWindow::on_cbCL78_toggled(bool value) {
  spd->setCLSupported(78, value);
}
void MainWindow::on_cbCL80_toggled(bool value) {
  spd->setCLSupported(80, value);
}
void MainWindow::on_cbCL82_toggled(bool value) {
  spd->setCLSupported(82, value);
}
void MainWindow::on_cbCL84_toggled(bool value) {
  spd->setCLSupported(84, value);
}
void MainWindow::on_cbCL86_toggled(bool value) {
  spd->setCLSupported(86, value);
}
void MainWindow::on_cbCL88_toggled(bool value) {
  spd->setCLSupported(88, value);
}
void MainWindow::on_cbCL90_toggled(bool value) {
  spd->setCLSupported(90, value);
}
void MainWindow::on_cbCL92_toggled(bool value) {
  spd->setCLSupported(92, value);
}
void MainWindow::on_cbCL94_toggled(bool value) {
  spd->setCLSupported(94, value);
}
void MainWindow::on_cbCL96_toggled(bool value) {
  spd->setCLSupported(96, value);
}
void MainWindow::on_cbCL98_toggled(bool value) {
  spd->setCLSupported(98, value);
}

void MainWindow::on_spinBoxtAA_valueChanged(int value) {
  spd->settAA(value);
  ui->spinBoxtAA_Ticks->setValue(spd->gettAA_tick());
}

void MainWindow::on_spinBoxtAA_Ticks_valueChanged(int value) {
  if (value == spd->gettAA_tick()) {
    return;
  }

  spd->settAA_tick(value);
  ui->spinBoxtAA->setValue(spd->gettAA());
}

void MainWindow::on_spinBoxtRCD_valueChanged(int value) {
  spd->settRCD(value);
  ui->spinBoxtRCD_Ticks->setValue(spd->gettRCD_tick());
}

void MainWindow::on_spinBoxtRP_valueChanged(int value) {
  spd->settRP(value);
  ui->spinBoxtRP_Ticks->setValue(spd->gettRP_tick());
}

void MainWindow::on_spinBoxtRAS_valueChanged(int value) {
  spd->settRAS(value);
  ui->spinBoxtRAS_Ticks->setValue(spd->gettRAS_tick());
}

void MainWindow::on_spinBoxtRC_valueChanged(int value) {
  spd->settRC(value);
  ui->spinBoxtRC_Ticks->setValue(spd->gettRC_tick());
}

void MainWindow::on_spinBoxtWR_valueChanged(int value) {
  spd->settWR(value);
  ui->spinBoxtWR_Ticks->setValue(spd->gettWR_tick());
}

void MainWindow::on_spinBoxtRFC1_valueChanged(int value) {
  spd->settRFC1_slr(value);
  ui->spinBoxtRFC1_Ticks->setValue(spd->gettRFC1_slr_tick());
}

void MainWindow::on_spinBoxtRFC2_valueChanged(int value) {
  spd->settRFC2_slr(value);
  ui->spinBoxtRFC2_Ticks->setValue(spd->gettRFC2_slr_tick());
}

void MainWindow::on_spinBoxtRFC_valueChanged(int value) {
  spd->settRFCsb_slr(value);
  ui->spinBoxtRFC_Ticks->setValue(spd->gettRFCsb_slr_tick());
}

void MainWindow::on_spinBoxtRRD_L_valueChanged(int value) {
  spd->settRRD_L(value);
  ui->spinBoxtRRD_L_Ticks->setValue(spd->gettRRD_L_tick());
}

void MainWindow::on_spinBoxtRRD_L_LCLK_valueChanged(int value) {
  spd->settRRD_L_lowerLimit(value);
}

void MainWindow::on_spinBoxtCCD_L_valueChanged(int value) {
  spd->settCCD_L(value);
  ui->spinBoxtCCD_L_Ticks->setValue(spd->gettCCD_L_tick());
}

void MainWindow::on_spinBoxtCCD_L_LCLK_valueChanged(int value) {
  spd->settCCD_L_lowerLimit(value);
}

void MainWindow::on_spinBoxtCCD_L_WR_valueChanged(int value) {
  spd->settCCD_L_WR(value);
  ui->spinBoxtCCD_L_WR_Ticks->setValue(spd->gettCCD_L_WR_tick());
}

void MainWindow::on_spinBoxtCCD_L_WR_LCLK_valueChanged(int value) {
  spd->settCCD_L_WR_lowerLimit(value);
}

void MainWindow::on_spinBoxtCCD_L_WR2_valueChanged(int value) {
  spd->settCCD_L_WR2(value);
  ui->spinBoxtCCD_L_WR2_Ticks->setValue(spd->gettCCD_L_WR2_tick());
}

void MainWindow::on_spinBoxtCCD_L_WR2_LCLK_valueChanged(int value) {
  spd->settCCD_L_WR2_lowerLimit(value);
}

void MainWindow::on_spinBoxtFAW_valueChanged(int value) {
  spd->settFAW(value);
  ui->spinBoxtFAW_Ticks->setValue(spd->gettFAW_tick());
}

void MainWindow::on_spinBoxtFAW_LCLK_valueChanged(int value) {
  spd->settFAW_lowerLimit(value);
}

void MainWindow::on_spinBoxtCCD_L_WTR_valueChanged(int value) {
  spd->settCCD_L_WTR(value);
  ui->spinBoxtCCD_L_WTR_Ticks->setValue(spd->gettCCD_L_WTR_tick());
}

void MainWindow::on_spinBoxtCCD_L_WTR_LCLK_valueChanged(int value) {
  spd->settCCD_L_WTR_lowerLimit(value);
}

void MainWindow::on_spinBoxtCCD_S_WTR_valueChanged(int value) {
  spd->settCCD_S_WTR(value);
  ui->spinBoxtCCD_S_WTR_Ticks->setValue(spd->gettCCD_S_WTR_tick());
}

void MainWindow::on_spinBoxtCCD_S_WTR_LCLK_valueChanged(int value) {
  spd->settCCD_S_WTR_lowerLimit(value);
  ui->spinBoxtCCD_S_WTR_Ticks->setValue(spd->gettCCD_S_WTR_tick());
}

void MainWindow::on_spinBoxtRTP_valueChanged(int value) {
  spd->settRTP(value);
  ui->spinBoxtRTP_Ticks->setValue(spd->gettRTP_tick());
}

void MainWindow::on_spinBoxtRTP_LCLK_valueChanged(int value) {
  spd->settRTP_lowerLimit(value);
}

void MainWindow::on_spinBoxtAA_editingFinished() {
  ui->spinBoxtAA->setValue(spd->gettAA());
  ui->spinBoxtAA_Ticks->setValue(spd->gettAA_tick());
}

void MainWindow::on_spinBoxtAA_Ticks_editingFinished() {
  ui->spinBoxtAA->setValue(spd->gettAA());
  ui->spinBoxtAA_Ticks->setValue(spd->gettAA_tick());
}

void MainWindow::on_spinBoxtRCD_editingFinished() {
  ui->spinBoxtRCD->setValue(spd->gettRCD());
  ui->spinBoxtRCD_Ticks->setValue(spd->gettRCD_tick());
}

void MainWindow::on_spinBoxtRP_editingFinished() {
  ui->spinBoxtRP->setValue(spd->gettRP());
  ui->spinBoxtRP_Ticks->setValue(spd->gettRP_tick());
}

void MainWindow::on_spinBoxtRAS_editingFinished() {
  ui->spinBoxtRAS->setValue(spd->gettRAS());
  ui->spinBoxtRAS_Ticks->setValue(spd->gettRAS_tick());
}

void MainWindow::on_spinBoxtRC_editingFinished() {
  ui->spinBoxtRC->setValue(spd->gettRC());
  ui->spinBoxtRC_Ticks->setValue(spd->gettRC_tick());
}

void MainWindow::on_spinBoxtWR_editingFinished() {
  ui->spinBoxtWR->setValue(spd->gettWR());
  ui->spinBoxtWR_Ticks->setValue(spd->gettWR_tick());
}

void MainWindow::on_spinBoxtRFC1_editingFinished() {
  ui->spinBoxtRFC1->setValue(spd->gettRFC1_slr());
  ui->spinBoxtRFC1_Ticks->setValue(spd->gettRFC1_slr_tick());
}

void MainWindow::on_spinBoxtRFC2_editingFinished() {
  ui->spinBoxtRFC2->setValue(spd->gettRFC2_slr());
  ui->spinBoxtRFC2_Ticks->setValue(spd->gettRFC2_slr_tick());
}

void MainWindow::on_spinBoxtRFC_editingFinished() {
  ui->spinBoxtRFC->setValue(spd->gettRFCsb_slr());
  ui->spinBoxtRFC_Ticks->setValue(spd->gettRFCsb_slr_tick());
}

void MainWindow::on_spinBoxtRRD_L_editingFinished() {
  ui->spinBoxtRRD_L->setValue(spd->gettRRD_L());
  ui->spinBoxtRRD_L_Ticks->setValue(spd->gettRRD_L_tick());
}

void MainWindow::on_spinBoxtRRD_L_LCLK_editingFinished() {
  ui->spinBoxtRRD_L_LCLK->setValue(spd->gettRRD_L_lowerLimit());
}

void MainWindow::on_spinBoxtCCD_L_editingFinished() {
  ui->spinBoxtCCD_L->setValue(spd->gettCCD_L());
  ui->spinBoxtCCD_L_Ticks->setValue(spd->gettCCD_L_tick());
}

void MainWindow::on_spinBoxtCCD_L_LCLK_editingFinished() {
  ui->spinBoxtCCD_L_LCLK->setValue(spd->gettCCD_L_lowerLimit());
}

void MainWindow::on_spinBoxtCCD_L_WR_editingFinished() {
  ui->spinBoxtCCD_L_WR->setValue(spd->gettCCD_L_WR());
  ui->spinBoxtCCD_L_WR_Ticks->setValue(spd->gettCCD_L_WR_tick());
}

void MainWindow::on_spinBoxtCCD_L_WR_LCLK_editingFinished() {
  ui->spinBoxtCCD_L_WR_LCLK->setValue(spd->gettCCD_L_WR_lowerLimit());
}

void MainWindow::on_spinBoxtCCD_L_WR2_editingFinished() {
  ui->spinBoxtCCD_L_WR2->setValue(spd->gettCCD_L_WR2());
  ui->spinBoxtCCD_L_WR2_Ticks->setValue(spd->gettCCD_L_WR2_tick());
}

void MainWindow::on_spinBoxtCCD_L_WR2_LCLK_editingFinished() {
  ui->spinBoxtCCD_L_WR2_LCLK->setValue(spd->gettCCD_L_WR2_lowerLimit());
}

void MainWindow::on_spinBoxtFAW_editingFinished() {
  ui->spinBoxtFAW->setValue(spd->gettFAW());
  ui->spinBoxtFAW_Ticks->setValue(spd->gettFAW_tick());
}

void MainWindow::on_spinBoxtFAW_LCLK_editingFinished() {
  ui->spinBoxtFAW_LCLK->setValue(spd->gettFAW_lowerLimit());
}

void MainWindow::on_spinBoxtCCD_L_WTR_editingFinished() {
  ui->spinBoxtCCD_L_WTR->setValue(spd->gettCCD_L_WTR());
  ui->spinBoxtCCD_L_WTR_Ticks->setValue(spd->gettCCD_L_WTR_tick());
}

void MainWindow::on_spinBoxtCCD_L_WTR_LCLK_editingFinished() {
  ui->spinBoxtCCD_L_WTR_LCLK->setValue(spd->gettCCD_L_WTR_lowerLimit());
}

void MainWindow::on_spinBoxtCCD_S_WTR_editingFinished() {
  ui->spinBoxtCCD_S_WTR->setValue(spd->gettCCD_S_WTR());
  ui->spinBoxtCCD_S_WTR_Ticks->setValue(spd->gettCCD_S_WTR_tick());
}

void MainWindow::on_spinBoxtCCD_S_WTR_LCLK_editingFinished() {
  ui->spinBoxtCCD_S_WTR_LCLK->setValue(spd->gettCCD_S_WTR_lowerLimit());
  ui->spinBoxtCCD_S_WTR_Ticks->setValue(spd->gettCCD_S_WTR_tick());
}

void MainWindow::on_spinBoxtRTP_editingFinished() {
  ui->spinBoxtRTP->setValue(spd->gettRTP());
  ui->spinBoxtRTP_Ticks->setValue(spd->gettRTP_tick());
}

void MainWindow::on_spinBoxtRTP_LCLK_editingFinished() {
  ui->spinBoxtRTP_LCLK->setValue(spd->gettRTP_lowerLimit());
}

void MainWindow::on_spinBoxtRCD_Ticks_editingFinished() {
  ui->spinBoxtRCD->setValue(spd->gettRCD());
  ui->spinBoxtRCD_Ticks->setValue(spd->gettRCD_tick());
}

void MainWindow::on_spinBoxtRP_Ticks_editingFinished() {
  ui->spinBoxtRP->setValue(spd->gettRP());
  ui->spinBoxtRP_Ticks->setValue(spd->gettRP_tick());
}

void MainWindow::on_spinBoxtRAS_Ticks_editingFinished() {
  ui->spinBoxtRAS->setValue(spd->gettRAS());
  ui->spinBoxtRAS_Ticks->setValue(spd->gettRAS_tick());
}

void MainWindow::on_spinBoxtRC_Ticks_editingFinished() {
  ui->spinBoxtRC->setValue(spd->gettRC());
  ui->spinBoxtRC_Ticks->setValue(spd->gettRC_tick());
}

void MainWindow::on_spinBoxtWR_Ticks_editingFinished() {
  ui->spinBoxtWR->setValue(spd->gettWR());
  ui->spinBoxtWR_Ticks->setValue(spd->gettWR_tick());
}

void MainWindow::on_spinBoxtRFC1_Ticks_editingFinished() {
  ui->spinBoxtRFC1->setValue(spd->gettRFC1_slr());
  ui->spinBoxtRFC1_Ticks->setValue(spd->gettRFC1_slr_tick());
}

void MainWindow::on_spinBoxtRFC2_Ticks_editingFinished() {
  ui->spinBoxtRFC2->setValue(spd->gettRFC2_slr());
  ui->spinBoxtRFC2_Ticks->setValue(spd->gettRFC2_slr_tick());
}

void MainWindow::on_spinBoxtRFC_Ticks_editingFinished() {
  ui->spinBoxtRFC->setValue(spd->gettRFCsb_slr());
  ui->spinBoxtRFC_Ticks->setValue(spd->gettRFCsb_slr_tick());
}

void MainWindow::on_spinBoxtRRD_L_Ticks_editingFinished() {
  ui->spinBoxtRRD_L->setValue(spd->gettRRD_L());
  ui->spinBoxtRRD_L_Ticks->setValue(spd->gettRRD_L_tick());
}

void MainWindow::on_spinBoxtRRD_L_LCLK_Ticks_editingFinished() {
  ui->spinBoxtRRD_L_LCLK->setValue(spd->gettRRD_L_lowerLimit());
}

void MainWindow::on_spinBoxtCCD_L_Ticks_editingFinished() {
  ui->spinBoxtCCD_L->setValue(spd->gettCCD_L());
  ui->spinBoxtCCD_L_Ticks->setValue(spd->gettCCD_L_tick());
}

void MainWindow::on_spinBoxtCCD_L_LCLK_Ticks_editingFinished() {
  ui->spinBoxtCCD_L_LCLK->setValue(spd->gettCCD_L_lowerLimit());
}

void MainWindow::on_spinBoxtCCD_L_WR_Ticks_editingFinished() {
  ui->spinBoxtCCD_L_WR->setValue(spd->gettCCD_L_WR());
  ui->spinBoxtCCD_L_WR_Ticks->setValue(spd->gettCCD_L_WR_tick());
}

void MainWindow::on_spinBoxtCCD_L_WR_LCLK_Ticks_editingFinished() {
  ui->spinBoxtCCD_L_WR->setValue(spd->gettCCD_L_WR());
}

void MainWindow::on_spinBoxtCCD_L_WR2_Ticks_editingFinished() {
  ui->spinBoxtCCD_L_WR2->setValue(spd->gettCCD_L_WR2());
  ui->spinBoxtCCD_L_WR2_Ticks->setValue(spd->gettCCD_L_WR2_tick());
}

void MainWindow::on_spinBoxtCCD_L_WR2_LCLK_Ticks_editingFinished() {
  ui->spinBoxtCCD_L_WR2_LCLK->setValue(spd->gettCCD_L_WR2_lowerLimit());
}

void MainWindow::on_spinBoxtFAW_Ticks_editingFinished() {
  ui->spinBoxtFAW->setValue(spd->gettFAW());
  ui->spinBoxtFAW_Ticks->setValue(spd->gettFAW_tick());
}

void MainWindow::on_spinBoxtFAW_LCLK_Ticks_editingFinished() {
  ui->spinBoxtFAW_LCLK->setValue(spd->gettFAW_lowerLimit());
}

void MainWindow::on_spinBoxtCCD_L_WTR_Ticks_editingFinished() {
  ui->spinBoxtCCD_L_WTR->setValue(spd->gettCCD_L_WTR());
  ui->spinBoxtCCD_L_WTR_Ticks->setValue(spd->gettCCD_L_WTR_tick());
}

void MainWindow::on_spinBoxtCCD_L_WTR_LCLK_Ticks_editingFinished() {
  ui->spinBoxtCCD_L_WTR_LCLK->setValue(spd->gettCCD_L_WTR_lowerLimit());
}

void MainWindow::on_spinBoxtCCD_S_WTR_Ticks_editingFinished() {
  ui->spinBoxtCCD_S_WTR->setValue(spd->gettCCD_S_WTR());
  ui->spinBoxtCCD_S_WTR_Ticks->setValue(spd->gettCCD_S_WTR_tick());
}

void MainWindow::on_spinBoxtCCD_S_WTR_LCLK_Ticks_editingFinished() {
  ui->spinBoxtCCD_S_WTR_LCLK->setValue(spd->gettCCD_S_WTR_lowerLimit());
}

void MainWindow::on_spinBoxtRTP_Ticks_editingFinished() {
  ui->spinBoxtRTP->setValue(spd->gettRTP());
  ui->spinBoxtRTP_Ticks->setValue(spd->gettRTP_tick());
}

void MainWindow::on_spinBoxtRTP_LCLK_Ticks_editingFinished() {
  ui->spinBoxtRTP_LCLK->setValue(spd->gettRTP_lowerLimit());
}

void MainWindow::on_spinBoxtRCD_Ticks_valueChanged(int value) {
  if (value == spd->gettRCD_tick()) {
    return;
  }

  spd->settRCD_tick(value);
  ui->spinBoxtRCD->setValue(spd->gettRCD());
}

void MainWindow::on_spinBoxtRP_Ticks_valueChanged(int value) {
  if (value == spd->gettRP_tick()) {
    return;
  }

  spd->settRP_tick(value);
  ui->spinBoxtRP->setValue(spd->gettRP());
}

void MainWindow::on_spinBoxtRAS_Ticks_valueChanged(int value) {
  if (value == spd->gettRAS_tick()) {
    return;
  }

  spd->settRAS_tick(value);
  ui->spinBoxtRAS->setValue(spd->gettRAS());
}

void MainWindow::on_spinBoxtRC_Ticks_valueChanged(int value) {
  if (value == spd->gettRC_tick()) {
    return;
  }

  spd->settRC_tick(value);
  ui->spinBoxtRC->setValue(spd->gettRC());
}

void MainWindow::on_spinBoxtWR_Ticks_valueChanged(int value) {
  if (value == spd->gettWR_tick()) {
    return;
  }

  spd->settWR_tick(value);
  ui->spinBoxtWR->setValue(spd->gettWR());
}

void MainWindow::on_spinBoxtRFC1_Ticks_valueChanged(int value) {
  if (value == spd->gettRFC1_slr_tick()) {
    return;
  }

  // spd->settRFC1_slr_tick(value);
  // ui->spinBoxtRFC1->setValue(spd->gettRFC1_slr());
}

void MainWindow::on_spinBoxtRFC2_Ticks_valueChanged(int value) {
  if (value == spd->gettRFC2_slr_tick()) {
    return;
  }

  // spd->settRFC2_slr_tick(value);
  // ui->spinBoxtRFC2->setValue(spd->gettRFC2_slr());
}

void MainWindow::on_spinBoxtRFC_Ticks_valueChanged(int value) {
  if (value == spd->gettRFCsb_slr_tick()) {
    return;
  }

  // spd->settRFCsb_slr_tick(value);
  // ui->spinBoxtRFC_Ticks->setValue(spd->gettRFCsb_slr_tick());
}

void MainWindow::on_spinBoxtRRD_L_Ticks_valueChanged(int value) {
  if (value == spd->gettRRD_L_tick()) {
    return;
  }

  spd->settRRD_L_tick(value);
  ui->spinBoxtRRD_L->setValue(spd->gettRRD_L());
}

void MainWindow::on_spinBoxtRRD_L_LCLK_Ticks_valueChanged(int value) {
  if (value == spd->gettRRD_L_lowerLimit()) {
    return;
  }

  spd->settRRD_L_lowerLimit(value);
}

void MainWindow::on_spinBoxtCCD_L_Ticks_valueChanged(int value) {
  if (value == spd->gettCCD_L_tick()) {
    return;
  }

  spd->settCCD_L_tick(value);
  ui->spinBoxtCCD_L->setValue(spd->gettCCD_L());
}

void MainWindow::on_spinBoxtCCD_L_LCLK_Ticks_valueChanged(int value) {
  if (value == spd->gettCCD_L_lowerLimit()) {
    return;
  }

  spd->settCCD_L_lowerLimit(value);
}

void MainWindow::on_spinBoxtCCD_L_WR_Ticks_valueChanged(int value) {
  if (value == spd->gettCCD_L_WR_tick()) {
    return;
  }

  spd->settCCD_L_WR_tick(value);
  ui->spinBoxtCCD_L_WR->setValue(spd->gettCCD_L_WR());
}

void MainWindow::on_spinBoxtCCD_L_WR_LCLK_Ticks_valueChanged(int value) {
  if (value == spd->gettCCD_L_WR_lowerLimit()) {
    return;
  }

  spd->settCCD_L_WR_lowerLimit(value);
}

void MainWindow::on_spinBoxtCCD_L_WR2_Ticks_valueChanged(int value) {
  if (value == spd->gettCCD_L_WR2_tick()) {
    return;
  }

  spd->settCCD_L_WR2_tick(value);
  ui->spinBoxtCCD_L_WR2->setValue(spd->gettCCD_L_WR2());
}

void MainWindow::on_spinBoxtCCD_L_WR2_LCLK_Ticks_valueChanged(int value) {
  if (value == spd->gettCCD_L_WR2_lowerLimit()) {
    return;
  }

  spd->settCCD_L_WR2_lowerLimit(value);
}

void MainWindow::on_spinBoxtFAW_Ticks_valueChanged(int value) {
  if (value == spd->gettFAW_tick()) {
    return;
  }

  spd->settFAW_tick(value);
  ui->spinBoxtFAW->setValue(spd->gettFAW());
}

void MainWindow::on_spinBoxtFAW_LCLK_Ticks_valueChanged(int value) {
  if (value == spd->gettFAW_lowerLimit()) {
    return;
  }

  spd->settFAW_lowerLimit(value);
}

void MainWindow::on_spinBoxtCCD_L_WTR_Ticks_valueChanged(int value) {
  if (value == spd->gettCCD_L_WTR_tick()) {
    return;
  }

  spd->settCCD_L_WTR_tick(value);
  ui->spinBoxtCCD_L_WTR->setValue(spd->gettCCD_L_WTR());
}

void MainWindow::on_spinBoxtCCD_L_WTR_LCLK_Ticks_valueChanged(int value) {
  if (value == spd->gettCCD_L_WTR_lowerLimit()) {
    return;
  }

  spd->settCCD_L_WTR_lowerLimit(value);
}

void MainWindow::on_spinBoxtCCD_S_WTR_Ticks_valueChanged(int value) {
  if (value == spd->gettCCD_S_WTR_tick()) {
    return;
  }

  spd->settCCD_S_WTR_tick(value);
  ui->spinBoxtCCD_S_WTR->setValue(spd->gettCCD_S_WTR());
}

void MainWindow::on_spinBoxtCCD_S_WTR_LCLK_Ticks_valueChanged(int value) {
  if (value == spd->gettCCD_S_WTR_lowerLimit()) {
    return;
  }

  spd->settCCD_S_WTR_lowerLimit(value);
}

void MainWindow::on_spinBoxtRTP_Ticks_valueChanged(int value) {
  if (value == spd->gettRTP_tick()) {
    return;
  }

  spd->settRTP_tick(value);
  ui->spinBoxtRTP->setValue(spd->gettRTP());
}

void MainWindow::on_spinBoxtRTP_LCLK_Ticks_valueChanged(int value) {
  if (value == spd->gettRTP_lowerLimit()) {
    return;
  }

  spd->settRTP_lowerLimit(value);
}
