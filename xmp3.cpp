#include "xmp3.h"
#include "utilities.h"
#include <cstring>

XMP3_Profile::XMP3_Profile(XMP_ProfileStruct& rawXmpProfileIn) :
    xmpProfileStruct(rawXmpProfileIn) {
}

const unsigned short XMP3_Profile::getVPP() {
    return utilities::ConvertByteToVoltageDDR5(xmpProfileStruct.vpp);
}

void XMP3_Profile::setVPP(const unsigned short vpp) {
    xmpProfileStruct.vpp = utilities::ConvertVoltageToByteDDR5(vpp);
}

const unsigned short XMP3_Profile::getVDD() {
    return utilities::ConvertByteToVoltageDDR5(xmpProfileStruct.vdd);
}

void XMP3_Profile::setVDD(const unsigned short vdd) {
    xmpProfileStruct.vdd = utilities::ConvertVoltageToByteDDR5(vdd);
}

const unsigned short XMP3_Profile::getVDDQ() {
    return utilities::ConvertByteToVoltageDDR5(xmpProfileStruct.vddq);
}

void XMP3_Profile::setVDDQ(const unsigned short vddq) {
    xmpProfileStruct.vddq = utilities::ConvertVoltageToByteDDR5(vddq);
}

const unsigned short XMP3_Profile::getVMEMCtrl() {
    return utilities::ConvertByteToVoltageDDR5(xmpProfileStruct.vmemctrl);
}

void XMP3_Profile::setVMEMCtrl(const unsigned short vmem) {
    xmpProfileStruct.vmemctrl = utilities::ConvertVoltageToByteDDR5(vmem);
}

const unsigned short XMP3_Profile::getMinCycleTime() {
    return utilities::ConvertBytes(xmpProfileStruct.minCycleTime[0], xmpProfileStruct.minCycleTime[1]);
}

void XMP3_Profile::setMinCycleTime(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.minCycleTime[0], xmpProfileStruct.minCycleTime[1], value);
}

const unsigned int XMP3_Profile::getFrequency() {
    return static_cast<unsigned int>(1.0 / (getMinCycleTime() / 1000000.0));
}

const unsigned int XMP3_Profile::getMT() {
    return getFrequency() * 2;
}

void XMP3_Profile::setCLSupported(const int cl, const bool supported){
    utilities::SetCLSupportedDDR5(xmpProfileStruct.clSupported, cl, supported);
}

const bool XMP3_Profile::getCLSupported(const int cl){
    return utilities::IsCLSupportedDDR5(xmpProfileStruct.clSupported, cl);
}

const unsigned short XMP3_Profile::gettAA() {
    return utilities::ConvertBytes(xmpProfileStruct.tAA[0], xmpProfileStruct.tAA[1]);
}

void XMP3_Profile::settAA(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.tAA[0], xmpProfileStruct.tAA[1], value);
}

const unsigned short XMP3_Profile::gettRCD() {
    return utilities::ConvertBytes(xmpProfileStruct.tRCD[0], xmpProfileStruct.tRCD[1]);
}

void XMP3_Profile::settRCD(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.tRCD[0], xmpProfileStruct.tRCD[1], value);
}

const unsigned short XMP3_Profile::gettRP() {
    return utilities::ConvertBytes(xmpProfileStruct.tRP[0], xmpProfileStruct.tRP[1]);
}

void XMP3_Profile::settRP(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.tRP[0], xmpProfileStruct.tRP[1], value);
}

const unsigned short XMP3_Profile::gettRAS() {
    return utilities::ConvertBytes(xmpProfileStruct.tRAS[0], xmpProfileStruct.tRAS[1]);
}

void XMP3_Profile::settRAS(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.tRAS[0], xmpProfileStruct.tRAS[1], value);
}

const unsigned short XMP3_Profile::gettRC() {
    return utilities::ConvertBytes(xmpProfileStruct.tRC[0], xmpProfileStruct.tRC[1]);
}

void XMP3_Profile::settRC(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.tRC[0], xmpProfileStruct.tRC[1], value);
}

const unsigned short XMP3_Profile::gettWR() {
    return utilities::ConvertBytes(xmpProfileStruct.tWR[0], xmpProfileStruct.tWR[1]);
}

void XMP3_Profile::settWR(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.tWR[0], xmpProfileStruct.tWR[1], value);
}

const unsigned short XMP3_Profile::gettRFC1() {
    return utilities::ConvertBytes(xmpProfileStruct.tRFC1[0], xmpProfileStruct.tRFC1[1]);
}

void XMP3_Profile::settRFC1(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.tRFC1[0], xmpProfileStruct.tRFC1[1], value);
}

const unsigned short XMP3_Profile::gettRFC2() {
    return utilities::ConvertBytes(xmpProfileStruct.tRFC2[0], xmpProfileStruct.tRFC2[1]);
}

void XMP3_Profile::settRFC2(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.tRFC2[0], xmpProfileStruct.tRFC2[1], value);
}

const unsigned short XMP3_Profile::gettRFC() {
    return utilities::ConvertBytes(xmpProfileStruct.tRFC[0], xmpProfileStruct.tRFC[1]);
}

void XMP3_Profile::settRFC(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.tRFC[0], xmpProfileStruct.tRFC[1], value);
}

const unsigned short XMP3_Profile::gettRRD_L() {
    return utilities::ConvertBytes(xmpProfileStruct.tRRD_L[0], xmpProfileStruct.tRRD_L[1]);
}

void XMP3_Profile::settRRD_L(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.tRRD_L[0], xmpProfileStruct.tRRD_L[1], value);
}

const unsigned short XMP3_Profile::gettRRD_L_lowerLimit() {
    return xmpProfileStruct.tRRD_L_lowerLimit;
}

void XMP3_Profile::settRRD_L_lowerLimit(const unsigned short value) {
    xmpProfileStruct.tRRD_L_lowerLimit = value;
}

const unsigned short XMP3_Profile::gettCCD_L_WR() {
    return utilities::ConvertBytes(xmpProfileStruct.tCCD_L_WR[0], xmpProfileStruct.tCCD_L_WR[1]);
}

void XMP3_Profile::settCCD_L_WR(unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.tCCD_L_WR[0], xmpProfileStruct.tCCD_L_WR[1], value);
}

const unsigned short XMP3_Profile::gettCCD_L_WR_lowerLimit() {
    return xmpProfileStruct.tCCD_L_WR_lowerLimit;
}

void XMP3_Profile::settCCD_L_WR_lowerLimit(unsigned short value) {
    xmpProfileStruct.tCCD_L_WR_lowerLimit = value;
}

const unsigned short XMP3_Profile::gettCCD_L_WR2() {
    return utilities::ConvertBytes(xmpProfileStruct.tCCD_L_WR2[0], xmpProfileStruct.tCCD_L_WR2[1]);
}

void XMP3_Profile::settCCD_L_WR2(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.tCCD_L_WR2[0], xmpProfileStruct.tCCD_L_WR2[1], value);
}

const unsigned short XMP3_Profile::gettCCD_L_WR2_lowerLimit() {
    return xmpProfileStruct.tCCD_L_WR2_lowerLimit;
}

void XMP3_Profile::settCCD_L_WR2_lowerLimit(const unsigned short value) {
    xmpProfileStruct.tCCD_L_WR2_lowerLimit = value;
}

const unsigned short XMP3_Profile::gettCCD_L_WTR() {
    return utilities::ConvertBytes(xmpProfileStruct.tCCD_L_WTR[0], xmpProfileStruct.tCCD_L_WTR[1]);
}

void XMP3_Profile::settCCD_L_WTR(unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.tCCD_L_WTR[0], xmpProfileStruct.tCCD_L_WTR[1], value);
}

const unsigned short XMP3_Profile::gettCCD_L_WTR_lowerLimit() {
    return xmpProfileStruct.tCCD_L_WTR_lowerLimit;
}

void XMP3_Profile::settCCD_L_WTR_lowerLimit(unsigned short value) {
    xmpProfileStruct.tCCD_L_WTR_lowerLimit = value;
}

const unsigned short XMP3_Profile::gettCCD_S_WTR() {
    return utilities::ConvertBytes(xmpProfileStruct.tCCD_S_WTR[0], xmpProfileStruct.tCCD_S_WTR[1]);
}

void XMP3_Profile::settCCD_S_WTR(unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.tCCD_S_WTR[0], xmpProfileStruct.tCCD_S_WTR[1], value);
}

const unsigned short XMP3_Profile::gettCCD_S_WTR_lowerLimit() {
    return xmpProfileStruct.tCCD_S_WTR_lowerLimit;
}

void XMP3_Profile::settCCD_S_WTR_lowerLimit(unsigned short value) {
    xmpProfileStruct.tCCD_S_WTR_lowerLimit = value;
}

const unsigned short XMP3_Profile::gettCCD_L() {
    return utilities::ConvertBytes(xmpProfileStruct.tCCD_L[0], xmpProfileStruct.tCCD_L[1]);
}

void XMP3_Profile::settCCD_L(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.tCCD_L[0], xmpProfileStruct.tCCD_L[1], value);
}

const unsigned short XMP3_Profile::gettCCD_L_lowerLimit() {
    return xmpProfileStruct.tCCD_L_lowerLimit;
}

void XMP3_Profile::settCCD_L_lowerLimit(const unsigned short value) {
    xmpProfileStruct.tCCD_L_lowerLimit = value;
}

const unsigned short XMP3_Profile::gettRTP() {
    return utilities::ConvertBytes(xmpProfileStruct.tRTP[0], xmpProfileStruct.tRTP[1]);
}

void XMP3_Profile::settRTP(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.tRTP[0], xmpProfileStruct.tRTP[1], value);
}

const unsigned short XMP3_Profile::gettRTP_lowerLimit() {
    return xmpProfileStruct.tRTP_lowerLimit;
}

void XMP3_Profile::settRTP_lowerLimit(const unsigned short value) {
    xmpProfileStruct.tRTP_lowerLimit = value;
}

const unsigned short XMP3_Profile::gettFAW() {
    return utilities::ConvertBytes(xmpProfileStruct.tFAW[0], xmpProfileStruct.tFAW[1]);
}

void XMP3_Profile::settFAW(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.tFAW[0], xmpProfileStruct.tFAW[1], value);
}

const unsigned short XMP3_Profile::gettFAW_lowerLimit() {
    return xmpProfileStruct.tFAW_lowerLimit;
}

void XMP3_Profile::settFAW_lowerLimit(const unsigned short value) {
    xmpProfileStruct.tFAW_lowerLimit = value;
}

const bool XMP3_Profile::getIntelDynamicMemoryBoost() {
    return utilities::GetBit(xmpProfileStruct.memory_boost_realtime_training, IntelDynamicMemoryBoostBit);
}

void XMP3_Profile::setIntelDynamicMemoryBoost(const bool value) {
    utilities::SetBit(xmpProfileStruct.memory_boost_realtime_training, IntelDynamicMemoryBoostBit, value);
}

const bool XMP3_Profile::getRealTimeMemoryFrequencyOC() {
    return utilities::GetBit(xmpProfileStruct.memory_boost_realtime_training, RealTimeMemoryFrequencyOCBit);
}

void XMP3_Profile::setRealTimeMemoryFrequencyOC(const bool value) {
    utilities::SetBit(xmpProfileStruct.memory_boost_realtime_training, RealTimeMemoryFrequencyOCBit, value);
}

const unsigned short XMP3_Profile::getDimmsChannel(){
    // TODO
    return 1;
}

void XMP3_Profile::setDimmsChannel(unsigned short value) {
    // TODO
}

const CommandRate XMP3_Profile::getCommandRate() {
    unsigned short index = (unsigned short)(xmpProfileStruct.commandRate & 0xF);

    CommandRate val = CommandRate::Undefined;
    switch (index) {
        case 1:
            val = CommandRate::_1n;
            break;

        case 2:
            val = CommandRate::_2n;
            break;

        case 3:
            val = CommandRate::_3n;
            break;

        default:
            break;
    }

    return val;
}

void XMP3_Profile::setCommandRate(const CommandRate cr) {
    switch (cr) {
        case CommandRate::_1n:
            xmpProfileStruct.commandRate = ((xmpProfileStruct.commandRate & 0xF0) | (1 & 0xF));
            break;

        case CommandRate::_2n:
            xmpProfileStruct.commandRate = ((xmpProfileStruct.commandRate & 0xF0) | (2 & 0xF));
            break;

        case CommandRate::_3n:
            xmpProfileStruct.commandRate = ((xmpProfileStruct.commandRate & 0xF0) | (3 & 0xF));
            break;

        default:
            xmpProfileStruct.commandRate = ((xmpProfileStruct.commandRate & 0xF0) | (0 & 0xF));
            break;
    }
}

const unsigned short XMP3_Profile::getCRC() {
    return utilities::ConvertBytes(xmpProfileStruct.checksum[0], xmpProfileStruct.checksum[1]);
}

void XMP3_Profile::setCRC(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpProfileStruct.checksum[0], xmpProfileStruct.checksum[1], value);
}

void XMP3_Profile::fixCRC() {
    unsigned int  crc = utilities::Crc16(reinterpret_cast<unsigned char*>(&xmpProfileStruct), sizeof(XMP_ProfileStruct) - 2);
    setCRC(crc);
}

void XMP3_Profile::wipeProfile() {
    std::memset(&xmpProfileStruct, 0x0, sizeof (XMP_ProfileStruct));
}

void XMP3_Profile::resetProfile() {
    wipeProfile();

    // Create default JEDEC 6000B profile
    setVPP(180);
    setVDD(110);
    setVDDQ(110);
    setVMEMCtrl(110);

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
    settRRD_L(5000);
    settRRD_L_lowerLimit(8);
    settCCD_L_WR(20000);
    settCCD_L_WR_lowerLimit(32);
    settCCD_L_WR2(10000);
    settCCD_L_WR2_lowerLimit(16);
    settCCD_L_WTR(10000);
    settCCD_L_WTR_lowerLimit(16);
    settCCD_S_WTR(2500);
    settCCD_S_WTR_lowerLimit(4);
    settCCD_L(5000);
    settCCD_L_lowerLimit(8);
    settRTP(7500);
    settRTP_lowerLimit(12);
    settFAW(10666);
    settFAW_lowerLimit(32);
    setDimmsChannel(1);
    setIntelDynamicMemoryBoost(true);
    setRealTimeMemoryFrequencyOC(true);
    setCommandRate(CommandRate::_2n);
    setCLSupported(22, true);
    setCLSupported(26, true);
    setCLSupported(28, true);
    setCLSupported(30, true);
    setCLSupported(32, true);
    setCLSupported(36, true);
    setCLSupported(40, true);
    setCLSupported(42, true);
    setCLSupported(46, true);
    setCLSupported(48, true);
    setCLSupported(50, true);
    setCLSupported(54, true);
}

// XMP Bundle methods
XMP3_Bundle::XMP3_Bundle(XMP_Struct& xmpBlockRef) :
    xmpStruct(xmpBlockRef),
    profile1(xmpBlockRef.profile1),
    profile2(xmpBlockRef.profile2),
    profile3(xmpBlockRef.profile3),
    profileUser1(xmpBlockRef.user_profile1),
    profileUser2(xmpBlockRef.user_profile2) {
}

const bool XMP3_Bundle::isXMP1Enabled() {
    return utilities::GetBit(xmpStruct.header.profileEnBits, xmpProfile1EnableBit);
}

void XMP3_Bundle::setXMP1Enabled(const bool value) {
    utilities::SetBit(xmpStruct.header.profileEnBits, xmpProfile1EnableBit, value);
}

const bool XMP3_Bundle::isXMP2Enabled() {
    return utilities::GetBit(xmpStruct.header.profileEnBits, xmpProfile2EnableBit);
}

void XMP3_Bundle::setXMP2Enabled(const bool value) {
    utilities::SetBit(xmpStruct.header.profileEnBits, xmpProfile2EnableBit, value);
}

const bool XMP3_Bundle::isXMP3Enabled() {
    return utilities::GetBit(xmpStruct.header.profileEnBits, xmpProfile3EnableBit);
}

void XMP3_Bundle::setXMP3Enabled(const bool value) {
    utilities::SetBit(xmpStruct.header.profileEnBits, xmpProfile3EnableBit, value);
}

const std::string XMP3_Bundle::getXMP1ProfileName() {
    char* profileName = &(xmpStruct.header.profileName1[0]);
    return std::string(profileName);
}

void XMP3_Bundle::setXMP1ProfileName(const std::string value) {
    utilities::SetCString(value, maxXmpProfileName, &(xmpStruct.header.profileName1[0]));
}

const std::string XMP3_Bundle::getXMP2ProfileName() {
    char* profileName = &(xmpStruct.header.profileName2[0]);
    return std::string(profileName);
}

void XMP3_Bundle::setXMP2ProfileName(const std::string value) {
    utilities::SetCString(value, maxXmpProfileName, &(xmpStruct.header.profileName2[0]));
}

const std::string XMP3_Bundle::getXMP3ProfileName() {
    char* profileName = &(xmpStruct.header.profileName3[0]);
    return std::string(profileName);
}

void XMP3_Bundle::setXMP3ProfileName(const std::string value) {
    utilities::SetCString(value, maxXmpProfileName, &(xmpStruct.header.profileName3[0]));
}

void XMP3_Bundle::enableMagic() {
    xmpStruct.header.magic1 = XMPHeaderMagic[0];
    xmpStruct.header.magic2 = XMPHeaderMagic[1];
}

void XMP3_Bundle::clearMagic() {
    xmpStruct.header.magic1 = 0x00;
    xmpStruct.header.magic2 = 0x00;
}

bool XMP3_Bundle::isMagicPresent() {
    return (xmpStruct.header.magic1 == XMPHeaderMagic[0] && xmpStruct.header.magic2 == XMPHeaderMagic[1]);
}

const unsigned short XMP3_Bundle::getHeaderCRC() {
    return utilities::ConvertBytes(xmpStruct.header.checksum[0], xmpStruct.header.checksum[1]);
}

void XMP3_Bundle::setHeaderCRC(const unsigned short value) {
    utilities::Convert16bitUnsignedInteger(xmpStruct.header.checksum[0], xmpStruct.header.checksum[1], value);
}

void XMP3_Bundle::fixHeaderCRC() {
    unsigned int  crc = utilities::Crc16(reinterpret_cast<unsigned char*>(&xmpStruct.header), sizeof(XMP_HeaderStruct) - 2);
    setHeaderCRC(crc);
}

void XMP3_Bundle::fixCRCs() {
    fixHeaderCRC();
    // TODO: fix profile crcs
}

void XMP3_Bundle::wipe() {
    std::memset(&xmpStruct, 0x0, sizeof (XMP_Struct));
}
