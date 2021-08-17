#include "../MainWindow.hpp"
#include "../ui_mainwindow.h"

void MainWindow::setupButtons() {
    this->connect(ui->VideoStreamButton, SIGNAL(clicked(bool)), SLOT(switchVideoStream()));
    this->connect(ui->ScreenshotButton, SIGNAL(clicked(bool)), SLOT(takeScreenshot()));
    this->connect(ui->VideoCaptureButton, SIGNAL(clicked(bool)), SLOT(switchVideoCapture()));
    this->connect(ui->CommandsProtocolButton, SIGNAL(clicked(bool)), SLOT(switchSendingCommands()));
    this->connect(ui->ReceiveSettingsButton, SIGNAL(clicked(bool)), SLOT(receiveRobotSettings()));
    this->connect(ui->SendSettingsButton, SIGNAL(clicked(bool)), SLOT(sendRobotSettings()));
    this->connect(ui->SaveClientSettingsButton, SIGNAL(clicked(bool)), SLOT(saveClientSettings()));
    this->connect(ui->LoadClientSettingsButton, SIGNAL(clicked(bool)), SLOT(loadClientSettings()));
    this->connect(ui->RefreshGamepadsButton, SIGNAL(clicked(bool)), SLOT(refreshGamepads()));
    this->connect(ui->FullScreenButton, SIGNAL(clicked(bool)), SLOT(switchFullScreen()));
    this->connect(ui->ShowTabBarButton, SIGNAL(clicked(bool)), SLOT(showTabBar()));
    this->connect(ui->HideTabBarButton, SIGNAL(clicked(bool)), SLOT(hideTabBar()));
}

void MainWindow::switchVideoStream() {
    if (!_videoStream->IsOnline()) {
        _videoStream->StartAsync(pipeline);
    } else {
        _videoStream->Stop();
    }
}

void MainWindow::takeScreenshot() {

}

void MainWindow::switchVideoCapture() {

}

void MainWindow::switchSendingCommands() {
    if (!_commandsProtocol->IsOnline()) {
        _commandsProtocol->StartAsync(ui->RobotIPEdit->text(), COMMANDS_PORT);
    } else {
        _commandsProtocol->Stop();
    }
}

void MainWindow::receiveRobotSettings() {
    RobotSettingsStruct robotSettingsStruct;
    std::cout << ui->RobotIPEdit->text().toStdString() << std::endl;
    RobotSettingsProtocol().Recv(ui->RobotIPEdit->text(), SETTINGS_PORT, robotSettingsStruct);

    /// Выводим количество двигателей
    const double *moveCoefficientArray = robotSettingsStruct.ThrusterCoefficientArray();
    int motorsNumber = robotSettingsStruct.ThrusterNumber();
    ui->MotorsNumberSpinBox->setValue(motorsNumber);

    /// Выводим коэффициенты двигателей
    for (int i = 0; i < motorsNumber; i++) {
        for (int j = 0; j < 6; j++) {
            QString itemText = QString::number(moveCoefficientArray[i * 6 + j]);
            ui->MotorsTable->setItem(i, j, new QTableWidgetItem(itemText));
        }
    }

    /// Выводим число степеней свободы манипулятора
    const double *handCoefficientArray = robotSettingsStruct.HandCoefficientArray();
    int handFreedom = robotSettingsStruct.HandFreedom();
    ui->HandFreedomSpinBox->setValue(handFreedom);

    /// Выводим коэффициенты манипулятора
    for (int j = 0; j < handFreedom; j++) {
        QString itemText = QString::number(handCoefficientArray[j]);
        ui->HandTable->setItem(0, j, new QTableWidgetItem(itemText));
    }

    /// Выводим максимальную скорость двигателей
    ui->MaxSpeedEdit->setText(QString::number(robotSettingsStruct.MaxMotorsSpeed()));

    /// Выводим протокол двигателей
    switch (robotSettingsStruct.MotorsProtocol()) {
        case 1:
            ui->MotorsProtocolComboBox->setCurrentIndex(0);
            break;
        case 2:
            ui->MotorsProtocolComboBox->setCurrentIndex(1);
            break;
        case 4:
            ui->MotorsProtocolComboBox->setCurrentIndex(2);
            break;
        case 8:
            ui->MotorsProtocolComboBox->setCurrentIndex(3);
            break;
    }

    QMessageBox::information(this, "Сообщение", "Настройки успешно получены");
}

void MainWindow::sendRobotSettings() {

    RobotSettingsStruct robotSettingsStruct(ui->MotorsTable->rowCount(), ui->HandTable->columnCount());

    /// Считываем коэффициенты двигателей
    double *moveCoefficientArray = robotSettingsStruct.ThrusterCoefficientArray();
    std::vector<double> motorsVector(ui->MotorsTable->rowCount() * 6);
    for (int i = 0; i < ui->MotorsTable->rowCount(); i++) {
        for (int j = 0; j < ui->MotorsTable->columnCount(); j++) {
            moveCoefficientArray[i * 6 + j] = ui->MotorsTable->item(i, j)->text().toDouble();
        }
    }

    /// Считываем коэффициенты манипулятора
    double *handCoefficientArray = robotSettingsStruct.HandCoefficientArray();
    std::vector<double> handVector(ui->HandTable->columnCount());
    for (int j = 0; j < ui->HandTable->columnCount(); j++) {
        handCoefficientArray[j] = ui->HandTable->item(0, j)->text().toDouble();
    }

    /// Считываем максимальную скорость двигателей
    robotSettingsStruct.MaxMotorsSpeed() = (int16_t) ui->MaxSpeedEdit->text().toInt();

    /// Считываем протокол двигателей
    switch (ui->MotorsProtocolComboBox->currentIndex()) {
        case 0:
            robotSettingsStruct.MotorsProtocol() = DShotMode::DShot150;
            break;
        case 1:
            robotSettingsStruct.MotorsProtocol() = DShotMode::DShot300;
            break;
        case 2:
            robotSettingsStruct.MotorsProtocol() = DShotMode::DShot600;
            break;
        case 3:
            robotSettingsStruct.MotorsProtocol() = DShotMode::DShot1200;
            break;
    }

    //Временный вывод настроек в консоль
    std::cout << robotSettingsStruct;

    /// Отправка настроек роботу
    RobotSettingsProtocol().Send(ui->RobotIPEdit->text(), SETTINGS_PORT, std::move(robotSettingsStruct));

    QMessageBox::information(this, "Сообщение", "Настройки успешно отправлены");
}

void MainWindow::saveClientSettings() {
    ClientSettingsStruct settings;

    std::memcpy(settings.serverIP, ui->RobotIPEdit->text().begin(), sizeof(settings.serverIP));

    settings.leftShoulderActionID = (int8_t) ui->LeftShoulderComboBox->currentIndex();
    settings.rightShoulderActionID = (int8_t) ui->RightShoulderComboBox->currentIndex();
    settings.leftStickXActionID = (int8_t) ui->LeftStickXComboBox->currentIndex();
    settings.leftStickYActionID = (int8_t) ui->LeftStickYComboBox->currentIndex();
    settings.leftStickPressActionID = (int8_t) ui->LeftStickPressComboBox->currentIndex();
    settings.rightStickXActionID = (int8_t) ui->RightStickXComboBox->currentIndex();
    settings.rightStickYActionID = (int8_t) ui->RightStickYComboBox->currentIndex();
    settings.rightStickPressActionID = (int8_t) ui->RightStickPressComboBox->currentIndex();
    settings.dPadXActionID = (int8_t) ui->DPadXComboBox->currentIndex();
    settings.dPadYActionID = (int8_t) ui->DPadYComboBox->currentIndex();
    settings.triangleActionID = (int8_t) ui->TriangleComboBox->currentIndex();
    settings.crossActionID = (int8_t) ui->CrossComboBox->currentIndex();
    settings.rectangleActionID = (int8_t) ui->RectangleComboBox->currentIndex();
    settings.circleActionID = (int8_t) ui->CircleComboBox->currentIndex();
    settings.startActionID = (int8_t) ui->StartComboBox->currentIndex();
    settings.backActionID = (int8_t) ui->BackComboBox->currentIndex();

    settings.leftShoulderInverted = ui->LeftShoulderCheckBox->isChecked();
    settings.rightShoulderInverted = ui->RightShoulderCheckBox->isChecked();
    settings.leftStickXInverted = ui->LeftStickXCheckBox->isChecked();
    settings.leftStickYInverted = ui->LeftStickYCheckBox->isChecked();
    settings.rightStickXInverted = ui->RightStickXCheckBox->isChecked();
    settings.rightStickYInverted = ui->RightStickYCheckBox->isChecked();
    settings.dPadXInverted = ui->DPadXCheckBox->isChecked();
    settings.dPadYInverted = ui->DPadYCheckBox->isChecked();

    settings.Save();

    QMessageBox::information(this, "Сообщение", "Настройки успешно сохранены");
}

void MainWindow::loadClientSettings() {
    ClientSettingsStruct settings;
    settings.Load();

    ui->RobotIPEdit->setText(QString(settings.serverIP));

    ui->LeftShoulderComboBox->setCurrentIndex(settings.leftShoulderActionID);
    ui->RightShoulderComboBox->setCurrentIndex(settings.rightShoulderActionID);
    ui->LeftStickXComboBox->setCurrentIndex(settings.leftStickXActionID);
    ui->LeftStickYComboBox->setCurrentIndex(settings.leftStickYActionID);
    ui->LeftStickPressComboBox->setCurrentIndex(settings.leftStickPressActionID);
    ui->RightStickXComboBox->setCurrentIndex(settings.rightStickXActionID);
    ui->RightStickYComboBox->setCurrentIndex(settings.rightStickYActionID);
    ui->RightStickPressComboBox->setCurrentIndex(settings.rightStickPressActionID);
    ui->DPadXComboBox->setCurrentIndex(settings.dPadXActionID);
    ui->DPadYComboBox->setCurrentIndex(settings.dPadYActionID);
    ui->TriangleComboBox->setCurrentIndex(settings.triangleActionID);
    ui->CrossComboBox->setCurrentIndex(settings.crossActionID);
    ui->RectangleComboBox->setCurrentIndex(settings.rectangleActionID);
    ui->CircleComboBox->setCurrentIndex(settings.circleActionID);
    ui->StartComboBox->setCurrentIndex(settings.startActionID);
    ui->BackComboBox->setCurrentIndex(settings.backActionID);

    ui->LeftShoulderCheckBox->setChecked(settings.leftShoulderInverted);
    ui->RightShoulderCheckBox->setChecked(settings.rightShoulderInverted);
    ui->LeftStickXCheckBox->setChecked(settings.leftStickXInverted);
    ui->LeftStickYCheckBox->setChecked(settings.leftStickYInverted);
    ui->RightStickXCheckBox->setChecked(settings.rightStickXInverted);
    ui->RightStickYCheckBox->setChecked(settings.rightStickYInverted);
    ui->DPadXCheckBox->setChecked(settings.dPadXInverted);
    ui->DPadYCheckBox->setChecked(settings.dPadYInverted);

    //QMessageBox::information(this, "Сообщение", "Настройки успешно восстановлены");
}

void MainWindow::refreshGamepads() {
    std::list<int> gamepads = Control::GetGamepadsIds();
    ui->GamepadComboBox->clear();
    for (int id : gamepads) {
        ui->GamepadComboBox->addItem(QString::number(id));
    }
    // Путь для получения выбранного ID:
    // ui->GamepadComboBox->itemText(ui->GamepadComboBox->currentIndex()).toInt()
}

void MainWindow::switchFullScreen() {
    if (this->windowState() == Qt::WindowFullScreen) {
        this->setWindowState(Qt::WindowNoState);
    } else {
        this->setWindowState(Qt::WindowFullScreen);
    }
}

void MainWindow::showTabBar() {
    /// Показываем панель
    ui->TabWidget->tabBar()->show();

    /// Показываем все кнопки на панели
    ui->FullScreenButton->show();
    ui->HideTabBarButton->show();
    ui->CommandsProtocolButton->show();

    /// Скрываем кнопку показа панели
    ui->ShowTabBarButton->hide();
}

void MainWindow::hideTabBar() {
    /// Скрываем панель
    ui->TabWidget->tabBar()->hide();

    /// Скрываем все кнопки на панели
    ui->FullScreenButton->hide();
    ui->HideTabBarButton->hide();
    ui->CommandsProtocolButton->hide();

    /// Показываем кнопку показа панели (Ъеъ)
    ui->ShowTabBarButton->show();
}