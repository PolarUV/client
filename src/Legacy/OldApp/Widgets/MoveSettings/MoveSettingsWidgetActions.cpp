#include <ranges>
#include <Exceptions/Exceptions.hpp>
#include <QMessageBox>
#include "./MoveSettingsWidget.hpp"
#include "./MoveSettingsMessage.pb.h"
#include "./ui_MoveSettingsWidget.h"

void MoveSettingsWidget::SendSettings() {
    using namespace lib::network;

    std::string message = Serialize();

    Response response = resources_.Network.SendWriteRequest(0, message);

    StatusCodeCheck<Request::TypeEnum::W>(response.Header.Code);

    QMessageBox::about(nullptr, "Успех", "Настройки успешно отправлены");
}

void MoveSettingsWidget::ReceiveSettings() {
    using namespace lib::network;

    Response response = resources_.Network.SendReadRequest(0);

    StatusCodeCheck<Request::TypeEnum::R>(response.Header.Code, [&](){ Deserialize(response.Data);});
}

void MoveSettingsWidget::Deserialize(const std::string &data) noexcept {

    MoveSettingsMessage message;
    message.ParseFromArray(data.data(), data.size());

    /// Writing number of motor coefficients
    auto& thrusterCoefficient = message.thrusters_coefficient();
    ui->MotorsNumberSpinBox->setValue(thrusterCoefficient.size()/6);

    /// Writing motor coefficients
    for (int i = 0; i < thrusterCoefficient.size()/6; i++) {
        for (int j = 0; j < 6; j++) {
            QString itemText = QString::number(thrusterCoefficient[i * 6 + j]);
            ui->MotorsTable->setItem(i, j, new QTableWidgetItem(itemText));
        }
    }

    /// Writing the number of degrees of freedom of the hand
    auto& handCoefficient = message.hand_coefficient();
    ui->HandFreedomSpinBox->setValue(handCoefficient.size());

    /// Writing hand coefficients
    for (int j = 0; j < handCoefficient.size(); j++) {
        QString itemText = QString::number(handCoefficient[j]);
        ui->HandTable->setItem(0, j, new QTableWidgetItem(itemText));
    }

    /// Writing max motor speed
    ui->MaxSpeedEdit->setText(QString::number(message.maximum_motor_speed()));

    /// Writing motors protocol
    switch (message.motors_protocol()) {
        case MoveSettingsMessage::DSHOT150:
            ui->MotorsProtocolComboBox->setCurrentIndex(0);
            break;
        case MoveSettingsMessage::DSHOT300:
            ui->MotorsProtocolComboBox->setCurrentIndex(1);
            break;
        case MoveSettingsMessage::DSHOT600:
            ui->MotorsProtocolComboBox->setCurrentIndex(2);
            break;
        case MoveSettingsMessage::DSHOT1200:
            ui->MotorsProtocolComboBox->setCurrentIndex(3);
            break;
    }

    /// Writing PID coefficients
    for(auto i : std::ranges::iota_view(0,4)) {
        QString itemTextP = QString::number(message.pid()[i].p());
        QString itemTextI = QString::number(message.pid()[i].i());
        QString itemTextD = QString::number(message.pid()[i].d());
        ui->PIDTable->setItem(i, 0, new QTableWidgetItem(itemTextP));
        ui->PIDTable->setItem(i, 1, new QTableWidgetItem(itemTextI));
        ui->PIDTable->setItem(i, 2, new QTableWidgetItem(itemTextD));
    }

    /// Writing PID state
    stabilizationXCheckBox->setChecked(message.pid_enabled().x());
    stabilizationYCheckBox->setChecked(message.pid_enabled().y());
    stabilizationZCheckBox->setChecked(message.pid_enabled().z());
    stabilizationHCheckBox->setChecked(message.pid_enabled().h());
}

std::string MoveSettingsWidget::Serialize() const noexcept {

    MoveSettingsMessage message;

    /// Reading max motor speed
    message.set_maximum_motor_speed((int16_t) ui->MaxSpeedEdit->text().toInt());

    for (int i = 0; i < ui->MotorsTable->rowCount(); i++) {
        for (int j = 0; j < ui->MotorsTable->columnCount(); j++) {
            bool isConverted;
            float value = ui->MotorsTable->item(i, j)->text().toFloat(&isConverted);

            if (!isConverted)
                throw lib::exceptions::InvalidOperationException(
                        "Матрица коэффициентов двигателей\n содержит некорректный символ");

            message.add_thrusters_coefficient(value);
        }
    }

    for (int j = 0; j < ui->HandTable->columnCount(); j++) {
        bool isConverted;

        float value = ui->HandTable->item(0, j)->text().toFloat(&isConverted);

        if (!isConverted )
            throw lib::exceptions::InvalidOperationException(
                    "Матрица коэффициентов манипулятора\n содержит некорректный символ");

        message.add_hand_coefficient(value);
    }

    /// Reading motors protocol
    switch (ui->MotorsProtocolComboBox->currentIndex()) {
        case 0:
            message.set_motors_protocol(MoveSettingsMessage::DSHOT150);
            break;
        case 1:
            message.set_motors_protocol(MoveSettingsMessage::DSHOT300);
            break;
        case 2:
            message.set_motors_protocol(MoveSettingsMessage::DSHOT600);
            break;
        case 3:
            message.set_motors_protocol(MoveSettingsMessage::DSHOT1200);
            break;
    }

    /// Adding PID controllers
    auto X = message.mutable_pid()->Add();
    X->set_p(ui->PIDTable->item(0,0)->text().toFloat());
    X->set_i(ui->PIDTable->item(0,1)->text().toFloat());
    X->set_d(ui->PIDTable->item(0,2)->text().toFloat());

    auto Y = message.mutable_pid()->Add();
    Y->set_p(ui->PIDTable->item(1,0)->text().toFloat());
    Y->set_i(ui->PIDTable->item(1,1)->text().toFloat());
    Y->set_d(ui->PIDTable->item(1,2)->text().toFloat());

    auto Z = message.mutable_pid()->Add();
    Z->set_p(ui->PIDTable->item(2,0)->text().toFloat());
    Z->set_i(ui->PIDTable->item(2,1)->text().toFloat());
    Z->set_d(ui->PIDTable->item(2,2)->text().toFloat());

    auto Depth = message.mutable_pid()->Add();
    Depth->set_p(ui->PIDTable->item(3,0)->text().toFloat());
    Depth->set_i(ui->PIDTable->item(3,1)->text().toFloat());
    Depth->set_d(ui->PIDTable->item(3,2)->text().toFloat());

    auto PIDEnabled = message.mutable_pid_enabled();
    PIDEnabled->set_x(stabilizationXCheckBox->isChecked());
    PIDEnabled->set_y(stabilizationYCheckBox->isChecked());
    PIDEnabled->set_z(stabilizationZCheckBox->isChecked());
    PIDEnabled->set_h(stabilizationHCheckBox->isChecked());

    return message.SerializeAsString();
}

void MoveSettingsWidget::StartWidget() {
    ///ToDo: почему то если запускать .exe файл, то из-за этого всё ломается, я хз
//    ReceiveSettings();
}

void MoveSettingsWidget::StopWidget() {

}

