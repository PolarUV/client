#ifndef CLIENT_PYTHONENVIRONMENTWIDGET_HPP
#define CLIENT_PYTHONENVIRONMENTWIDGET_HPP

#pragma push_macro("slots")
#undef slots
#include <Python.h>
#pragma pop_macro("slots")

#include <QWidget>
#include "../WidgetResources.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class PythonEnvironmentWidget; }
QT_END_NAMESPACE

class PythonEnvironmentWidget : public QWidget {
Q_OBJECT

public:
    PythonEnvironmentWidget(QWidget *parent, WidgetResources& resources);

    ~PythonEnvironmentWidget() override;

public slots:
    void StartWidget();
    void StopWidget();

private:
    Ui::PythonEnvironmentWidget *ui;
    WidgetResources& resources_;

private slots:
    void ReleaseCode();
    void DebugCode();
};


#endif //CLIENT_PYTHONENVIRONMENTWIDGET_HPP
