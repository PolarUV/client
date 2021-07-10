#include "AuthorizationWidget.hpp"
#include "ui_AuthorizationWidget.h"

#include <QWindow>
#include <QMessageBox>

#include "../Input/Gamepad.hpp"

AuthorizationWidget::AuthorizationWidget(QMainWindow *parent) :
        QWidget(parent),
        ui(new Ui::AuthorizationWidget),
        ioContext_(),
        settings_("NARFU", "PolarUV-Client"),
        resources_() {

    ui->setupUi(this);

    if (!settings_.value("RobotIP").isNull()) {
        ui->RobotIPEdit->setText(settings_.value("RobotIP").toString());
    }

    /// Создаем в ресурсах два OpenGL-буфера для кадров
//    renderWindow_.setSurfaceType(QWindow::OpenGLSurface);
//    renderWindow_.create();
//
//    openGLContext_.create();
//    openGLContext_.makeCurrent(&renderWindow_);
//
//    fboFormat_.setSamples(16);
//    fboFormat_.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
//
//    resources_.telemetryFBO = new QOpenGLFramebufferObject(1920, 1080, fboFormat_);
//    resources_.displayFBO = new QOpenGLFramebufferObject(1920, 1080, fboFormat_);

    /// Соединяем собственные слоты
    connect(ui->RefreshGamepadIDsButton, SIGNAL(clicked(bool)), this, SLOT(RefreshGamepadIDs()));
    connect(ui->LaunchButton, SIGNAL(clicked(bool)), this, SLOT(LaunchHandler()));

    /// Соединяем слоты MainWindow
    connect(ui->DebugButton, SIGNAL(clicked(bool)), parent, SLOT(LaunchDebug()));
    connect(this, SIGNAL(StartWidget()), parent, SLOT(Launch()));

    keyF1_ = new QShortcut(Qt::Key_F1,parent,SLOT(LaunchDebug()));
    keyF2_ = new QShortcut(Qt::Key_F2,this,SLOT(LaunchHandler()));
}

AuthorizationWidget::~AuthorizationWidget() {
    delete ui;
}

void AuthorizationWidget::RefreshGamepadIDs() {
    auto gamepads = control::GetGamepadsIds();
    ui->GamepadComboBox->clear();

    for (size_t id = 0; id < gamepads.size(); ++id)
        if (gamepads[id])
            ui->GamepadComboBox->addItem(QString::number(id));
}

void AuthorizationWidget::LaunchHandler() {

    auto ip = ui->RobotIPEdit->text().toStdString();

    bool isConnected = resources_.Network.TryConnect(ip);

    if (!isConnected) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось подключиться к роботу");
        return;
    }

    settings_.setValue("RobotIP", ui->RobotIPEdit->text());

    emit StartWidget();
}

