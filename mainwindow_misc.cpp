#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "ddr5spd_structs.h"

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
  unsigned int max = ui->cdDensity->count();
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

void MainWindow::on_sbManufacturingYear_valueChanged(int value) {
  spd->setManufacturingYear(value);
}

void MainWindow::on_sbManufacturingWeek_valueChanged(int value) {
  spd->setManufacturingWeek(value);
}

void MainWindow::on_sbManufacturingYear_editingFinished() {
  ui->sbManufacturingYear->setValue(spd->getManufacturingYear());
}

void MainWindow::on_sbManufacturingWeek_editingFinished() {
  ui->sbManufacturingWeek->setValue(spd->getManufacturingWeek());
}

void MainWindow::on_lePartNumber_editingFinished() {
  QString val = ui->lePartNumber->text();
  spd->setPartNumber(val.toStdString());
  val = QString::fromStdString(spd->getPartNumber());
  ui->lePartNumber->setText(val);
}

void MainWindow::update_cbBankGroup() {
  int val = std::distance(bankGroupsBitsMap.begin(), std::find(bankGroupsBitsMap.begin(), bankGroupsBitsMap.end(), spd->getBankGroups()));

  ui->cbBankGroup->setCurrentIndex(val);
}

void MainWindow::update_cbBanksPerBankGroup() {
  int val =
      std::distance(banksPerBankGroupBitsMap.begin(), std::find(banksPerBankGroupBitsMap.begin(), banksPerBankGroupBitsMap.end(), spd->getBanksPerBankGroup()));

  ui->cbBanksPerBankGroup->setCurrentIndex(val);
}

void MainWindow::update_cbColumnAddresses() {
  int val = std::distance(columnAddressBitsMap.begin(), std::find(columnAddressBitsMap.begin(), columnAddressBitsMap.end(), spd->getColumnAddresses()));

  ui->cbColumnAddresses->setCurrentIndex(val);
}

void MainWindow::update_cbRowAddresses() {
  int val = std::distance(rowAddressBitsMap.begin(), std::find(rowAddressBitsMap.begin(), rowAddressBitsMap.end(), spd->getRowAddresses()));

  ui->cbRowAddresses->setCurrentIndex(val);
}

void MainWindow::update_cdDeviceWidth() {
  int val = std::distance(deviceWidthMap.begin(), std::find(deviceWidthMap.begin(), deviceWidthMap.end(), spd->getDeviceWidth()));

  ui->cdDeviceWidth->setCurrentIndex(val);
}
