#include "mainwindow.h"

#include "./ui_mainwindow.h"

void MainWindow::exportEXPOProfile2() {
  if (spd != nullptr) {
    exportEXPOProfile(spd->expoBundle.profile2.getCopy());
  }
}

void MainWindow::importEXPOProfile2() {
  if (spd == nullptr) {
    return;
  }

  spd->expoBundle.profile2.import(importEXPOProfile());
  reloadEXPO2Tab();
}

void MainWindow::reloadEXPO2Tab() {
  EXPO_Profile dummy;

  // EXPO Header
  EXPO_Profile &expo_profile = spd->isEXPOPresent() ? spd->expoBundle.profile2 : dummy;
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
  ui->ltAA_Ticks_EXPO2->setText(QString::number(expo_profile.gettAA_tick()));
  ui->sbtRCD_EXPO2->setValue(expo_profile.gettRCD());
  ui->ltRCD_Ticks_EXPO2->setText(QString::number(expo_profile.gettRCD_tick()));
  ui->sbtRP_EXPO2->setValue(expo_profile.gettRP());
  ui->ltRP_Ticks_EXPO2->setText(QString::number(expo_profile.gettRP_tick()));
  ui->sbtRAS_EXPO2->setValue(expo_profile.gettRAS());
  ui->ltRAS_Ticks_EXPO2->setText(QString::number(expo_profile.gettRAS_tick()));
  ui->sbtRC_EXPO2->setValue(expo_profile.gettRC());
  ui->ltRC_Ticks_EXPO2->setText(QString::number(expo_profile.gettRC_tick()));
  ui->sbtWR_EXPO2->setValue(expo_profile.gettWR());
  ui->ltWR_Ticks_EXPO2->setText(QString::number(expo_profile.gettWR_tick()));
  ui->sbtRFC1_EXPO2->setValue(expo_profile.gettRFC1());
  ui->ltRFC1_Ticks_EXPO2->setText(QString::number(expo_profile.gettRFC1_tick()));
  ui->sbtRFC2_EXPO2->setValue(expo_profile.gettRFC2());
  ui->ltRFC2_Ticks_EXPO2->setText(QString::number(expo_profile.gettRFC2_tick()));
  ui->sbtRFC_EXPO2->setValue(expo_profile.gettRFC());
  ui->ltRFC_Ticks_EXPO2->setText(QString::number(expo_profile.gettRFC_tick()));
  // Enhanced timings
  ui->sbtRRD_L_EXPO2->setValue(expo_profile.gettRRD_L());
  ui->ltRRD_L_Ticks_EXPO2->setText(QString::number(expo_profile.gettRRD_L_tick()));
  ui->sbtCCD_L_EXPO2->setValue(expo_profile.gettCCD_L());
  ui->ltCCD_L_Ticks_EXPO2->setText(QString::number(expo_profile.gettCCD_L_tick()));
  ui->sbtCCD_L_WR_EXPO2->setValue(expo_profile.gettCCD_L_WR());
  ui->ltCCD_L_WR_Ticks_EXPO2->setText(QString::number(expo_profile.gettCCD_L_WR_tick()));
  ui->sbtCCD_L_WR2_EXPO2->setValue(expo_profile.gettCCD_L_WR2());
  ui->ltCCD_L_WR2_Ticks_EXPO2->setText(QString::number(expo_profile.gettCCD_L_WR2_tick()));
  ui->sbtFAW_EXPO2->setValue(expo_profile.gettFAW());
  ui->ltFAW_Ticks_EXPO2->setText(QString::number(expo_profile.gettFAW_tick()));
  ui->sbtCCD_L_WTR_EXPO2->setValue(expo_profile.gettCCD_L_WTR());
  ui->ltCCD_L_WTR_Ticks_EXPO2->setText(QString::number(expo_profile.gettCCD_L_WTR_tick()));
  ui->sbtCCD_S_WTR_EXPO2->setValue(expo_profile.gettCCD_S_WTR());
  ui->ltCCD_S_WTR_Ticks_EXPO2->setText(QString::number(expo_profile.gettCCD_S_WTR_tick()));
  ui->sbtRTP_EXPO2->setValue(expo_profile.gettRTP());
  ui->ltRTP_Ticks_EXPO2->setText(QString::number(expo_profile.gettRTP_tick()));
}

void MainWindow::on_cbEnabled_EXPO2_toggled(bool val) {
  spd->expoBundle.setEXPO2Enabled(val);
}

void MainWindow::on_sbVDD_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.setVDD(value);
}

void MainWindow::on_sbVDDQ_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.setVDDQ(value);
}

void MainWindow::on_sbVPP_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.setVPP(value);
}

void MainWindow::on_spinMinCycleTime_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.setMinCycleTime(value);

  QString frequencyStr = QString::number(spd->expoBundle.profile2.getFrequency()) + " MHz";
  QString mtStr = QString::number(spd->expoBundle.profile2.getMT()) + " MT/s";

  ui->lFrequencyValue_EXPO2->setText(frequencyStr);
  ui->lMTValue_EXPO2->setText(mtStr);
}

void MainWindow::on_sbtAA_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.settAA(value);
  ui->ltAA_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettAA_tick()));
}

void MainWindow::on_sbtRCD_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.settRCD(value);
  ui->ltRCD_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRCD_tick()));
}

void MainWindow::on_sbtRP_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.settRP(value);
  ui->ltRP_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRP_tick()));
}

void MainWindow::on_sbtRAS_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.settRAS(value);
  ui->ltRAS_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRAS_tick()));
}

void MainWindow::on_sbtRC_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.settRC(value);
  ui->ltRC_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRC_tick()));
}

void MainWindow::on_sbtWR_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.settWR(value);
  ui->ltWR_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettWR_tick()));
}

void MainWindow::on_sbtRFC1_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.settRFC1(value);
  ui->ltRFC1_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRFC1_tick()));
}

void MainWindow::on_sbtRFC2_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.settRFC2(value);
  ui->ltRFC2_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRFC2_tick()));
}

void MainWindow::on_sbtRFC_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.settRFC(value);
  ui->ltRFC_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRFC_tick()));
}

void MainWindow::on_sbtRRD_L_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.settRRD_L(value);
  ui->ltRRD_L_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRRD_L_tick()));
}

void MainWindow::on_sbtCCD_L_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.settCCD_L(value);
  ui->ltCCD_L_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettCCD_L_tick()));
}

void MainWindow::on_sbtCCD_L_WR_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.settCCD_L_WR(value);
  ui->ltCCD_L_WR_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettCCD_L_WR_tick()));
}

void MainWindow::on_sbtCCD_L_WR2_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.settCCD_L_WR2(value);
  ui->ltCCD_L_WR2_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettCCD_L_WR2_tick()));
}

void MainWindow::on_sbtFAW_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.settFAW(value);
  ui->ltFAW_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettFAW_tick()));
}

void MainWindow::on_sbtCCD_L_WTR_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.settCCD_L_WTR(value);
  ui->ltCCD_L_WTR_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettCCD_L_WTR_tick()));
}

void MainWindow::on_sbtCCD_S_WTR_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.settCCD_S_WTR(value);
  ui->ltCCD_S_WTR_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtRTP_EXPO2_valueChanged(int value) {
  spd->expoBundle.profile2.settRTP(value);
  ui->ltRTP_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRTP_tick()));
}

void MainWindow::on_sbVDD_EXPO2_editingFinished() {
  ui->sbVDD_EXPO2->setValue(spd->expoBundle.profile2.getVDD());
}

void MainWindow::on_sbVDDQ_EXPO2_editingFinished() {
  ui->sbVDDQ_EXPO2->setValue(spd->expoBundle.profile2.getVDDQ());
}

void MainWindow::on_sbVPP_EXPO2_editingFinished() {
  ui->sbVPP_EXPO2->setValue(spd->expoBundle.profile2.getVPP());
}

void MainWindow::on_spinMinCycleTime_EXPO2_editingFinished() {
  ui->spinMinCycleTime_EXPO2->setValue(spd->expoBundle.profile2.getMinCycleTime());
}

void MainWindow::on_sbtAA_EXPO2_editingFinished() {
  ui->sbtAA_EXPO2->setValue(spd->expoBundle.profile2.gettAA());
  ui->ltAA_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettAA_tick()));
}

void MainWindow::on_sbtRCD_EXPO2_editingFinished() {
  ui->sbtRCD_EXPO2->setValue(spd->expoBundle.profile2.gettRCD());
  ui->ltRCD_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRCD_tick()));
}

void MainWindow::on_sbtRP_EXPO2_editingFinished() {
  ui->sbtRP_EXPO2->setValue(spd->expoBundle.profile2.gettRP());
  ui->ltRP_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRP_tick()));
}

void MainWindow::on_sbtRAS_EXPO2_editingFinished() {
  ui->sbtRAS_EXPO2->setValue(spd->expoBundle.profile2.gettRAS());
  ui->ltRAS_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRAS_tick()));
}

void MainWindow::on_sbtRC_EXPO2_editingFinished() {
  ui->sbtRC_EXPO2->setValue(spd->expoBundle.profile2.gettRC());
  ui->ltRC_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRC_tick()));
}

void MainWindow::on_sbtWR_EXPO2_editingFinished() {
  ui->sbtWR_EXPO2->setValue(spd->expoBundle.profile2.gettWR());
  spd->expoBundle.profile2.settWR(ui->sbtWR_EXPO2->value());
  ui->ltWR_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettWR_tick()));
}

void MainWindow::on_sbtRFC1_EXPO2_editingFinished() {
  ui->sbtRFC1_EXPO2->setValue(spd->expoBundle.profile2.gettRFC1());
  spd->expoBundle.profile2.settRFC1(ui->sbtRFC1_EXPO2->value());
  ui->ltRFC1_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRFC1_tick()));
}

void MainWindow::on_sbtRFC2_EXPO2_editingFinished() {
  ui->sbtRFC2_EXPO2->setValue(spd->expoBundle.profile2.gettRFC2());
  spd->expoBundle.profile2.settRFC2(ui->sbtRFC2_EXPO2->value());
  ui->ltRFC2_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRFC2_tick()));
}

void MainWindow::on_sbtRFC_EXPO2_editingFinished() {
  ui->sbtRFC_EXPO2->setValue(spd->expoBundle.profile2.gettRFC());
  ui->ltRFC_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRFC_tick()));
}

void MainWindow::on_sbtRRD_L_EXPO2_editingFinished() {
  ui->sbtRRD_L_EXPO2->setValue(spd->expoBundle.profile2.gettRRD_L());
  ui->ltRRD_L_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRRD_L_tick()));
}

void MainWindow::on_sbtCCD_L_EXPO2_editingFinished() {
  ui->sbtCCD_L_EXPO2->setValue(spd->expoBundle.profile2.gettCCD_L());
  ui->ltCCD_L_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettCCD_L_tick()));
}

void MainWindow::on_sbtCCD_L_WR_EXPO2_editingFinished() {
  ui->sbtCCD_L_WR_EXPO2->setValue(spd->expoBundle.profile2.gettCCD_L_WR());
  ui->ltCCD_L_WR_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettCCD_L_WR_tick()));
}

void MainWindow::on_sbtCCD_L_WR2_EXPO2_editingFinished() {
  ui->sbtCCD_L_WR2_EXPO2->setValue(spd->expoBundle.profile2.gettCCD_L_WR2());
  ui->ltCCD_L_WR2_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettCCD_L_WR2_tick()));
}

void MainWindow::on_sbtFAW_EXPO2_editingFinished() {
  ui->sbtFAW_EXPO2->setValue(spd->expoBundle.profile2.gettFAW());
  ui->ltFAW_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettFAW_tick()));
}

void MainWindow::on_sbtCCD_L_WTR_EXPO2_editingFinished() {
  ui->sbtCCD_L_WTR_EXPO2->setValue(spd->expoBundle.profile2.gettCCD_L_WTR());
  ui->ltCCD_L_WTR_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettCCD_L_WTR_tick()));
}

void MainWindow::on_sbtCCD_S_WTR_EXPO2_editingFinished() {
  ui->sbtCCD_S_WTR_EXPO2->setValue(spd->expoBundle.profile2.gettCCD_S_WTR());
  ui->ltCCD_S_WTR_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtRTP_EXPO2_editingFinished() {
  ui->sbtRTP_EXPO2->setValue(spd->expoBundle.profile2.gettRTP());
  ui->ltRTP_Ticks_EXPO2->setText(QString::number(spd->expoBundle.profile2.gettRTP_tick()));
}
