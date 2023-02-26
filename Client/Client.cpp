#include "Client.h"

#include <iostream>

std::mutex Client::io_access;

void Client::Connect() {
    socket->connect(*ep);
    areConnected = true;
}

void Client::Start() {
    read_thread = std::thread([this](){ this->Read(); });

    while (true)
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
}

void Client::Read() {
    while (areConnected) {
        socket->read_some(buffer(intList));
        if (!intList.empty()) {
            std::lock_guard<std::mutex> lock(io_access);
            for (auto i : intList)
                std::cout << i << " ";
            std::cout << std::endl;
            intList.clear();
        }
    }
}

Client::Client(const std::string &ip, size_t port) : areConnected(false) {
    ep = std::make_unique<ip::tcp::endpoint>(ip::address::from_string(ip), port);
    socket = std::make_unique<ip::tcp::socket>(service);
}
