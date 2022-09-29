#include "DisplayWidget.hpp"
#include "ui_DisplayWidget.h"
#include <array>
#include <QGraphicsDropShadowEffect>


DisplayWidget::DisplayWidget(QMainWindow *mainWindow, WidgetResources &resources) :
        QOpenGLWidget(mainWindow),
        ui(new Ui::DisplayWidget),
        resources_(resources),
        stream_(),
        painter_(),
        screenshotFlag_(false){

    ui->setupUi(this);

    placeholderImage_ = QImage("Icons/Background.png");
    updateTimer_ = std::make_unique<QTimer>();
    updateTimer_->start(1000 / 30);
    connect(updateTimer_.get(), SIGNAL(timeout()), this, SLOT(update()));

    connect(ui->SideBarButton, SIGNAL(clicked(bool)), this, SLOT(HideSideBarButton()));
    connect(ui->SideBarButton, SIGNAL(clicked(bool)), mainWindow, SLOT(ShowSideBar()));

    connect(ui->CameraButton, SIGNAL(clicked(bool)), this, SLOT(SwitchVideoStream()));
    connect(ui->RecordingButton, SIGNAL(clicked(bool)), this, SLOT(SwitchVideoCapture()));
    connect(ui->ScreenshotButton, SIGNAL(clicked(bool)), this, SLOT(SetScreenshotFlag()));

    ui->SideBarButton->hide();
    ui->ScreenshotLabel->hide();
    ui->RecordingLabel->hide();
    ui->RecordingButton->hide();

    std::array elements = {
            ui->SideBarButton, ui->ScreenshotButton, ui->CameraButton, ui->RecordingButton,
    };

    for (auto &element : elements) {
        auto *shadowEffect = new QGraphicsDropShadowEffect(this);
        shadowEffect->setOffset(0, 0);
        shadowEffect->setBlurRadius(5.0);
        shadowEffect->setColor(Qt::black);
        element->setGraphicsEffect(shadowEffect);
    }
}

DisplayWidget::~DisplayWidget() {
    delete ui;
}

void DisplayWidget::ShowSideBarButton() {
    ui->SideBarButton->show();
}

void DisplayWidget::HideSideBarButton() {
    ui->SideBarButton->hide();
}

void DisplayWidget::StopWidget() {

}

void DisplayWidget::StartWidget() {

}







