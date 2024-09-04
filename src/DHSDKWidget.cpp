#include "DHSDKWidget.h"
#include <QDateTime>
#include <thread>
#include <dhnetsdk.h>

static void OnDHDisconnect(LLONG lLoginID, char* pchDVRIP, LONG nDVRPort, LDWORD dwUser) {

}

DHSDKWidget::DHSDKWidget(QWidget* parent):dhsdk_user_id(-1),QWidget(parent) {
    ui = new Ui::DHSDKWidget();
    ui->setupUi(this);

    //connect(ui->sdkTest, SIGNAL(clicked()), this, SLOT(sdkTest()));

    connect(this, SIGNAL(AppendLog(const QString&)), this, SLOT(AppendLogToWindow(const QString&)));

    {
        // SDK初始化
        NETSDK_INIT_PARAM dh_sdk_param = { 0 };
        dh_sdk_param.nThreadNum = std::thread::hardware_concurrency() >> 1;
        CLIENT_InitEx(&OnDHDisconnect, 0, &dh_sdk_param);
    }

    //// 获取模拟能力集
    //NET_DVR_SDKLOCAL_CFG sdk_locak_cfg = { 0 };
    //if (NET_DVR_GetSDKLocalConfig(&sdk_locak_cfg) < 0) {
    //    Q_EMIT AppendLog(QString::fromUtf8("cuc_sdk:NET_DVR_GetSDKLocalConfig fail with error %1").arg(NET_DVR_GetLastError()));
    //    return;
    //}

    //NET_DVR_LOCAL_ABILITY_PARSE_CFG sdk_local_ability = { 0 };
    //if (NET_DVR_GetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_ABILITY_PARSE, &sdk_local_ability) < 0) {
    //    Q_EMIT AppendLog(QString::fromUtf8("cuc_sdk:NET_DVR_GetSDKLocalCfg fail with error %1").arg(NET_DVR_GetLastError()));
    //    return;
    //}
    //// 启用能力集
}

DHSDKWidget::~DHSDKWidget() {
    delete ui;
}

void DHSDKWidget::deviceConn() {

}

void DHSDKWidget::loopTest() {

}

void DHSDKWidget::sdkTest() {
    // 登录解码器
    LLONG lLoginHandle = 0;
    int nChannelID = 0; // 通道号

    NET_IN_LOGIN_WITH_HIGHLEVEL_SECURITY stInparam = { 0 };
    stInparam.dwSize = sizeof(stInparam);
    strncpy(stInparam.szIP, "10.3.220.123", sizeof(stInparam.szIP) - 1);
    strncpy(stInparam.szUserName, "admin", sizeof(stInparam.szUserName) - 1);
    strncpy(stInparam.szPassword, "Lty@1qaz", sizeof(stInparam.szPassword) - 1);
    stInparam.nPort = 37777;// 设备上设置的tcp访问的端口
    stInparam.emSpecCap = EM_LOGIN_SPEC_CAP_TCP;
    NET_OUT_LOGIN_WITH_HIGHLEVEL_SECURITY stOutparam = { 0 };
    stOutparam.dwSize = sizeof(stOutparam);

    lLoginHandle = CLIENT_LoginWithHighLevelSecurity(&stInparam, &stOutparam);
    if (!lLoginHandle) {
        // 登录失败
        Q_EMIT AppendLog(QString::fromUtf8("CLIENT_LoginWithHighLevelSecurity error:%1").arg(CLIENT_GetLastError()));
    }

    // 查询解码器信息
    DEV_DECODER_INFO stDecoderInfo = { 0 };
    if (!CLIENT_QueryDecoderInfo(lLoginHandle, &stDecoderInfo, 2000)) {
        Q_EMIT AppendLog(QString::fromUtf8("CLIENT_QueryDecoderInfo error:%1").arg(CLIENT_GetLastError()));
    }
    {
        // 打印解码器信息

    }

}
void DHSDKWidget::AppendLogToWindow(const QString& log) {
    QDateTime time = QDateTime::currentDateTime();

    ui->log_out->append(QString("%1:%2").arg(time.toString("yyyy.MM.dd-hh:mm:ss.zzz")).arg(log));
}

