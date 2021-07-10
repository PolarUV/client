#ifndef CLIENT_MOVESETTINGSWIDGET_HPP
#define CLIENT_MOVESETTINGSWIDGET_HPP

//this must be first include
#include "../WidgetResources.hpp"

#include <QWidget>
#include <QCheckBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MoveSettingsWidget; }
QT_END_NAMESPACE

class MoveSettingsWidget : public QWidget {
Q_OBJECT

public:
    MoveSettingsWidget(QWidget *parent, WidgetResources &resources);

    ~MoveSettingsWidget() override;

private:

    [[nodiscard]] std::string Serialize() const noexcept;

    void Deserialize(const std::string &data) noexcept;

public slots:

    void StartWidget();

    void StopWidget();

private slots:

    void SendSettings();

    void ReceiveSettings();

    void UpdateMotorsTable(int value);

    void UpdateHandTable(int value);

    void UpdateMaxSpeedEdit(int value);

    void UpdateMaxSpeedSlider(const QString &string);

private:

    WidgetResources &resources_;
    Ui::MoveSettingsWidget *ui;

    QCheckBox *stabilizationXCheckBox;
    QCheckBox *stabilizationYCheckBox;
    QCheckBox *stabilizationZCheckBox;
    QCheckBox *stabilizationHCheckBox;
};

#endif