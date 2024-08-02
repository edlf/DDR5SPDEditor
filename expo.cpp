#include "expo.h"
#include "utilities.h"
#include <cstring>

EXPO_ProfileStruct dummy;

EXPO_Profile::EXPO_Profile(EXPO_ProfileStruct& rawExpoProfileIn) :
    expoProfileStruct(rawExpoProfileIn) {
}

EXPO_Profile::EXPO_Profile() :
    expoProfileStruct(dummy) {
}

const unsigned short EXPO_Profile::getVPP() {
    return utilities::ConvertByteToVoltageDDR5(expoProfileStruct.vpp);
}

void EXPO_Profile::setVPP(const unsigned short vpp) {
    expoProfileStruct.vpp = utilities::ConvertVoltageToByteDDR5(vpp);
}

const unsigned short EXPO_Profile::getVDD() {
    return utilities::ConvertByteToVoltageDDR5(expoProfileStruct.vdd);
}

void EXPO_Profile::setVDD(const unsigned short vdd) {
    expoProfileStruct.vdd = utilities::ConvertVoltageToByteDDR5(vdd);
}

const unsigned short EXPO_Profile::getVDDQ() {
    return utilities::ConvertByteToVoltageDDR5(expoProfileStruct.vddq);
}

void EXPO_Profile::setVDDQ(const unsigned short vddq) {
    expoProfileStruct.vddq = utilities::ConvertVoltageToByteDDR5(vddq);
}

const unsigned short EXPO_Profile::getMinCycleTime() {
    return expoProfileStruct.minCycleTime;
}

void EXPO_Profile::setMinCycleTime(const unsigned short value) {
    expoProfileStruct.minCycleTime = value;
}

const unsigned int EXPO_Profile::getFrequency() {
    return static_cast<unsigned int>(1.0 / (getMinCycleTime() / 1000000.0));
}

const unsigned int EXPO_Profile::getMT() {
    return getFrequency() * 2;
}

const unsigned short EXPO_Profile::gettAA() {
    return expoProfileStruct.tAA;
}

void EXPO_Profile::settAA(const unsigned short value) {
    expoProfileStruct.tAA = value;
}

const unsigned short EXPO_Profile::gettRCD() {
    return expoProfileStruct.tRCD;
}

void EXPO_Profile::settRCD(const unsigned short value) {
    expoProfileStruct.tRCD = value;
}

const unsigned short EXPO_Profile::gettRP() {
    return expoProfileStruct.tRP;
}

void EXPO_Profile::settRP(const unsigned short value) {
    expoProfileStruct.tRP = value;
}

const unsigned short EXPO_Profile::gettRAS() {
    return expoProfileStruct.tRAS;
}

void EXPO_Profile::settRAS(const unsigned short value) {
    expoProfileStruct.tRAS = value;
}

const unsigned short EXPO_Profile::gettRC() {
    return expoProfileStruct.tRC;
}

void EXPO_Profile::settRC(const unsigned short value) {
    expoProfileStruct.tRC = value;
}

const unsigned short EXPO_Profile::gettWR() {
    return expoProfileStruct.tWR;
}

void EXPO_Profile::settWR(const unsigned short value) {
    expoProfileStruct.tWR = value;
}

const unsigned short EXPO_Profile::gettRFC1() {
    return expoProfileStruct.tRFC1;
}

void EXPO_Profile::settRFC1(const unsigned short value) {
    expoProfileStruct.tRFC1 = value;
}

const unsigned short EXPO_Profile::gettRFC2() {
    return expoProfileStruct.tRFC2;
}

void EXPO_Profile::settRFC2(const unsigned short value) {
    expoProfileStruct.tRFC2 = value;
}

const unsigned short EXPO_Profile::gettRFC() {
    return expoProfileStruct.tRFC;
}

void EXPO_Profile::settRFC(const unsigned short value) {
    expoProfileStruct.tRFC = value;
}

const unsigned short EXPO_Profile::getDimmsChannel(){
    // TODO
    return 1;
}

void EXPO_Profile::setDimmsChannel(unsigned short value) {
    // TODO
}

void EXPO_Profile::wipeProfile() {
    std::memset(&expoProfileStruct, 0x0, sizeof (EXPO_ProfileStruct));
}

void EXPO_Profile::resetProfile() {
    wipeProfile();

    // Create default JEDEC 6000B profile
    setVPP(180);
    setVDD(110);
    setVDDQ(110);
    setMinCycleTime(333);
    settAA(16000);
    settRCD(16000);
    settRP(16000);
    settRAS(32000);
    settRC(48000);
    settWR(30000);
    settRFC1(295);
    settRFC2(160);
    settRFC(130);
    setDimmsChannel(1);
}

const bool EXPO_Profile::hasData() {
    unsigned int  crc = utilities::Crc16(reinterpret_cast<unsigned char*>(&expoProfileStruct), sizeof(EXPO_ProfileStruct) - 2);
    return crc != 0x0;
}

EXPO_ProfileStruct EXPO_Profile::getCopy(){
    return expoProfileStruct;
}

void EXPO_Profile::import(const EXPO_ProfileStruct in) {
    expoProfileStruct = in;
}

// EXPO Bundle methods
EXPO_Bundle::EXPO_Bundle(EXPO_Struct& expoBlockRef) :
    expoStruct(expoBlockRef),
    profile1(expoBlockRef.profile1) {
}

void EXPO_Bundle::enableMagic() {
    expoStruct.header.magic[0] = EXPOHeaderMagic[0];
    expoStruct.header.magic[1] = EXPOHeaderMagic[1];
    expoStruct.header.magic[2] = EXPOHeaderMagic[2];
    expoStruct.header.magic[3] = EXPOHeaderMagic[3];
}

void EXPO_Bundle::clearMagic() {
    expoStruct.header.magic[0] = 0x00;
    expoStruct.header.magic[1] = 0x00;
    expoStruct.header.magic[2] = 0x00;
    expoStruct.header.magic[3] = 0x00;
}

bool EXPO_Bundle::isMagicPresent() {
    return (expoStruct.header.magic[0] == EXPOHeaderMagic[0] &&
            expoStruct.header.magic[1] == EXPOHeaderMagic[1] &&
            expoStruct.header.magic[2] == EXPOHeaderMagic[2] &&
            expoStruct.header.magic[3] == EXPOHeaderMagic[3]);
}

const unsigned short EXPO_Bundle::getCRC() {
    return expoStruct.checksum;
}

void EXPO_Bundle::setCRC(const unsigned short value) {
    expoStruct.checksum = value;
}

void EXPO_Bundle::fixCRC() {
    unsigned int  crc = utilities::Crc16(reinterpret_cast<unsigned char*>(&expoStruct), sizeof(EXPO_Struct) - 2);
    setCRC(crc);
}

void EXPO_Bundle::wipe() {
    std::memset(&expoStruct, 0x0, sizeof (EXPO_Struct));
}
