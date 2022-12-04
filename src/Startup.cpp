#include "Exceptions/ExitException.hpp"
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
        app.AddWindow<NetworkWindow>();
        app.Run();
    } catch (const ExitException& e) {
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        PolarError << "Some error occurred: " << e.what();
    } catch (...) {
        std::terminate();
    }
    return EXIT_FAILURE;
}
