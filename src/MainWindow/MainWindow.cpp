#include "MainWindow.hpp"
#include "./ui_mainwindow.h"

#define SERVER_IP "192.168.1.50"
#define PORT 1999
#define COMMAND_DELAY 3000

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::StartVideoCapture() {
    cv::namedWindow("Main", cv::WINDOW_NORMAL);

    cv::UMat inFrame, outFrame;

    this->_stream.open(pipeline, cv::CAP_GSTREAMER);

    if (!this->_stream.isOpened()) {
        std::cout << "Чё-та стримчанского я не вижу\n";
        return;
    }

    for (;;) {
        this->_stream >> inFrame;

        if (inFrame.empty()) {
            std::cout << "Кадров больше нет\n";
            return;
        }

        outFrame = std::move(inFrame);
        cv::imshow("Main", outFrame);
    }
}

void MainWindow::StopVideoCapture() {
    this->_stream.release();
}

void MainWindow::on_socketConnectButton_clicked() {
    if (!_dataProtocol.IsOnline())
        _dataProtocol.StartAsync(SERVER_IP, PORT);
    else
        _dataProtocol.Stop();
}