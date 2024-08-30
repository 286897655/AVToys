#pragma once

#include <QWidget>
#include "ui_DHSDK.h"
#include <dhnetsdk.h>
class DHSDKWidget : public QWidget
{
    Q_OBJECT

public:
    DHSDKWidget(QWidget* parent = nullptr);
    ~DHSDKWidget();

Q_SIGNALS:
    void AppendLog(const QString& log);

private Q_SLOTS:
    void deviceConn();
    void loopTest();
    void sdkTest();
    void AppendLogToWindow(const QString& log);

private:
    Ui::DHSDKWidget* ui;
    LONG dhsdk_user_id;
};