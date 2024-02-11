#ifndef XMP3_H
#define XMP3_H

#include <string>


enum class CommandRate
{
    Undefined,
    _1n,
    _2n,
    _3n
};

constexpr size_t XMPProfileSize = 0x40;
constexpr size_t maxXmpProfileName = 15;
constexpr unsigned int IntelDynamicMemoryBoostBit = 0;
constexpr unsigned int RealTimeMemoryFrequencyOCBit = 1 ;
constexpr char XMPHeaderMagic[] = { 0x0C, 0x4A };
constexpr unsigned int xmpProfile1EnableBit = 0;
constexpr unsigned int xmpProfile2EnableBit = 1;
constexpr unsigned int xmpProfile3EnableBit = 2;

#pragma pack(push,1)
struct XMP_HeaderStruct {
    unsigned char magic1;
    unsigned char magic2;
    unsigned char version;
    unsigned char profileEnBits;

    unsigned char unknown_04; // 0x00
    unsigned char pmicManufacturerId[2];

    unsigned char unknown_07; // 0x01
    unsigned char unknown_08; // 0x03
    unsigned char unknown_09; // 0x12
    unsigned char unknown_0A; // 0x00
    unsigned char unknown_0B; // 0x00
    unsigned char unknown_0C; // 0x00
    unsigned char unknown_0D; // 0x00

    char profileName1[maxXmpProfileName];
    unsigned char spacer1;
    char profileName2[maxXmpProfileName];
    unsigned char spacer2;
    char profileName3[maxXmpProfileName];
    unsigned char spacer3;
    unsigned char checksum[2];
};

struct XMP_ProfileStruct {
    unsigned char vpp;
    unsigned char vdd;
    unsigned char vddq;
    unsigned char unknown_03;
    unsigned char vmemctrl;
    unsigned char minCycleTime[2];
    unsigned char clSupported[5];
    unsigned char unkown_0A;
    unsigned char tAA[2];
    unsigned char tRCD[2];
    unsigned char tRP[2];
    unsigned char tRAS[2];
    unsigned char tRC[2];
    unsigned char tWR[2];
    unsigned char tRFC1[2];
    unsigned char tRFC2[2];
    unsigned char tRFC[2];
    unsigned char tRRD_L[2];
    unsigned char tRRD_L_lowerLimit;
    unsigned char tCCD_L_WR[2];
    unsigned char tCCD_L_WR_lowerLimit;
    unsigned char tCCD_L_WR2[2];
    unsigned char tCCD_L_WR2_lowerLimit;
    unsigned char tCCD_L_WTR[2];
    unsigned char tCCD_L_WTR_lowerLimit;
    unsigned char tCCD_S_WTR[2];
    unsigned char tCCD_S_WTR_lowerLimit;
    unsigned char tCCD_L[2];
    unsigned char tCCD_L_lowerLimit;
    unsigned char tRTP[2];
    unsigned char tRTP_lowerLimit;
    unsigned char tFAW[2];
    unsigned char tFAW_lowerLimit;
    unsigned char unknown_07;
    unsigned char unknown_08;
    unsigned char unknown_09;
    unsigned char unknown_0A;
    unsigned char memory_boost_realtime_training;
    unsigned char commandRate;
    unsigned char unknown_0D;

    // Byte 0x3E-0x4F
    unsigned char checksum[2];
};

struct XMP_Struct {
    XMP_HeaderStruct header;
    XMP_ProfileStruct profile1;
    XMP_ProfileStruct profile2;
    XMP_ProfileStruct profile3;
    XMP_ProfileStruct user_profile1;
    XMP_ProfileStruct user_profile2;
};
#pragma pack(pop)

static_assert(sizeof(XMP_Struct) == (sizeof(XMP_HeaderStruct) + 5*sizeof(XMP_ProfileStruct)), "XMP Block size is incorrect");
static_assert(sizeof(XMP_HeaderStruct) == 0x40, "XMP Header has to be 64 bytes in size");
static_assert(sizeof(XMP_ProfileStruct) == 0x40, "XMP Profile has to be 64 bytes in size");

class XMP3_Profile {
public:
    XMP3_Profile(XMP_ProfileStruct&);

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

private:
    XMP_ProfileStruct& xmpProfileStruct;
};

class XMP3_Bundle {
public:
    XMP3_Bundle(XMP_Struct&);

    const bool isXMP1Enabled();
    void setXMP1Enabled(const bool);

    const bool isXMP2Enabled();
    void setXMP2Enabled(const bool);

    const bool isXMP3Enabled();
    void setXMP3Enabled(const bool);

    const std::string getXMP1ProfileName();
    void setXMP1ProfileName(const std::string);

    const std::string getXMP2ProfileName();
    void setXMP2ProfileName(const std::string);

    const std::string getXMP3ProfileName();
    void setXMP3ProfileName(const std::string);

    void enableMagic();
    void clearMagic();
    bool isMagicPresent();

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
    XMP_Struct& rawXmp;
};

#endif // XMP3_H
