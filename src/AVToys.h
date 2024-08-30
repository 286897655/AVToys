#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AVToys.h"
#include "HCSDKWidget.h"
#include "DHSDKWidget.h"

class AVToys : public QMainWindow
{
    Q_OBJECT

public:
    AVToys(QWidget *parent = nullptr);
    ~AVToys();

private:
    Ui::AVToysClass ui;
    HCSDKWidget* hcsdk_widget_;
    DHSDKWidget* dhsdk_widget_;
};
