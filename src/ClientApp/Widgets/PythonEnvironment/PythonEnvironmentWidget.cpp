#include "PythonEnvironmentWidget.hpp"
#include "ui_PythonEnvironmentWidget.h"


PythonEnvironmentWidget::PythonEnvironmentWidget(QWidget *parent, WidgetResources& resources) :
        QWidget(parent),
        ui(new Ui::PythonEnvironmentWidget),
        resources_(resources){
    ui->setupUi(this);

    connect(ui->DebugCodeButton, SIGNAL(clicked(bool)),this, SLOT(DebugCode()));
    connect(ui->ReleaseCodeButton, SIGNAL(clicked(bool)),this, SLOT(ReleaseCode()));

    ui->ReleaseCodeButton->setIcon(QIcon("Icons/PlayIcon.png"));
    ui->DebugCodeButton->setIcon(QIcon("Icons/BugIcon.png"));
}


PythonEnvironmentWidget::~PythonEnvironmentWidget() {
    delete ui;
}


void PythonEnvironmentWidget::ReleaseCode() {
    Py_Initialize();

    ui->ProgressBar->setValue(25);

    PyObject *pyModule = PyImport_AddModule("__main__");

    std::string stdOutErr =
            "import sys\n"
            "class CatchOutErr:\n"
            "\tdef __init__(self):\n"
            "\t\tself.value = ''\n"
            "\tdef write(self, txt):\n"
            "\t\tself.value += txt\n"
            "catchOutErr = CatchOutErr()\n"
            "sys.stdout = catchOutErr\n"
            "sys.stderr = catchOutErr\n";

    PyRun_SimpleString(stdOutErr.c_str());

    const char *str = qPrintable(ui->CodeEdit->toPlainText());
    PyRun_SimpleString(str);

    ui->ProgressBar->setValue(50);

    PyObject *pyCatcher = PyObject_GetAttrString(pyModule, "catchOutErr");

    PyErr_Print();

    PyObject *pyOutput = PyObject_GetAttrString(pyCatcher, "value");

    ui->ProgressBar->setValue(75);

    PyObject *temp_bytes = PyUnicode_AsEncodedString(pyOutput, "UTF-8", "strict");
    std::string output = PyBytes_AS_STRING(temp_bytes);
    if (!output.empty()) {
        ui->OutputEdit->setText(output.c_str());
    }

    ui->ProgressBar->setValue(100);

    Py_Finalize();

    ui->ProgressBar->setValue(0);
}


void PythonEnvironmentWidget::DebugCode() {
    Py_Initialize();

    ui->ProgressBar->setValue(25);

    const char *str = qPrintable(ui->CodeEdit->toPlainText());
    PyRun_SimpleString(str);

    ui->ProgressBar->setValue(100);

    Py_Finalize();

    ui->ProgressBar->setValue(0);
}

void PythonEnvironmentWidget::StopWidget() {

}

void PythonEnvironmentWidget::StartWidget() {

}