#pragma once

#include <QWidget>
#include "ui_HCSDK.h"

class HCSDKWidget : public QWidget
{
    Q_OBJECT

public:
    HCSDKWidget(QWidget *parent = nullptr);
    ~HCSDKWidget();

Q_SIGNALS:
    void AppendLog(const QString& log);

private Q_SLOTS:
    void deviceConn();
    void loopTest();
    void sdkTest();
    void AppendLogToWindow(const QString& log);

private:
    Ui::HCSDKWidget* ui;
    int hcsdk_user_id;
};
