#ifndef SDK_MAP_HPP_
#define SDK_MAP_HPP_
/**
 * @brief define some sdk map information,such as error code and video audio code
 *
 */

#include "HCSDK/HCNetSDK.h"
#include <memory>

enum HCSDK_EXCEPTION {
    HCSDK_EXCEPTION_EXCHANGE = 0x00,
    HCSDK_EXCEPTION_AUDIOEXCHANGE,
    HCSDK_EXCEPTION_ALARM,
    HCSDK_EXCEPTION_PREVIEW,
    HCSDK_EXCEPTION_SERIAL,
    HCSDK_EXCEPTION_RECONNECT,
    HCSDK_EXCEPTION_ALARMRECONNECT,
    HCSDK_EXCEPTION_SERIALRECONNECT,
    HCSDK_SERIAL_RECONNECTSUCCESS,
    HCSDK_EXCEPTION_PLAYBACK,
    HCSDK_EXCEPTION_DISKFMT,
    HCSDK_EXCEPTION_PASSIVEDECODE,
    HCSDK_EXCEPTION_EMAILTEST,
    HCSDK_EXCEPTION_BACKUP,
    HCSDK_PREVIEW_RECONNECTSUCCESS,
    HCSDK_ALARM_RECONNECTSUCCESS,
    HCSDK_RESUME_EXCHANGE,
    HCSDK_NETWORK_FLOWTEST_EXCEPTION,
    HCSDK_EXCEPTION_PICPREVIEWRECONNECT,
    HCSDK_PICPREVIEW_RECONNECTSUCCESS,
    HCSDK_EXCEPTION_PICPREVIEW,
    HCSDK_EXCEPTION_MAX_ALARM_INFO,
    HCSDK_EXCEPTION_LOST_ALARM,
    HCSDK_EXCEPTION_PASSIVETRANSRECONNECT,
    HCSDK_PASSIVETRANS_RECONNECTSUCCESS,
    HCSDK_EXCEPTION_PASSIVETRANS,
    HCSDK_EXCEPTION_RELOGIN,
    HCSDK_RELOGIN_SUCCESS,
    HCSDK_EXCEPTION_PASSIVEDECODE_RECONNNECT,
    HCSDK_EXCEPTION_CLUSTER_CS_ARMFAILED,
    HCSDK_EXCEPTION_RELOGIN_FAILED,
    HCSDK_EXCEPTION_PREVIEW_RECONNECT_CLOSED,
    HCSDK_EXCEPTION_ALARM_RECONNECT_CLOSED,
    HCSDK_EXCEPTION_SERIAL_RECONNECT_CLOSED,
    HCSDK_EXCEPTION_PIC_RECONNECT_CLOSED,
    HCSDK_EXCEPTION_PASSIVE_DECODE_RECONNECT_CLOSED,
    HCSDK_EXCEPTION_PASSIVE_TRANS_RECONNECT_CLOSED,
    HCSDK_EXCEPTION_UNDEFINE
};

#define HCSDK_EXCEPTION_TABLE(XX) \
    XX(HCSDK_EXCEPTION_EXCHANGE,                        EXCEPTION_EXCHANGE,                         "用户交互时异常(注册心跳超时,心跳间隔为2分钟)")  \
    XX(HCSDK_EXCEPTION_AUDIOEXCHANGE,                   EXCEPTION_AUDIOEXCHANGE,                    "语音对讲异常")                               \
    XX(HCSDK_EXCEPTION_ALARM,                           EXCEPTION_ALARM,                            "报警异常")                                   \
    XX(HCSDK_EXCEPTION_PREVIEW,                         EXCEPTION_PREVIEW,                          "网络预览异常")                               \
    XX(HCSDK_EXCEPTION_SERIAL,                          EXCEPTION_SERIAL,                           "透明通道异常")                               \
    XX(HCSDK_EXCEPTION_RECONNECT,                       EXCEPTION_RECONNECT,                        "预览时重连")                                 \
    XX(HCSDK_EXCEPTION_ALARMRECONNECT,                  EXCEPTION_ALARMRECONNECT,                   "报警时重连")                                 \
    XX(HCSDK_EXCEPTION_SERIALRECONNECT,                 EXCEPTION_SERIALRECONNECT,                  "透明通道重连")                               \
    XX(HCSDK_SERIAL_RECONNECTSUCCESS,                   SERIAL_RECONNECTSUCCESS,                    "透明通道重连成功")                           \
    XX(HCSDK_EXCEPTION_PLAYBACK,                        EXCEPTION_PLAYBACK,                         "回放异常")                                   \
    XX(HCSDK_EXCEPTION_DISKFMT,                         EXCEPTION_DISKFMT,                          "硬盘格式化")                                 \
    XX(HCSDK_EXCEPTION_PASSIVEDECODE,                   EXCEPTION_PASSIVEDECODE,                    "被动解码异常")                               \
    XX(HCSDK_EXCEPTION_EMAILTEST,                       EXCEPTION_EMAILTEST,                        "邮件测试异常")                              \
    XX(HCSDK_EXCEPTION_BACKUP,                          EXCEPTION_BACKUP,                           "备份异常")                                   \
    XX(HCSDK_PREVIEW_RECONNECTSUCCESS,                  PREVIEW_RECONNECTSUCCESS,                   "预览时重连成功")                            \
    XX(HCSDK_ALARM_RECONNECTSUCCESS,                    ALARM_RECONNECTSUCCESS,                     "报警时重连成功")                             \
    XX(HCSDK_RESUME_EXCHANGE,                           RESUME_EXCHANGE,                            "用户交互恢复")                                \
    XX(HCSDK_NETWORK_FLOWTEST_EXCEPTION,                NETWORK_FLOWTEST_EXCEPTION,                 "网络流量检测异常")                           \
    XX(HCSDK_EXCEPTION_PICPREVIEWRECONNECT,             EXCEPTION_PICPREVIEWRECONNECT,              "图片预览重连")              \
    XX(HCSDK_PICPREVIEW_RECONNECTSUCCESS,               PICPREVIEW_RECONNECTSUCCESS,                "图片预览重连成功")    \
    XX(HCSDK_EXCEPTION_PICPREVIEW,                      EXCEPTION_PICPREVIEW,                       "图片预览异常")        \
    XX(HCSDK_EXCEPTION_MAX_ALARM_INFO,                  EXCEPTION_MAX_ALARM_INFO,                   "报警信息缓存已达上限") \
    XX(HCSDK_EXCEPTION_LOST_ALARM,                      EXCEPTION_LOST_ALARM,                       "报警丢失")             \
    XX(HCSDK_EXCEPTION_PASSIVETRANSRECONNECT,           EXCEPTION_PASSIVETRANSRECONNECT,            "被动转码重连")        \
    XX(HCSDK_PASSIVETRANS_RECONNECTSUCCESS,             PASSIVETRANS_RECONNECTSUCCESS,              "被动转码重连成功")    \
    XX(HCSDK_EXCEPTION_PASSIVETRANS,                    EXCEPTION_PASSIVETRANS,                     "被动转码异常")        \
    XX(HCSDK_EXCEPTION_RELOGIN,                         EXCEPTION_RELOGIN,                          "用户重登陆")          \
    XX(HCSDK_RELOGIN_SUCCESS,                           RELOGIN_SUCCESS,                            "用户重登陆成功")     \
    XX(HCSDK_EXCEPTION_PASSIVEDECODE_RECONNNECT,        EXCEPTION_PASSIVEDECODE_RECONNNECT,         "被动解码重连")      \
    XX(HCSDK_EXCEPTION_CLUSTER_CS_ARMFAILED,            EXCEPTION_CLUSTER_CS_ARMFAILED,             "集群报警异常")        \
    XX(HCSDK_EXCEPTION_RELOGIN_FAILED,                  EXCEPTION_RELOGIN_FAILED,                   "重登陆失败，停止重登陆")     \
    XX(HCSDK_EXCEPTION_PREVIEW_RECONNECT_CLOSED,        EXCEPTION_PREVIEW_RECONNECT_CLOSED,         "关闭预览重连功能")          \
    XX(HCSDK_EXCEPTION_ALARM_RECONNECT_CLOSED,          EXCEPTION_ALARM_RECONNECT_CLOSED,           "关闭报警重连功能")         \
    XX(HCSDK_EXCEPTION_SERIAL_RECONNECT_CLOSED,         EXCEPTION_SERIAL_RECONNECT_CLOSED,          "关闭透明通道重连功能")     \
    XX(HCSDK_EXCEPTION_PIC_RECONNECT_CLOSED,            EXCEPTION_PIC_RECONNECT_CLOSED,             "关闭回显重连功能")          \
    XX(HCSDK_EXCEPTION_PASSIVE_DECODE_RECONNECT_CLOSED, EXCEPTION_PASSIVE_DECODE_RECONNECT_CLOSED,  "关闭被动解码重连功能")      \
    XX(HCSDK_EXCEPTION_PASSIVE_TRANS_RECONNECT_CLOSED,  EXCEPTION_PASSIVE_TRANS_RECONNECT_CLOSED,   "关闭被动转码重连功能")                                   


namespace HCSDK {
    struct HCSDK_CODE_MESSAGE {
        DWORD code;
        const char* message;
    };
    const char* StringOf_HCSDK_Exception(DWORD epcode);
    const char* StringOf_HCSDK_LastError(DWORD error);
    std::unique_ptr<HCSDK_CODE_MESSAGE> GetLastError();
    std::unique_ptr<HCSDK_CODE_MESSAGE> GetException(DWORD epcode);
}

#endif//SDK_MAP_HPP_