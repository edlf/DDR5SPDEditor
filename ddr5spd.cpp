#include "ddr5spd.h"
#include "utilities.h"

#include <algorithm>

DDR5SPD::DDR5SPD(SPD_Struct value) :
    spdStruct(value),
    xmpBundle(spdStruct.xmpBlock)
{
}

const unsigned short DDR5SPD::getMinCycleTime() {
    return utilities::ConvertBytes(spdStruct.minCycleTime[0], spdStruct.minCycleTime[1]);
}

void DDR5SPD::setMinCycleTime(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.minCycleTime[0], spdStruct.minCycleTime[1], value);
}

const unsigned short DDR5SPD::getMaxCycleTime() {
    return utilities::ConvertBytes(spdStruct.maxCycleTime[0], spdStruct.maxCycleTime[1]);
}

void DDR5SPD::setMaxCycleTime(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.maxCycleTime[0], spdStruct.maxCycleTime[1], value);
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
    return utilities::ConvertBytes(spdStruct.tAA[0], spdStruct.tAA[1]);
}

void DDR5SPD::settAA(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tAA[0], spdStruct.tAA[1], value);
}

const unsigned short DDR5SPD::gettRCD() {
    return utilities::ConvertBytes(spdStruct.tRCD[0], spdStruct.tRCD[1]);
}

void DDR5SPD::settRCD(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tRCD[0], spdStruct.tRCD[1], value);
}

const unsigned short DDR5SPD::gettRP() {
    return utilities::ConvertBytes(spdStruct.tRP[0], spdStruct.tRP[1]);
}

void DDR5SPD::settRP(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tRP[0], spdStruct.tRP[1], value);
}

const unsigned short DDR5SPD::gettRAS() {
    return utilities::ConvertBytes(spdStruct.tRAS[0], spdStruct.tRAS[1]);
}

void DDR5SPD::settRAS(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tRAS[0], spdStruct.tRAS[1], value);
}

const unsigned short DDR5SPD::gettRC() {
    return utilities::ConvertBytes(spdStruct.tRC[0], spdStruct.tRC[1]);
}

void DDR5SPD::settRC(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tRC[0], spdStruct.tRC[1], value);
}

const unsigned short DDR5SPD::gettWR() {
    return utilities::ConvertBytes(spdStruct.tWR[0], spdStruct.tWR[1]);
}

void DDR5SPD::settWR(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tWR[0], spdStruct.tWR[1], value);
}

const unsigned short DDR5SPD::gettRFC1_slr() {
    return utilities::ConvertBytes(spdStruct.tRFC1_slr[0], spdStruct.tRFC1_slr[1]);
}

void DDR5SPD::settRFC1_slr(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tRFC1_slr[0], spdStruct.tRFC1_slr[1], value);
}

const unsigned short DDR5SPD::gettRFC2_slr() {
    return utilities::ConvertBytes(spdStruct.tRFC2_slr[0], spdStruct.tRFC2_slr[1]);
}

void DDR5SPD::settRFC2_slr(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tRFC2_slr[0], spdStruct.tRFC2_slr[1], value);
}

const unsigned short DDR5SPD::gettRFCsb_slr() {
    return utilities::ConvertBytes(spdStruct.tRFCsb_slr[0], spdStruct.tRFCsb_slr[1]);
}

void DDR5SPD::settRFCsb_slr(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tRFCsb_slr[0], spdStruct.tRFCsb_slr[1], value);
}

const unsigned short DDR5SPD::gettRFC1_dlr() {
    return utilities::ConvertBytes(spdStruct.tRFC1_dlr[0], spdStruct.tRFC1_dlr[1]);
}

void DDR5SPD::settRFC1_dlr(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tRFC1_dlr[0], spdStruct.tRFC1_dlr[1], value);
}

const unsigned short DDR5SPD::gettRFC2_dlr() {
    return utilities::ConvertBytes(spdStruct.tRFC2_dlr[0], spdStruct.tRFC2_dlr[1]);
}

void DDR5SPD::settRFC2_dlr(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tRFC2_dlr[0], spdStruct.tRFC2_dlr[1], value);
}

const unsigned short DDR5SPD::gettRFCsb_dlr() {
    return utilities::ConvertBytes(spdStruct.tRFCsb_dlr[0], spdStruct.tRFCsb_dlr[1]);
}

void DDR5SPD::settRFCsb_dlr(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tRFCsb_dlr[0], spdStruct.tRFCsb_dlr[1], value);
}

const unsigned short DDR5SPD::gettRRD_L() {
    return utilities::ConvertBytes(spdStruct.tRRD_L[0], spdStruct.tRRD_L[1]);
}

void DDR5SPD::settRRD_L(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tRRD_L[0], spdStruct.tRRD_L[1], value);
}

const unsigned short DDR5SPD::gettRRD_L_lowerLimit() {
    return spdStruct.tRRD_L_lowerLimit;
}

void DDR5SPD::settRRD_L_lowerLimit(const unsigned short value) {
    spdStruct.tRRD_L_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_L() {
    return utilities::ConvertBytes(spdStruct.tCCD_L[0], spdStruct.tCCD_L[1]);
}

void DDR5SPD::settCCD_L(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tCCD_L[0], spdStruct.tCCD_L[1], value);
}

const unsigned short DDR5SPD::gettCCD_L_lowerLimit() {
    return spdStruct.tCCD_L_lowerLimit;
}

void DDR5SPD::settCCD_L_lowerLimit(const unsigned short value) {
    spdStruct.tCCD_L_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_L_WR() {
    return utilities::ConvertBytes(spdStruct.tCCD_L_WR[0], spdStruct.tCCD_L_WR[1]);
}

void DDR5SPD::settCCD_L_WR(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tCCD_L_WR[0], spdStruct.tCCD_L_WR[1], value);
}

const unsigned short DDR5SPD::gettCCD_L_WR_lowerLimit(){
    return spdStruct.tCCD_L_WR_lowerLimit;
}

void DDR5SPD::settCCD_L_WR_lowerLimit(const unsigned short value) {
    spdStruct.tCCD_L_WR_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_L_WR2() {
    return utilities::ConvertBytes(spdStruct.tCCD_L_WR2[0], spdStruct.tCCD_L_WR2[1]);
}

void DDR5SPD::settCCD_L_WR2(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tCCD_L_WR2[0], spdStruct.tCCD_L_WR2[1], value);
}

const unsigned short DDR5SPD::gettCCD_L_WR2_lowerLimit() {
    return spdStruct.tCCD_L_WR2_lowerLimit;
}

void DDR5SPD::settCCD_L_WR2_lowerLimit(const unsigned short value) {
    spdStruct.tCCD_L_WR2_lowerLimit = value;
}

const unsigned short DDR5SPD::gettFAW() {
    return utilities::ConvertBytes(spdStruct.tFAW[0], spdStruct.tFAW[1]);
}

void DDR5SPD::settFAW(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tFAW[0], spdStruct.tFAW[1], value);
}

const unsigned short DDR5SPD::gettFAW_lowerLimit() {
    return spdStruct.tFAW_lowerLimit;
}

void DDR5SPD::settFAW_lowerLimit(const unsigned short value) {
    spdStruct.tFAW_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_L_WTR() {
    return utilities::ConvertBytes(spdStruct.tCCD_L_WTR[0], spdStruct.tCCD_L_WTR[1]);
}

void DDR5SPD::settCCD_L_WTR(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tCCD_L_WTR[0], spdStruct.tCCD_L_WTR[1], value);
}

const unsigned short DDR5SPD::gettCCD_L_WTR_lowerLimit() {
    return spdStruct.tCCD_L_WTR_lowerLimit;
}

void DDR5SPD::settCCD_L_WTR_lowerLimit(const unsigned short value) {
    spdStruct.tCCD_L_WTR_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_S_WTR() {
    return utilities::ConvertBytes(spdStruct.tCCD_S_WTR[0], spdStruct.tCCD_S_WTR[1]);
}

void DDR5SPD::settCCD_S_WTR(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tCCD_S_WTR[0], spdStruct.tCCD_S_WTR[1], value);
}

const unsigned short DDR5SPD::gettCCD_S_WTR_lowerLimit() {
    return spdStruct.tCCD_S_WTR_lowerLimit;
}

void DDR5SPD::settCCD_S_WTR_lowerLimit(const unsigned short value) {
    spdStruct.tCCD_S_WTR_lowerLimit = value;
}

const unsigned short DDR5SPD::gettRTP() {
    return utilities::ConvertBytes(spdStruct.tRTP[0], spdStruct.tRTP[1]);
}

void DDR5SPD::settRTP(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tRTP[0], spdStruct.tRTP[1], value);
}

const unsigned short DDR5SPD::gettRTP_lowerLimit(){
    return spdStruct.tRTP_lowerLimit;
}

void DDR5SPD::settRTP_lowerLimit(const unsigned short value) {
    spdStruct.tRTP_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_M() {
    return utilities::ConvertBytes(spdStruct.tCCD_M[0], spdStruct.tCCD_M[1]);
}

void DDR5SPD::settCCD_M(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tCCD_M[0], spdStruct.tCCD_M[1], value);
}

const unsigned short DDR5SPD::gettCCD_M_lowerLimit() {
    return spdStruct.tCCD_M_lowerLimit;
}

void DDR5SPD::settCCD_M_lowerLimit(const unsigned short value) {
    spdStruct.tCCD_M_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_M_WR() {
    return utilities::ConvertBytes(spdStruct.tCCD_M_WR[0], spdStruct.tCCD_M_WR[1]);
}

void DDR5SPD::settCCD_M_WR(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tCCD_M_WR[0], spdStruct.tCCD_M_WR[1], value);
}

const unsigned short DDR5SPD::gettCCD_M_WR_lowerLimit() {
    return spdStruct.tCCD_M_WR_lowerLimit;
}

void DDR5SPD::settCCD_M_WR_lowerLimit(const unsigned short value) {
    spdStruct.tCCD_M_WR_lowerLimit = value;
}

const unsigned short DDR5SPD::gettCCD_M_WTR() {
    return utilities::ConvertBytes(spdStruct.tCCD_M_WTR[0], spdStruct.tCCD_M_WTR[1]);
}

void DDR5SPD::settCCD_M_WTR(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.tCCD_M_WTR[0], spdStruct.tCCD_M_WTR[1], value);
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

const unsigned short DDR5SPD::getManufacturingYear(){
    return spdStruct.manufactureDate[0];   // Year is represented in hex e.g. 0x22 = 2022
}

void DDR5SPD::setManufacturingYear(const unsigned short value) {
    // TODO: Check max value
    if (value > 99) {
        spdStruct.manufactureDate[0] = 99;
    } else {
        spdStruct.manufactureDate[0] = value;
    }
}

const unsigned short DDR5SPD::getManufacturingWeek() {
    return spdStruct.manufactureDate[1];
}

void DDR5SPD::setManufacturingWeek(const unsigned short value)
{
    // 52 weeks in a year
    if (value > 52) {
        spdStruct.manufactureDate[1] = 52;
    } else {
        spdStruct.manufactureDate[1] = value;
    }
}

const std::string DDR5SPD::getPartNumber() {
    return std::string(spdStruct.modulePartnumber[0], partNumberSize);
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

const unsigned short DDR5SPD::getCRC() {
    return utilities::ConvertBytes(spdStruct.checksum[0], spdStruct.checksum[1]);
}

void DDR5SPD::setCRC(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(spdStruct.checksum[0], spdStruct.checksum[1], value);
}

void DDR5SPD::fixCRC() {
    unsigned int  crc = utilities::Crc16(reinterpret_cast<unsigned char*>(&spdStruct), jedecBlockSize - 2);
    setCRC(crc);
}

const bool DDR5SPD::isXMPPresent() {
    return xmpBundle.isMagicPresent();
}
