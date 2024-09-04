#include "HCSDKWidget.h"
#include <QDateTime>
#include <QDebug>
#include <HCSDK/HCNetSDK.h>



HCSDKWidget::HCSDKWidget(QWidget *parent)
    :hcsdk_user_id(-1), QWidget(parent)
{
    ui = new Ui::HCSDKWidget();
    ui->setupUi(this);

    NET_DVR_Init();
    NET_DVR_SetLogToFile(3);

    connect(ui->btnConn, SIGNAL(clicked()), this, SLOT(deviceConn()));
    connect(ui->btnLoopTest, SIGNAL(clicked()), this, SLOT(loopTest()));

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
    // 设置连接设备默认值
    {
        ui->txtDeviveIP->setText(QString::fromUtf8("10.3.220.151"));
        ui->txtDeviceUser->setText(QString::fromUtf8("admin"));
        ui->txtDevicePwd->setText(QString::fromUtf8("Lty@1qaz"));
    }
}

HCSDKWidget::~HCSDKWidget()
{
    delete ui;
}

constexpr static size_t HCSDK_MAX_DEVICES = 512;
constexpr static size_t HCSDK_MAX_VM_WIN_NUM = 256;

void HCSDKWidget::deviceConn() {
    QString device_ip = ui->txtDeviveIP->text().trimmed();
    QString device_port = ui->txtDevicePort->text().trimmed();
    if (device_port.isEmpty()) {
        device_port = "8000";
    }
    QString device_user = ui->txtDeviceUser->text().trimmed();
    QString device_pwd = ui->txtDevicePwd->text().trimmed();

    Q_EMIT AppendLog(QString::fromUtf8("海康SDK连接设备:%1:%2---%3 %4").arg(device_ip).arg(device_port).arg(device_user).arg(device_pwd));
    std::string str_ip = device_ip.toStdString();
    int port = device_port.toInt();
    std::string str_user = device_user.toStdString();
    std::string str_pwd = device_pwd.toStdString();

    NET_DVR_USER_LOGIN_INFO login_info = { 0 };
    NET_DVR_DEVICEINFO_V40 device_info_v40 = { 0 };

    // IP
    ::strcpy(login_info.sDeviceAddress, str_ip.c_str());
    // port
    login_info.wPort = port;
    // usr
    ::strcpy(login_info.sUserName, str_user.c_str());
    // pwd
    ::strcpy(login_info.sPassword, str_pwd.c_str());

    LONG userid = NET_DVR_Login_V40(&login_info, &device_info_v40);
    if (userid < 0) {
        // 登录失败
        Q_EMIT AppendLog(QString::fromUtf8("NET_DVR_Login_V40 sync login fail with error %1").arg(NET_DVR_GetLastError()));
        return;
    }
    hcsdk_user_id = userid;
    Q_EMIT AppendLog(QString::fromUtf8("NET_DVR_Login_V40 sync login success,user id %1").arg(hcsdk_user_id));
}

void HCSDKWidget::loopTest() {
    if (hcsdk_user_id < 0) {
        Q_EMIT AppendLog(QString::fromUtf8("未登录，请登录后测试轮询"));
        return;
    }
    std::string rtsp1 = "rtsp://106.74.15.244:2554/SPg5ol5nMd2O/RSSPg5ol5nMd2O-g24s3q1gYx";
    std::string rtsp2 = "rtsp://106.74.27.132:2554/SPg5ol5nMd2O/RSSPg5ol5nMd2O-gFys3qbcWr";

    // 停止窗口的动态解码
    // 1墙 1窗 1 子窗口
    constexpr DWORD active_handle = 1 + (1 << 16) + (1 << 24);
    constexpr DWORD active_handle5 = 1 + (5 << 16) + (1 << 24);
    if (!NET_DVR_MatrixStopDynamic(hcsdk_user_id, active_handle)) {
        Q_EMIT AppendLog(QString::fromUtf8("NET_DVR_MatrixStopDynamic %1 error %2").arg(active_handle).arg(NET_DVR_GetLastError()));

        return;
    }
    if (!NET_DVR_MatrixStopDynamic(hcsdk_user_id, active_handle5)) {
        Q_EMIT AppendLog(QString::fromUtf8("NET_DVR_MatrixStopDynamic %1 error %2").arg(active_handle5).arg(NET_DVR_GetLastError()));

        return;
    }


    // 获取轮询通道开关状态
    DWORD loop_dec_enable = 0;
    if (!NET_DVR_MatrixGetLoopDecChanEnable(hcsdk_user_id, active_handle, &loop_dec_enable)) {
        Q_EMIT AppendLog(QString::fromUtf8("NET_DVR_MatrixGetLoopDecChanEnable %1 error %2").arg(active_handle).arg(NET_DVR_GetLastError()));

        return;
    }
    Q_EMIT AppendLog(QString::fromUtf8("轮询通道 %1 状态 %2").arg(active_handle).arg(loop_dec_enable));
    if (!loop_dec_enable) {
        Q_EMIT AppendLog(QString::fromUtf8("打开轮询通道 %1").arg(active_handle));
        loop_dec_enable = 1;
        if (!NET_DVR_MatrixSetLoopDecChanEnable(hcsdk_user_id, active_handle, loop_dec_enable)) {
            Q_EMIT AppendLog(QString::fromUtf8("NET_DVR_MatrixSetLoopDecChanEnable %1 error %2").arg(active_handle).arg(NET_DVR_GetLastError()));

            return;
        }
    }

    

    Q_EMIT AppendLog(QString::fromUtf8("设置轮询取流信息：%1 \n %2").arg(QString::fromStdString(rtsp1)).arg(QString::fromStdString(rtsp2)));
    NET_DVR_PU_STREAM_URL url1 = {0}, url2 = { 0 };
    strcpy((char*)url1.strURL, rtsp1.c_str());
    strcpy((char*)url2.strURL, rtsp2.c_str());
    url1.byEnable = 1;
    url2.byEnable = 1;


    NET_DVR_MATRIX_LOOP_DECINFO_V41 mat_loop_dec = {0};
    mat_loop_dec.dwSize = sizeof(NET_DVR_MATRIX_LOOP_DECINFO_V41);
    mat_loop_dec.dwPoolTime = 30;
    mat_loop_dec.struchanConInfo[0].byEnable = 1;
    mat_loop_dec.struchanConInfo[0].byStreamMode = 2;
    mat_loop_dec.struchanConInfo[0].uDecStreamMode.struUrlInfo = url1;

    mat_loop_dec.struchanConInfo[1].byEnable = 1;
    mat_loop_dec.struchanConInfo[1].byStreamMode = 2;
    mat_loop_dec.struchanConInfo[1].uDecStreamMode.struUrlInfo = url2;

    if (!NET_DVR_MatrixSetLoopDecChanInfo_V41(hcsdk_user_id, active_handle, &mat_loop_dec)) {
        Q_EMIT AppendLog(QString::fromUtf8("NET_DVR_MatrixSetLoopDecChanInfo_V41 %1 error %2").arg(active_handle).arg(NET_DVR_GetLastError()));

        return;
    }

    mat_loop_dec = { 0 };
    mat_loop_dec.dwSize = sizeof(NET_DVR_MATRIX_LOOP_DECINFO_V41);
    mat_loop_dec.dwPoolTime = 30;
    mat_loop_dec.struchanConInfo[0].byEnable = 1;
    mat_loop_dec.struchanConInfo[0].byStreamMode = 2;
    mat_loop_dec.struchanConInfo[0].uDecStreamMode.struUrlInfo = url1;

    mat_loop_dec.struchanConInfo[1].byEnable = 1;
    mat_loop_dec.struchanConInfo[1].byStreamMode = 2;
    mat_loop_dec.struchanConInfo[1].uDecStreamMode.struUrlInfo = url2;

    if (!NET_DVR_MatrixSetLoopDecChanInfo_V41(hcsdk_user_id, active_handle5, &mat_loop_dec)) {
        Q_EMIT AppendLog(QString::fromUtf8("NET_DVR_MatrixSetLoopDecChanInfo_V41 %1 error %2").arg(active_handle5).arg(NET_DVR_GetLastError()));

        return;
    }

    /*constexpr DWORD active_handle2 = 1 + (2 << 16) + (1 << 24);
    constexpr DWORD active_handle3 = 1 + (3 << 16) + (1 << 24);

    constexpr DWORD active_handle4 = 1 + (4 << 16) + (1 << 24);*/
    
    /*constexpr DWORD active_handle4 = 1 + (6 << 16) + (1 << 24);*/

}

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
