#include "Screenshotter.hpp"
#include <QString>
#include <ctime>
#include <string>
#include <string_view>

constexpr std::string_view ImageNameTemplate = R"(Media\Image\YYYY-MM-DD:HH-MM-SS.png)";
constexpr std::string_view ImageNameMask = R"(Media\Image\%Y-%m-%d-%H-%M-%S.png)";

QString CreateFileName() {
    std::string filename;
    filename.reserve(ImageNameTemplate.size() * 2);
    filename.append(ImageNameTemplate);

    time_t now = time(nullptr);

    struct tm *timeStruct = localtime(&now);

    strftime(filename.data(),
             filename.size(),
             ImageNameMask.begin(),
             timeStruct);

    return {filename.c_str()};
}

ScreenShotter::ScreenShotter(): queue_(), thread_(&ScreenShotter::TakeScreenshot, this) {}
ScreenShotter::~ScreenShotter() { queue_.AddFrame(QImage()); thread_.join();}

void ScreenShotter::TakeScreenshot(){
    for(;;){

        auto screenshot = queue_.GetFrame();

        if(screenshot.isNull())
            return;

        screenshot.save(CreateFileName());
    }
}