#include "ddr5spd.h"
#include "utilities.h"

#include <algorithm>

DDR5SPD::DDR5SPD(SPD_Struct value) :
    spdStruct(value),
    xmpBundle(spdStruct.xmpBlock)
{
}

const unsigned short DDR5SPD::getMinCycleTime() {
    return spdStruct.minCycleTime;
}

void DDR5SPD::setMinCycleTime(const unsigned short value) {
    spdStruct.minCycleTime = value;
}

const unsigned short DDR5SPD::getMaxCycleTime() {
    return spdStruct.maxCycleTime;
}

void DDR5SPD::setMaxCycleTime(const unsigned short value) {
    spdStruct.maxCycleTime = value;
}

const unsigned int DDR5SPD::getFrequency() {
    return static_cast<unsigned int>(1.0 / (getMinCycleTime() / 1000000.0));
}

const unsigned int DDR5SPD::getMT() {
    return getFrequency() * 2;
}

void DDR5SPD::setCLSupported(const int cl, const bool supported){
    utilities::SetCLSupportedDDR5(spdStruct.clSupported, cl, supported);
}

const bool DDR5SPD::getCLSupported(const int cl){
    return utilities::IsCLSupportedDDR5(spdStruct.clSupported, cl);
}

const unsigned short DDR5SPD::gettAA() {
    return spdStruct.tAA;
}

void DDR5SPD::settAA(const unsigned short value) {
    spdStruct.tAA = value;
}

const unsigned short DDR5SPD::gettRCD() {
    return spdStruct.tRCD;
}

void DDR5SPD::settRCD(const unsigned short value) {
    spdStruct.tRCD = value;
}

const unsigned short DDR5SPD::gettRP() {
    return spdStruct.tRP;
}

void DDR5SPD::settRP(const unsigned short value) {
    spdStruct.tRP = value;
}

const unsigned short DDR5SPD::gettRAS() {
    return spdStruct.tRAS;
}

void DDR5SPD::settRAS(const unsigned short value) {
    spdStruct.tRAS = value;
}

const unsigned short DDR5SPD::gettRC() {
    return spdStruct.tRC;
}

void DDR5SPD::settRC(const unsigned short value) {
    spdStruct.tRC = value;
}

const unsigned short DDR5SPD::gettWR() {
    return spdStruct.tWR;
}

void DDR5SPD::settWR(const unsigned short value) {
    spdStruct.tWR = value;
}

const unsigned short DDR5SPD::gettRFC1_slr() {
    return spdStruct.tRFC1_slr;
}

void DDR5SPD::settRFC1_slr(const unsigned short value) {
    spdStruct.tRFC1_slr = value;
}

const unsigned short DDR5SPD::gettRFC2_slr() {
    return spdStruct.tRFC2_slr;
}

void DDR5SPD::settRFC2_slr(const unsigned short value) {
    spdStruct.tRFC2_slr = value;
}

const unsigned short DDR5SPD::gettRFCsb_slr() {
    return spdStruct.tRFCsb_slr;
}

void DDR5SPD::settRFCsb_slr(const unsigned short value) {
    spdStruct.tRFCsb_slr = value;
}

const unsigned short DDR5SPD::gettRFC1_dlr() {
    return spdStruct.tRFC1_dlr;
}

void DDR5SPD::settRFC1_dlr(const unsigned short value) {
    spdStruct.tRFC1_dlr = value;
}

const unsigned short DDR5SPD::gettRFC2_dlr() {
    return spdStruct.tRFC2_dlr;
}

void DDR5SPD::settRFC2_dlr(const unsigned short value) {
    spdStruct.tRFC2_dlr = value;
}

const unsigned short DDR5SPD::gettRFCsb_dlr() {
    return spdStruct.tRFCsb_dlr;
}

void DDR5SPD::settRFCsb_dlr(const unsigned short value) {
    spdStruct.tRFCsb_dlr = value;
}

const unsigned short DDR5SPD::gettRRD_L() {
    return spdStruct.tRRD_L;
}

void DDR5SPD::settRRD_L(const unsigned short value) {
    spdStruct.tRRD_L = value;
}

const unsigned short DDR5SPD::gettRRD_L_lowerLimit() {
    return spdStruct.tRRD_L_lowerLimit;
}

void DDR5SPD::settRRD_L_lowerLimit(const unsigned short value) {
    spdStruct.tRRD_L_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_L() {
    return spdStruct.tCCD_L;
}

void DDR5SPD::settCCD_L(const unsigned short value) {
    spdStruct.tCCD_L = value;
}

const unsigned short DDR5SPD::gettCCD_L_lowerLimit() {
    return spdStruct.tCCD_L_lowerLimit;
}

void DDR5SPD::settCCD_L_lowerLimit(const unsigned short value) {
    spdStruct.tCCD_L_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_L_WR() {
    return spdStruct.tCCD_L_WR;
}

void DDR5SPD::settCCD_L_WR(const unsigned short value) {
    spdStruct.tCCD_L_WR = value;
}

const unsigned short DDR5SPD::gettCCD_L_WR_lowerLimit(){
    return spdStruct.tCCD_L_WR_lowerLimit;
}

void DDR5SPD::settCCD_L_WR_lowerLimit(const unsigned short value) {
    spdStruct.tCCD_L_WR_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_L_WR2() {
    return spdStruct.tCCD_L_WR2;
}

void DDR5SPD::settCCD_L_WR2(const unsigned short value) {
    spdStruct.tCCD_L_WR2 = value;
}

const unsigned short DDR5SPD::gettCCD_L_WR2_lowerLimit() {
    return spdStruct.tCCD_L_WR2_lowerLimit;
}

void DDR5SPD::settCCD_L_WR2_lowerLimit(const unsigned short value) {
    spdStruct.tCCD_L_WR2_lowerLimit = value;
}

const unsigned short DDR5SPD::gettFAW() {
    return spdStruct.tFAW;
}

void DDR5SPD::settFAW(const unsigned short value) {
    spdStruct.tFAW = value;
}

const unsigned short DDR5SPD::gettFAW_lowerLimit() {
    return spdStruct.tFAW_lowerLimit;
}

void DDR5SPD::settFAW_lowerLimit(const unsigned short value) {
    spdStruct.tFAW_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_L_WTR() {
    return spdStruct.tCCD_L_WTR;
}

void DDR5SPD::settCCD_L_WTR(const unsigned short value) {
    spdStruct.tCCD_L_WTR = value;
}

const unsigned short DDR5SPD::gettCCD_L_WTR_lowerLimit() {
    return spdStruct.tCCD_L_WTR_lowerLimit;
}

void DDR5SPD::settCCD_L_WTR_lowerLimit(const unsigned short value) {
    spdStruct.tCCD_L_WTR_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_S_WTR() {
    return spdStruct.tCCD_S_WTR;
}

void DDR5SPD::settCCD_S_WTR(const unsigned short value) {
    spdStruct.tCCD_S_WTR = value;
}

const unsigned short DDR5SPD::gettCCD_S_WTR_lowerLimit() {
    return spdStruct.tCCD_S_WTR_lowerLimit;
}

void DDR5SPD::settCCD_S_WTR_lowerLimit(const unsigned short value) {
    spdStruct.tCCD_S_WTR_lowerLimit = value;
}

const unsigned short DDR5SPD::gettRTP() {
    return spdStruct.tRTP;
}

void DDR5SPD::settRTP(const unsigned short value) {
    spdStruct.tRTP = value;
}

const unsigned short DDR5SPD::gettRTP_lowerLimit(){
    return spdStruct.tRTP_lowerLimit;
}

void DDR5SPD::settRTP_lowerLimit(const unsigned short value) {
    spdStruct.tRTP_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_M() {
    return spdStruct.tCCD_M;
}

void DDR5SPD::settCCD_M(const unsigned short value) {
   spdStruct.tCCD_M = value;
}

const unsigned short DDR5SPD::gettCCD_M_lowerLimit() {
    return spdStruct.tCCD_M_lowerLimit;
}

void DDR5SPD::settCCD_M_lowerLimit(const unsigned short value) {
    spdStruct.tCCD_M_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_M_WR() {
    return spdStruct.tCCD_M_WR;
}

void DDR5SPD::settCCD_M_WR(const unsigned short value) {
    spdStruct.tCCD_M_WR = value;
}

const unsigned short DDR5SPD::gettCCD_M_WR_lowerLimit() {
    return spdStruct.tCCD_M_WR_lowerLimit;
}

void DDR5SPD::settCCD_M_WR_lowerLimit(const unsigned short value) {
    spdStruct.tCCD_M_WR_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_M_WTR() {
    return spdStruct.tCCD_M_WTR;
}

void DDR5SPD::settCCD_M_WTR(const unsigned short value) {
    spdStruct.tCCD_M_WTR = value;
}

const unsigned short DDR5SPD::gettCCD_M_WTR_lowerLimit() {
    return spdStruct.tCCD_M_WTR_lowerLimit;
}

void DDR5SPD::settCCD_M_WTR_lowerLimit(const unsigned short value) {
    spdStruct.tCCD_M_WTR_lowerLimit = value;
}

const unsigned short DDR5SPD::getBanksPerBankGroup(){
    return banksPerBankGroupBitsMap[(spdStruct.firstBankGroups & 0x7)];
}

void DDR5SPD::setBanksPerBankGroup(const unsigned short value) {
    int index = std::distance(banksPerBankGroupBitsMap.begin(),
                              std::find(banksPerBankGroupBitsMap.begin(), banksPerBankGroupBitsMap.end(), value));

    if (index >= 0 && value <= 2) {
        spdStruct.firstBankGroups = ((spdStruct.firstBankGroups & 0xF8) | (index));
    }
}

const unsigned short DDR5SPD::getBankGroups() {
    return bankGroupsBitsMap[(spdStruct.firstBankGroups >> 5)];
}

void DDR5SPD::setBankGroups(const unsigned short value) {
    int index = std::distance(bankGroupsBitsMap.begin(),
                              std::find(bankGroupsBitsMap.begin(), bankGroupsBitsMap.end(), value));

    if (index >= 0 && value <= 3) {
        spdStruct.firstBankGroups = ((spdStruct.firstBankGroups & 0x1F) | (index << 5));
    }
}

const unsigned short DDR5SPD::getColumnAddresses(){
    return columnAddressBitsMap[(spdStruct.firstAddressing >> 5)];
}

void DDR5SPD::setColumnAddresses(const unsigned short value) {
    int index = std::distance(columnAddressBitsMap.begin(),
                              std::find(columnAddressBitsMap.begin(), columnAddressBitsMap.end(), value));

    if (index >= 0 && value <= 1) {
        spdStruct.firstAddressing = ((spdStruct.firstAddressing & 0x1F) | (index << 5));
    }
}

const unsigned short DDR5SPD::getRowAddresses() {
    return rowAddressBitsMap[(spdStruct.firstAddressing & 0x1F)];
}

void DDR5SPD::setRowAddresses(const unsigned short value) {
    int index = std::distance(rowAddressBitsMap.begin(),
                              std::find(rowAddressBitsMap.begin(), rowAddressBitsMap.end(), value));

    if (index >= 0 && value <= 3) {
        spdStruct.firstAddressing = ((spdStruct.firstAddressing & 0xE0) | (index));
    }
}

const unsigned short DDR5SPD::getDeviceWidth(){
    return deviceWidthMap[(spdStruct.firstIOWitdth >> 5)];
}

void DDR5SPD::setDeviceWidth(const unsigned short value) {
    int index = std::distance(deviceWidthMap.begin(),
                              std::find(deviceWidthMap.begin(), deviceWidthMap.end(), value));

    if (index >= 0 && value <= 3) {
        spdStruct.firstIOWitdth = ((spdStruct.firstIOWitdth & 0x1F) | (index << 5));
    }
}

const char DDR5SPD::getManufacturingYear() {
    // Year is represented in hex e.g. 0x22 = 2022
    return utilities::convert_date_byte(spdStruct.manufactureDate[0]);
}

void DDR5SPD::setManufacturingYear(const char value) {
    if (value > 99) {
        spdStruct.manufactureDate[0] = utilities::convert_to_date_byte(99);
    } else {
        spdStruct.manufactureDate[0] = utilities::convert_to_date_byte(value);
    }
}

const char DDR5SPD::getManufacturingWeek() {
    return utilities::convert_date_byte(spdStruct.manufactureDate[1]);
}

void DDR5SPD::setManufacturingWeek(const char value) {
    // 52 weeks in a year
    if (value > 52) {
        spdStruct.manufactureDate[1] = utilities::convert_to_date_byte(52);
    } else {
        spdStruct.manufactureDate[1] = utilities::convert_to_date_byte(value);
    }
}

const std::string DDR5SPD::getPartNumber() {
    return std::string(spdStruct.modulePartnumber);
}

void DDR5SPD::setPartNumber(const std::string partNumber)
{
    unsigned int stringLen = partNumber.size();

    // Check if string is too big
    if (stringLen > partNumberSize) {
        stringLen = partNumberSize;
    }

    std::string str = partNumber.substr(0, stringLen);

    // Copy substring to partnumber
    for (int i = 0; i < str.size(); ++i) {
        spdStruct.modulePartnumber[i] = str[i];
    }
    // Terminate string with 0's, although JEDEC recomends spaces
    for (int i = str.size(); i < partNumberSize; ++i) {
        spdStruct.modulePartnumber[i] = 0;
    }
}

const unsigned short DDR5SPD::calculateJedecCRC() {
    return utilities::Crc16(reinterpret_cast<unsigned char*>(&spdStruct), jedecBlockSize - 2);
}

const unsigned short DDR5SPD::getCRC() {
    return spdStruct.checksum;
}

void DDR5SPD::setCRC(const unsigned short value) {
    spdStruct.checksum = value;
}

void DDR5SPD::fixCRC() {
    setCRC(calculateJedecCRC());
}

const bool DDR5SPD::isXMPPresent() {
    return xmpBundle.isMagicPresent();
}

const bool DDR5SPD::isCRCValid(){
    return (calculateJedecCRC() == spdStruct.checksum);
}

const char * const DDR5SPD::getPointerToStruct() {
    return reinterpret_cast<char*>(&spdStruct);
}

const FormFactor DDR5SPD::getFormFactor() {
    return formFactorMap[spdStruct.moduleType & 0xF];
}

void DDR5SPD::setFormFactor(const FormFactor value) {
    int val = std::distance(formFactorMap.begin(),
                            std::find(formFactorMap.begin(), formFactorMap.end(), value));

    spdStruct.moduleType = ((spdStruct.moduleType & 0xF0) | (val & 0xF));
}

const Density DDR5SPD::getDensity() {
    if ((spdStruct.firstDensityPackage & 0xF) < 9) {
        return densityMap[spdStruct.firstDensityPackage & 0xF];
    }

    return Density::_0Gb;
}

void DDR5SPD::setDensity(const Density value) {
    int val = std::distance(densityMap.begin(),
                            std::find(densityMap.begin(), densityMap.end(), value));

    spdStruct.firstDensityPackage = ((spdStruct.firstDensityPackage & 0xF0) | (val & 0xF));
}
