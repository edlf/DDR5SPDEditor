#ifndef XMP3_H
#define XMP3_H

#include <string>
#include "ddr5spd_structs.h"

using namespace ddr5_structs;

class XMP3_Profile {
public:
    XMP3_Profile(ddr5_structs::XMP_ProfileStruct&);
    XMP3_Profile();

    // Voltages
    const unsigned short getVPP();
    void setVPP(const unsigned short);

    const unsigned short getVDD();
    void setVDD(const unsigned short);

    const unsigned short getVDDQ();
    void setVDDQ(const unsigned short);

    // Unkown byte 03 (0x00)

    const unsigned short getVMEMCtrl();
    void setVMEMCtrl(const unsigned short);

    // Cycle + CAS
    const unsigned short getMinCycleTime();
    void setMinCycleTime(const unsigned short);
    const unsigned int getFrequency();
    const unsigned int getMT();

    void setCLSupported(int cl, bool supported);
    const bool getCLSupported(int cl);

    // Timings
    const unsigned short gettAA();
    void settAA(const unsigned short);

    const unsigned short gettRCD();
    void settRCD(const unsigned short);

    const unsigned short gettRP();
    void settRP(const unsigned short);

    const unsigned short gettRAS();
    void settRAS(const unsigned short);

    const unsigned short gettRC();
    void settRC(const unsigned short);

    const unsigned short gettWR();
    void settWR(const unsigned short);

    const unsigned short gettRFC1();
    void settRFC1(const unsigned short);

    const unsigned short gettRFC2();
    void settRFC2(const unsigned short);

    const unsigned short gettRFC();
    void settRFC(const unsigned short);

    const unsigned short gettRRD_L();
    void settRRD_L(const unsigned short);
    const unsigned short gettRRD_L_lowerLimit();
    void settRRD_L_lowerLimit(const unsigned short);

    const unsigned short gettCCD_L_WR();
    void settCCD_L_WR(unsigned short);
    const unsigned short gettCCD_L_WR_lowerLimit();
    void settCCD_L_WR_lowerLimit(unsigned short);

    const unsigned short gettCCD_L_WR2();
    void settCCD_L_WR2(const unsigned short);
    const unsigned short gettCCD_L_WR2_lowerLimit();
    void settCCD_L_WR2_lowerLimit(const unsigned short);

    const unsigned short gettCCD_L_WTR();
    void settCCD_L_WTR(unsigned short);
    const unsigned short gettCCD_L_WTR_lowerLimit();
    void settCCD_L_WTR_lowerLimit(unsigned short);

    const unsigned short gettCCD_S_WTR();
    void settCCD_S_WTR(unsigned short);
    const unsigned short gettCCD_S_WTR_lowerLimit();
    void settCCD_S_WTR_lowerLimit(unsigned short);

    const unsigned short gettCCD_L();
    void settCCD_L(const unsigned short);
    const unsigned short gettCCD_L_lowerLimit();
    void settCCD_L_lowerLimit(const unsigned short);

    const unsigned short gettRTP();
    void settRTP(const unsigned short);
    const unsigned short gettRTP_lowerLimit();
    void settRTP_lowerLimit(const unsigned short);

    const unsigned short gettFAW();
    void settFAW(const unsigned short);
    const unsigned short gettFAW_lowerLimit();
    void settFAW_lowerLimit(const unsigned short);

    // Unkown byte 07 (0x00)
    // Unkown byte 08 (0x00)
    // Unkown byte 09 (0x00)
    // Unkown byte 0A (0x00)

    const unsigned short getDimmsChannel();
    void setDimmsChannel(unsigned short);

    const bool getIntelDynamicMemoryBoost();
    void setIntelDynamicMemoryBoost(const bool);

    const bool getRealTimeMemoryFrequencyOC();
    void setRealTimeMemoryFrequencyOC(const bool);

    const CommandRate getCommandRate();
    void setCommandRate(const CommandRate);

    // Unknown byte 0D (0x00)

    const unsigned short getCRC();
    void setCRC(const unsigned short);

    void fixCRC();

    void wipeProfile();
    void resetProfile();

    const bool hasData();

    XMP_ProfileStruct getCopy();
    void import(const XMP_ProfileStruct);

private:
    XMP_ProfileStruct& xmpProfileStruct;
};

class XMP3_Bundle {
public:
    XMP3_Bundle(XMP_Struct&);
    XMP3_Bundle(XMP_Struct&, bool);

    const bool isXMP1Enabled();
    void setXMP1Enabled(const bool);

    const bool isXMP2Enabled();
    void setXMP2Enabled(const bool);

    const bool isXMP3Enabled();
    void setXMP3Enabled(const bool);

    const bool isXMPUser1Present();

    const bool isXMPUser2Present();

    const std::string getXMP1ProfileName();
    void setXMP1ProfileName(const std::string);

    const std::string getXMP2ProfileName();
    void setXMP2ProfileName(const std::string);

    const std::string getXMP3ProfileName();
    void setXMP3ProfileName(const std::string);

    void enableMagic();
    void clearMagic();
    bool isMagicPresent();
    void resetXMPtoSample();

    const unsigned short getHeaderCRC();
    void setHeaderCRC(const unsigned short);

    void fixHeaderCRC();

    void fixCRCs();

    void wipe();

    XMP3_Profile profile1;
    XMP3_Profile profile2;
    XMP3_Profile profile3;
    XMP3_Profile profileUser1;
    XMP3_Profile profileUser2;

private:
    XMP_Struct& xmpStruct;
    bool expoCoexistence;
};

#endif // XMP3_H
