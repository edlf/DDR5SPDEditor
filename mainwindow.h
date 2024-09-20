#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>

#include "ddr5spd.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

const QString appName = "DDR5 SPD Editor";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    void saveFile();
    bool saveFileEnabled();
    void closeFile();
    bool closeFileEnabled();
    void exit();

    void createXMPBlock();
    void wipeXMP();
    void wipeXMPProfile1();
    void wipeXMPProfile2();
    void wipeXMPProfile3();
    void wipeXMPProfileU1();
    void wipeXMPProfileU2();

    void loadSampleXMPProfile1();
    void loadSampleXMPProfile2();
    void loadSampleXMPProfile3();
    void loadSampleXMPProfileU1();
    void loadSampleXMPProfileU2();

    void exportXMPProfile(const XMP_ProfileStruct&);
    void exportXMPProfile1();
    void exportXMPProfile2();
    void exportXMPProfile3();
    void exportXMPProfileU1();
    void exportXMPProfileU2();

    XMP_ProfileStruct importXMPProfile();
    XMP_ProfileStruct importXMPProfileFromEXPO(const EXPO_ProfileStruct&);
    void importXMPProfile1();
    void importXMPProfile2();
    void importXMPProfile3();
    void importXMPProfileU1();
    void importXMPProfileU2();

    void enableXMPMagicBits();
    void disableXMPMagicBits();

    void createEXPOBlock();
    void wipeEXPO();
    void exportEXPOProfile(const EXPO_ProfileStruct&);
    EXPO_ProfileStruct importEXPOProfile();
    void exportEXPOProfile1();
    void exportEXPOProfile2();
    void importEXPOProfile1();
    void importEXPOProfile2();
    void importEXPOProfile1FromXMP1();
    void importEXPOProfile1FromXMP2();
    void importEXPOProfile1FromXMPU2();
    void importEXPOProfile2FromXMP1();
    void importEXPOProfile2FromXMP2();
    void importEXPOProfile2FromXMPU2();

    void reloadUI();
    void reloadJEDECTab();
    void reloadXMP1Tab();
    void reloadXMP2Tab();
    void reloadXMP3Tab();
    void reloadXMPU1Tab();
    void reloadXMPU2Tab();
    void reloadEXPO1Tab();
    void reloadEXPO2Tab();
    void reloadMiscTab();

    // Slots JEDEC
    void on_spinMinCycleTime_editingFinished();
    void on_spinMaxCycleTime_editingFinished();
    void on_cbCL20_toggled(bool);
    void on_cbCL22_toggled(bool);
    void on_cbCL24_toggled(bool);
    void on_cbCL26_toggled(bool);
    void on_cbCL28_toggled(bool);
    void on_cbCL30_toggled(bool);
    void on_cbCL32_toggled(bool);
    void on_cbCL34_toggled(bool);
    void on_cbCL36_toggled(bool);
    void on_cbCL38_toggled(bool);
    void on_cbCL40_toggled(bool);
    void on_cbCL42_toggled(bool);
    void on_cbCL44_toggled(bool);
    void on_cbCL46_toggled(bool);
    void on_cbCL48_toggled(bool);
    void on_cbCL50_toggled(bool);
    void on_cbCL52_toggled(bool);
    void on_cbCL54_toggled(bool);
    void on_cbCL56_toggled(bool);
    void on_cbCL58_toggled(bool);
    void on_cbCL60_toggled(bool);
    void on_cbCL62_toggled(bool);
    void on_cbCL64_toggled(bool);
    void on_cbCL66_toggled(bool);
    void on_cbCL68_toggled(bool);
    void on_cbCL70_toggled(bool);
    void on_cbCL72_toggled(bool);
    void on_cbCL74_toggled(bool);
    void on_cbCL76_toggled(bool);
    void on_cbCL78_toggled(bool);
    void on_cbCL80_toggled(bool);
    void on_cbCL82_toggled(bool);
    void on_cbCL84_toggled(bool);
    void on_cbCL86_toggled(bool);
    void on_cbCL88_toggled(bool);
    void on_cbCL90_toggled(bool);
    void on_cbCL92_toggled(bool);
    void on_cbCL94_toggled(bool);
    void on_cbCL96_toggled(bool);
    void on_cbCL98_toggled(bool);

    void on_spinBoxtAA_editingFinished();
    void on_spinBoxtRCD_editingFinished();
    void on_spinBoxtRP_editingFinished();
    void on_spinBoxtRAS_editingFinished();
    void on_spinBoxtRC_editingFinished();
    void on_spinBoxtWR_editingFinished();
    void on_spinBoxtRFC1_editingFinished();
    void on_spinBoxtRFC2_editingFinished();
    void on_spinBoxtRFC_editingFinished();
    void on_spinBoxtRRD_L_editingFinished();
    void on_spinBoxtRRD_L_LCLK_editingFinished();
    void on_spinBoxtCCD_L_editingFinished();
    void on_spinBoxtCCD_L_LCLK_editingFinished();
    void on_spinBoxtCCDL_L_WR_editingFinished();
    void on_spinBoxtCCDL_L_WR_LCLK_editingFinished();
    void on_spinBoxtCCDL_L_WR2_editingFinished();
    void on_spinBoxtCCDL_L_WR2_LCLK_editingFinished();
    void on_spinBoxtFAW_editingFinished();
    void on_spinBoxtFAW_LCLK_editingFinished();
    void on_spinBoxtCCD_L_WTR_editingFinished();
    void on_spinBoxtCCD_L_WTR_LCLK_editingFinished();
    void on_spinBoxtCCD_S_WTR_editingFinished();
    void on_spinBoxtCCD_S_WTR_LCLK_editingFinished();
    void on_spinBoxtRTP_editingFinished();
    void on_spinBoxtRTP_LCLK_editingFinished();

    // Slots XMP1
    void on_leProfileName_XMP1_editingFinished();
    void on_cbEnabled_XMP1_toggled(bool);
    void on_cbDynamicMemBoost_XMP1_toggled(bool);
    void on_cbRealTimeMemOC_XMP1_toggled(bool);
    void on_sbVDD_XMP1_editingFinished();
    void on_sbVDDQ_XMP1_editingFinished();
    void on_sbVPP_XMP1_editingFinished();
    void on_sbVmemctrl_XMP1_editingFinished();
    void on_spinMinCycleTime_XMP1_editingFinished();
    void on_cbCommandRate_XMP1_currentIndexChanged(int);

    void on_cbCL20_XMP1_toggled(bool);
    void on_cbCL22_XMP1_toggled(bool);
    void on_cbCL24_XMP1_toggled(bool);
    void on_cbCL26_XMP1_toggled(bool);
    void on_cbCL28_XMP1_toggled(bool);
    void on_cbCL30_XMP1_toggled(bool);
    void on_cbCL32_XMP1_toggled(bool);
    void on_cbCL34_XMP1_toggled(bool);
    void on_cbCL36_XMP1_toggled(bool);
    void on_cbCL38_XMP1_toggled(bool);
    void on_cbCL40_XMP1_toggled(bool);
    void on_cbCL42_XMP1_toggled(bool);
    void on_cbCL44_XMP1_toggled(bool);
    void on_cbCL46_XMP1_toggled(bool);
    void on_cbCL48_XMP1_toggled(bool);
    void on_cbCL50_XMP1_toggled(bool);
    void on_cbCL52_XMP1_toggled(bool);
    void on_cbCL54_XMP1_toggled(bool);
    void on_cbCL56_XMP1_toggled(bool);
    void on_cbCL58_XMP1_toggled(bool);
    void on_cbCL60_XMP1_toggled(bool);
    void on_cbCL62_XMP1_toggled(bool);
    void on_cbCL64_XMP1_toggled(bool);
    void on_cbCL66_XMP1_toggled(bool);
    void on_cbCL68_XMP1_toggled(bool);
    void on_cbCL70_XMP1_toggled(bool);
    void on_cbCL72_XMP1_toggled(bool);
    void on_cbCL74_XMP1_toggled(bool);
    void on_cbCL76_XMP1_toggled(bool);
    void on_cbCL78_XMP1_toggled(bool);
    void on_cbCL80_XMP1_toggled(bool);
    void on_cbCL82_XMP1_toggled(bool);
    void on_cbCL84_XMP1_toggled(bool);
    void on_cbCL86_XMP1_toggled(bool);
    void on_cbCL88_XMP1_toggled(bool);
    void on_cbCL90_XMP1_toggled(bool);
    void on_cbCL92_XMP1_toggled(bool);
    void on_cbCL94_XMP1_toggled(bool);
    void on_cbCL96_XMP1_toggled(bool);
    void on_cbCL98_XMP1_toggled(bool);

    void on_sbtAA_XMP1_editingFinished();
    void on_sbtRCD_XMP1_editingFinished();
    void on_sbtRP_XMP1_editingFinished();
    void on_sbtRAS_XMP1_editingFinished();
    void on_sbtRC_XMP1_editingFinished();
    void on_sbtWR_XMP1_editingFinished();
    void on_sbtRFC1_XMP1_editingFinished();
    void on_sbtRFC2_XMP1_editingFinished();
    void on_sbtRFC_XMP1_editingFinished();
    void on_sbtRRD_L_XMP1_editingFinished();
    void on_sbtRRD_L_LCLK_XMP1_editingFinished();
    void on_sbtCCD_L_XMP1_editingFinished();
    void on_sbtCCD_L_LCLK_XMP1_editingFinished();
    void on_sbtCCDL_L_WR_XMP1_editingFinished();
    void on_sbtCCDL_L_WR_LCLK_XMP1_editingFinished();
    void on_sbtCCDL_L_WR2_XMP1_editingFinished();
    void on_sbtCCDL_L_WR2_LCLK_XMP1_editingFinished();
    void on_sbtFAW_XMP1_editingFinished();
    void on_sbtFAW_LCLK_XMP1_editingFinished();
    void on_sbtCCD_L_WTR_XMP1_editingFinished();
    void on_sbtCCD_L_WTR_LCLK_XMP1_editingFinished();
    void on_sbtCCD_S_WTR_XMP1_editingFinished();
    void on_sbtCCD_S_WTR_LCLK_XMP1_editingFinished();
    void on_sbtRTP_XMP1_editingFinished();
    void on_sbtRTP_LCLK_XMP1_editingFinished();

    // Slots XMP2
    void on_leProfileName_XMP2_editingFinished();
    void on_cbEnabled_XMP2_toggled(bool);
    void on_cbDynamicMemBoost_XMP2_toggled(bool);
    void on_cbRealTimeMemOC_XMP2_toggled(bool);
    void on_sbVDD_XMP2_editingFinished();
    void on_sbVDDQ_XMP2_editingFinished();
    void on_sbVPP_XMP2_editingFinished();
    void on_sbVmemctrl_XMP2_editingFinished();
    void on_spinMinCycleTime_XMP2_editingFinished();
    void on_cbCommandRate_XMP2_currentIndexChanged(int);

    void on_cbCL20_XMP2_toggled(bool);
    void on_cbCL22_XMP2_toggled(bool);
    void on_cbCL24_XMP2_toggled(bool);
    void on_cbCL26_XMP2_toggled(bool);
    void on_cbCL28_XMP2_toggled(bool);
    void on_cbCL30_XMP2_toggled(bool);
    void on_cbCL32_XMP2_toggled(bool);
    void on_cbCL34_XMP2_toggled(bool);
    void on_cbCL36_XMP2_toggled(bool);
    void on_cbCL38_XMP2_toggled(bool);
    void on_cbCL40_XMP2_toggled(bool);
    void on_cbCL42_XMP2_toggled(bool);
    void on_cbCL44_XMP2_toggled(bool);
    void on_cbCL46_XMP2_toggled(bool);
    void on_cbCL48_XMP2_toggled(bool);
    void on_cbCL50_XMP2_toggled(bool);
    void on_cbCL52_XMP2_toggled(bool);
    void on_cbCL54_XMP2_toggled(bool);
    void on_cbCL56_XMP2_toggled(bool);
    void on_cbCL58_XMP2_toggled(bool);
    void on_cbCL60_XMP2_toggled(bool);
    void on_cbCL62_XMP2_toggled(bool);
    void on_cbCL64_XMP2_toggled(bool);
    void on_cbCL66_XMP2_toggled(bool);
    void on_cbCL68_XMP2_toggled(bool);
    void on_cbCL70_XMP2_toggled(bool);
    void on_cbCL72_XMP2_toggled(bool);
    void on_cbCL74_XMP2_toggled(bool);
    void on_cbCL76_XMP2_toggled(bool);
    void on_cbCL78_XMP2_toggled(bool);
    void on_cbCL80_XMP2_toggled(bool);
    void on_cbCL82_XMP2_toggled(bool);
    void on_cbCL84_XMP2_toggled(bool);
    void on_cbCL86_XMP2_toggled(bool);
    void on_cbCL88_XMP2_toggled(bool);
    void on_cbCL90_XMP2_toggled(bool);
    void on_cbCL92_XMP2_toggled(bool);
    void on_cbCL94_XMP2_toggled(bool);
    void on_cbCL96_XMP2_toggled(bool);
    void on_cbCL98_XMP2_toggled(bool);

    void on_sbtAA_XMP2_editingFinished();
    void on_sbtRCD_XMP2_editingFinished();
    void on_sbtRP_XMP2_editingFinished();
    void on_sbtRAS_XMP2_editingFinished();
    void on_sbtRC_XMP2_editingFinished();
    void on_sbtWR_XMP2_editingFinished();
    void on_sbtRFC1_XMP2_editingFinished();
    void on_sbtRFC2_XMP2_editingFinished();
    void on_sbtRFC_XMP2_editingFinished();
    void on_sbtRRD_L_XMP2_editingFinished();
    void on_sbtRRD_L_LCLK_XMP2_editingFinished();
    void on_sbtCCD_L_XMP2_editingFinished();
    void on_sbtCCD_L_LCLK_XMP2_editingFinished();
    void on_sbtCCDL_L_WR_XMP2_editingFinished();
    void on_sbtCCDL_L_WR_LCLK_XMP2_editingFinished();
    void on_sbtCCDL_L_WR2_XMP2_editingFinished();
    void on_sbtCCDL_L_WR2_LCLK_XMP2_editingFinished();
    void on_sbtFAW_XMP2_editingFinished();
    void on_sbtFAW_LCLK_XMP2_editingFinished();
    void on_sbtCCD_L_WTR_XMP2_editingFinished();
    void on_sbtCCD_L_WTR_LCLK_XMP2_editingFinished();
    void on_sbtCCD_S_WTR_XMP2_editingFinished();
    void on_sbtCCD_S_WTR_LCLK_XMP2_editingFinished();
    void on_sbtRTP_XMP2_editingFinished();
    void on_sbtRTP_LCLK_XMP2_editingFinished();

    // Slots XMP3
    void on_leProfileName_XMP3_editingFinished();
    void on_cbEnabled_XMP3_toggled(bool);
    void on_cbDynamicMemBoost_XMP3_toggled(bool);
    void on_cbRealTimeMemOC_XMP3_toggled(bool);
    void on_sbVDD_XMP3_editingFinished();
    void on_sbVDDQ_XMP3_editingFinished();
    void on_sbVPP_XMP3_editingFinished();
    void on_sbVmemctrl_XMP3_editingFinished();
    void on_spinMinCycleTime_XMP3_editingFinished();
    void on_cbCommandRate_XMP3_currentIndexChanged(int);

    void on_cbCL20_XMP3_toggled(bool);
    void on_cbCL22_XMP3_toggled(bool);
    void on_cbCL24_XMP3_toggled(bool);
    void on_cbCL26_XMP3_toggled(bool);
    void on_cbCL28_XMP3_toggled(bool);
    void on_cbCL30_XMP3_toggled(bool);
    void on_cbCL32_XMP3_toggled(bool);
    void on_cbCL34_XMP3_toggled(bool);
    void on_cbCL36_XMP3_toggled(bool);
    void on_cbCL38_XMP3_toggled(bool);
    void on_cbCL40_XMP3_toggled(bool);
    void on_cbCL42_XMP3_toggled(bool);
    void on_cbCL44_XMP3_toggled(bool);
    void on_cbCL46_XMP3_toggled(bool);
    void on_cbCL48_XMP3_toggled(bool);
    void on_cbCL50_XMP3_toggled(bool);
    void on_cbCL52_XMP3_toggled(bool);
    void on_cbCL54_XMP3_toggled(bool);
    void on_cbCL56_XMP3_toggled(bool);
    void on_cbCL58_XMP3_toggled(bool);
    void on_cbCL60_XMP3_toggled(bool);
    void on_cbCL62_XMP3_toggled(bool);
    void on_cbCL64_XMP3_toggled(bool);
    void on_cbCL66_XMP3_toggled(bool);
    void on_cbCL68_XMP3_toggled(bool);
    void on_cbCL70_XMP3_toggled(bool);
    void on_cbCL72_XMP3_toggled(bool);
    void on_cbCL74_XMP3_toggled(bool);
    void on_cbCL76_XMP3_toggled(bool);
    void on_cbCL78_XMP3_toggled(bool);
    void on_cbCL80_XMP3_toggled(bool);
    void on_cbCL82_XMP3_toggled(bool);
    void on_cbCL84_XMP3_toggled(bool);
    void on_cbCL86_XMP3_toggled(bool);
    void on_cbCL88_XMP3_toggled(bool);
    void on_cbCL90_XMP3_toggled(bool);
    void on_cbCL92_XMP3_toggled(bool);
    void on_cbCL94_XMP3_toggled(bool);
    void on_cbCL96_XMP3_toggled(bool);
    void on_cbCL98_XMP3_toggled(bool);

    void on_sbtAA_XMP3_editingFinished();
    void on_sbtRCD_XMP3_editingFinished();
    void on_sbtRP_XMP3_editingFinished();
    void on_sbtRAS_XMP3_editingFinished();
    void on_sbtRC_XMP3_editingFinished();
    void on_sbtWR_XMP3_editingFinished();
    void on_sbtRFC1_XMP3_editingFinished();
    void on_sbtRFC2_XMP3_editingFinished();
    void on_sbtRFC_XMP3_editingFinished();
    void on_sbtRRD_L_XMP3_editingFinished();
    void on_sbtRRD_L_LCLK_XMP3_editingFinished();
    void on_sbtCCD_L_XMP3_editingFinished();
    void on_sbtCCD_L_LCLK_XMP3_editingFinished();
    void on_sbtCCDL_L_WR_XMP3_editingFinished();
    void on_sbtCCDL_L_WR_LCLK_XMP3_editingFinished();
    void on_sbtCCDL_L_WR2_XMP3_editingFinished();
    void on_sbtCCDL_L_WR2_LCLK_XMP3_editingFinished();
    void on_sbtFAW_XMP3_editingFinished();
    void on_sbtFAW_LCLK_XMP3_editingFinished();
    void on_sbtCCD_L_WTR_XMP3_editingFinished();
    void on_sbtCCD_L_WTR_LCLK_XMP3_editingFinished();
    void on_sbtCCD_S_WTR_XMP3_editingFinished();
    void on_sbtCCD_S_WTR_LCLK_XMP3_editingFinished();
    void on_sbtRTP_XMP3_editingFinished();
    void on_sbtRTP_LCLK_XMP3_editingFinished();

    // Slots XMP User 1
    void on_cbDynamicMemBoost_XMPU1_toggled(bool);
    void on_cbRealTimeMemOC_XMPU1_toggled(bool);
    void on_sbVDD_XMPU1_editingFinished();
    void on_sbVDDQ_XMPU1_editingFinished();
    void on_sbVPP_XMPU1_editingFinished();
    void on_sbVmemctrl_XMPU1_editingFinished();
    void on_spinMinCycleTime_XMPU1_editingFinished();
    void on_cbCommandRate_XMPU1_currentIndexChanged(int);

    void on_cbCL20_XMPU1_toggled(bool);
    void on_cbCL22_XMPU1_toggled(bool);
    void on_cbCL24_XMPU1_toggled(bool);
    void on_cbCL26_XMPU1_toggled(bool);
    void on_cbCL28_XMPU1_toggled(bool);
    void on_cbCL30_XMPU1_toggled(bool);
    void on_cbCL32_XMPU1_toggled(bool);
    void on_cbCL34_XMPU1_toggled(bool);
    void on_cbCL36_XMPU1_toggled(bool);
    void on_cbCL38_XMPU1_toggled(bool);
    void on_cbCL40_XMPU1_toggled(bool);
    void on_cbCL42_XMPU1_toggled(bool);
    void on_cbCL44_XMPU1_toggled(bool);
    void on_cbCL46_XMPU1_toggled(bool);
    void on_cbCL48_XMPU1_toggled(bool);
    void on_cbCL50_XMPU1_toggled(bool);
    void on_cbCL52_XMPU1_toggled(bool);
    void on_cbCL54_XMPU1_toggled(bool);
    void on_cbCL56_XMPU1_toggled(bool);
    void on_cbCL58_XMPU1_toggled(bool);
    void on_cbCL60_XMPU1_toggled(bool);
    void on_cbCL62_XMPU1_toggled(bool);
    void on_cbCL64_XMPU1_toggled(bool);
    void on_cbCL66_XMPU1_toggled(bool);
    void on_cbCL68_XMPU1_toggled(bool);
    void on_cbCL70_XMPU1_toggled(bool);
    void on_cbCL72_XMPU1_toggled(bool);
    void on_cbCL74_XMPU1_toggled(bool);
    void on_cbCL76_XMPU1_toggled(bool);
    void on_cbCL78_XMPU1_toggled(bool);
    void on_cbCL80_XMPU1_toggled(bool);
    void on_cbCL82_XMPU1_toggled(bool);
    void on_cbCL84_XMPU1_toggled(bool);
    void on_cbCL86_XMPU1_toggled(bool);
    void on_cbCL88_XMPU1_toggled(bool);
    void on_cbCL90_XMPU1_toggled(bool);
    void on_cbCL92_XMPU1_toggled(bool);
    void on_cbCL94_XMPU1_toggled(bool);
    void on_cbCL96_XMPU1_toggled(bool);
    void on_cbCL98_XMPU1_toggled(bool);

    void on_sbtAA_XMPU1_editingFinished();
    void on_sbtRCD_XMPU1_editingFinished();
    void on_sbtRP_XMPU1_editingFinished();
    void on_sbtRAS_XMPU1_editingFinished();
    void on_sbtRC_XMPU1_editingFinished();
    void on_sbtWR_XMPU1_editingFinished();
    void on_sbtRFC1_XMPU1_editingFinished();
    void on_sbtRFC2_XMPU1_editingFinished();
    void on_sbtRFC_XMPU1_editingFinished();
    void on_sbtRRD_L_XMPU1_editingFinished();
    void on_sbtRRD_L_LCLK_XMPU1_editingFinished();
    void on_sbtCCD_L_XMPU1_editingFinished();
    void on_sbtCCD_L_LCLK_XMPU1_editingFinished();
    void on_sbtCCDL_L_WR_XMPU1_editingFinished();
    void on_sbtCCDL_L_WR_LCLK_XMPU1_editingFinished();
    void on_sbtCCDL_L_WR2_XMPU1_editingFinished();
    void on_sbtCCDL_L_WR2_LCLK_XMPU1_editingFinished();
    void on_sbtFAW_XMPU1_editingFinished();
    void on_sbtFAW_LCLK_XMPU1_editingFinished();
    void on_sbtCCD_L_WTR_XMPU1_editingFinished();
    void on_sbtCCD_L_WTR_LCLK_XMPU1_editingFinished();
    void on_sbtCCD_S_WTR_XMPU1_editingFinished();
    void on_sbtCCD_S_WTR_LCLK_XMPU1_editingFinished();
    void on_sbtRTP_XMPU1_editingFinished();
    void on_sbtRTP_LCLK_XMPU1_editingFinished();

    // Slots XMP User 2
    void on_cbDynamicMemBoost_XMPU2_toggled(bool);
    void on_cbRealTimeMemOC_XMPU2_toggled(bool);
    void on_sbVDD_XMPU2_editingFinished();
    void on_sbVDDQ_XMPU2_editingFinished();
    void on_sbVPP_XMPU2_editingFinished();
    void on_sbVmemctrl_XMPU2_editingFinished();
    void on_spinMinCycleTime_XMPU2_editingFinished();
    void on_cbCommandRate_XMPU2_currentIndexChanged(int);

    void on_cbCL20_XMPU2_toggled(bool);
    void on_cbCL22_XMPU2_toggled(bool);
    void on_cbCL24_XMPU2_toggled(bool);
    void on_cbCL26_XMPU2_toggled(bool);
    void on_cbCL28_XMPU2_toggled(bool);
    void on_cbCL30_XMPU2_toggled(bool);
    void on_cbCL32_XMPU2_toggled(bool);
    void on_cbCL34_XMPU2_toggled(bool);
    void on_cbCL36_XMPU2_toggled(bool);
    void on_cbCL38_XMPU2_toggled(bool);
    void on_cbCL40_XMPU2_toggled(bool);
    void on_cbCL42_XMPU2_toggled(bool);
    void on_cbCL44_XMPU2_toggled(bool);
    void on_cbCL46_XMPU2_toggled(bool);
    void on_cbCL48_XMPU2_toggled(bool);
    void on_cbCL50_XMPU2_toggled(bool);
    void on_cbCL52_XMPU2_toggled(bool);
    void on_cbCL54_XMPU2_toggled(bool);
    void on_cbCL56_XMPU2_toggled(bool);
    void on_cbCL58_XMPU2_toggled(bool);
    void on_cbCL60_XMPU2_toggled(bool);
    void on_cbCL62_XMPU2_toggled(bool);
    void on_cbCL64_XMPU2_toggled(bool);
    void on_cbCL66_XMPU2_toggled(bool);
    void on_cbCL68_XMPU2_toggled(bool);
    void on_cbCL70_XMPU2_toggled(bool);
    void on_cbCL72_XMPU2_toggled(bool);
    void on_cbCL74_XMPU2_toggled(bool);
    void on_cbCL76_XMPU2_toggled(bool);
    void on_cbCL78_XMPU2_toggled(bool);
    void on_cbCL80_XMPU2_toggled(bool);
    void on_cbCL82_XMPU2_toggled(bool);
    void on_cbCL84_XMPU2_toggled(bool);
    void on_cbCL86_XMPU2_toggled(bool);
    void on_cbCL88_XMPU2_toggled(bool);
    void on_cbCL90_XMPU2_toggled(bool);
    void on_cbCL92_XMPU2_toggled(bool);
    void on_cbCL94_XMPU2_toggled(bool);
    void on_cbCL96_XMPU2_toggled(bool);
    void on_cbCL98_XMPU2_toggled(bool);

    void on_sbtAA_XMPU2_editingFinished();
    void on_sbtRCD_XMPU2_editingFinished();
    void on_sbtRP_XMPU2_editingFinished();
    void on_sbtRAS_XMPU2_editingFinished();
    void on_sbtRC_XMPU2_editingFinished();
    void on_sbtWR_XMPU2_editingFinished();
    void on_sbtRFC1_XMPU2_editingFinished();
    void on_sbtRFC2_XMPU2_editingFinished();
    void on_sbtRFC_XMPU2_editingFinished();
    void on_sbtRRD_L_XMPU2_editingFinished();
    void on_sbtRRD_L_LCLK_XMPU2_editingFinished();
    void on_sbtCCD_L_XMPU2_editingFinished();
    void on_sbtCCD_L_LCLK_XMPU2_editingFinished();
    void on_sbtCCDL_L_WR_XMPU2_editingFinished();
    void on_sbtCCDL_L_WR_LCLK_XMPU2_editingFinished();
    void on_sbtCCDL_L_WR2_XMPU2_editingFinished();
    void on_sbtCCDL_L_WR2_LCLK_XMPU2_editingFinished();
    void on_sbtFAW_XMPU2_editingFinished();
    void on_sbtFAW_LCLK_XMPU2_editingFinished();
    void on_sbtCCD_L_WTR_XMPU2_editingFinished();
    void on_sbtCCD_L_WTR_LCLK_XMPU2_editingFinished();
    void on_sbtCCD_S_WTR_XMPU2_editingFinished();
    void on_sbtCCD_S_WTR_LCLK_XMPU2_editingFinished();
    void on_sbtRTP_XMPU2_editingFinished();
    void on_sbtRTP_LCLK_XMPU2_editingFinished();

    // Slots EXPO1
    void on_cbEnabled_EXPO1_toggled(bool);
    void on_sbVDD_EXPO1_editingFinished();
    void on_sbVDDQ_EXPO1_editingFinished();
    void on_sbVPP_EXPO1_editingFinished();
    void on_spinMinCycleTime_EXPO1_editingFinished();

    void on_sbtAA_EXPO1_editingFinished();
    void on_sbtRCD_EXPO1_editingFinished();
    void on_sbtRP_EXPO1_editingFinished();
    void on_sbtRAS_EXPO1_editingFinished();
    void on_sbtRC_EXPO1_editingFinished();
    void on_sbtWR_EXPO1_editingFinished();
    void on_sbtRFC1_EXPO1_editingFinished();
    void on_sbtRFC2_EXPO1_editingFinished();
    void on_sbtRFC_EXPO1_editingFinished();
    void on_sbtRRD_L_EXPO1_editingFinished();
    void on_sbtCCD_L_EXPO1_editingFinished();
    void on_sbtCCDL_L_WR_EXPO1_editingFinished();
    void on_sbtCCDL_L_WR2_EXPO1_editingFinished();
    void on_sbtFAW_EXPO1_editingFinished();
    void on_sbtCCD_L_WTR_EXPO1_editingFinished();
    void on_sbtCCD_S_WTR_EXPO1_editingFinished();
    void on_sbtRTP_EXPO1_editingFinished();

    // Slots EXPO2
    void on_cbEnabled_EXPO2_toggled(bool);
    void on_sbVDD_EXPO2_editingFinished();
    void on_sbVDDQ_EXPO2_editingFinished();
    void on_sbVPP_EXPO2_editingFinished();
    void on_spinMinCycleTime_EXPO2_editingFinished();

    void on_sbtAA_EXPO2_editingFinished();
    void on_sbtRCD_EXPO2_editingFinished();
    void on_sbtRP_EXPO2_editingFinished();
    void on_sbtRAS_EXPO2_editingFinished();
    void on_sbtRC_EXPO2_editingFinished();
    void on_sbtWR_EXPO2_editingFinished();
    void on_sbtRFC1_EXPO2_editingFinished();
    void on_sbtRFC2_EXPO2_editingFinished();
    void on_sbtRFC_EXPO2_editingFinished();
    void on_sbtRRD_L_EXPO2_editingFinished();
    void on_sbtCCD_L_EXPO2_editingFinished();
    void on_sbtCCDL_L_WR_EXPO2_editingFinished();
    void on_sbtCCDL_L_WR2_EXPO2_editingFinished();
    void on_sbtFAW_EXPO2_editingFinished();
    void on_sbtCCD_L_WTR_EXPO2_editingFinished();
    void on_sbtCCD_S_WTR_EXPO2_editingFinished();
    void on_sbtRTP_EXPO2_editingFinished();

    // Misc tab
    void update_cbFormFactor();
    void update_cbDensity();
    void update_cbBankGroup();
    void update_cbBanksPerBankGroup();
    void update_cbColumnAddresses();
    void update_cbRowAddresses();
    void update_cdDeviceWidth();
    void on_cbFormFactor_currentIndexChanged(int);
    void on_cdDensity_currentIndexChanged(int);
    void on_cbBankGroup_currentIndexChanged(int);
    void on_cbBanksPerBankGroup_currentIndexChanged(int);
    void on_cbColumnAddresses_currentIndexChanged(int);
    void on_cbRowAddresses_currentIndexChanged(int);
    void on_cdDeviceWidth_currentIndexChanged(int);
    void on_sbManufacturingYear_editingFinished();
    void on_sbManufacturingWeek_editingFinished();
    void on_lePartNumber_editingFinished();
    void setDensity(const unsigned int val);

private:
    void clearUI();
    void disableUI();
    void enableUI();
    void toggleUI(const bool);
    void toggleXMPUI(const bool, const bool);
    void toggleEXPOUI(const bool);
    void reloadSPD();
    void reloadXMP_EXPO();

    unsigned short minCycle;

    DDR5SPD* spd = nullptr;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
