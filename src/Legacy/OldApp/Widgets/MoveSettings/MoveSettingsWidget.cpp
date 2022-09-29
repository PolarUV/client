#include "MoveSettingsWidget.hpp"
#include "ui_MoveSettingsWidget.h"

MoveSettingsWidget::MoveSettingsWidget(QWidget *parent, WidgetResources& resources) :
        QWidget(parent),
        resources_(resources),
        ui(new Ui::MoveSettingsWidget) {

    ui->setupUi(this);

    /// Connecting buttons
    this->connect(ui->ReceiveSettingsButton, SIGNAL(clicked(bool)), SLOT(ReceiveSettings()));
    this->connect(ui->SendSettingsButton, SIGNAL(clicked(bool)), SLOT(SendSettings()));

    /// Connecting other
    this->connect(ui->MotorsNumberSpinBox, SIGNAL(valueChanged(int)), SLOT(UpdateMotorsTable(int)));
    this->connect(ui->HandFreedomSpinBox, SIGNAL(valueChanged(int)), SLOT(UpdateHandTable(int)));
    this->connect(ui->MaxSpeedSlider, SIGNAL(valueChanged(int)), SLOT(UpdateMaxSpeedEdit(int)));
    this->connect(ui->MaxSpeedEdit, SIGNAL(textChanged(QString)), SLOT(UpdateMaxSpeedSlider(QString)));

    /// Changing default header labels for MotorsTable
    QStringList motorsLabelsList = {"Fx", "Fy", "Fz", "Mx", "My", "Mz"};
    ui->MotorsTable->setHorizontalHeaderLabels(motorsLabelsList);

    /// Changing default header labels for PIDsTable
    QStringList pidsHLabelsList = {"П", "И", "Д", "Вкл"};
    QStringList pidsVLabelsList = {"X", "Y", "Z", "H"};
    ui->PIDTable->setHorizontalHeaderLabels(pidsHLabelsList);
    ui->PIDTable->setVerticalHeaderLabels(pidsVLabelsList);

    stabilizationXCheckBox = new QCheckBox();
    stabilizationYCheckBox = new QCheckBox();
    stabilizationZCheckBox = new QCheckBox();
    stabilizationHCheckBox = new QCheckBox();

    ui->PIDTable->setCellWidget(0, ui->PIDTable->columnCount()-1, stabilizationXCheckBox);
    ui->PIDTable->setCellWidget(1, ui->PIDTable->columnCount()-1, stabilizationYCheckBox);
    ui->PIDTable->setCellWidget(2, ui->PIDTable->columnCount()-1, stabilizationZCheckBox);
    ui->PIDTable->setCellWidget(3, ui->PIDTable->columnCount()-1, stabilizationHCheckBox);
}

MoveSettingsWidget::~MoveSettingsWidget() {
    delete ui;
}

void MoveSettingsWidget::UpdateMotorsTable(int value) {
    /// Changing the height of the table
    ui->MotorsTable->setMinimumHeight((value + 1) * 25 + 2);
    ui->MotorsTable->setMaximumHeight((value + 1) * 25 + 2);

    /// Setting the number of rows in the table
    ui->MotorsTable->setRowCount(value);

    /// Filling the empty cells with zeros
    for (int i = 0; i < ui->MotorsTable->rowCount(); i++) {
        for (int j = 0; j < ui->MotorsTable->columnCount(); j++) {
            if (ui->MotorsTable->item(i, j) == nullptr) {
                ui->MotorsTable->setItem(i, j, new QTableWidgetItem("0.0"));
                ui->MotorsTable->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}

void MoveSettingsWidget::UpdateHandTable(int value) {
    /// Changing the width of the table
    ui->HandTable->setMinimumWidth(value * 50 + 1);
    ui->HandTable->setMaximumWidth(value * 50 + 1);

    /// Setting the number of columns in the table
    ui->HandTable->setColumnCount(value);

    /// Filling the empty cells with zeros
    for (int j = 0; j < ui->HandTable->columnCount(); j++) {
        if (ui->HandTable->item(0, j) == nullptr) {
            ui->HandTable->setItem(0, j, new QTableWidgetItem("0.0"));
            ui->HandTable->item(0,j)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void MoveSettingsWidget::UpdateMaxSpeedEdit(int value) {
    ui->MaxSpeedEdit->setText(QString::number(value));
}

void MoveSettingsWidget::UpdateMaxSpeedSlider(const QString &string) {
    ui->MaxSpeedSlider->setValue(string.toInt());
}