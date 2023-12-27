#include "ddr5spd.h"
#include "utilities.h"

#include <algorithm>

DDR5SPD::DDR5SPD(QByteArray byteArray){
    if (byteArray.length() != eepromSize) {
        // TODO error out
        return;
    }

    // TODO: Find proper way to do this
    rawSpd = *reinterpret_cast<RawSPD*>(byteArray.data());
}

const unsigned short DDR5SPD::getMinCycleTime() {
    return utilities::ConvertBytes(rawSpd.minCycleTime[0], rawSpd.minCycleTime[1]);
}

void DDR5SPD::setMinCycleTime(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.minCycleTime[0], rawSpd.minCycleTime[1], value);
}

const unsigned short DDR5SPD::getMaxCycleTime() {
    return utilities::ConvertBytes(rawSpd.maxCycleTime[0], rawSpd.maxCycleTime[1]);
}

void DDR5SPD::setMaxCycleTime(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.maxCycleTime[0], rawSpd.maxCycleTime[1], value);
}

const unsigned DDR5SPD::shortgettAA() {
    return utilities::ConvertBytes(rawSpd.tAA[0], rawSpd.tAA[1]);
}

void DDR5SPD::settAA(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tAA[0], rawSpd.tAA[1], value);
}

const unsigned short DDR5SPD::gettRCD() {
    return utilities::ConvertBytes(rawSpd.tRCD[0], rawSpd.tRCD[1]);
}

void DDR5SPD::settRCD(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tRCD[0], rawSpd.tRCD[1], value);
}

const unsigned short DDR5SPD::gettRP() {
    return utilities::ConvertBytes(rawSpd.tRP[0], rawSpd.tRP[1]);
}

void DDR5SPD::settRP(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tRP[0], rawSpd.tRP[1], value);
}

const unsigned short DDR5SPD::gettRAS() {
    return utilities::ConvertBytes(rawSpd.tRAS[0], rawSpd.tRAS[1]);
}

void DDR5SPD::settRAS(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tRAS[0], rawSpd.tRAS[1], value);
}

const unsigned short DDR5SPD::gettRC() {
    return utilities::ConvertBytes(rawSpd.tRC[0], rawSpd.tRC[1]);
}

void DDR5SPD::settRC(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tRC[0], rawSpd.tRC[1], value);
}

const unsigned short DDR5SPD::gettWR() {
    return utilities::ConvertBytes(rawSpd.tWR[0], rawSpd.tWR[1]);
}

void DDR5SPD::settWR(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tWR[0], rawSpd.tWR[1], value);
}

const unsigned short DDR5SPD::gettRFC1_slr() {
    return utilities::ConvertBytes(rawSpd.tRFC1_slr[0], rawSpd.tRFC1_slr[1]);
}

void DDR5SPD::settRFC1_slr(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tRFC1_slr[0], rawSpd.tRFC1_slr[1], value);
}

const unsigned short DDR5SPD::gettRFC2_slr() {
    return utilities::ConvertBytes(rawSpd.tRFC2_slr[0], rawSpd.tRFC2_slr[1]);
}

void DDR5SPD::settRFC2_slr(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tRFC2_slr[0], rawSpd.tRFC2_slr[1], value);
}

const unsigned short DDR5SPD::gettRFCsb_slr() {
    return utilities::ConvertBytes(rawSpd.tRFCsb_slr[0], rawSpd.tRFCsb_slr[1]);
}

void DDR5SPD::settRFCsb_slr(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tRFCsb_slr[0], rawSpd.tRFCsb_slr[1], value);
}

const unsigned short DDR5SPD::gettRFC1_dlr() {
    return utilities::ConvertBytes(rawSpd.tRFC1_dlr[0], rawSpd.tRFC1_dlr[1]);
}

void DDR5SPD::settRFC1_dlr(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tRFC1_dlr[0], rawSpd.tRFC1_dlr[1], value);
}

const unsigned short DDR5SPD::gettRFC2_dlr() {
    return utilities::ConvertBytes(rawSpd.tRFC2_dlr[0], rawSpd.tRFC2_dlr[1]);
}

void DDR5SPD::settRFC2_dlr(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tRFC2_dlr[0], rawSpd.tRFC2_dlr[1], value);
}

const unsigned short DDR5SPD::gettRFCsb_dlr() {
    return utilities::ConvertBytes(rawSpd.tRFCsb_dlr[0], rawSpd.tRFCsb_dlr[1]);
}

void DDR5SPD::settRFCsb_dlr(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tRFCsb_dlr[0], rawSpd.tRFCsb_dlr[1], value);
}

const unsigned short DDR5SPD::gettRRD_L() {
    return utilities::ConvertBytes(rawSpd.tRRD_L[0], rawSpd.tRRD_L[1]);
}

void DDR5SPD::settRRD_L(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tRRD_L[0], rawSpd.tRRD_L[1], value);
}

const unsigned short DDR5SPD::gettRRD_L_lowerLimit() {
    return rawSpd.tRRD_L_lowerLimit;
}

void DDR5SPD::settRRD_L_lowerLimit(const unsigned short value) {
    rawSpd.tRRD_L_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_L() {
    return utilities::ConvertBytes(rawSpd.tCCD_L[0], rawSpd.tCCD_L[1]);
}

void DDR5SPD::settCCD_L(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tCCD_L[0], rawSpd.tCCD_L[1], value);
}

const unsigned short DDR5SPD::gettCCD_L_lowerLimit() {
    return rawSpd.tCCD_L_lowerLimit;
}

void DDR5SPD::settCCD_L_lowerLimit(const unsigned short value) {
    rawSpd.tCCD_L_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_L_WR() {
    return utilities::ConvertBytes(rawSpd.tCCD_L_WR[0], rawSpd.tCCD_L_WR[1]);
}

void DDR5SPD::settCCD_L_WR(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tCCD_L_WR[0], rawSpd.tCCD_L_WR[1], value);
}

const unsigned short DDR5SPD::gettCCD_L_WR_lowerLimit(){
    return rawSpd.tCCD_L_WR_lowerLimit;
}

void DDR5SPD::settCCD_L_WR_lowerLimit(const unsigned short value) {
    rawSpd.tCCD_L_WR_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_L_WR2() {
    return utilities::ConvertBytes(rawSpd.tCCD_L_WR2[0], rawSpd.tCCD_L_WR2[1]);
}

void DDR5SPD::settCCD_L_WR2(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tCCD_L_WR2[0], rawSpd.tCCD_L_WR2[1], value);
}

const unsigned short DDR5SPD::gettCCD_L_WR2_lowerLimit() {
    return rawSpd.tCCD_L_WR2_lowerLimit;
}

void DDR5SPD::settCCD_L_WR2_lowerLimit(const unsigned short value) {
    rawSpd.tCCD_L_WR2_lowerLimit = value;
}

const unsigned short DDR5SPD::gettFAW() {
    return utilities::ConvertBytes(rawSpd.tFAW[0], rawSpd.tFAW[1]);
}

void DDR5SPD::settFAW(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tFAW[0], rawSpd.tFAW[1], value);
}

const unsigned short DDR5SPD::gettFAW_lowerLimit() {
    return rawSpd.tFAW_lowerLimit;
}

void DDR5SPD::settFAW_lowerLimit(const unsigned short value) {
    rawSpd.tFAW_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_L_WTR() {
    return utilities::ConvertBytes(rawSpd.tCCD_L_WTR[0], rawSpd.tCCD_L_WTR[1]);
}

void DDR5SPD::settCCD_L_WTR(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tCCD_L_WTR[0], rawSpd.tCCD_L_WTR[1], value);
}

const unsigned short DDR5SPD::gettCCD_L_WTR_lowerLimit() {
    return rawSpd.tCCD_L_WTR_lowerLimit;
}

void DDR5SPD::settCCD_L_WTR_lowerLimit(const unsigned short value) {
    rawSpd.tCCD_L_WTR_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_S_WTR() {
    return utilities::ConvertBytes(rawSpd.tCCD_S_WTR[0], rawSpd.tCCD_S_WTR[1]);
}

void DDR5SPD::settCCD_S_WTR(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tCCD_S_WTR[0], rawSpd.tCCD_S_WTR[1], value);
}

const unsigned short DDR5SPD::gettCCD_S_WTR_lowerLimit() {
    return rawSpd.tCCD_S_WTR_lowerLimit;
}

void DDR5SPD::settCCD_S_WTR_lowerLimit(const unsigned short value) {
    rawSpd.tCCD_S_WTR_lowerLimit = value;
}

const unsigned short DDR5SPD::gettRTP() {
    return utilities::ConvertBytes(rawSpd.tRTP[0], rawSpd.tRTP[1]);
}

void DDR5SPD::settRTP(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tRTP[0], rawSpd.tRTP[1], value);
}

const unsigned short DDR5SPD::gettRTP_lowerLimit(){
    return rawSpd.tRTP_lowerLimit;
}

void DDR5SPD::settRTP_lowerLimit(const unsigned short value) {
    rawSpd.tRTP_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_M() {
    return utilities::ConvertBytes(rawSpd.tCCD_M[0], rawSpd.tCCD_M[1]);
}

void DDR5SPD::settCCD_M(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tCCD_M[0], rawSpd.tCCD_M[1], value);
}

const unsigned short DDR5SPD::gettCCD_M_lowerLimit() {
    return rawSpd.tCCD_M_lowerLimit;
}

void DDR5SPD::settCCD_M_lowerLimit(const unsigned short value) {
    rawSpd.tCCD_M_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_M_WR() {
    return utilities::ConvertBytes(rawSpd.tCCD_M_WR[0], rawSpd.tCCD_M_WR[1]);
}

void DDR5SPD::settCCD_M_WR(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tCCD_M_WR[0], rawSpd.tCCD_M_WR[1], value);
}

const unsigned short DDR5SPD::gettCCD_M_WR_lowerLimit() {
    return rawSpd.tCCD_M_WR_lowerLimit;
}

void DDR5SPD::settCCD_M_WR_lowerLimit(const unsigned short value) {
    rawSpd.tCCD_M_WR_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_M_WTR() {
    return utilities::ConvertBytes(rawSpd.tCCD_M_WTR[0], rawSpd.tCCD_M_WTR[1]);
}

void DDR5SPD::settCCD_M_WTR(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.tCCD_M_WTR[0], rawSpd.tCCD_M_WTR[1], value);
}

const unsigned short DDR5SPD::gettCCD_M_WTR_lowerLimit() {
    return rawSpd.tCCD_M_WTR_lowerLimit;
}

void DDR5SPD::settCCD_M_WTR_lowerLimit(const unsigned short value) {
    rawSpd.tCCD_M_WTR_lowerLimit = value;
}

const unsigned short DDR5SPD::getBanksPerBankGroup(){
    return banksPerBankGroupBitsMap[(rawSpd.firstBankGroups & 0x7)];
}

void DDR5SPD::setBanksPerBankGroup(const unsigned short value) {
    int index = std::distance(banksPerBankGroupBitsMap.begin(),
                              std::find(banksPerBankGroupBitsMap.begin(), banksPerBankGroupBitsMap.end(), value));

    if (index >= 0 && value <= 2) {
        rawSpd.firstBankGroups = ((rawSpd.firstBankGroups & 0xF8) | (index));
    }
}

const unsigned short DDR5SPD::getBankGroups() {
    return bankGroupsBitsMap[(rawSpd.firstBankGroups >> 5)];
}

void DDR5SPD::setBankGroups(const unsigned short value) {
    int index = std::distance(bankGroupsBitsMap.begin(),
                              std::find(bankGroupsBitsMap.begin(), bankGroupsBitsMap.end(), value));

    if (index >= 0 && value <= 3) {
        rawSpd.firstBankGroups = ((rawSpd.firstBankGroups & 0x1F) | (index << 5));
    }
}

const unsigned short DDR5SPD::getColumnAddresses(){
    return columnAddressBitsMap[(rawSpd.firstAddressing >> 5)];
}

void DDR5SPD::setColumnAddresses(const unsigned short value) {
    int index = std::distance(columnAddressBitsMap.begin(),
                              std::find(columnAddressBitsMap.begin(), columnAddressBitsMap.end(), value));

    if (index >= 0 && value <= 1) {
        rawSpd.firstAddressing = ((rawSpd.firstAddressing & 0x1F) | (index << 5));
    }
}

const unsigned short DDR5SPD::getRowAddresses() {
    return rowAddressBitsMap[(rawSpd.firstAddressing & 0x1F)];
}

void DDR5SPD::setRowAddresses(const unsigned short value) {
    int index = std::distance(rowAddressBitsMap.begin(),
                              std::find(rowAddressBitsMap.begin(), rowAddressBitsMap.end(), value));

    if (index >= 0 && value <= 3) {
        rawSpd.firstAddressing = ((rawSpd.firstAddressing & 0xE0) | (index));
    }
}

const unsigned short DDR5SPD::getDeviceWidth(){
    return deviceWidthMap[(rawSpd.firstIOWitdth >> 5)];
}

void DDR5SPD::setDeviceWidth(const unsigned short value) {
    int index = std::distance(deviceWidthMap.begin(),
                              std::find(deviceWidthMap.begin(), deviceWidthMap.end(), value));

    if (index >= 0 && value <= 3) {
        rawSpd.firstIOWitdth = ((rawSpd.firstIOWitdth & 0x1F) | (index << 5));
    }
}

const unsigned short DDR5SPD::getManufacturingYear(){
    return rawSpd.manufactureDate[0];   // Year is represented in hex e.g. 0x22 = 2022
}

void DDR5SPD::setManufacturingYear(const unsigned short value) {
    // TODO: Check max value
    if (value > 99) {
        rawSpd.manufactureDate[0] = 99;
    } else {
        rawSpd.manufactureDate[0] = value;
    }
}

const unsigned short DDR5SPD::getManufacturingWeek() {
    return rawSpd.manufactureDate[1];
}

void DDR5SPD::setManufacturingWeek(const unsigned short value)
{
    // 52 weeks in a year
    if (value > 52) {
        rawSpd.manufactureDate[1] = 52;
    } else {
        rawSpd.manufactureDate[1] = value;
    }
}

const std::string DDR5SPD::getPartNumber() {
    return std::string(rawSpd.modulePartnumber[0], partNumberSize);
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
        rawSpd.modulePartnumber[i] = str[i];
    }
    // Terminate string with 0's, although JEDEC recomends spaces
    for (int i = str.size(); i < partNumberSize; ++i) {
        rawSpd.modulePartnumber[i] = 0;
    }
}

const unsigned short DDR5SPD::getCRC() {
    return utilities::ConvertBytes(rawSpd.checksum[0], rawSpd.checksum[1]);
}

void DDR5SPD::setCRC(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(rawSpd.checksum[0], rawSpd.checksum[1], value);
}
