#include "./CommandsProtocol/CommandsProtocol.hpp"

#include <iostream>

CommandsProtocol::CommandsProtocol(size_t gamepadId)
        : _gamepad(gamepadId) {
    this->_isOnline = false;
    this->_isThreadActive = false;
    this->_errorStatus = CommandsProtocol::ErrorType::Ok;
}

CommandsProtocol::~CommandsProtocol() {
    this->_socket.Disconnect();
    this->SetOnlineStatus(false);
    ///ToDo: motov.s - когда-нибудь придумай что-нибудь получше этого безобразия
    while (this->IsThreadActive())
        std::this_thread::sleep_for(std::chrono::microseconds(1));
}

void CommandsProtocol::SetGamepadId(size_t id) {
    this->_gamepad.UpdateGamepadId(id);
}

size_t CommandsProtocol::GetGamepadId() const {
    this->_gamepad.GetGamepadId();
}

bool CommandsProtocol::GetError() const {

    this->_errorStatusMutex.lock_shared();
    bool errorStatus = this->_errorStatus;
    this->_errorStatusMutex.unlock_shared();

    return errorStatus;
}

void CommandsProtocol::Start(const QString &address, uint16_t port) {

    bool isConnected = this->_socket.ConnectToServer(address, port);

    if (!isConnected) {
        this->SetErrorStatus(BaseProtocol::ErrorType::CantConnectToServer);
        return;
    }

    std::chrono::high_resolution_clock timer;

    this->SetOnlineStatus(true);

    for (size_t i = 0; _socket.IsOnline(); i++) {
        auto currentTime = timer.now();

        std::shared_ptr<CommandsStruct> commands = this->_gamepad.GetCommandsStruct();
        _socket.Send((char *) (commands.get()), CommandsStructLen);

        TelemetryStruct telemetry{};
        _socket.Recv((char *) &telemetry, TelemetryStructLen);

        this->SetTelemetryStruct(telemetry);

        std::cout << telemetry << std::endl;

        ///ToDo: найти способ получше держать период 2мс
        while (std::chrono::duration<double, std::micro>(timer.now() - currentTime).count() < 2000) {}

        //std::this_thread::sleep_for(std::chrono::microseconds(2000 - (size_t) deltaTime));
        //std::cout << i << ' ' <<std::chrono::duration<double, std::micro>(timer.now() - currentTime).count()<<std::endl;

    }

    this->SetOnlineStatus(false);
    this->SetThreadStatus(false);
}

void CommandsProtocol::Stop() {
    this->_socket.Disconnect();
    this->SetErrorStatus(CommandsProtocol::ErrorType::ConnectionLost);
    this->SetOnlineStatus(false);
}

void CommandsProtocol::StartAsync(const QString &address, uint16_t port) {
    if (this->IsStreamOnline())
        return;

    this->_transferThread = std::thread(&CommandsProtocol::Start, this, address, port);
    this->_transferThread.detach();

    this->SetThreadStatus(true);
}

TelemetryStruct CommandsProtocol::GetTelemetryStruct() {
    this->_telemetryMutex.lock_shared();
    TelemetryStruct telemetry = this->_telemetry;
    this->_telemetryMutex.unlock_shared();
    return telemetry;
}


