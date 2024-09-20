#include "xmp3.h"
#include "utilities.h"
#include <cstring>

// TODO: Remove hack
XMP_ProfileStruct dummyXMPProfile;

XMP3_Profile::XMP3_Profile(XMP_ProfileStruct& rawXmpProfileIn) :
    xmpProfileStruct(rawXmpProfileIn) {
}

XMP3_Profile::XMP3_Profile() :
    xmpProfileStruct(dummyXMPProfile) {
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
    return xmpProfileStruct.minCycleTime;
}

void XMP3_Profile::setMinCycleTime(const unsigned short value) {
    xmpProfileStruct.minCycleTime = value;
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
    return xmpProfileStruct.tAA;
}

void XMP3_Profile::settAA(const unsigned short value) {
    xmpProfileStruct.tAA = value;
}

const unsigned short XMP3_Profile::gettRCD() {
    return xmpProfileStruct.tRCD;
}

void XMP3_Profile::settRCD(const unsigned short value) {
    xmpProfileStruct.tRCD = value;
}

const unsigned short XMP3_Profile::gettRP() {
    return xmpProfileStruct.tRP;
}

void XMP3_Profile::settRP(const unsigned short value) {
    xmpProfileStruct.tRP = value;
}

const unsigned short XMP3_Profile::gettRAS() {
    return xmpProfileStruct.tRAS;
}

void XMP3_Profile::settRAS(const unsigned short value) {
    xmpProfileStruct.tRAS = value;
}

const unsigned short XMP3_Profile::gettRC() {
    return xmpProfileStruct.tRC;
}

void XMP3_Profile::settRC(const unsigned short value) {
    xmpProfileStruct.tRC = value;
}

const unsigned short XMP3_Profile::gettWR() {
    return xmpProfileStruct.tWR;
}

void XMP3_Profile::settWR(const unsigned short value) {
    xmpProfileStruct.tWR = value;
}

const unsigned short XMP3_Profile::gettRFC1() {
    return xmpProfileStruct.tRFC1;
}

void XMP3_Profile::settRFC1(const unsigned short value) {
    xmpProfileStruct.tRFC1 = value;
}

const unsigned short XMP3_Profile::gettRFC2() {
    return xmpProfileStruct.tRFC2;
}

void XMP3_Profile::settRFC2(const unsigned short value) {
    xmpProfileStruct.tRFC2 = value;
}

const unsigned short XMP3_Profile::gettRFC() {
    return xmpProfileStruct.tRFC;
}

void XMP3_Profile::settRFC(const unsigned short value) {
    xmpProfileStruct.tRFC = value;
}

const unsigned short XMP3_Profile::gettRRD_L() {
    return xmpProfileStruct.tRRD_L;
}

void XMP3_Profile::settRRD_L(const unsigned short value) {
    xmpProfileStruct.tRRD_L = value;
}

const unsigned short XMP3_Profile::gettRRD_L_lowerLimit() {
    return xmpProfileStruct.tRRD_L_lowerLimit;
}

void XMP3_Profile::settRRD_L_lowerLimit(const unsigned short value) {
    xmpProfileStruct.tRRD_L_lowerLimit = value;
}

const unsigned short XMP3_Profile::gettCCD_L_WR() {
    return xmpProfileStruct.tCCD_L_WR;
}

void XMP3_Profile::settCCD_L_WR(unsigned short value) {
    xmpProfileStruct.tCCD_L_WR = value;
}

const unsigned short XMP3_Profile::gettCCD_L_WR_lowerLimit() {
    return xmpProfileStruct.tCCD_L_WR_lowerLimit;
}

void XMP3_Profile::settCCD_L_WR_lowerLimit(unsigned short value) {
    xmpProfileStruct.tCCD_L_WR_lowerLimit = value;
}

const unsigned short XMP3_Profile::gettCCD_L_WR2() {
    return xmpProfileStruct.tCCD_L_WR2;
}

void XMP3_Profile::settCCD_L_WR2(const unsigned short value) {
    xmpProfileStruct.tCCD_L_WR2 = value;
}

const unsigned short XMP3_Profile::gettCCD_L_WR2_lowerLimit() {
    return xmpProfileStruct.tCCD_L_WR2_lowerLimit;
}

void XMP3_Profile::settCCD_L_WR2_lowerLimit(const unsigned short value) {
    xmpProfileStruct.tCCD_L_WR2_lowerLimit = value;
}

const unsigned short XMP3_Profile::gettCCD_L_WTR() {
    return xmpProfileStruct.tCCD_L_WTR;
}

void XMP3_Profile::settCCD_L_WTR(unsigned short value) {
    xmpProfileStruct.tCCD_L_WTR = value;
}

const unsigned short XMP3_Profile::gettCCD_L_WTR_lowerLimit() {
    return xmpProfileStruct.tCCD_L_WTR_lowerLimit;
}

void XMP3_Profile::settCCD_L_WTR_lowerLimit(unsigned short value) {
    xmpProfileStruct.tCCD_L_WTR_lowerLimit = value;
}

const unsigned short XMP3_Profile::gettCCD_S_WTR() {
    return xmpProfileStruct.tCCD_S_WTR;
}

void XMP3_Profile::settCCD_S_WTR(unsigned short value) {
    xmpProfileStruct.tCCD_S_WTR = value;
}

const unsigned short XMP3_Profile::gettCCD_S_WTR_lowerLimit() {
    return xmpProfileStruct.tCCD_S_WTR_lowerLimit;
}

void XMP3_Profile::settCCD_S_WTR_lowerLimit(unsigned short value) {
    xmpProfileStruct.tCCD_S_WTR_lowerLimit = value;
}

const unsigned short XMP3_Profile::gettCCD_L() {
    return xmpProfileStruct.tCCD_L;
}

void XMP3_Profile::settCCD_L(const unsigned short value) {
    xmpProfileStruct.tCCD_L = value;
}

const unsigned short XMP3_Profile::gettCCD_L_lowerLimit() {
    return xmpProfileStruct.tCCD_L_lowerLimit;
}

void XMP3_Profile::settCCD_L_lowerLimit(const unsigned short value) {
    xmpProfileStruct.tCCD_L_lowerLimit = value;
}

const unsigned short XMP3_Profile::gettRTP() {
    return xmpProfileStruct.tRTP;
}

void XMP3_Profile::settRTP(const unsigned short value) {
    xmpProfileStruct.tRTP = value;
}

const unsigned short XMP3_Profile::gettRTP_lowerLimit() {
    return xmpProfileStruct.tRTP_lowerLimit;
}

void XMP3_Profile::settRTP_lowerLimit(const unsigned short value) {
    xmpProfileStruct.tRTP_lowerLimit = value;
}

const unsigned short XMP3_Profile::gettFAW() {
    return xmpProfileStruct.tFAW;
}

void XMP3_Profile::settFAW(const unsigned short value) {
    xmpProfileStruct.tFAW = value;
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
    return xmpProfileStruct.checksum;
}

void XMP3_Profile::setCRC(const unsigned short value) {
    xmpProfileStruct.checksum = value;
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

const bool XMP3_Profile::hasData() {
    unsigned int  crc = utilities::Crc16(reinterpret_cast<unsigned char*>(&xmpProfileStruct), sizeof(XMP_ProfileStruct) - 2);
    return crc != 0x0;
}

XMP_ProfileStruct XMP3_Profile::getCopy(){
    return xmpProfileStruct;
}

void XMP3_Profile::import(const XMP_ProfileStruct in) {
    xmpProfileStruct = in;
}

// XMP Bundle methods
XMP3_Bundle::XMP3_Bundle(XMP_Struct& xmpBlockRef) :
    xmpStruct(xmpBlockRef),
    profile1(xmpBlockRef.profile1),
    profile2(xmpBlockRef.profile2),
    profile3(xmpBlockRef.profile3),
    profileUser1(xmpBlockRef.user_profile1),
    profileUser2(xmpBlockRef.user_profile2),
    expoCoexistence(false) {
}

XMP3_Bundle::XMP3_Bundle(XMP_Struct& xmpBlockRef, bool expo) :
    xmpStruct(xmpBlockRef),
    profile1(xmpBlockRef.profile1),
    profile2(xmpBlockRef.profile2),
    profile3(xmpBlockRef.profile3),
    profileUser1(xmpBlockRef.user_profile1),
    profileUser2(xmpBlockRef.user_profile2),
    expoCoexistence(expo) {
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
    if (expoCoexistence) {
        utilities::SetBit(xmpStruct.header.profileEnBits, xmpProfile3EnableBit, false);
    } else {
        utilities::SetBit(xmpStruct.header.profileEnBits, xmpProfile3EnableBit, value);
    }
}

const bool XMP3_Bundle::isXMPUser1Present() {
    if (expoCoexistence) {
        return false;
    }

    return profileUser1.hasData();
}

const bool XMP3_Bundle::isXMPUser2Present() {
    return profileUser2.hasData();
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
    if (expoCoexistence) {
        return std::string("EXPO");
    } else {
        char* profileName = &(xmpStruct.header.profileName3[0]);
        return std::string(profileName);
    }
}

void XMP3_Bundle::setXMP3ProfileName(const std::string value) {
    if (!expoCoexistence) {
        utilities::SetCString(value, maxXmpProfileName, &(xmpStruct.header.profileName3[0]));
    }
}

void XMP3_Bundle::enableMagic() {
    xmpStruct.header.magic1 = XMPHeaderMagic[0];
    xmpStruct.header.magic2 = XMPHeaderMagic[1];
    xmpStruct.header.version = XMPHeaderVersion;
}

void XMP3_Bundle::clearMagic() {
    xmpStruct.header.magic1 = 0x00;
    xmpStruct.header.magic2 = 0x00;
    xmpStruct.header.version = 0x00;
}

bool XMP3_Bundle::isMagicPresent() {
    return ((xmpStruct.header.magic1 == XMPHeaderMagic[0]) &&
            (xmpStruct.header.magic2 == XMPHeaderMagic[1]) &&
            (xmpStruct.header.version == XMPHeaderVersion));
}

void XMP3_Bundle::resetXMPtoSample() {
    wipe();
    enableMagic();
    profile1.resetProfile();
    setXMP1ProfileName("Profile 1");
    setXMP1Enabled(true);
    fixCRCs();
}

const unsigned short XMP3_Bundle::getHeaderCRC() {
    return xmpStruct.header.checksum;
}

void XMP3_Bundle::setHeaderCRC(const unsigned short value) {
    xmpStruct.header.checksum = value;
}

void XMP3_Bundle::fixHeaderCRC() {
    unsigned int  crc = utilities::Crc16(reinterpret_cast<unsigned char*>(&xmpStruct.header), sizeof(XMP_HeaderStruct) - 2);
    setHeaderCRC(crc);
}

void XMP3_Bundle::fixCRCs() {
    fixHeaderCRC();

    if (isXMP1Enabled()) {
        profile1.fixCRC();
    }

    if (isXMP2Enabled()) {
        profile2.fixCRC();
    }

    if (~!expoCoexistence) {
        if (isXMP3Enabled()) {
            profile3.fixCRC();
        }

        if (isXMPUser1Present()) {
            profileUser1.fixCRC();
        }
    }

    if (isXMPUser2Present()) {
        profileUser2.fixCRC();
    }
}

void XMP3_Bundle::wipe() {
    if (expoCoexistence) {
        std::memset(&xmpStruct.header, 0x0, sizeof (XMP_HeaderStruct));
        std::memset(&xmpStruct.profile1, 0x0, sizeof (XMP_ProfileStruct));
        std::memset(&xmpStruct.profile2, 0x0, sizeof (XMP_ProfileStruct));
        std::memset(&xmpStruct.user_profile2, 0x0, sizeof (XMP_ProfileStruct));
    } else {
        std::memset(&xmpStruct, 0x0, sizeof (XMP_Struct));
    }
}
