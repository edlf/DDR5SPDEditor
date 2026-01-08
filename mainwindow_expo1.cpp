#include "mainwindow.h"

#include "./ui_mainwindow.h"

void MainWindow::reloadEXPO1Tab() {
  EXPO_Profile dummy;

  // EXPO Header
  EXPO_Profile &expo_profile = spd->isEXPOPresent() ? spd->expoBundle.profile1 : dummy;
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
  ui->ltAA_Ticks_EXPO1->setText(QString::number(expo_profile.gettAA_tick()));
  ui->sbtRCD_EXPO1->setValue(expo_profile.gettRCD());
  ui->ltRCD_Ticks_EXPO1->setText(QString::number(expo_profile.gettRCD_tick()));
  ui->sbtRP_EXPO1->setValue(expo_profile.gettRP());
  ui->ltRP_Ticks_EXPO1->setText(QString::number(expo_profile.gettRP_tick()));
  ui->sbtRAS_EXPO1->setValue(expo_profile.gettRAS());
  ui->ltRAS_Ticks_EXPO1->setText(QString::number(expo_profile.gettRAS_tick()));
  ui->sbtRC_EXPO1->setValue(expo_profile.gettRC());
  ui->ltRC_Ticks_EXPO1->setText(QString::number(expo_profile.gettRC_tick()));
  ui->sbtWR_EXPO1->setValue(expo_profile.gettWR());
  ui->ltWR_Ticks_EXPO1->setText(QString::number(expo_profile.gettWR_tick()));
  ui->sbtRFC1_EXPO1->setValue(expo_profile.gettRFC1());
  ui->ltRFC1_Ticks_EXPO1->setText(QString::number(expo_profile.gettRFC1_tick()));
  ui->sbtRFC2_EXPO1->setValue(expo_profile.gettRFC2());
  ui->ltRFC2_Ticks_EXPO1->setText(QString::number(expo_profile.gettRFC2_tick()));
  ui->sbtRFC_EXPO1->setValue(expo_profile.gettRFC());
  ui->ltRFC_Ticks_EXPO1->setText(QString::number(expo_profile.gettRFC_tick()));
  // Enhanced timings
  ui->sbtRRD_L_EXPO1->setValue(expo_profile.gettRRD_L());
  ui->ltRRD_L_Ticks_EXPO1->setText(QString::number(expo_profile.gettRRD_L_tick()));
  ui->sbtCCD_L_EXPO1->setValue(expo_profile.gettCCD_L());
  ui->ltCCD_L_Ticks_EXPO1->setText(QString::number(expo_profile.gettCCD_L_tick()));
  ui->sbtCCD_L_WR_EXPO1->setValue(expo_profile.gettCCD_L_WR());
  ui->ltCCD_L_WR_Ticks_EXPO1->setText(QString::number(expo_profile.gettCCD_L_WR_tick()));
  ui->sbtCCD_L_WR2_EXPO1->setValue(expo_profile.gettCCD_L_WR2());
  ui->ltCCD_L_WR2_Ticks_EXPO1->setText(QString::number(expo_profile.gettCCD_L_WR2_tick()));
  ui->sbtFAW_EXPO1->setValue(expo_profile.gettFAW());
  ui->ltFAW_Ticks_EXPO1->setText(QString::number(expo_profile.gettFAW_tick()));
  ui->sbtCCD_L_WTR_EXPO1->setValue(expo_profile.gettCCD_L_WTR());
  ui->ltCCD_L_WTR_Ticks_EXPO1->setText(QString::number(expo_profile.gettCCD_L_WTR_tick()));
  ui->sbtCCD_S_WTR_EXPO1->setValue(expo_profile.gettCCD_S_WTR());
  ui->ltCCD_S_WTR_Ticks_EXPO1->setText(QString::number(expo_profile.gettCCD_S_WTR_tick()));
  ui->sbtRTP_EXPO1->setValue(expo_profile.gettRTP());
  ui->ltRTP_Ticks_EXPO1->setText(QString::number(expo_profile.gettRTP_tick()));
}

void MainWindow::on_cbEnabled_EXPO1_toggled(bool val) {
  spd->expoBundle.setEXPO1Enabled(val);
}

void MainWindow::on_sbVDD_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.setVDD(value);
}

void MainWindow::on_sbVDDQ_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.setVDDQ(value);
}

void MainWindow::on_sbVPP_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.setVPP(value);
}

void MainWindow::on_spinMinCycleTime_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.setMinCycleTime(value);

  QString frequencyStr = QString::number(spd->expoBundle.profile1.getFrequency()) + " MHz";
  QString mtStr = QString::number(spd->expoBundle.profile1.getMT()) + " MT/s";

  ui->lFrequencyValue_EXPO1->setText(frequencyStr);
  ui->lMTValue_EXPO1->setText(mtStr);
}

void MainWindow::on_sbtAA_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.settAA(value);
  ui->ltAA_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettAA_tick()));
}

void MainWindow::on_sbtRCD_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.settRCD(value);
  ui->ltRCD_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRCD_tick()));
}

void MainWindow::on_sbtRP_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.settRP(value);
  ui->ltRP_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRP_tick()));
}

void MainWindow::on_sbtRAS_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.settRAS(value);
  ui->ltRAS_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRAS_tick()));
}

void MainWindow::on_sbtRC_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.settRC(value);
  ui->ltRC_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRC_tick()));
}

void MainWindow::on_sbtWR_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.settWR(value);
  ui->ltWR_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettWR_tick()));
}

void MainWindow::on_sbtRFC1_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.settRFC1(value);
  ui->ltRFC1_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRFC1_tick()));
}

void MainWindow::on_sbtRFC2_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.settRFC2(value);
  ui->ltRFC2_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRFC2_tick()));
}

void MainWindow::on_sbtRFC_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.settRFC(value);
  ui->ltRFC_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRFC_tick()));
}

void MainWindow::on_sbtRRD_L_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.settRRD_L(value);
  ui->ltRRD_L_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRRD_L_tick()));
}

void MainWindow::on_sbtCCD_L_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.settCCD_L(value);
  ui->ltCCD_L_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettCCD_L_tick()));
}

void MainWindow::on_sbtCCD_L_WR_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.settCCD_L_WR(value);
  ui->ltCCD_L_WR_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettCCD_L_WR_tick()));
}

void MainWindow::on_sbtCCD_L_WR2_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.settCCD_L_WR2(value);
  ui->ltCCD_L_WR2_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettCCD_L_WR2_tick()));
}

void MainWindow::on_sbtFAW_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.settFAW(value);
  ui->ltFAW_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettFAW_tick()));
}

void MainWindow::on_sbtCCD_L_WTR_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.settCCD_L_WTR(value);
  ui->ltCCD_L_WTR_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettCCD_L_WTR_tick()));
}

void MainWindow::on_sbtCCD_S_WTR_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.settCCD_S_WTR(value);
  ui->ltCCD_S_WTR_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtRTP_EXPO1_valueChanged(int value) {
  spd->expoBundle.profile1.settRTP(value);
  ui->ltRTP_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRTP_tick()));
}

void MainWindow::on_sbVDD_EXPO1_editingFinished() {
  ui->sbVDD_EXPO1->setValue(spd->expoBundle.profile1.getVDD());
}

void MainWindow::on_sbVDDQ_EXPO1_editingFinished() {
  ui->sbVDDQ_EXPO1->setValue(spd->expoBundle.profile1.getVDDQ());
}

void MainWindow::on_sbVPP_EXPO1_editingFinished() {
  ui->sbVPP_EXPO1->setValue(spd->expoBundle.profile1.getVPP());
}

void MainWindow::on_spinMinCycleTime_EXPO1_editingFinished() {
  ui->spinMinCycleTime_EXPO1->setValue(spd->expoBundle.profile1.getMinCycleTime());
}

void MainWindow::on_sbtAA_EXPO1_editingFinished() {
  ui->sbtAA_EXPO1->setValue(spd->expoBundle.profile1.gettAA());
  ui->ltAA_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettAA_tick()));
}

void MainWindow::on_sbtRCD_EXPO1_editingFinished() {
  ui->sbtRCD_EXPO1->setValue(spd->expoBundle.profile1.gettRCD());
  ui->ltRCD_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRCD_tick()));
}

void MainWindow::on_sbtRP_EXPO1_editingFinished() {
  ui->sbtRP_EXPO1->setValue(spd->expoBundle.profile1.gettRP());
  ui->ltRP_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRP_tick()));
}

void MainWindow::on_sbtRAS_EXPO1_editingFinished() {
  ui->sbtRAS_EXPO1->setValue(spd->expoBundle.profile1.gettRAS());
  ui->ltRAS_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRAS_tick()));
}

void MainWindow::on_sbtRC_EXPO1_editingFinished() {
  ui->sbtRC_EXPO1->setValue(spd->expoBundle.profile1.gettRC());
  ui->ltRC_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRC_tick()));
}

void MainWindow::on_sbtWR_EXPO1_editingFinished() {
  ui->sbtWR_EXPO1->setValue(spd->expoBundle.profile1.gettWR());
  spd->expoBundle.profile1.settWR(ui->sbtWR_EXPO1->value());
  ui->ltWR_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettWR_tick()));
}

void MainWindow::on_sbtRFC1_EXPO1_editingFinished() {
  ui->sbtRFC1_EXPO1->setValue(spd->expoBundle.profile1.gettRFC1());
  spd->expoBundle.profile1.settRFC1(ui->sbtRFC1_EXPO1->value());
  ui->ltRFC1_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRFC1_tick()));
}

void MainWindow::on_sbtRFC2_EXPO1_editingFinished() {
  ui->sbtRFC2_EXPO1->setValue(spd->expoBundle.profile1.gettRFC2());
  spd->expoBundle.profile1.settRFC2(ui->sbtRFC2_EXPO1->value());
  ui->ltRFC2_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRFC2_tick()));
}

void MainWindow::on_sbtRFC_EXPO1_editingFinished() {
  ui->sbtRFC_EXPO1->setValue(spd->expoBundle.profile1.gettRFC());
  ui->ltRFC_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRFC_tick()));
}

void MainWindow::on_sbtRRD_L_EXPO1_editingFinished() {
  ui->sbtRRD_L_EXPO1->setValue(spd->expoBundle.profile1.gettRRD_L());
  ui->ltRRD_L_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRRD_L_tick()));
}

void MainWindow::on_sbtCCD_L_EXPO1_editingFinished() {
  ui->sbtCCD_L_EXPO1->setValue(spd->expoBundle.profile1.gettCCD_L());
  ui->ltCCD_L_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettCCD_L_tick()));
}

void MainWindow::on_sbtCCD_L_WR_EXPO1_editingFinished() {
  ui->sbtCCD_L_WR_EXPO1->setValue(spd->expoBundle.profile1.gettCCD_L_WR());
  ui->ltCCD_L_WR_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettCCD_L_WR_tick()));
}

void MainWindow::on_sbtCCD_L_WR2_EXPO1_editingFinished() {
  ui->sbtCCD_L_WR2_EXPO1->setValue(spd->expoBundle.profile1.gettCCD_L_WR2());
  ui->ltCCD_L_WR2_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettCCD_L_WR2_tick()));
}

void MainWindow::on_sbtFAW_EXPO1_editingFinished() {
  ui->sbtFAW_EXPO1->setValue(spd->expoBundle.profile1.gettFAW());
  ui->ltFAW_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettFAW_tick()));
}

void MainWindow::on_sbtCCD_L_WTR_EXPO1_editingFinished() {
  ui->sbtCCD_L_WTR_EXPO1->setValue(spd->expoBundle.profile1.gettCCD_L_WTR());
  ui->ltCCD_L_WTR_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettCCD_L_WTR_tick()));
}

void MainWindow::on_sbtCCD_S_WTR_EXPO1_editingFinished() {
  ui->sbtCCD_S_WTR_EXPO1->setValue(spd->expoBundle.profile1.gettCCD_S_WTR());
  ui->ltCCD_S_WTR_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettCCD_S_WTR_tick()));
}

void MainWindow::on_sbtRTP_EXPO1_editingFinished() {
  ui->sbtRTP_EXPO1->setValue(spd->expoBundle.profile1.gettRTP());
  ui->ltRTP_Ticks_EXPO1->setText(QString::number(spd->expoBundle.profile1.gettRTP_tick()));
}
