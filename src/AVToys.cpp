#include "AVToys.h"

AVToys::AVToys(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    hcsdk_widget_ = nullptr;

    // sdk测试
    QToolBar* hksdk_toolbar = this->addToolBar(QString::fromUtf8("HCSDK测试"));
    QAction* hcsdk_action = new QAction(QString::fromUtf8("HCSDK测试"), hksdk_toolbar);
    connect(hcsdk_action, &QAction::triggered, this, [this]() {
        if (!hcsdk_widget_) {
            hcsdk_widget_ = new HCSDKWidget();
        }
        hcsdk_widget_->show();
        });
    hksdk_toolbar->addAction(hcsdk_action);
    QToolBar* dhsdk_toolbar = this->addToolBar(QString::fromUtf8("DHSDK测试"));
    QAction* dhsdk_action = new QAction(QString::fromUtf8("DHSDK测试"), dhsdk_toolbar);
    connect(dhsdk_action, &QAction::triggered, this, [this]() {
        if (!dhsdk_widget_) {
            dhsdk_widget_ = new DHSDKWidget();
        }
        dhsdk_widget_->show();
    });
    dhsdk_toolbar->addAction(dhsdk_action);
}

AVToys::~AVToys()
{
    if (hcsdk_widget_) {
        delete hcsdk_widget_;
        hcsdk_widget_ = nullptr;
    }
    if (dhsdk_widget_) {
        delete dhsdk_widget_;
        dhsdk_widget_ = nullptr;
    }
}
