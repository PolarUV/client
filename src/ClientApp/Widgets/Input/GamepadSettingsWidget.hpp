#ifndef CLIENT_COMMANSSETTINGSWIDGET_HPP
#define CLIENT_COMMANSSETTINGSWIDGET_HPP

#include "../WidgetResources.hpp"

#include <QWidget>
#include <QSettings>
#include <QTimer>

#include "CommandsStruct.hpp"
#include "GamepadSettingsStruct.hpp"
#include "Gamepad.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class GamepadSettingsWidget; }
QT_END_NAMESPACE

class CommandsSettingsWidget : public QWidget {
Q_OBJECT
    constexpr static auto TIMEOUT_ms = std::chrono::milliseconds(15);
public:
    CommandsSettingsWidget(QWidget *parent, WidgetResources &resources);

    ~CommandsSettingsWidget() override;

    GamepadSettingsStruct GetGamepadSettings();

private:

    Ui::GamepadSettingsWidget *ui;

    std::unique_ptr<QSettings> settings_;

    WidgetResources& resources_;

    control::Gamepad gamepad_;

    QTimer timer_;

    /// ToDo: убрать костыль
    uint8_t reverseTicks;
    uint8_t zeroTicks;

public slots:

    void StartWidget();

    void StopWidget();

private slots:

    void LoadSettings();

    void SaveSettings();

    void SendCommand();
};

#endif
