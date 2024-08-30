#include "HCSDKWidget.h"
#include <QDateTime>
#include <HCSDK/HCNetSDK.h>
#include "SDKMap.hpp"


HCSDKWidget::HCSDKWidget(QWidget *parent)
    : QWidget(parent)
{
    ui = new Ui::HCSDKWidget();
    ui->setupUi(this);

    NET_DVR_Init();
    NET_DVR_SetLogToFile(3);

    connect(ui->sdkTest, SIGNAL(clicked()), this, SLOT(sdkTest()));

    connect(this, SIGNAL(AppendLog(const QString&)), this, SLOT(AppendLogToWindow(const QString&)));

    // 获取模拟能力集
    NET_DVR_SDKLOCAL_CFG sdk_locak_cfg = { 0 };
    if (NET_DVR_GetSDKLocalConfig(&sdk_locak_cfg) < 0) {
        Q_EMIT AppendLog(QString::fromUtf8("cuc_sdk:NET_DVR_GetSDKLocalConfig fail with error %1").arg(NET_DVR_GetLastError()));
        return;
    }

    NET_DVR_LOCAL_ABILITY_PARSE_CFG sdk_local_ability = { 0 };
    if (NET_DVR_GetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_ABILITY_PARSE, &sdk_local_ability) < 0) {
        Q_EMIT AppendLog(QString::fromUtf8("cuc_sdk:NET_DVR_GetSDKLocalCfg fail with error %1").arg(NET_DVR_GetLastError()));
        return;
    }
    // 启用能力集
}

HCSDKWidget::~HCSDKWidget()
{
    delete ui;
}

constexpr static size_t HCSDK_MAX_DEVICES = 512;
constexpr static size_t HCSDK_MAX_VM_WIN_NUM = 256;

void HCSDKWidget::sdkTest() {
    NET_DVR_USER_LOGIN_INFO login_info = { 0 };
    NET_DVR_DEVICEINFO_V40 device_info_v40 = { 0 };
    login_info.bUseAsynLogin = 0;//use sync login
    std::string device_ip = "10.3.220.151";
    int device_port = 8000;
    std::string device_usr = "admin";
    std::string device_pwd = "Lty@1qaz";
    // IP
    ::strcpy(login_info.sDeviceAddress, device_ip.c_str());
    // port
    login_info.wPort = device_port;
    // usr
    ::strcpy(login_info.sUserName, device_usr.c_str());
    // pwd
    ::strcpy(login_info.sPassword, device_pwd.c_str());

    LONG userid = NET_DVR_Login_V40(&login_info, &device_info_v40);
    if (userid < 0) {
        // 登录失败
        Q_EMIT AppendLog(QString::fromUtf8("cuc_sdk:NET_DVR_Login_V40 sync login fail with error %1").arg(NET_DVR_GetLastError()));
        return;
    }
    

    // 测试删除窗口
    
    DWORD modify_wnd_no = 16777218;
    NET_DVR_VIDEOWALLWINDOWPOSITION winPos = { 0 };
    winPos.dwSize = sizeof(NET_DVR_VIDEOWALLWINDOWPOSITION);
    winPos.byEnable = 0;
    winPos.dwWindowNo = modify_wnd_no;
    DWORD status =  0 ;
    DWORD ret_win_no =  0 ;

    NET_DVR_IN_PARAM struInputPapam = { 0 };
    NET_DVR_OUT_PARAM struOutputPapam = { 0 };
    struInputPapam.struCondBuf.pBuf = &modify_wnd_no;
    struInputPapam.struCondBuf.nLen = 1 * sizeof(DWORD);
    struInputPapam.struInParamBuf.pBuf = &winPos;
    struInputPapam.struInParamBuf.nLen = 1 * sizeof(NET_DVR_VIDEOWALLWINDOWPOSITION);
    struOutputPapam.lpStatusList = &status;
    struOutputPapam.struOutBuf.pBuf = &ret_win_no;
    struOutputPapam.struOutBuf.nLen = 1 * sizeof(DWORD);

    // 通过开窗函数关闭窗口
    if (!NET_DVR_SetDeviceConfigEx(userid, NET_DVR_SET_VIDEOWALLWINDOWPOSITION,
        1,
        &struInputPapam, &struOutputPapam)) {
        Q_EMIT AppendLog(QString::fromUtf8("cuc_sdk:NET_DVR_SetDeviceConfigEx fail with error %1").arg(NET_DVR_GetLastError()));
        return;
    }
    // delete success
    Q_EMIT AppendLog(QString::fromUtf8("delete window success"));

}

void HCSDKWidget::AppendLogToWindow(const QString& log) {
    QDateTime time = QDateTime::currentDateTime();

    ui->log_out->append(QString("%1:%2").arg(time.toString("yyyy.MM.dd-hh:mm:ss.zzz")).arg(log));
}
