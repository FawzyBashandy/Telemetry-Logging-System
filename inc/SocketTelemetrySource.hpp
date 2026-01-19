#pragma once
#include "ITelemetrySource.hpp"
#include "SafeSocket.hpp"
#include <string>

class SocketTelemetrySourceImpl : public ITelemetrySource {
public:
    explicit SocketTelemetrySourceImpl(std::string socketPath)
        : socketPath_(std::move(socketPath)) {}

    bool openSource() override {
        if (socket_.isOpen()) return true;
        return socket_.connect(socketPath_);
    }

    bool readSource(std::string& out) override {
        out.clear();
        char ch;

        while (true) {
            ssize_t n = socket_.read(&ch, 1);
            if (n <= 0) return false;
            if (ch == '\n') break;
            out.push_back(ch);
        }
        return true;
    }

private:
    std::string socketPath_;
    SafeSocket socket_;
};
