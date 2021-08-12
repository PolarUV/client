#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <fstream>
#include <windows.h>
#include <thread>
#include <chrono>

#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QThread>
#include <QMouseEvent>

#include "./DataStructs/ClientSettingsStruct/ClientSettingsStruct.hpp"
#include "./Protocols/Protocols.hpp"
#include "./Gamepad/Gamepad.hpp"

#define SERVER_IP "169.254.154.5"
// 192.168.1.50 - motov.s
// 169.254.154.5 - shushkov.d
#define COMMANDS_PORT 1999
#define SETTINGS_PORT 2020


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

constexpr char pipeline[] = "tcpclientsrc host=169.254.154.5 port=5000 ! gdpdepay ! rtph264depay ! decodebin ! autovideoconvert  ! appsink sync=false";


class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void placeWidgets();
    void loadClientSettings();
    static QImage cvMatToQImage(const cv::Mat &mat);
    static QPixmap cvMatToPixmap(const cv::Mat &mat);

private slots:
    void on_CommandsProtocolButton_clicked();
    void on_GamepadButton_clicked();
    void on_VideoStreamButton_clicked();
    void on_ReceiveSettingsButton_clicked();
    void on_SendSettingsButton_clicked();
    void on_LoadClientSettingsButton_clicked();
    void on_SaveClientSettingsButton_clicked();

    void on_FullScreenButton_clicked();

    void on_MotorsNumberSpinBox_valueChanged(int value);
    void on_HandFreedomSpinBox_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    bool _widgetsPlaced;

    VideoProtocol *_videoStream;
    CommandsProtocol *_commandsProtocol;
    RobotSettingsProtocol *_settingsProtocol;
};
#endif

