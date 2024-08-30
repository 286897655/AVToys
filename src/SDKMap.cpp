#include "SDKMap.hpp"

#define XX(HCSDK_EXCEPTION_ID,HCSDK_EXCEPTION_CODE,HCSDK_EXCEPTION_MESSAGE)                                         \
    case HCSDK_EXCEPTION_CODE:{                                                                                     \
        return HCSDK_EXCEPTION_MESSAGE;                                                                             \
    }                                                                                                               \

#define HCSDK_ERROR_TABLE(YY)                       \
    YY(0,   NET_DVR_NOERROR,                "没有错误")\
    YY(1,   NET_DVR_PASSWORD_ERROR,         "用户名密码错误。注册时输入的用户名或者密码错误")\
    YY(4,   NET_DVR_CHANNEL_ERROR,          "通道号错误")\
    YY(5,   NET_DVR_OVER_MAXLINK,           "设备总的连接数超过最大")\
    YY(6,   NET_DVR_VERSIONNOMATCH,         "版本不匹配。SDK和设备的版本不匹配。")\
    YY(7,   NET_DVR_NETWORK_FAIL_CONNECT,   "连接设备失败。设备不在线或网络原因引起的连接超时等。")\
    YY(8,   NET_DVR_NETWORK_SEND_ERROR,     "向设备发送失败")\
    YY(9,   NET_DVR_NETWORK_RECV_ERROR,     "从设备接收数据失败。")\
    YY(10,  NET_DVR_NETWORK_RECV_TIMEOUT,   "从设备接收数据超时。")\
    YY(11,  NET_DVR_NETWORK_ERRORDATA,      "传送的数据有误。发送给设备或者从设备接收到的数据错误，如远程参数配置时输入设备不支持的值。") \
    YY(12,  NET_DVR_ORDER_ERROR,            "调用次序错误")\
    YY(13,  NET_DVR_OPERNOPERMIT,           "无此权限。用户对某个功能模块的权限，例如无预览权限用户预览返回此错误。")\
    YY(14,  NET_DVR_COMMANDTIMEOUT,         "设备命令执行超时。")\
    YY(17,  NET_DVR_PARAMETER_ERROR,        "参数错误。SDK接口中给入的输入或输出参数为空,或者参数格式或值不符合要求。")\
    YY(23,  NET_DVR_NOSUPPORT,              "设备不支持。")\
    YY(24,  NET_DVR_BUSY,                   "设备忙。")\
    YY(28,  NET_DVR_DVRNORESOURCE,          "设备资源不足")\
    YY(29,  NET_DVR_DVROPRATEFAILED,        "设备操作失败")\
    YY(36,  NET_DVR_OPERNOTFINISH,          "上次的操作还没有完成")\
    YY(44,  NET_DVR_CREATESOCKET_ERROR,     "上创建SOCKET出错")\
    YY(45,  NET_DVR_SETSOCKET_ERROR,        "设置SOCKET出错")\
    YY(46,  NET_DVR_MAX_NUM,                "个数达到最大。分配的注册连接数、预览连接数超过SDK支持的最大数。")\
    YY(47,  NET_DVR_USERNOTEXIST,           "用户不存在。注册的用户ID已注销或不可用。")\
    YY(102, NET_DVR_USER_NOT_SUCC_LOGIN,    "用户还没登录成功。")\
    YY(105, NET_DVR_PACKET_TYPE_NOT_SUPPORT,"码流封装格式错误")\
    YY(107, NET_DVR_LOAD_HCPREVIEW_SDK_ERROR,"预览组件加载失败")\
    YY(108, NET_DVR_LOAD_HCVOICETALK_SDK_ERROR,    "语音组件加载失败")\
    YY(109, NET_DVR_LOAD_HCALARM_SDK_ERROR,    "报警组件加载失败")\
    YY(110, NET_DVR_LOAD_HCPLAYBACK_SDK_ERROR,    "回放组件加载失败")\
    YY(111, NET_DVR_LOAD_HCDISPLAY_SDK_ERROR,    "显示组件加载失败")\
    YY(112, NET_DVR_LOAD_HCINDUSTRY_SDK_ERROR,    "行业应用组件加载失败")\
    YY(113, NET_DVR_LOAD_HCGENERALCFGMGR_SDK_ERROR,    "通用配置管理组件加载失败")\
    YY(114, NET_DVR_LOAD_HCCOREDEVCFG_SDK_ERROR,    "设备配置核心组件加载失败")\
    YY(121, NET_DVR_CORE_VER_MISMATCH,    "单独加载组件时,组件与core版本不匹配")\
    YY(122, NET_DVR_CORE_VER_MISMATCH_HCPREVIEW,    "预览组件与core版本不匹配")\
    YY(123, NET_DVR_CORE_VER_MISMATCH_HCVOICETALK,    "语音组件与core版本不匹配")\
    YY(124, NET_DVR_CORE_VER_MISMATCH_HCALARM,    "报警组件与core版本不匹配")\
    YY(125, NET_DVR_CORE_VER_MISMATCH_HCPLAYBACK,    "回放组件与core版本不匹配")\
    YY(126, NET_DVR_CORE_VER_MISMATCH_HCDISPLAY,    "显示组件与core版本不匹配")\
    YY(127, NET_DVR_CORE_VER_MISMATCH_HCINDUSTRY,    "行业应用组件与core版本不匹配")\
    YY(128, NET_DVR_CORE_VER_MISMATCH_HCGENERALCFGMGR,    "通用配置管理组件与core版本不匹配")\
    YY(136, NET_DVR_COM_VER_MISMATCH_HCPREVIEW,    "预览组件与HCNetSDK版本不匹配")\
    YY(137, NET_DVR_COM_VER_MISMATCH_HCVOICETALK,    "语音组件与HCNetSDK版本不匹配")\
    YY(138, NET_DVR_COM_VER_MISMATCH_HCALARM,    "报警组件与HCNetSDK版本不匹配")\
    YY(139, NET_DVR_COM_VER_MISMATCH_HCPLAYBACK,    "回放组件与HCNetSDK版本不匹配")\
    YY(140, NET_DVR_COM_VER_MISMATCH_HCDISPLAY,    "显示组件与HCNetSDK版本不匹配")\
    YY(141, NET_DVR_COM_VER_MISMATCH_HCINDUSTRY,    "行业应用组件与HCNetSDK版本不匹配")\
    YY(142, NET_DVR_COM_VER_MISMATCH_HCGENERALCFGMGR,    "通用配置管理组件与HCNetSDK版本不匹配")\
    YY(153, NET_DVR_USER_LOCKED,    "用户名被锁定")\
    YY(154, NET_DVR_INVALID_USERID,    "无效用户ID")\
    YY(155, NET_DVR_LOW_LOGIN_VERSION,    "登录版本低")\
    YY(156, NET_DVR_LOAD_LIBEAY32_DLL_ERROR,    "加载libeay32.dll库失败")\
    YY(157, NET_DVR_LOAD_SSLEAY32_DLL_ERROR,    "加载ssleay32.dll库失败")\
    YY(158, NET_ERR_LOAD_LIBICONV,    "加载libiconv.dll库失败")\
    YY(901, NET_ERR_WINCHAN_IDX,    "开窗通道号错误")\
    YY(902, NET_ERR_WIN_LAYER,    "窗口层数错误，单个屏幕上最多覆盖的窗口层数")\
    YY(903, NET_ERR_WIN_BLK_NUM,    "窗口的块数错误，单个窗口可覆盖的屏幕个数")\
    YY(904, NET_ERR_OUTPUT_RESOLUTION,    "输出分辨率错误")\
    YY(905, NET_ERR_LAYOUT,    "场景号错误")\
    YY(906, NET_ERR_INPUT_RESOLUTION,    "输入分辨率不支持")\
    YY(907, NET_ERR_SUBDEVICE_OFFLINE,    "子设备不在线")\
    YY(908, NET_ERR_NO_DECODE_CHAN,    "没有空闲解码通道")\
    YY(909, NET_ERR_MAX_WINDOW_ABILITY,    "开窗能力上限，解码子设备能力上限或者显示处理器能力上限导致")\
    YY(910, NET_ERR_ORDER_ERROR,    "调用顺序有误")\
    YY(911, NET_ERR_PLAYING_PLAN,    "正在执行预案")\
    YY(912, NET_ERR_DECODER_USED,    "解码板正在使用")\
    YY(913, NET_ERR_OUTPUT_BOARD_DATA_OVERFLOW,    "输出板数据量超限")\
    YY(914, NET_ERR_SAME_USER_NAME,    "用户名相同")\
    YY(915, NET_ERR_INVALID_USER_NAME,    "无效用户名")\
    YY(916, NET_ERR_MATRIX_USING,    "输入矩阵正在使用")\
    YY(917, NET_ERR_DIFFERENT_CHAN_TYPE,    "通道类型不同（矩阵输出通道和控制器的输入为不同的类型）。")\
    YY(918, NET_ERR_INPUT_CHAN_BINDED,    "输入通道已经被其他矩阵绑定。")\
    YY(919, NET_ERR_BINDED_OUTPUT_CHAN_OVERFLOW,    "正在使用的矩阵输出通道个数超过矩阵与控制器绑定的通道个数。")\
    YY(920, NET_ERR_MAX_SIGNAL_NUM,    "输入信号源个数达到上限。")\
    YY(921, NET_ERR_INPUT_CHAN_USING,    "输入通道正在使用。")\
    YY(922, NET_ERR_MANAGER_LOGON,    "管理员已经登陆，操作失败。")\
    YY(923, NET_ERR_USERALREADY_LOGON,    "该用户已经登陆，操作失败。")\
    YY(924, NET_ERR_LAYOUT_INIT,    "场景正在初始化，操作失败。")\
    YY(925, NET_ERR_BASEMAP_SIZE_NOT_MATCH,    "底图大小不符")\
    YY(926, NET_ERR_WINDOW_OPERATING,    "窗口正在执行其他操作，本次操作失败。")\
    YY(927, NET_ERR_SIGNAL_UPLIMIT,    "信号源开窗个数达到上限。")\
    YY(943, NET_ERR_WINDOW_SIZE_OVERLIMIT,    "窗口大小超限")\
    YY(951, NET_ERR_MAX_WIN_OVERLAP,    "达到最大窗口重叠数")\
    YY(952, NET_ERR_STREAMID_CHAN_BOTH_VALID,    "stream ID和通道号同时有效")\
    YY(953, NET_ERR_NO_ZERO_CHAN,    "设备无零通道")\
    YY(955, NEED_RECONNECT,    "需要重定向（转码子系统使用）")\
    YY(956, NET_ERR_NO_STREAM_ID,    "流ID不存在")\
    YY(957, NET_DVR_TRANS_NOT_START,    "转码未启动")\
    YY(958, NET_ERR_MAXNUM_STREAM_ID,    "流ID数达到上限")\
    YY(959, NET_ERR_WORKMODE_MISMATCH,    "工作模式不匹配")\
    YY(960, NET_ERR_MODE_IS_USING,    "已工作在当前模式")\
    YY(961, NET_ERR_DEV_PROGRESSING,    "设备正在处理中")\
    YY(962, NET_ERR_PASSIVE_TRANSCODING,    "正在被动转码")\
    YY(975, NET_DVR_ERR_WINDOW_SIZE_PLACE,    "窗口位置错误")\
    YY(976, NET_DVR_ERR_RGIONAL_RESTRICTIONS,    "屏幕距离超限")\
    YY(984, NET_DVR_ERR_CLOSE_WINDOWS,    "操作失败，请先关闭窗口")\
    YY(985, NET_DVR_ERR_MATRIX_LOOP_ABILITY,    "超出轮巡解码能力限制")\
    YY(986, NET_DVR_ERR_MATRIX_LOOP_TIME,    "轮巡解码时间不支持")\
    YY(987, NET_DVR_ERR_LINKED_OUT_ABILITY,    "联动通道数超过上限")


#define YY(INT,HKSDK_ERROR_CODE,HKSDK_ERROR_MESSAGE)    \
    case HKSDK_ERROR_CODE:{                             \
        return HKSDK_ERROR_MESSAGE;                     \
    }


namespace HCSDK {
    const char* StringOf_HCSDK_LastError(DWORD error) {
        switch (error) {
            HCSDK_ERROR_TABLE(YY)
        }
        return "HCSDK Undefined Error";
    }

    const char* StringOf_HCSDK_Exception(DWORD epcode) {
        switch (epcode) {
            HCSDK_EXCEPTION_TABLE(XX)
        default:break;
        }
        return "HCSDK Undefined Exception";
    }
    std::unique_ptr<HCSDK_CODE_MESSAGE> GetLastError() {
        std::unique_ptr<HCSDK_CODE_MESSAGE> last_error = nullptr;
        last_error.reset(new HCSDK_CODE_MESSAGE());
        last_error->code = NET_DVR_GetLastError();
        last_error->message = StringOf_HCSDK_LastError(last_error->code);
        return last_error;
    }

    std::unique_ptr<HCSDK_CODE_MESSAGE> GetException(DWORD epcode) {
        std::unique_ptr<HCSDK_CODE_MESSAGE> exception = nullptr;
        exception.reset(new HCSDK_CODE_MESSAGE());
        exception->code = epcode;
        exception->message = StringOf_HCSDK_Exception(epcode);
        return exception;
    }

};

