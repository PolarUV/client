#include "Lib.hpp"
#include "Logger/Logger.hpp"

#include "App/App.hpp"

#include <cstdlib>
#include <iostream>

int main() {
    Lib();

    try {
        auto app = App();
        app.AddWindow<SettingsWindow>();
        app.AddWindow<ConsoleWindow>();
        app.Run();
    } catch (const std::exception &e) {
        PolarError << "Some error occurred: " << e.what();
        return EXIT_FAILURE;
    } catch (...) {
        std::terminate();
    }
    return EXIT_SUCCESS;
}
